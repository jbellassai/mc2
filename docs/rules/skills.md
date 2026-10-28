# Skills: where each one is read

Hero skill bytes (`HERO+0x17…0x29`, `docs/structs.h`). "Best in party" = `_HighStat(offset)`. Caps per race in `_maxtbl` (DS:2C7E, 20 skills × 6 races, below).

| skill | offset | used by | effect |
|---|---|---|---|
| sword / axe / archery / fist | 17–19, 1B | combat (`combat.md`) | to-hit and damage; improve after a successful attack |
| magic | 1A | `_Magic`, combat | spell energy cost `cost − magic/4`; spell power (`spells.md`); improves when casting a `SKLSPLS` spell |
| swim | 1C | `P01 ovl_194e` | entering water terrain: every member needs > 0, best swimmer > `(weather−99)/2`, each member > `(weather − energy)/2` (*Swimming* below) |
| trade | 1D | `P90` | haggling vs the merchant's skill (`economy.md`); never improves by trading |
| stealth | 1E | `P92 ovl_0716` (daily) | a travelling companion (task 8): each travel day a 1-in-10 check, `RndCo(100) ≥ stealth` → captured and jailed in a region dungeon (`assignments.md`) |
| research | 1F | `P05` library | subject needs `research ≥ required` (20–70); immediate subjects take `(100 − research)/4 + 1` ticks to read (`services.md`) |
| soul reading | 20 | `P96 ovl_0b5c` (best in party, `_Advice`) | before a fight, `RndCo(100) ≤ soul reading` → the monsters' attitude is told (`combat.md`, *Talk before a fight*) |
| lockpick | 21 | `P02`, `P07` | `min(99, dex/2 + lockpick)` vs d100 to pick doors/chests/search spots; a failed roll breaks the Pick; improves on success (`locations.md`) |
| track | 22 | `P02 ovl_1690` (best in party) | town ambush: `RndCo(200) < track` → "%o detects an ambush!" and the fight is not an ambush |
| music | 23 | `V06 INT61_1d` (combat), V06 0x2860 (Horn) | each known song of the instrument charms every monster of its race with chance `RndCo(200) ≤ music + 100`, once per use (`encounters.md`, *Combat songs*); the Horn's effect repeats `music/20 + 1` times |
| carpentry | 24 | `P93 ovl_1137` (best in party), `P05` jobs | open-camp shelter: sleep caps raised by `carpentry/2` (`camp.md`); carpenter job wage |
| smith | 25 | `P93` Fix, `P05` jobs | each 5-min tick `RndCo(100) ≤ smith` repairs one damage point (`camp.md`); metalsmith job wage |
| gemcut | 26 | `P05` jobs | daily wage of a gemcutter job (`services.md`); otherwise unused |
| tailor | 27 | `P97 0x728`, `_tailorcharm`, `P05` jobs | adds to charm in dialogue checks (`dialogue.md`) and reduces weather energy loss (`time_weather.md`) |
| hunt | 28 | `P93` Hunt | `terrain + weather + hunt/2 ≥ RndCo(100)` → +1 Food twice an hour (`camp.md`); improves on success |
| leadership | 29 | `P96 0x789` | pre-combat *Rally* (after a coin flip that can start an ambush instead): `RndCo(100) < leader's leadership` → every other member `bravery += RndCo(3)+1`, `agility += 4`, capped 12, for that fight (`combat.md`, *Talk before a fight*) |

Learning: skills rise through `_SkillUp`/`_SkillUp0` rolls at the uses marked "improves" (chance `(50−skill)/4` % below 50, 1 % above, plus a weapon base for the five combat skills — `combat.md`, *Skill advancement*) and through **school lessons** (`services.md`: one lesson = +3…+9 up to a racial cap, lesson length shortened by `h_intellg`). Soul reading has no reader at all; research only gates library subjects; gemcut only pays a job wage.

## Swimming (`P01 ovl_194e`)

A world-map step on foot onto a tile that is not walkable, not a town entrance and holds no boat (`ships.md`) is a swim when the tile's terrain class is river (12) or water (13); any other class is simply blocked. With `w = swim_weather[weather]` (P01 file 0x2F6: Clear 100, Overcast 110, Fog 120, Rain 150, Thunderstorm 170, Snow 190, Blizzard/Freezing/Gale 200, Sweltering 100, Sandstorm 110, Hurricane 190), members scanned from slot 5 down:

1. already in the water (OV_0x1bd, overlay-private) → "Too far to swim!" (comtxt 0x77): the party can cross **one** water square at a time;
2. a member with swim 0 → "%a can't swim!" (0x78);
3. `(w − 99)/2 ≥` the best swim skill → "The weather is too stormy to swim!" (0x79);
4. a member with `(w − h_energy)/2 ≥` their swim skill → "%a can not endure a swim!" (0x7A);
5. otherwise the party steps into the water and OV_0x1bd = 1. Any walkable step (@0xD7D) or step against non-water terrain clears it.

The swim step costs time and energy like a land step with `_curter` = 12 or 13, past the end of the 10-entry tables (`time_weather.md`): `terrain_time` then reads the weather table's bytes 2–3 (0, 0) and `terrain_energy` the clothing table's first-row bytes 2–3 (0 for a river, 1 for water).

## Racial caps (`_maxtbl`, `_MaxSkill(hero, idx)`)
A skill never rises above its cap by use or lessons; magic is capped at 0 for anyone with `h_magic == 0`.

| skill | Human | Wizard | Elf | Halfling | Dwarf | Orc |
|---|---|---|---|---|---|---|
| sword | 99 | 40 | 75 | 60 | 60 | 75 |
| axe | 75 | 10 | 25 | 50 | 99 | 50 |
| archery | 80 | 25 | 99 | 80 | 75 | 50 |
| magic | 75 | 99 | 75 | 0 | 0 | 0 |
| fist | 99 | 40 | 99 | 50 | 75 | 99 |
| swim | 99 | 30 | 99 | 99 | 10 | 30 |
| trade | 99 | 25 | 40 | 99 | 75 | 35 |
| stealth | 75 | 40 | 75 | 99 | 60 | 20 |
| research | 99 | 99 | 99 | 50 | 50 | 0 |
| soul reading | 75 | 50 | 99 | 99 | 99 | 20 |
| lockpick | 60 | 20 | 50 | 99 | 99 | 50 |
| track | 75 | 25 | 99 | 50 | 99 | 60 |
| music | 75 | 10 | 99 | 99 | 25 | 0 |
| carpentry | 75 | 25 | 99 | 99 | 50 | 40 |
| smith | 75 | 25 | 75 | 75 | 99 | 30 |
| gemcut | 75 | 25 | 75 | 99 | 99 | 25 |
| tailor | 75 | 25 | 99 | 99 | 50 | 25 |
| hunt | 99 | 25 | 99 | 75 | 75 | 75 |
| leadership | 99 | 50 | 99 | 60 | 75 | 10 |
| glamour count | 0 | 0 | 0 | 0 | 0 | 0 |
