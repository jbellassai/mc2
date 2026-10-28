# New game: hero profiles and the starting state

Sources: `P81.MCO` (startup overlay: title, intro, hero setup; profile records at file 0x82D–0xC79, templates 0xC79–0xFE9, init code @0x17E4–0x1951, profile copy @0x1BF7, name entry @0x2200), `decomp/overlays/P81.c` (partial), saves `FFSAVx.MCS`.

There is no stat rolling. The player picks one of **five pre-built heroes** (the manual's "Hero Profiles A–E"), optionally renames them, and optionally imports a hero from *The Magic Candle* or *Keys to Maramon*.

## Flow (`P81`)
1. Title, "Legends tell of a hero named %h." Choice of starting fresh or "Bring heroes from which Mindcraft game?" (import, below).
2. "Refer to your Gamebook to select the Hero Profile you want to use (A-E)." — a 5-entry menu; the index (0–4) selects the 220-byte `HERO` record copied into `_member0` (player slot 0).
3. "Do you want to disclose %p true name?" — No keeps the profile's names. Yes: "Please type in the full name (up to 12 letters):" → `h_fullnm`, "Now type in a nickname (up to 5 letters):" → `h_name`; "Are these names correct?" loops. Typed names keep their first letter and lower-case the rest (`@0x220C`).
4. For an imported hero: "Was %h a woman in disguise?" → `h_sex = 1` on Yes (the profile records carry their own sex: B and D are women).
5. Coins: the record's `h_gold` bytes are `hundreds, units` → `h_gold = b0·100 + b1` (A 500, B 300, C 350, D 800, E 600).
6. Intro story (Rebnard on Castle Oshcrun, Captain Garlin's ship), then "%h has landed in Telermain."

## The five profiles
All are Human, bravery 12, loyalty 10, 51 hp, energy 99, no god seen, no carpentry/smith/gemcut/tailor. Pack amounts in `[n]` are the equipment byte (`0x80|n`, the wear count repaired by camp *Fix*, `camp.md`); worn items = `h_wears` slots (armour + clothing).

| profile | A | B | C | D | E |
|---|---|---|---|---|---|
| name | Lukas (Lukas Al Dem, M) | Luka (Luka Ni Dem, F) | Lukas (Lukas Al Dem, M) | Luka (Luka Ni Dem, F) | Lukas (Lukas Al Dem, M) |
| bravery | 12 | 12 | 12 | 12 | 12 |
| strength | 6 | 5 | 7 | 6 | 6 |
| dexterity | 5 | 5 | 7 | 7 | 5 |
| endurance | 6 | 6 | 6 | 6 | 6 |
| agility | 5 | 7 | 5 | 8 | 5 |
| loyalty | 10 | 10 | 10 | 10 | 10 |
| charm | 6 | 6 | 4 | 4 | 6 |
| intellect | 8 | 8 | 7 | 7 | 8 |
| resist | 4 | 4 | 3 | 3 | 4 |
| helped | 12 | 12 | 12 | 12 | 12 |
| sword | 30 | 30 | 45 | 45 | 35 |
| axe | 10 | 10 | 30 | 30 | 15 |
| archery | 40 | 45 | 30 | 30 | 35 |
| magic | 40 | 40 | 30 | 30 | 35 |
| fist | 30 | 25 | 40 | 30 | 30 |
| swim | 45 | 45 | 35 | 40 | 45 |
| trade | 20 | 20 | 20 | 35 | 20 |
| stealth | 40 | 40 | 25 | 20 | 30 |
| research | 10 | 10 | 10 | 25 | 15 |
| soulread | 45 | 45 | 15 | 15 | 30 |
| lockpick | 15 | 15 | 10 | 10 | 25 |
| track | 40 | 40 | 25 | 25 | 25 |
| music | 10 | 25 | 10 | 10 | 75 |
| carpentry | 0 | 0 | 0 | 0 | 0 |
| smith | 0 | 0 | 0 | 0 | 0 |
| gemcut | 0 | 0 | 0 | 0 | 0 |
| tailor | 0 | 0 | 0 | 0 | 0 |
| hunt | 50 | 50 | 25 | 25 | 30 |
| leadership | 50 | 50 | 50 | 50 | 50 |
| hit points | 51 | 51 | 51 | 51 | 51 |
| defprob | 40 | 40 | 40 | 40 | 40 |
| coins | 500 | 300 | 350 | 800 | 600 |
| songs | none | none | none | none | 2 known |
| spell charges | Confuse 5, Shatter 15, Locate 9, Assess 4, Heal 9, Weaken 9, Resurrect 3, Courage 6 | Confuse 5, Shatter 15, Locate 9, Assess 4, Heal 9, Weaken 9, Resurrect 3, Courage 6 | Fear 10, Shatter 18, Fireball 12, Weaken 5, Freeze 2 | Fear 10, Shatter 18, Fireball 12, Weaken 5, Freeze 2 | Confuse 5, Shatter 15, Locate 9, Assess 4, Heal 9, Weaken 9, Resurrect 3, Courage 6 |
| pack | 3× Blu Pearl, Scimitar [0], Smallaxe [4], Ashbow [19], Leather armor [0], Suede outfit [5], 18× Food, 6× Potion, 18× Sermin, 12× Gonshi, 4× Loka, 2× Medicin, Map, 50× Arrow, Blanket | 3× Blu Pearl, 5× Ruby, Scimitar [0], Smallaxe [4], Ashbow [19], Leather armor [0], Suede outfit [5], 18× Food, 6× Potion, 18× Sermin, 12× Gonshi, 4× Loka, 2× Medicin, Map, 50× Arrow, Blanket | 5× Jade, Longsword [0], Chain mail [0], Wool outfit [0], 12× Food, 4× Potion, 8× Sermin, 16× Gonshi, 10× Nift, 4× Mirget, 5× Luffin, 16× Fireglobe, Map | 5× Topaz, Longsword [0], Chain mail [0], Wool outfit [0], 12× Food, 4× Potion, 8× Sermin, 16× Gonshi, 10× Nift, 4× Mirget, 5× Luffin, 16× Fireglobe, Map | 4× Blu Pearl, Scimitar [0], Smallaxe [4], Ashbow [19], Leather armor [0], Suede outfit [5], 18× Food, 6× Potion, 18× Sermin, 12× Gonshi, 5× Loka, 3× Medicin, Map, Lyre, Flute, 50× Arrow, Blanket |

Coins: the profile record's `h_gold` word holds two bytes `{hundreds, units}` (profile C = `03 32` = 350), like C-file prices; the saved new-game hero has the plain value (500).

Profiles A/B/E are the ranger-mage build (bow, Confuse/Locate/Heal charges, 50 Arrows, Blanket, Loka), C/D the fighter build (Longsword, Chain, Fear/Fireball charges, Fireglobes, mushrooms). E is the bard variant: music 75, Lyre + Flute, two songs known.

## Starting state (init `@0x17E4`)
| what | value |
|---|---|
| clock | 8:30, day 2 of month 6, year 10, season 2, `_daynite = 'L'`, temperature 6 |
| `_remdays` | 1000 (days left before the game ends) |
| location | Telermain (`_curvar = 2`, town program 2, tileset 2), window (93,14), leader at (97,17) = window + (4,3), formation cell 0 (`FFSAVA`; the init also writes (14,3), purpose not traced); world position `_wildxy = (29,56)` |
| party | slot 0 = hero, slots 1–5 empty (`_party = 0xFF`), `_formatn` 0xFF |
| `_beenflg` | bit for entry 0 set |
| events | bits 10, 88, 117 set (`events.md`: 10 and 88 are P92 daily tests, 117 gates P97 hiring) |
| captains | all six `_capsta = 3` (at their home ports), `_curcap = 0xFF` (`ships.md`) |
| casinos | all 8 banks 1000 coins (`special_rooms.md`) |
| mushroom patches | `_mushsta` all nibbles 15 (`locations.md`) |
| `_snakelocs` | 256 bytes 0xFF; `_met` 32 bytes (P81 file 0x165F); `_ptrlxy` 256 bytes (file 0x16E4, patrol start positions, `encounters.md`); `_setupxy` 48 bytes (file 0x162F, the 6×4 combat formation offsets); `_ssnwthrs` `[100,0,143,0,…]` |
| assignments | all 0xFF except four companions who **start captured** (task 101, `assignments.md`): Ben Trimmon (NPC 5) and Eldai (10) in Shann 1 (D45), Rogga (28) in Maratul 2 (D38), Tamas (30) in the Catacombs (D67); each record carries the prison room/x,y and the region/world x,y to return to (`as_region/as_wildx/as_wildy` = 5/67/79 for Shann, 15/216/57 and 15/213/49 for the others) |

## Importing a hero
"Bring heroes from which Mindcraft game?" (The Magic Candle / Keys to Maramon), then "What drive and path for the saved game?" and a saved-game list ("Game %c is still in progress."). The imported hero's names are shown ("From The Magic Candle … Full Name / Nickname", "Are these names correct?") and copied over profile fields; the MC1 companion identified by a byte in the old save selects one of four 220-byte templates (P81 file 0xC79: **Kelligan**, **Stavros**, **Lumelia** "Melia", **Hornbern** "Hob"; `h_orinum = 7`, `h_relatn = 1`, race Human, no hp set) who "has arrived in Telermain from Maramon, and has settled in at the Eastern Breeze Tavern". Exact field mapping from the old save formats: TODO (not needed for a port that cannot read 1989 saves).
