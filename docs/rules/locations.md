# Locations: dungeon rooms, chests, searches, keys

Sources: `P07.MCO` (dungeon-room program), `P01` (entering a dungeon from the world map), `P02` (town search / keys), `P09` (puzzle rooms), `Dnn.MCV` sub-tables (`docs/formats.md`). Dungeon levels are program-2 locations like towns (`P02` + `V02`); `P04` = mushroom patches, `P05` = service rooms, `P06` = the combat room program.

## Look (`_Look`, EXE 1166:049B; Talk at an empty square uses the same tail, FFFAR `ovl_2c1b`)
Mark a square; the line starts "%h sees " (common text 0x08; in a town with the square out of sight, "It's " 0x115 instead). Then:
- a party member / known companion (`num < 0x20`) → their name;
- any other person → "a "/"an " (0x0E/0x0F, chosen by a vowel table) + the **type name** `DS:2296[type]` (man, woman, wizard, elf, … — named NPCs are described by type too); in combat a dead one gets "a dead " (0x112) + the monster name;
- otherwise the tile's name from the tileset's `txttbl` (names carry their own article: "a signpost", "cobblestones"), then "." (0x10), then the **look spot** text when `lkdata` has a record for the square (below) and the square is in line of sight.
*Talk* aimed at a square with nobody on it prints "%h talks to " (0x11) + the same tail.

**Line of sight** (towns and dungeon levels only, `_curmpg` 2: P02 `ovl_1ae7`, jump-table entry 0x1E): with `_losflag` set, V02 `INT60_0B` builds the blob map of the 11×9 window from the marked square. Open squares are those `_ChkWlk` passes, which with `_losflag` also accepts the tileset's second tile list (after the walk list's 0xFF; `tiledata` `walkable_los`), so water and the like do not block. The marked square starts at 0 even if it is a wall, and the flood spreads 8-way (P02 file 0x81E/0x826) one step a pass. The square is in sight (`_losresult` 1) when the looker's blob value equals the Chebyshev distance between them (`ovl_1b3c`): no wall lengthens the way. So a wall face next to open floor is seen, the wall behind it is not, and nothing outside the window is. Port: `main.ts` *inSight*, *look*.

## Pointer table conventions
A `Dnn.MCV` starts with 20 u16 pointers in `LOCTYPE` order. An **unused table has the same value as `roomptr`** (the first real table), e.g. D20 `treasptr = spdoors = locptr = 0x47 = roomptr`. `tools/locdump.py` (fixed 2026-10-27) treats those as empty. Real record shapes seen so far:

| table | record | meaning |
|---|---|---|
| `lkdata` | `{x, y, text}` ×n, 0-terminated | **Look spots** (FFFAR look, file 0x2C5D): looking at `(x, y)` outside combat, with line of sight, appends `loctext[text & 0x7F]` to the description; with bit 0x80 only while a non-companion NPC (number ≥ 0x20) stands there. The Dark Candle rooms start the table `(type − 1) · 4` bytes in, so each room shows its own inscription (`P07 ovl_069e`) |
| `hroomptr` | `HROOM` 13 bytes `{hrmid, hrmgrp, hrmreward, hrmrewamt, hrmmap, hrmxy[4]}` | **dungeon rooms** (see below) |
| `spetbl` (towns and dungeon levels, P02) | `{x, y, type, d1, d2, d3}` ×n, 0-terminated | special spots: 0 ambush, 1 teleportal, 2/3 lockpick/search spots (`d2` = `treasptr` group and its `_chests` bit, `d3 ≠ 0` → trapped, V02 service 0x15), 4 pit (unused), 5 hidden chute, 6 companion remark — *Dungeon levels* below |
| `spetbl` (P09 puzzle rooms) | `{x1, y1, x2, y2}` rectangles | — |
| `treasptr` (towns) | `id, {item, amount}…, 0xFF` groups | contents of search spot `id`; `item 0x80` prints the special text (local 0x10 + loctext) instead |
| `spdoors` | `{?, x, y, newtile, text}` ×n, 0xFF-terminated | tiles swapped when a key door opens (`P02 ovl_0d70`, *Towns* → **Keys**); byte 0 is never read; `text` of the first record = success line, `text + 1` = failure line |
| `locevptr` (P01) | per world-map entrance *n*: a 0xFF-terminated list of event bits | the entrance exists only while one of the listed events is set (`P01 ovl_0f21`) |
| `hroomptr` word pairs `{npc, text}` (P91) | — | what a party member says when talked to in this room (`dialogue.md`). Read only when `_curmpg > 2` (room programs: services, scenes, P07…), so it never meets the HROOM records of program-2 dungeon levels — the slot is reused per program |

## Dungeon rooms (`HROOM`, program P07)
Entering a room from a dungeon map copies its record to `_hroomrec` (P01 does it for wilderness entrances: `{entrno, grpno, 0…, hrmmap = OV_0x1C1}`):
- `hrmmap & 0xF` selects one of the small room maps (`_thismap` + n·0x65), `hrmxy[4]` are the four door/feature positions placed by `ovl_049a`.
- `hrmgrp` = the **encounter group** guarding the room (`_grpsptr[grp − 60]`, combat type 5); after the guards die the room's bit in `_dunrms` is set and they never return.
- `hrmreward`/`hrmrewamt`: a **chest** (tile 0x1F at (1,1)) with `amount × item`, or if `reward ≥ 0x80` a **fountain** (tile 0x1C at (9,0)) of spell `reward − 0x80` with `amount` charges. Opened chests / drunk fountains are remembered in `_duntre` by `hrmid`.
- `_hroomtype` is set when a door is entered (`P02` → V02 service 0x12, table at V02 file 0xE19, 14 room ids then their 14 types at 0xE27: `15 F6 12 1D 49 4A F7 FD FE` → 1 prison cell; `F8 F9 FA FB` → 2–5 Dark Candle rooms; `44` → 6 Vankruh's chamber, shown only with `_events+8 & 4`, `_VANKRUHXY`). Types 2–5 use `lkdata` row `type−1` (4 bytes: the candle at (4,1) and its inscription text) and open permanently once event `0x3C + type` is set.

**The room** (P07 `ovl_0099`): map G05 chunk `hrmmap & 0xF` (chunk 0 loaded, chunk n copied over it), drawn with the door PGM's tileset. A chest puts tile 0x1F at (1,1); a fountain 0x1C at (9,0) and 0x0E at (9,1). Each side n = 0 W, 1 N, 2 E, 3 S whose `hrmxy[n] ≠ 0` gets a door: its two squares from P07 file 0x03 (x) / 0x0B (y), `[(0,3),(0,4)] [(4,0),(5,0)] [(10,3),(10,4)] [(4,8),(5,8)]`, and its two tiles from the tileset's `doorptr` bytes `2n, 2n+1` (`ovl_049a`; V16: W 10 11, N 6B 6C, E 6D 6E, S 08 09). The guards' arena is the same map with the same features (P96 `ovl_0cca`). Entering without a fight places the members at formation `door type − 6` of `_setupxy` (`_PlacePerson`); after a won fight they keep their squares (`_p07flg`). Bumping a door square (`_RMove` 1 + `_ChkDoor`, side n into `_exitdir`) or stepping off the map (`_RMove` 2) asks to leave; Yes restores the level (`_ResLocD`) with the window at `hrmxy[_exitdir]` — low byte x, high byte y — and the formation at window + (4,3). Texts: P07 file 0x806, 15 strings (0 already open, 1 " It's empty.", 2 trapped, 3 poisoned!, 4 ill!, 5 But the chest is open., 6 It contains %b %as…, 7/8 move closer, 9 %h opens the chest., 10 " of %a spells.", 11 Will %h drink from it?, 12 %h gains %b %a spells., 13 How refreshing!, 14 It contains a %a…); trap condition bits P07 0x804 `[8, 2]` by `hrmid & 1`.

### Opening a chest (`P07 ovl_0969`)
Requires **using a Pick** (0x50) on the chest from an adjacent square. Already open → "The chest is already open." Otherwise:
```
skill  = min(99, h_dextrty/2 + h_lockpck)
if RndCo(100) ≥ skill:  the pick breaks (−1 Pick, sound 0x15)      — the chest still opens
trap:  RndCo(4) == 0 and RndCo(120) > skill  →  "The chest is trapped! %h is poisoned/ill!"
       condition bit = hrmid & 1 ? Ill (0x02) : Poisoned (0x08); h_energy /= 2, h_hitpts /= 2
else:  lockpick skill-up roll (_SkillUp0, skill 10)
```
Then "It contains %b %as. Will %h take them?" → `IncObj(hero, item, amount)` (a weapon/armour counts as 1), `_duntre` bit set, hirelings' `partybucks += value × amount` (`economy.md`); taking item 0x1E (Darkfinder) sets `_events+11 & 0x20`.

### Fountains (`ovl_0d54`)
"Will %h drink from it?" → if the hero has magic (`h_magic ≠ 0`) and the spell is not 0x2A: `h_spells[spell] += amount` (cap 99), "%h gains %b %a spells." The spell charges are given once per fountain (`_duntre` bit by `hrmid`). Every other case — spell 0x2A, a hero without magic, or a fountain already used — is a plain drink, repeatable: "How refreshing!" and the drinker's **energy is set to 99** (`_IsHeTr`, sound 0x19).

### Dark Candle rooms (`_hroomtype` 2–5, data `D98`, P07 `ovl_06c2`)
Four elden are imprisoned in candle flames; each room is reached through a dungeon door (`tools/doors.py`): Despair (id 0xF8) in Dorak 6, Pain (0xF9) in Ruz 2, Anguish (0xFA) in Namaz 6, Slow Death (0xFB) in Dragos 3 and Dreax 2. *Look* shows the inscription (`D98` texts 0–3). The room reacts to **using the matching scroll** (item `0x4A + type`: White 0x4C Despair/Zifar, Gray 0x4D Pain/Zulain, 0x4E Anguish/Zewinul, Blue 0x4F Slow Death/Zidoni; the elden's name is `D98.gwrds[item − 0x4C]`):
- scroll not yet deciphered (`h_invamt & 0x80` clear, `items.md`) → "The scroll is blank." (text 4);
- user has `h_magic == 0` → "%h cannot pronounce the arcane words scribed on the %a. The foul candle blazes on!" (5);
- else texts 6–7 (the incantation, the flame burns the scroll), sound 5, the scroll is consumed, the candle tile changes (`_mapyl+6 = 0x5D`), a `Bang` at the hero, "%o has been set free!" (8), the room's KNPC pointer is advanced `(type−1)·11` bytes so the freed elden appears, and **event `0x3C + type`** (62 Zifar, 63 Zulain, 64 Zewinul, 65 Zidoni) is set.
The freed elden then speak `D98` texts 9–12 (meet at Wanasol Hall; Zidoni: bring King Rebnard) and the Wanasol Hall scene in `quest_scenes.md` takes over. The Blue Scroll comes from that scene; the others are found/bought and deciphered through library research (`services.md`).

Talking to an NPC listed in `resids` while `_swgreet` is 2 runs P07 `ovl_04ef`: D98 text 9 + the KNPC record's byte 5. The candle square is cell 5 = (5,0); on a later visit with the event set the flame is out (`ovl_07c1` on entry) and the elden is gone (the KNPC pointer is only advanced at the moment of freeing).

Web port (`chamber.ts`, `main.ts` *candle*): all of the above except the sound and the Bang. Vankruh's chamber (type 6, room 0x44 in Dorak 7): Greet in the fight stores Vankruh's square (record 6, P96 0x84B) in `_VANKRUHXY` before the weapon check; on entry with event 66 set P07 `ovl_069e` advances the KNPC pointer by 0x37 to D98 record 5 (Vankruh, NPC 185, name word 4), writes `_VANKRUHXY` as its square and sets `_swgreet` 2, so Talk gets `ovl_04ef`: D98 text 9 + 4, "You may pass." Built (`Chamber.meet`; `_VANKRUHXY` is saved).

### Prisoners (`_hroomtype == 1`)
Companions captured earlier (stealth failure while travelling, `assignments.md`) are stored as assignment records with task 0x65 at this location/room/hroom (`_AssignedHere` compares `as_loc/as_room/as_hroom`). On entry (P07 `ovl_05ad`) each such record's task becomes 0xFF (idle here: the record stays), the companion is placed near (2,4) (`_PlacePerson`, stored in `as_x/as_y`) and P07 text 0x539 "The prisoner says: 'Many thanks for the rescue!'" is shown; four captives (P07 file 0x56A: NPCs 5, 10, 30, 28) also set events 40, 42, 43, 44. The freed companion then stands in the cell until invited (`assignments.md`, *Rejoining*).

## Town searches (`P02`, *Search* command)
At a `spetbl` spot of type 2/3: same pick formula as chests (`dex/2 + lockpick` vs d100, failure breaks a Pick), lockpick skill-up, then the spot's `treasptr` group lists `{item, amount}` pairs; "%h will take…" picks a hero (`HeroSel`) and sets the spot's bit in `_chests`. A spot with `d3 ≠ 0` first runs the V02 trapped-chest service.

## Towns (`P02`, program 2)
- **Time**: every 12 steps = one 5-minute tick (`_CalUpd`); every second tick all members lose 1 energy (`ovl_0fca`). The walk-on-water counter decrements per step.
- **Locked doors** (`ovl_196b`, menu 0x10 = Knock/Pick/Break/End): a door whose `type` is not 0 or 3 (and has no key bit) is locked; unless its resident is in the party ("I have a key") it gives four choices:
  - *Knock* (sound 0x11): if the resident is in (`_TimCalc` on their hours, not removed in `_npcsta`, and the RESID event conditions hold) → "A voice from within asks: Whom do you seek?" — type a word; if it matches the resident's name (`_WMatch` against `gwrds`) → "That's me! Would you like to come in?" (yes = enter), else "There is no one here by that name. Goodbye!". Nobody home → "There is no response." If the resident is in your party → "I have a key. Shall we go in?".
  - *Pick lock*: impossible when `doorstn == 0xFF`; needs a Pick (0x50); `min(99, dex/2 + lockpick) > RndCo(100)` → "The lock clicks open!" (entered with `rmdata+5 = 1`), else the pick breaks.
  - *Break*: impossible when `doorstn == 0xFF`; succeeds if `doorstn < h_strngth` of the acting hero → "%h breaks open the door!" (`rmdata+5 = 2`), else "The door withstands %h's assault." `doorstn` is one value per location (`LOCTYPE+56`).
  - *End* leaves. Texts are P02's own table (file 0x67, `ModTxt(n)`): 0 locked, 1 no response, 2 whom do you seek, 3 no one by that name, 4 that's me, 5 I have a key, **6 "%h resists the urge to break into a quiet private home." = the reply to Pick or Break when `doorstn == 0xFF`** (every town has 0xFF, so town homes can only be knocked on), 7 lock clicks open, 8 breaks open, 9 " The party goes inside.", 10 withstands, 11 needs a lockpick; a broken pick prints common text 0x90 (inferred).
- **Keys** (`ovl_0d70`): a door whose type byte has bit 0x80 is a key door; the key is item `type & 0x7F` and it only has to be somewhere in the party (`_SearchInv`, any member) — nothing is used or consumed. With it, every `spdoors` record's tile at `(x, y)` becomes `newtile` and the member carrying the key says `loctext[text]` ("'I have the %a.' It opens the door to Deraum!") and the party **goes through** at once: the door's PGM record becomes the program (P02 `L_198c`; Cellars 2's is program 8, D60); without it `loctext[text + 1]` ("The crystal door to Deraum is magically locked.") and nothing else. Data: Cellars 2 doors (62–63, 4) need the Crystal Key 0x5A (from Maalaq, `quest_scenes.md`), Mandarg 4 doors (64–65, 4) the Iron Key 0x5C. Oshcrun carries a copy of the Cellars 2 records but no key door.
- **Lockpick on things** (`ovl_1044`, using a Pick 0x50): mark an adjacent square ("Mark the target."); it must be a `spetbl` type-2 spot ("%h can not use a lockpick on that!", comtxt 0x8F, otherwise); the pick roll as above (a miss: "The lockpick breaks!" 0x90, −1 Pick, the lock still opens); a spot with `d3 ≠ 0` runs V02 service 0x15 (trap: `RndCo(120) > skill` → d3 1 Poisoned / 2 Ill, energy and HP halved, the chest texts of V02 0x107), otherwise the lockpick skill roll.
- **Digging** (`ovl_1131`, using a **Shovel** 0x46 — correction: not a *Search* command): "Where shall %h dig?" (0x7F), an adjacent square; an unwalkable square with no `lkdata` entry → "%h is unable to dig there." (0x80); no type-3 spot there → "%h finds nothing." (0x81).
- Both then share `0x11B0`: the group's `_chests` bit set → "%h finds nothing."; else "%h unearths treasure!" (0x82, for a picked lock too), each `{item, amount}` printed (`_PrtTreasure`; item 0x80 → the location text `amount`), "Who will take the treasure?" (0x85) → `HeroSel` → the bit is set and that member gets everything (weapons/armour 9–0x30 as one unworn item); an `_IncObj` refusal stops and the question comes again for the rest. Cellars 1: the lock at (7,5) holds Durren's note ("buried 40 paces south, 9 paces east"), which is the dig spot at (16,45): 50 Coins and 4 Emeralds.
- **Map flask** (`ovl_13c4`, locations with `pearlsw`): the *Map* command needs a Pearl (or asks to use a Blu Pearl); the pearl is dropped into the flask and the minimap is shown. With a plain Pearl there is a 1-in-10 roll where `h_dextrty ≤ RndCo(20)` shatters the flask ("The map flask shatters!", −1 Map Flask).

## Dungeon levels (`P02` movement, `spetbl` spots, room doors)
Dungeon levels ("Cellars 1 X", "Dorak 3 X"…) are ordinary **program-2 locations** (`P02` + `V02` via INT 60h, `_InDungeon()` true); there is no separate dungeon-level program. Everything below also runs in towns. Positions are absolute map coordinates; the party occupies one square per member (`_p1x/_p1y[6]`), each member at window + (4 + c mod 3, 3 + c div 3) where c is their cell in the 3×3 formation `_formatn` (`_NewPXY`, DS:0x91C/0x925); the shipped saves keep the leader in cell 0, so a lone leader stands at window + (4,3) (`FFSAVA`: window (93,14), leader (97,17)). Inside a P05 room the same cell offsets are added to the room's base square (`FFSAVE`: base (4,5), members at (4,5) (5,5) (6,5)). `_Invite` puts a recruit in the first free cell whose square is walkable and has no NPC (`_ChkForm`).

### A step (`P02` 0x45E → direction routine → `ovl_067d`)
For each occupied party slot (5…0) the target square is tested in order:
1. a member who is Dead, Paralyzed, Exhausted, Poisoned or Starving (`h_cond1 & 0xFC`) counts as blocked — so nobody moves (read from the code, not yet checked in play);
2. walkable (`_ChkWlk`) → ok; else, while `_wlkwcount > 0` (Walkwater), a tile in the tileset's segment-4 list (V02 service 02: water and rocks in B60, `spells.md`) → ok;
3. an **exit** (`exitptr` `{x, y, pgm, tx, ty}`) → change level: PGM record `pgm` (`_curmpg/_curtils/_curvar`) at `(tx, ty)` (exception: in **Shumaran** (`_curvar == 0x39`, D57, the wandering Tundra town) every exit leads to a world-map position chosen by `_month` (0–11) from the 12 `{x, y}` window origins stored in the `weathr` slot: Jan–Feb and Dec (168,34), Mar–May (158,21), Jun–Aug (168,18), Sep–Nov (147,25) — i.e. next to the town's four world-map entrances (173,37), (163,24), (173,21), (152,28), which are switched by the season events, *World map* below);
4. a **door** (`roomptr` `{x, y, pgm, id, type}`, list ends at the first `x == 0`) → enter it (below). Exception, **pass-through doors** (type 2, `pgm` = 'x' or 'y', `id` = '+' or '−'; Oshcrun, Ground Floor, Katarra, Dragos 2, Drakhelm, Drakhelm 1/3): the whole party jumps (its extent along that axis + 1) squares in that direction — the extent comes from the occupied cells of the 3×3 formation `_formatn` (`_PartyWH`), and the step is re-tested from there (P02 0x7E9: the window moves, then `ovl_067d` again), so the party lands jump + step away — the archways are two squares thick, a `+` door on the near square and a `−` door on the far one (blocked → it stays where it was);
5. otherwise blocked; V02 service 08 records what blocked him in `_bangstg[member]`: 1 = a tileset `aniptr` record of class **'C'** (the barrier Pierce removes), 2 = class **'B'** (the barrier Repel removes), 5 = plain wall.

If any member is blocked the whole party stays put, sound 0x0E plays and V02 service 09 runs: every member with `_bangstg = 1` loses **10 + RndCo(10) energy**, with `_bangstg = 2` loses **1 HP**; HP is then floored at 1 (a barrier never kills), `_IsHeTr`, `MultiBang(0x17)`. A successful step costs time (12 steps = one 5-minute tick, `Towns` above), decrements `_wlkwcount`, then checks the special spots.

### Special spots (`spetbl` 6-byte records `{x, y, type, d1, d2, d3}`, `P02 ovl_151a`)
After each step `ovl_189d` scans the 3×3 squares around the leader for a record (`ovl_1926`, the first match per square; unmatched types fall through to the next match). Some types fire only if a member actually stands on the square. Counts are over all program-2 locations:

| type | n | trigger | effect |
|---|---|---|---|
| 0 | 163 | 3×3 around the leader | **ambush**: `_entrno = d2` (ambush id), `_grpno = d1` (encounter group, `encounters.md`), `_hroomrec = {d2, d1, 0, 0, map d3, …}`. Skipped if `_ambush` bit `d2` is set (set after the fight is won). Otherwise `_cmbtyp = 0` (fight on the street map, members keep their squares), `_diff = locdiff − 1`, `_exitdir[] = 0xFFFF`, `_docmbt = 1`, `_ambflg = 1` (monsters act first). The ambush is **detected** — `_ambflg = 0`, "%o detects an ambush!" — if the spot is the one the last *Sense* spell pointed at (V02 service 0x13 result kept in `cs:0x133`), or if `RndCo(200) < best h_track in party`. Ambush ids 12, 101, 97, 108, 155, 110 also set events 49, 70, 71, 72, 90, 107 when they trigger (P02 file 0x1743/0x1749; Deraum and Drakhelm 2/3). |
| 1 | 120 | a member on the square | **teleportal**: "The party is swept into a teleportal!" (comtxt 0x7B), sound 0x14, a sprite effect (`_MFXInit`/`_movetileFX`), then level change to PGM record `d1` at `(d2, d3)` (`ovl_196b`). Never used up. Hidden on the map; *Detect* animates type-1 spots while it lasts (V02 service 0x0D, `spells.md`). Several squares often share one target (Maratul 4/5 trap corridors). |
| 2, 3 | 19, 17 | — (only by using a Pick / a Shovel) | lockpick / dig spots (`Towns` above; `d2` = `treasptr` group and `_chests` bit, `d3 ≠ 0` = trapped). |
| 4 | 0 | a member on the square | **pit**: "The party stumbles into a pit!" (0x7D) and nothing else — no data uses it. |
| 5 | 9 | a member on the square | **hidden chute**: level change to PGM `d1` at `(d2, d3)`, then "The party slides through a hidden chute!" (0x7E). Ruz 1, Shann 2/3, Drakhelm 1/2… |
| 6 | 38 | 3×3 around the leader | **companion remark**: speaker = the first of members 1–5 (never the player) with `h_race == d1 & 0x7F` when `d1 ≥ 0x80`, else `h_orinum == d1`; `d1 == 0xFE` = no speaker. No such member, or `d2 ≠ 0xFF` and event `d2` is set → nothing (the spot stays armed). Else V02 service 0x0E sets a quest event for some remarks (table below), the location's `loctext[d3]` is printed in the speaker's voice, the record's type becomes 0xFF and its bit is set in `_spetbldone`. |

`_spetbldone` (128 bits, one per record index) survives only while the party stays on the same level: V02 service 0x16, run on every level load, clears all bits when `_curvar` differs from the last program-2 level (`_lastp02var`) and otherwise re-disables the marked records. **Quirk**: leaving a level and coming back re-arms every remark (ambushes are permanent through `_ambush`).

Remark → event table (V02 file 0xBDB: 27 remark text ids, then 27 events, then 27 `_locspec` values; the event is set only when the remark id *and* the current `_locspec` match):

| `_locspec` | remark id → event |
|---|---|
| 29 | 5→54, 0→48, 2→83, 7→108, 3→109 |
| 30 | 0→48, 18→97, 15→51 |
| 31 | 21→110 |
| 32 | 4→98, 5→99, 6→111 |
| 33 | 4→116 |
| 35 | 6→112, 2→113 |
| 62 | 3→73, 24→74, 30→75, 10→76, 14→77, 4→78 |
| 64 | 3→80, 15→81 |
| 65 | 7→59 |
| 69 | 13→68, 19→106 |
| 70 | 28→118 |

### Doors into dungeon rooms (`roomptr` type 6–9, `P02` 0x8F8)
A door whose type is 6–9 (the type is also the arena formation side, `combat.md`) is a **dungeon room**. Its PGM record is always `{6, tileset, 6, …}` — "program 6" here means *room with guards*, not an overlay that runs on its own:
1. `_rmdata+4` = the PGM's tileset; the `HROOM` record with `hrmid == id` is copied from the level's own `hroomptr` table into `_hroomrec`; `_cmbtyp = 5`.
2. Group 0xCA (rooms 251 in Dragos 3 and D93) is replaced by group 0xDE, room id 0xFC, map 12 while event 32 (in `_locspec 0x41` = Dragos 3) or event 31 (elsewhere) is clear (P02 0x947: the copied `_hroomrec` gets group, map and id, and the id P02 goes on with is 0xFC too, so the `_dunrms` bit and `_hroomtype` are 0xFC's; the doors and reward stay). Port: `main.ts` *guardedRoom*.
3. `_grpno = hrmgrp`, `_diff = locdiff − 1`, `_hroomtype` from V02 service 0x12 (`Dungeon rooms` above).
4. If the room's `_dunrms` bit is set (guards already beaten): `_curmpg = 7`, `_curvar = 0x62` (D98) — the party walks straight into the room program **P07**. Otherwise `_docmbt = 1`, `_ambflg = 0`: the fight runs first (`_DoACmbt`: **P06 is the combat room program** at 0CA8:2000, P96/P94/P95 at 0CA8:0000). Winning sets the `_dunrms` bit and P95 switches to P07 the same way (`_p07flg`).

## World map (`P01`, region records `R32`–`R47`)

The world map is one 256×256 map; the party is always inside one of 16 **region records** (`_curreg`, `Rnn.MCV`, same 20-pointer `LOCTYPE` layout but several slots are reused — `tools/worldspots.py original` prints everything below):

| slot | content |
|---|---|
| `roomptr` | **features** `{x, y, pgmidx, rmid, type}` until `x == 0` (`ovl_0c1e`): mushroom patches (program 4), temples (`P09 D59`, ids 192–206, type 3), dungeon gates (`P09 D14` "A Gate", ids 208–215, type 4/20), the Oolau shrine (`P08 D36`) |
| `exitptr` | **town entrances** `{x, y, pgmidx, tx, ty}` until `x == 0`: stepping on it loads the town (`pgmidx` → PGM list → program 2 + D-file) at `(tx, ty)` |
| `locptr` | **spots** `LOCSPOT{x, y, pgmidx, rmid, type, wx, wy, ev, text, icon}` until `0xFF` (`ovl_0c28`): `ev == 0xFE` always, else index n of the n-th 0xFF-terminated `locevptr` list of `{event, text}` pairs — the spot exists while a listed event is set, and the first such pair's byte replaces `text` (`ovl_0c64`). Entering it sets `_pwinxy` = (wx, wy) (P01 0xD60, `mov ax, [bx+5]`). `type`, `text` (a region text: "A stronghold!", "A Camp!") and `icon` (E00) are what the party sees from a neighbouring square (`encounters.md`, *Engage*; until 2026-10-29 these docs read `text`/`icon` as the arrival window). Carries the 16 **strongholds** (`P05 D19`, ids 0x5C–0x6B, the Assign destinations; "secure from all threats while inside"), the hunt (0x59, N. Misor 60,27) and track (0x53, S. Misor 62,47) schools, huts/camps (`P05 D36` ids 1–4, `[9,0,0]`: Ziyx's hut in Demonspine, camps in The Throat and S. Misor — not piers), teleportals (`P09 D61` ids 0xA9–0xB6) and event-gated towns (Demonspine 88,36 after event 4 or 8; Shumaran, the Tundra nomad town, at one of four places by season: the spot's `ev` picks event list n of `{event, tx}` pairs (`ovl_0c64` skips n 0xFF-terminated lists; the first pair whose event is set enables the spot and supplies the arrival x) — R44 lists 0–3 = season events 12/9/10/11, i.e. winter (173,37), spring (163,24), summer (173,21), autumn (152,28); each pair's byte is 0x21 "A Camp!", and every one enters D57 with the window at (21,31)) |
| `gwrds` | 8 **guard spots** `{x, y, ?}` (zero = none); `_grdsta` bit `region·8 + n` marks a cleared guard; `newsr` = the encounter group number for each of the 8 |
| `weathr` | 4 seasons × 4 `{threshold, weather, duration}` (`time_weather.md`) |
| `loctext` | 0 "A mushroom patch!", 1 "A port of ethereal travel!", 2–7 ship names, 9–14 captain names, 0x0F–0x2C sailing/world-map messages (identical in all 16 regions) |

Ships and captains: `ships.md`.

Web port: features (programs 4, 8, 9) and spots (programs 2, 5, 8, 9) are entered by stepping on them (`world.ts` *spot*); a spot of a room program is treated like a feature with `rmid` as the room id. Not traced: P01's own handling of a spot's `tx, ty` for room programs (the port ignores them there).

### Mushroom patches (program `P04`, data `D04`, map `G00E00.MCM`)

30 patches (feature ids 0–29) across 14 regions; the item grown at patch `id` is `D04.gwrds[id]` (0x33 Sermin, 0x34 Gonshi, 0x35 Nift, 0x36 Mirget, 0x37 Luffin, 0x3C Loka — Turpin is never grown). The patch map is variant `_curter` (terrain under the party) of the 16 11×9 maps in `G00E00.MCM`. State: `_mushsta` (DS:7067, 32 bytes, one **nibble per patch**: even id = high nibble) = mushrooms left, 0–15, all 15 in a new game; **regrowth** +1 every 8th day (`_juldate & 7 == 0`, `P92 ovl_02cb`). Entering draws `count` mushrooms at the first `count` of 15 fixed positions (P04 file 0x88/0x97: x `[3,3,4,6,7,7,8,8,8,7,6,3,2,2,1]`, y `[2,1,1,1,1,2,2,3,5,7,7,6,6,5,4]`, placed with `_PlacePerson` so occupied cells shift); stepping on one asks "%h may pick %b %as" and gives `amount[kind]` = Sermin 6, Gonshi 4, Nift 3, Mirget 2, Luffin 3, Turpin 2, Loka 2 (file 0x72) to the acting member (`_IncObj`; a full pack refuses and the mushroom stays), then `count−1` is written back. Empty patch: "No more mushrooms are growing here."

Details (P01 `ovl_0d01`, P04 `ovl_0146`/`ovl_0441`/`ovl_050f`, checked in the port):
- **Entering.** Stepping onto the feature square spends the step's time (`ovl_10f7`) and enters at once; the window is not moved (`_pwinxy = _winxy`), so leaving puts the party back on the square it stepped from. `_rmdata` = the feature id, `_curter` = terrain class of the feature square, and the tileset is `P01` file 0x36A `[_terrain]` = `[7, 7, 13, 68, 68, 7, 7, 7, 13, 7]` (`ovl_09bf`; V07 forest/grass, V13, V68).
- **Placing.** `_NewPXY` puts the formation at (4,3) + cell, then each member is re-placed with `_PlacePerson`; the mushrooms come after, so they avoid the party but not each other. `_PlacePerson(x, y)`: (x, y) if it is on the 11×9 map, walkable, and holds no party member or NPC; else the first free square on Manhattan diamonds of radius 1, 2, …, each walked clockwise from its west corner (W, N, E, S for radius 1; direction tables DS:0995/0999).
- **Drawing.** Each mushroom is E00 icon frame `P04 0x7C[kind]`: 0x10 (scattered caps: Sermin, Gonshi, Turpin) or 0x11 (a clump: Nift, Mirget, Luffin, Loka).
- **Picking.** Only the acting member moves (`_RMove`); landing on a mushroom asks "%h may pick %b %as." (D04 text 0). On *Yes* `_IncObj` adds the amount; when it refuses ("%o can't carry any more of that." comtxt 0x32 over 99, "%o is at maximum inventory capacity." 0x33) the mushroom stays. Otherwise the count drops by one, the last placed mushroom takes over the picked one's list slot (its square does not change), and the count is written to `_mushsta` at once. D04 text 2 "%h picks up %b %as." is presumably printed by `ovl_04dd` (not decompiled).
- **Leaving.** `_RMove` returns 2 for any step off the 11×9 map (unsigned x ≥ 11 or y ≥ 9, so also x/y = −1); P04 asks comtxt 0x23 "Do you want to leave now?".
- `_juldate` is 0 in a new game (all saves), so the first regrowth is on the 8th day.

## Unused
`notyet0` (`LOCTYPE+38`, "not yet") is never read: no overlay touches `[si+0x6B93]` and the EXE never references DS:B889; its values just point into other tables. (Engraved words — temple names, gate passwords — are in `special_rooms.md`.)
