# Skills: where each one is read

Hero skill bytes (`HERO+0x17…0x29`, `docs/structs.h`). "Best in party" = `_HighStat(offset)`. Caps per race in `_maxtbl` (`combat.md`).

| skill | offset | used by | effect |
|---|---|---|---|
| sword / axe / archery / fist | 17–19, 1B | combat (`combat.md`) | to-hit and damage; improve after a successful attack |
| magic | 1A | `_Magic`, combat | spell energy cost `cost − magic/4`; spell power (`spells.md`); improves when casting a `SKLSPLS` spell |
| swim | 1C | `P01 ovl_194e` | entering water terrain: every member needs > 0, best swimmer > `(weather−99)/2`, each member > `(weather − energy)/2` (`time_weather.md`, *Swimming*) |
| trade | 1D | `P90` | haggling vs the merchant's skill (`economy.md`); never improves by trading |
| stealth | 1E | `P92 ovl_0716` (daily) | a travelling companion (task 8): each travel day a 1-in-10 check, `RndCo(100) ≥ stealth` → captured and jailed in a region dungeon (`assignments.md`) |
| research | 1F | `P05` library | subject needs `research ≥ required` (20–70); immediate subjects take `(100 − research)/4 + 1` ticks to read (`services.md`) |
| soul reading | 20 | — | **no reader found** (trainable at Wanasol, `services.md`) |
| lockpick | 21 | `P02`, `P07` | `min(99, dex/2 + lockpick)` vs d100 to pick doors/chests/search spots; a failed roll breaks the Pick; improves on success (`locations.md`) |
| track | 22 | `P02 ovl_1690` (best in party) | town ambush: `RndCo(200) < track` → "%o detects an ambush!" and the fight is not an ambush |
| music | 23 | `V06 0x2860` (combat) | playing an instrument in combat repeats its effect `music/20 + 1` times (TODO: which effect per instrument/song) |
| carpentry | 24 | `P93 ovl_1137` (best in party), `P05` jobs | open-camp shelter: sleep caps raised by `carpentry/2` (`camp.md`); carpenter job wage |
| smith | 25 | `P93` Fix, `P05` jobs | each 5-min tick `RndCo(100) ≤ smith` repairs one damage point (`camp.md`); metalsmith job wage |
| gemcut | 26 | `P05` jobs | daily wage of a gemcutter job (`services.md`); otherwise unused |
| tailor | 27 | `P97 0x728`, `_tailorcharm`, `P05` jobs | adds to charm in dialogue checks (`dialogue.md`) and reduces weather energy loss (`time_weather.md`) |
| hunt | 28 | `P93` Hunt | `terrain + weather + hunt/2 ≥ RndCo(100)` → +1 Food twice an hour (`camp.md`); improves on success |
| leadership | 29 | `P96 0x789` | pre-combat *Rally*: `RndCo(100) < leader's leadership` → the rally succeeds (every other member `bravery += RndCo(3)+1`, `agility += 4`, capped 12) |

Learning: skills rise through `_SkillUp` rolls at the uses marked "improves" and through **school lessons** (`services.md`: one lesson = +3…+9 up to a racial cap, lesson length shortened by `h_intellg`). Soul reading has no reader at all; research only gates library subjects; gemcut only pays a job wage.
