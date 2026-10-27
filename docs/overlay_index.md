# Overlay index

Readable decompiles: `decomp/overlays/Pnn.c` (regenerate: `tools/ovl_batch.sh` then `tools/ovl_pp.py`). Roles inferred from embedded text and the EXE calls each overlay makes; `__curmpg` (current location program) takes the values 1,2,4,5,7 in engine checks. Entry *n* = n-th `JMP` in the leading table, reached via `_LocPgm(n)` / `_RoomPgm(n)`.

| overlay | entries | role (evidence) |
|---|---|---|
| P01 | 1 | wilderness / world-map location program (calendar updates `CalUpd1`, `FindBit` event flags, loads room overlays) |
| P02 | 5 | town program ("The door is locked", "Whom do you seek?", shop/door handling) |
| P04 | 2 | small location program (yes/no prompts, `InitMap`) |
| P05 | 2 | mindstone / teleport location (`UseMindstone` ×16) |
| P06 | 26 | library of small routines, 26 entry points, uses `SkillUp`, `AutoPause` — probably the room-program half (`_RoomPgm`, offset 0x2000) for generic rooms |
| P07 | 1 | dungeon program (prisoners, chests, traps) |
| P08 | 2 | King Rebnard's court / main quest NPC scenes (`MultiFX` effects, crystal key) |
| P09 | 1 | engraved-word / puzzle rooms (`PrtWrd`) |
| P70 | 1 | notepad (`NOTES000.MCN`) |
| P81 | 4 | startup: title, intro story, character setup (`graphmode`, `VGAFadeIn`, `readfile`); loaded as overlay 0x51 (16 KB) at `_Hello` |
| P88 | 1 | travel / destination menu ("Isle of Winds", "North Misor", "Wait Here") |
| P89 | 0 | no jump table; a few tile/graphics routines (`OrTile`, `PageFlip`) — special effect |
| P90 | 3 | trade and gifts (Altesen's orb, buy/sell with gold check, `IncObj/DecObj`) |
| P91 | 6 | town NPC small talk ("nice weather", The King) |
| P92 | 2 | **hour tick**: clock/day/season, sunrise/sunset, weather per region, hunger, assignment updates, paydays (`docs/rules/time_weather.md`, `npcs.md`) |
| P93 | 1 | camp: sleep / learn / activities (`SetTxtSpell`, `ListSel`) |
| P94 | 29 | combat spell program (location half, 0x5E): the `SPLVECS` offset-0 slots (`_Fear` 4 … `_Drain` 27) are stubs that `INT 61h` into V06; also the spell-AI target picker (`ovl_15f8`) and combat mouse UI |
| P95 | 1 | resurrection & post-combat ("Mark the target", `SumStat`); overlay 0x5F |
| P96 | 1 | combat main loop (entry 0 = the fight) (`RndCo` random, `PlacePerson`, `Locate`); overlay 0x60 |
| P97 | 3 | party management: hire / dismiss companions |
| P98 | 1 | Quit / Save / Restart menu |

| V06 | INT 61h, 59 fns | combat effects + monster AI: spell handlers (`docs/rules/spells.md`), target choice ("Closest / Low hp / Magic-user / Leader …"), truce/bribe, rally |

Numbers 0x51/0x5E/0x5F/0x60 = decimal 81/94/95/96 match the file names. `FFFAR.MCO` (not in this table) is the always-resident far routine set: 75 strings incl. "Companion", "Hireling", "Learning %a".

## Open items
- `INT 60h`/`61h` = the location/room V-files (`V02`, `V05`, `V06`), see `docs/overlays.md`. `V02`/`V05` handlers not yet mapped.
- `_crossovlycall` (`EXE_crossovlycall(...)`) calls between the location and room halves.
- Which `Pnn` each location uses is decided by overlay code / `PGM` records, not yet traced.
