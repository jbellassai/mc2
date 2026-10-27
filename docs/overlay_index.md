# Overlay index

Readable decompiles: `decomp/overlays/Pnn.c` (regenerate: `tools/ovl_batch.sh` then `tools/ovl_pp.py`). Roles inferred from embedded text and the EXE calls each overlay makes; `__curmpg` (current location program) takes the values 1,2,4,5,7 in engine checks. Entry *n* = n-th `JMP` in the leading table, reached via `_LocPgm(n)` / `_RoomPgm(n)`.

| overlay | entries | role (evidence) |
|---|---|---|
| P01 | 1 | wilderness / world-map location program (calendar updates `CalUpd1`, `FindBit` event flags, loads room overlays; ships and captains `rules/ships.md`, swimming `rules/skills.md`) |
| P02 | 5 | town program ("The door is locked", "Whom do you seek?", shop/door handling) |
| P04 | 2 | **mushroom patches** on the world map (`_mushsta` nibbles, regrowth every 8 days) — `docs/rules/locations.md`, *Mushroom patches* |
| P05 | 2 | **service rooms**: inns, schools, jobs, libraries, wizards' lodges, taverns/stores, region camps — room id selects the tables (`docs/rules/services.md`) |
| P06 | 26 | **dungeon level program** (PGM `pgmnum` 6, data `D06`): the 26 entry points are the EXE's room-program vector names (`_Attack`, `_MDamage`, `_MAttend`, `_AniMonster`, `_GetRec1/2`…) — monsters on the dungeon map attack/are attacked in place (`combat.md` attack resolution `ovl_050a`); its rooms load P07 at +0x2000 |
| P07 | 1 | dungeon **room** program: prison cells, chests, fountains, Dark Candle rooms, Vankruh's chamber (`rules/locations.md`) |
| P08 | 2 | **quest scenes**: King's court gifts, Maalaq's crystal key, Altesen Orb, Marked Ones / Blue Scroll, ghost, White Scroll disaster trigger, Oolau nest ending — `docs/rules/quest_scenes.md` |
| P09 | 1 | **special rooms**: casinos (2d6), teleportals (3-piece combinations), temples (gods, demands, blessings), dungeon gates (passwords), meeting halls — `docs/rules/special_rooms.md` |
| P70 | 1 | notepad (`NOTES000.MCN`) |
| P81 | 4 | startup: title, intro story, hero profile selection and new-game init (`rules/new_game.md`); loaded as overlay 0x51 (16 KB) at `_Hello` |
| P88 | 2 | **Assign** (0: send a companion travelling/waiting or commit a room task + destination) and **Recall** (1: Mindstone assignment report, redirect) — `docs/rules/assignments.md` |
| P89 | 0 | **Teleport picker** (loaded by P01 Teleport): skill-tiered target rectangle, moves the party (`docs/rules/spells.md`) |
| P90 | 3 | **trade and gifts**: 0 Buy, 1 Sell, 2 Give — haggling vs. `h_trade`, lots, gift lists (`docs/rules/economy.md`) |
| P91 | 6 | town NPC small talk ("nice weather", The King) |
| P92 | 2 | **hour tick**: clock/day/season, sunrise/sunset, weather per region, hunger, assignment updates, paydays (`docs/rules/time_weather.md`, `npcs.md`) |
| P93 | 1 | **camp**: sleep/learn/hunt/fix/watch loop, campsite rules (`docs/rules/camp.md`) |
| P94 | 29 | combat spell program (location half, 0x5E): the `SPLVECS` offset-0 slots (`_Fear` 4 … `_Drain` 27) are stubs that `INT 61h` into V06; also the spell-AI target picker (`ovl_15f8`) and combat mouse UI |
| P95 | 1 | resurrection & post-combat ("Mark the target", `SumStat`, loot → `h_partybucks`, volunteer attitude/departure `ovl_0fc0`); overlay 0x5F |
| P96 | 1 | combat main loop (entry 0 = the fight) (`RndCo` random, `PlacePerson`, `Locate`); overlay 0x60 |
| P97 | 3 | party management: hire / dismiss companions |
| P98 | 1 | Quit / Save / Restart menu |

| V06 | INT 61h, 59 fns | combat effects + monster AI: spell handlers (`docs/rules/spells.md`), target choice ("Closest / Low hp / Magic-user / Leader …"), truce/bribe, rally |

Numbers 0x51/0x5E/0x5F/0x60 = decimal 81/94/95/96 match the file names. `FFFAR.MCO` (not in this table) is the always-resident far routine set: 75 strings incl. "Companion", "Hireling", "Learning %a".

## Open items
- `INT 60h`/`61h` = the location/room V-files (`V02`, `V05`, `V06`), see `docs/overlays.md`. `V02`/`V05` handlers not yet mapped.
- `_crossovlycall` (`EXE_crossovlycall(...)`) calls between the location and room halves.
- Which `Pnn` each location uses is decided by overlay code / `PGM` records, not yet traced.
