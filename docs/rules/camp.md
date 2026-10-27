# Camp: sleep, learn, hunt, watch, repair

Source: `P93.MCO` (`ovl_0271` camp loop; helpers `ovl_07e5` HP, `ovl_0813` energy, `ovl_0849/0886` repair, `ovl_1099` campsite, `ovl_1137` shelter). Menu = EXE menu 13 (command words Use, Recall, Sleep, Magic, Learn, Off, Fix, Watch, Hunt, Put, Assign, End); where camping is impossible menu 22 (Use, Recall, Put, Off, End).

## Where you can camp (`ovl_1099` → `_CAMPSITE` bits)
| `_curmpg` | site | bit |
|---|---|---|
| 1 wilderness | open camp (sailing: 4) | 2 |
| 7 dungeon | dungeon camp | 8 |
| 5 town, rooms 0x40–0x47 | rented inn room (`_RENTPTR` = nights left; camp ends when it hits 0) | 0x20 |
| 5 town, rooms 0x5C–0x6B, or `_locspec 0x14` room 9 | guest room | 0x10 |
| anything else | no camping: menu 22 | 1 |

Only an open camp (bit 2) rolls wilderness encounters while camping (P01 cross-overlay calls 6 and 9 every tick); if a fight starts it is an **ambush** unless some member is on *Watch* (`P01 ovl_0790`: `_ambflg = 1` when no `h_actvty == 9`). Watch is only offered when bits 1|2 are set.

## The loop
Every 5-minute `CalUpd` tick, for each party member (`h_actvty`):
- **0 / sleeping** (`Sleep` sets everyone to 0 after "Is everyone going to sleep?"): `hp += 1` up to a cap and `energy += 1` up to a cap (`_IsHeTr` re-evaluates tired/exhausted). Caps: indoors or with a **Blanket** (0x52) in the sleeper's pack: `hpmax` and 99. Open camp without a blanket: `min(hpmax, hpmax/2 + shelter)` and `min(99, 50 + shelter)`, where `shelter = HighStat(carpentry)/2` — the party's best carpenter halves the penalty (`ovl_1137`). Poisoned or Ill (`cond1 & 0x0A`) halves the caps.
- **1 learn** (`Learn`): pick a spell book (0x53–0x59) from the pack, then a spell in it (`ovl_0a15`: book → 6 spells, `h_spells[(book−0x53)·6 + i]`). `h_lrncnt = _LrnTim(spell, hero) = max(2, _speltim[spell] − h_intellg)`; each tick with `cond1 == 0` decrements it, at 0 the spell gets +1 charge (cap 99) and the timer restarts. `_speltim` (DS:2B8F, 32 spells): `10,16,12,6,10,5,8,12,6,12,5,16,8,5,12,6,8,35,20,20,12,20,16,50,10,25,15,25,20,10,30,35`. Needs `h_magic > 0` and the hero must not be busy (`h_actvty`). The charm/intelligence check is per spell, so a hero with intellg ≥ speltim learns one charge every 10 minutes.
- **3 hunt** (`Hunt`): on the hour and half hour, `RndCo(100)`; success if `terrain[curter] + weather[weather] + h_hunt/2 ≥ roll` → `+1 Food`, then a hunt skill-up roll (`_SkillUp0`, skill index 0x11 = h_hunt). Tables (P93 @0x003 / @0x00D, −1 = hunting impossible): terrain `[–, –, +18, +5, 0, +25, −25, −35, −15, +10]`; weather `Clear +10, Overcast 0, Fog −40, Rain −30, Thunderstorm −60, Snow −20, Blizzard –, Freezing 0, Gale –, Sweltering +10, Sandstorm –, Hurricane –`. Not while seasick.
- **6 fix** (`Fix`): each tick `RndCo(100) ≤ h_smith` repairs one point: scan party members round-robin for an inventory amount byte `> 0x80` (**damaged flag** in `h_invamt`: high bit + damage count) and decrement it.
- **9 watch** (`Watch`): no effect except preventing the ambush above.
- Any condition (`cond1 ≠ 0`) or seasickness stops learn/hunt/fix with "%o can't continue the current activity" (`ovl_1061`, actvty = 0xFF).
Camping ends on a key/mouse press, when the rented room expires, or when combat starts; all activities reset to 0xFF.

## Other camp commands
- `Magic`: cast a spell from camp (`_Magic`, the usual gate in `spells.md`).
- `Put`/`Off`: wear/remove armour and clothing (0x1F–0x30) — the only place equipment is changed. Six `h_wears` slots; each item has a **garment class** (`ovl_0d25`): 1 = body armour 0x1F–0x27, 2 = helmet 0x28–0x2A, 4 = clothing 0x2B–0x30. Putting on an item whose class is already worn replaces that item (text 0x11); otherwise it takes the first free slot (text 0x0E). No race or class restriction is checked.
- `Use`: `_UseItem` → FFFAR `ovl_173e`: Rope, Orb, Horn, Conch, the four Scrolls, Pick, Arrow and Flute only **show the item's picture** here (window set-up + `_StartGraf`); scripted effects live in location programs.
- `Assign`: give a companion a job/task (assignment records, `npcs.md`).
