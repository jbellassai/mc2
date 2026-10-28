# NPCs, companions, assignments

Sources: EXE `_InitNPC`, `_TimCalc`, `_CapAtLiberty`, `_AssignedHere`, `_FindAss`, `_ChkDepartures`, `_GreetKNPC` (`out/decomp/MC2_all.c`); `P97.MCO` (hire/dismiss), `P92.MCO` (daily assignment update); location sub-tables (`tools/locdump.py original out/locs`).

## Who stands where (`_InitNPC`, on entering a map)

`_npclocs` (5-byte `{x,y,type,tile,num}`, up to 50) is rebuilt from three sources, each entry adjusted by `_AdjNPCXY`:

1. **GEN** records (`loc.genptr`, `{x,y,type,tile,num}`, FF-terminated): generic townsfolk. `num ≥ 0xFC` always; `0xFA` only when `_daynite=='L'`; `0xFB` only when `'D'`.
2. **KNPC** records (`loc.knpcptr`, 10 bytes `{x,y,type,tile,num,name,appear,disapp,ifevent,ifnevent}`, FF-terminated): named NPCs. Shown when all hold: NPC bit `num` **not** set in `_npcsta` (set = in the party / removed); `_CapAtLiberty` (type 0x1D = ship captain ashore: shown only if `_capsta[i]==3`, `ships.md`); `_TimCalc(appear, disapp)` (hour in `[appear, disapp)` with wrap-around; `appear==disapp` = always); `ifevent` 0 or event bit set; `ifnevent` 0 or event bit clear. `num ≥ 0x20` also sets a "present" bit in `_npcshere`. `name` indexes the location's keyword list `gwrds` (NUL-separated strings; also the words you can ask about).
3. **Assignments** (`_assgn0`, 31 × 25-byte `ASSIGNMENT`): any record with `as_loc == _locspec`, `as_room == _currm`, `as_task != 8` and matching hire-room (`as_hroom`) is placed at `(as_x, as_y)` with `as_race/as_tile`, number `as_npc`.

Rooms: `loc.resids` is indexed by **room id** (`RESID{name,num,appear,disapp,ifevent,ifnevent}`, used by `P02` as `resids[_rmdata*6]`): the resident who runs that room (shopkeeper, innkeeper …), with the same hour/event rules. `peopr` = `{word, npc, x}` triples: which NPC a "People" keyword refers to. `newsr` = `{a,b,c}` triples for the News keyword (TODO).

## Companions

- The hero array `_member0` holds **37** `HERO` records (220 B): slot 0 = player (Lukas Al Dem), slots 1–5 unused, slots **6–36 = companions 1–31** (`h_orinum` 1–31). NPC number `num < 0x20` in KNPC/RESID is a companion: hero = `_member0[num+5]` (`_GreetKNPC`: `npcno*0xDC + _member5`). Save `FFSAVA.MCS`: 1 Sakar (Dwarf), 2 Rimfiztrik (Wizard), 3 Nehor (Elf), 4 Tuff (Halfling), 5 Ben Trimmon, 6 Q. Crystyn, 7 Ralle d'Bois, 8 Durin, 9 Eflun, 10 Eldai, 11 Gilondo, 12 Cmdr. Grolf, 13 Sir Gustron, 14 Jimbo Lim, 15 Kruga, 16 Lupi, 17 Strephonio, 18 Madir, 19 Perin, 20 Nimmo, 21 Buzbazgut (Orc), 22 Nazim, 23 Fr Orbonn, 24 Brother Polo, 25 Argas, 26 King Rebnard, 27 Lord Rexor, 28 Rogga, 29 Lady Subia, 30 Tamas, 31 Somona.
- `h_relatn`: 1 = volunteer, 2 = hired (gets `h_paydays[4]`: hire day +29 mod 30 then every 7 days; paid at 17:00/18:00 by `P92 ovl_09ff` — not a wage but a *fair share* check on loot vs. gifts, see `docs/rules/economy.md`; attitude ≤ 3 on payday → leaves), 3 = King. `P97 ovl_02d6`: relation 2 asks a yes/no (wage), relation 3 needs `_events+8 & 2`.
- `h_attitude` (`+0xD2`): per-companion mood value (Sakar 180, Strephonio 20 …). **0xFF = wants to leave**: `_ChkDepartures` sees it on the next hour and P97 `ovl_05f7` dismisses: attitude reset to 5, party slot freed, record copied back to `_member0[orinum+5]`, `h_inhand=0xFF`, and the NPC's `_npcsta` bit is **cleared**, so the companion reappears wherever the location tables place them (their KNPC/RESID entries, hours permitting). Known homes from `out/locs/npcs.txt`: 1 Sakar in Cellars 1 (captive, type 4), 4 Tuff and 14 Jimbo in Ketrop, 7 Ralle in a tavern, 9 Eflun in Drakhelm, 11 Gilondo in Llendora, 13 Gustron in Oshcrun, 17 Strephonio in Shann 6, 27 Rexor / 29 Subia in Top Level, others are placed by assignments or scripts (P0x).

## Assignments (`ASSIGNMENT`, 25 B; `_FindAss(n)` = `_assgn0[n−1]`)

`as_npc, as_loc, as_room, as_x, as_y, as_task, as_done, as_gowildx, as_misc, as_race, as_tile, as_hroom, as_region, as_wildx, as_wildy, as_goreg, as_gowildy, as_gold(u16), as_date, as_daysleft, as_hour, as_goloc, as_goroom, as_godays`. Empty = `as_npc == 0xFF`. Created by the *Assign* command (`P88`) from a pending room task (`P05` schools/jobs/libraries/lodges) or as plain travel/wait; updated daily by `P92 ovl_0561`. Full rules, task codes, captures and morale: **`assignments.md`**; the rooms that create tasks: **`services.md`**.

So a companion who is "missing" is either back home (npcsta bit cleared) or on an assignment record; both are findable from the save: `_npcsta` (DS:6E67), `_assgn0` (DS:70CB).

## Captains ashore
KNPC type 0x1D rows are ship captains, shown only while their ship is docked at home (`_capsta[i] == 3`, `_CapAtLiberty`); no shipped location has one. Ships: `ships.md`.

## Attitude (0–200) and why companions leave
- Hired (`h_relatn 2`): weekly fair-share settlement (`economy.md`, *Hirelings*): attitude scaled by what they were given vs. a quarter of the loot; ≤ 3 → `h_attitude = 0xFF`.
- Assigned companions (away from the party) run a separate daily morale check and may quit (`assignments.md`).
- Every new day (`P92 ovl_02ed`) each volunteer in party slots 1–5 with attitude < 100 gets **+1**.
- Volunteers (`h_relatn 1`): after every combat `attitude = max(0, attitude + h_loyalty − 20)` (`P95 ovl_0fc0`); at ≤ 40 they leave with probability `P(RndCo(80) ≥ attitude) · P(RndCo(12) ≥ loyalty)`.
- A companion who leaves (`h_attitude 0xFF`, P97 `ovl_05f7`) is reset to attitude **5**, so one who is recruited again starts out unhappy.
- Initial values per companion (from `FFSAVA.MCS`): e.g. Buzbazgut 200/loyalty 11, Nazim 150/11, King Rebnard 200/12, Somona 20/6, Strephonio 20/0, Argas 20/0 (hired).
