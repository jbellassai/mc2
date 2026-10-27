# Skills: where each one is read

Hero skill bytes (`HERO+0x17…0x29`, `docs/structs.h`). "Best in party" = `_HighStat(offset)`. Caps per race in `_maxtbl` (`combat.md`).

| skill | offset | used by | effect |
|---|---|---|---|
| sword / axe / archery / fist | 17–19, 1B | combat (`combat.md`) | to-hit and damage; improve after a successful attack |
| magic | 1A | `_Magic`, combat | spell energy cost `cost − magic/4`; spell power (`spells.md`); improves when casting a `SKLSPLS` spell |
| swim | 1C | `P01 ovl_194e` | entering water terrain: every member needs > 0, best swimmer > `(weather−99)/2`, each member > `(weather − energy)/2` (`time_weather.md`, *Swimming*) |
| trade | 1D | `P90` | haggling vs the merchant's skill (`economy.md`); never improves by trading |
| stealth | 1E | `P92 ovl_0716` (hourly) | companions on assignment task 0x65: each hour a 1-in-10 check, `RndCo(100) < stealth` avoids `ovl_0b40` (TODO: capture / relocation) |
| research | 1F | — | **no reader found** (all `[bx+0x1F]` hits are combat-record fields) |
| soul reading | 20 | — | **no reader found** |
| lockpick | 21 | `P02`, `P07` | `min(99, dex/2 + lockpick)` vs d100 to pick doors/chests/search spots; a failed roll breaks the Pick; improves on success (`locations.md`) |
| track | 22 | `P02 ovl_1690` (best in party) | town ambush: `RndCo(200) < track` → "%o detects an ambush!" and the fight is not an ambush |
| music | 23 | `V06 0x2860` (combat) | playing an instrument in combat repeats its effect `music/20 + 1` times (TODO: which effect per instrument/song) |
| carpentry | 24 | `P93 ovl_1137` (best in party) | open-camp shelter: sleep caps raised by `carpentry/2` (`camp.md`) |
| smith | 25 | `P93` Fix | each 5-min tick `RndCo(100) ≤ smith` repairs one damage point (`camp.md`) |
| gemcut | 26 | — | **no reader found** |
| tailor | 27 | `P97 0x728`, `_tailorcharm` | adds to charm in dialogue checks (`dialogue.md`) and reduces weather energy loss (`time_weather.md`) |
| hunt | 28 | `P93` Hunt | `terrain + weather + hunt/2 ≥ RndCo(100)` → +1 Food twice an hour (`camp.md`); improves on success |
| leadership | 29 | `P96 0x789` | pre-combat *Rally*: `RndCo(100) < leader's leadership` → the rally succeeds (every other member `bravery += RndCo(3)+1`, `agility += 4`, capped 12) |

Learning: skills rise only through `_SkillUp` rolls at the uses marked "improves" and through scripted teachers; the camp *Learn* command teaches spells, not skills (`camp.md`). Research, soul reading and gemcut appear to be unused by the code (they may only be shown on the character sheet) — worth confirming with a runtime test before a port drops them.
