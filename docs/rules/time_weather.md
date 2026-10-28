# Time, weather, travel and upkeep

Sources: `P92.MCO` (hourly clock program, `decomp/overlays/P92.c`), `P01.MCO` (world map, `P01.c`), EXE `_CalUpd1`/`_DecEnergy`/`_DecSpells`/`_IsHeHu`/`_IsHeTr` (`out/decomp/MC2_all.c`), region records `R32`–`R47` (`docs/formats.md`).

## Clock

- `_startsvdta` (DS:4CF6, the first saved byte) is the **minute**; `_hour`, `_date` (1–30), `_month` (0–11), `_juldate` (day counter), `_daynite` (`'L'` light / `'D'` dark), `_season`, `_weather`, `_curreg` live right after it.
- `_CalUpd1()` = **5 minutes**: minute += 5; every call runs `_DecSpells` (glamour/charm counters `h_glamcnt`, detect spell timer `_detectsw`) and `_DecEnergy`; when the minute passes 59 it loads **P92** and runs it (the hour tick), then checks departures (`_ChkDepartures`: any party member with `h_attitude == 0xFF` → P97 dismissal), and reloads P93 if camping.
- **P92 hour tick** (`ovl_0102`…): minute = 0, hour++; hour == `sunrise[month]` → `_daynite='L'`, events bit0 cleared; hour == `sunset[month]` → `'D'`, bit0 set; hour > 23 → **new day** (`ovl_01cd`): `_juldate++`, `_date++`, month rolls at 30 days, year at 12 months; month 9 sets event bit (`_events+3 |= 8`); every 8th day `ovl_02cb`; `_disasterday+7` sets `_events |= 2`; `_juldate == 20` sets `_events+14 |= 4`. New month → `ovl_0265`: `_season = seasontbl[month]`, event flags from `mflags[month]`, and the regional season weather table is re-copied; casino bank refills 200/month to 1000.
- Sunrise/sunset per month (P92 file 0x0E / 0x1A): `[8,8,7,7,7,6,6,6,7,7,7,8]` / `[18,18,19,19,19,20,20,20,19,19,19,18]`. Season per month (file 0x24D): `[0,0,1,1,1,2,2,2,3,3,3,0]`. The same month change (`ovl_0265`) keeps one **season event** set and clears the other three (table file 0x259): event 12 winter (Dec–Feb), 9 spring (Mar–May), 10 summer (Jun–Aug), 11 autumn (Sep–Nov). Data uses them to move the Tundra town Shumaran (`locations.md`).
- Fixed hourly events: 07:00 `ovl_0447` (captain status 6→7, removes coins…), 08:00 `ovl_040d`, 12:00 `ovl_04b0` (8 rent counters −1), 17:00/18:00 `ovl_09ff` (hired companions, `h_relatn==2`, whose payday `h_paydays[]` is today get paid / react). Every hour: `ovl_0321` hunger, `ovl_04c7` weather, `ovl_0561` assignment updates (see `npcs.md`).

## Weather (`P92 ovl_04c7`, hourly)

- 16 **regions** (`_curreg`), each with `_curwthrs[reg] = {weather, hours_left}`. Every hour all 16 `hours_left` decrement.
- Entering a new region on the world map (`P01 ovl_14fd`) loads `R(32+reg).MCV` and copies `weathr[season] ` (4 triples) into `_ssnwthrs`. New month re-copies.
- When the current region's `hours_left` hits 0: `r = RndCo(100)`; take the first triple `(threshold, weather, dur)` with `r < threshold`; `_weather = weather`; `hours_left = hi(dur) + RndCo(lo(dur) − hi(dur) + 2)` where `hi/lo` are the nibbles of `dur` (e.g. `0x8F` → 8 + RndCo(9) hours).
- Weather codes (`_w_weather` DS:424E): 0 Clear, 1 Overcast, 2 Fog, 3 Rain, 4 Thunderstorm, 5 Snow, 6 Blizzard, 7 Freezing, 8 Gale, 9 Sweltering, 10 Sandstorm, 11 Hurricane. `_tempert` exists but nothing in the overlays writes or reads it (dead).
- Example, Oshcrun region (R32), season 0: `(30,Overcast,8–16h) (60,Snow,8–16h) (90,Rain,5–10h) (100,Blizzard,7–14h)`; all 16 tables are printed by `tools/locdump.py`-style parsing in formats.md notes.

## World-map step cost (`P01 ovl_10f7`, per step when not sailing)

```
steps_of_5min = terrain_time[curter] + 4 + weather_time[weather]
                + 1 if daynite == 'D'
                + 1 if any party member has h_cond1 != 0
energy_loss(member) = terrain_energy[curter] + max(0, clothing[item][weather] − _tailorcharm)
```
Tables (P01 file offsets): `terrain_time` @0x276 `[1,1,1,1,2,3,3,4,5,5]` (by terrain class `_curter`), `weather_time` @0x280 `[-,-,0,0,1,1,2,2,3,3,4,4]`, sailing `@0x28C [-,-,0,0,1,2,3,4,1,2,3,4]` (+4 base), `terrain_energy` @0x298 `[1,1,1,1,2,2,2,3,4,5,0,0]`. Energy is removed with `_DecSta(slot, h_energy, 1)` that many times, then `_IsHeTr`.

### Clothing (P01 file 0x2A2, 7 rows × 12 weathers; row chosen by `ovl_1a47`)
For each member the six `h_wears` slots are scanned for the first item in 0x2B–0x30; none → row "none" (0x31). Entry = energy penalty per step in that weather, minus `_tailorcharm` (floor 0).

| item | Clear | Overc | Fog | Rain | Thund | Snow | Blizz | Freez | Gale | Swelt | Sand | Hurr |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Elvenspun (0x2B) | 0 | 0 | 0 | 1 | 1 | 1 | 1 | 2 | 1 | 1 | 2 | 2 |
| Suede outfit (0x2C) | 0 | 0 | 0 | 1 | 2 | 4 | 5 | 6 | 3 | 3 | 4 | 3 |
| Cotton robe (0x2D) | 0 | 0 | 0 | 2 | 3 | 6 | 7 | 8 | 4 | 1 | 1 | 4 |
| Silk robe (0x2E) | 0 | 0 | 0 | 3 | 3 | 7 | 8 | 9 | 5 | 1 | 1 | 5 |
| Wool outfit (0x2F) | 0 | 0 | 0 | 1 | 2 | 2 | 3 | 4 | 3 | 7 | 2 | 3 |
| Furs (0x30) | 2 | 0 | 0 | 3 | 1 | 2 | 2 | 3 | 3 | 9 | 5 | 4 |
| nothing | 1 | 2 | 3 | 5 | 9 | 9 | 9 | 9 | 9 | 0 | 9 | 9 |

Elvenspun is never worse than 2 and dominates every other outfit in every weather; Cotton/Silk win only in Sweltering/Sandstorm (1) and Wool/Furs are the cold-weather choices among ordinary clothes.

## Energy, hunger, conditions (EXE)

- `_DecEnergy` runs at minute 0 and 30: each party member with `h_actvty != 0` loses energy 1 (4 if `h_cond1 & 0x0A`, i.e. Poisoned or Ill), +1 more if `h_inhand != 0xFF` (holding a weapon).
- `_IsHeTr`: energy 0 → Exhausted (`h_cond1 |= 0x10`), < 15 → Tired (`h_cond2 |= 0x20`).
- Hunger (`P92 ovl_0321`, hourly): `h_lastmeal++`; when it reaches `HUNGERHOURS[race]` (`DS:3AA8 = [24,28,25,18,30,20]` for Human, Wizard, Elf, Halfling, Dwarf, Orc) the member auto-eats Food (item 0x31, `_DoUse` → `_EatMeal`, no message) if **their own** Food slot (`_SearchInv` on that member) holds more than 5 (assigned NPCs: more than 1), else `_IsHeHu` (`P92 ovl_039d`; the threshold table is copied at P92 file 0x26 and equals DS:3AA8): Hungry (`h_cond2 |= 0x40`), and Starving (`h_cond1 |= 4`) at 4× the threshold.
- Condition bits (names `_w_conds` DS:4204, `_SumStat` shows the highest set bit of `cond1<<8 | cond2`): `cond1` 0x80 Dead, 0x40 —, 0x20 Paralyzed, 0x10 Exhausted, 0x08 Poisoned, 0x04 Starving, 0x02 Ill, 0x01 Wounded; `cond2` 0x80 Unconscious(?), 0x40 Hungry, 0x20 Tired.
- Hunting in camp (`P93`): success if `terrain_base[curter] + weather_mod[weather] + hunt_skill/2 ≥ threshold` (tables P93 file 0x103/0x10D) → Food.
