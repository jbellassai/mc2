# Locations: dungeon rooms, chests, searches, keys

Sources: `P07.MCO` (dungeon-room program), `P01` (entering a dungeon from the world map), `P02` (town search / keys), `P09` (puzzle rooms), `Dnn.MCV` sub-tables (`docs/formats.md`). Work in progress — the town program `P02` and the dungeon-map programs `P04/P05` are only partly decoded.

## Pointer table conventions
A `Dnn.MCV` starts with 20 u16 pointers in `LOCTYPE` order. An **unused table has the same value as `roomptr`** (the first real table), e.g. D20 `treasptr = spdoors = locptr = 0x47 = roomptr`. `tools/locdump.py` (fixed 2026-10-27) treats those as empty. Real record shapes seen so far:

| table | record | meaning |
|---|---|---|
| `lkdata` | `{x, y, id}` ×n, 0-terminated | positions of lockable/special spots with an id (D30: `(35,87)→11, (54,50)→1, (47,40)→150`) |
| `hroomptr` | `HROOM` 13 bytes `{hrmid, hrmgrp, hrmreward, hrmrewamt, hrmmap, hrmxy[4]}` | **dungeon rooms** (see below) |
| `spetbl` (towns, P02) | `{x, y, type, sub, value:u16}` ×n, 0-terminated | special spots: the lookup (`ovl_1926`) matches the party position and a type filter (2 and 3 = searchable spots), returns `value` (= chest/search id) and `sub` (≠ 0 → handled by `V02` INT 60h, e.g. trapped chest service 15) |
| `spetbl` (P09 puzzle rooms) | `{x1, y1, x2, y2}` rectangles | — |
| `treasptr` (towns) | `id, {item, amount}…, 0xFF` groups | contents of search spot `id`; `item 0x80` prints the special text (local 0x10 + loctext) instead |
| `spdoors` | `{?, x, y, newtile, ?}` ×n, 0xFF-terminated | doors opened with a key item: every record's tile is replaced by `newtile` (`P02 ovl_0d70`, key = `_useditem & 0x7F`) — exact first/last byte TODO |
| `locevptr` (P01) | per world-map entrance *n*: a 0xFF-terminated list of event bits | the entrance exists only while one of the listed events is set (`P01 ovl_0f21`) |
| `hroomptr` word pairs `{npc, text}` (P91) | — | a companion's remark on entering this location (`dialogue.md`); conflicts with the HROOM use in dungeons — probably a per-program reuse of the slot, TODO verify |

## Dungeon rooms (`HROOM`, program P07)
Entering a room from a dungeon map copies its record to `_hroomrec` (P01 does it for wilderness entrances: `{entrno, grpno, 0…, hrmmap = OV_0x1C1}`):
- `hrmmap & 0xF` selects one of the small room maps (`_thismap` + n·0x65), `hrmxy[4]` are the four door/feature positions placed by `ovl_049a`.
- `hrmgrp` = the **encounter group** guarding the room (`_grpsptr[grp − 60]`, combat type 5); after the guards die the room's bit in `_dunrms` is set and they never return.
- `hrmreward`/`hrmrewamt`: a **chest** (tile 0x1F at (1,1)) with `amount × item`, or if `reward ≥ 0x80` a **fountain** (tile 0x1C at (9,0)) of spell `reward − 0x80` with `amount` charges. Opened chests / drunk fountains are remembered in `_duntre` by `hrmid`.
- `_hroomtype`: 1 = prison cell, 2–5 = lock types (P07 adds `(type−1)·4` to `lkdata`), 6 = Vankruh's chamber (needs `_events+8 & 2`); types 2–5 also check event bit `type + 0x3C`.

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
"Will %h drink from it?" → if the hero has magic (`h_magic ≠ 0`) and the spell is not 0x2A: `h_spells[spell] += amount` (cap 99), "%h gains %b %a spells." Spell 0x2A (or no magic) is a plain drink: "How refreshing!" (effect TODO — `ovl_0f04`). Once per fountain (`_duntre`).

### Prisoners (`_hroomtype == 1`)
Companions captured earlier (stealth failure while travelling, `assignments.md`) are stored as assignment records with task 0x65 at this location/room/hroom (`_AssignedHere` compares `as_loc/as_room/as_hroom`). On entry each such record is cleared, the companion is placed at (2,4) and says "Many thanks for the rescue!"; four specific captives (P07 table @0x56A) also set an event bit. Leaving clears their `_npcsta` bit so they re-appear per the normal placement rules (`npcs.md`).

## Town searches (`P02`, *Search* command)
At a `spetbl` spot of type 2/3: same pick formula as chests (`dex/2 + lockpick` vs d100, failure breaks a Pick), lockpick skill-up, then the spot's `treasptr` group lists `{item, amount}` pairs; "%h will take…" picks a hero (`HeroSel`) and sets the spot's bit in `_chests`. A `sub ≠ 0` spot first runs the V02 service (trap).

## Towns (`P02`, program 2)
- **Time**: every 12 steps = one 5-minute tick (`_CalUpd`); every second tick all members lose 1 energy (`ovl_0fca`). The walk-on-water counter decrements per step.
- **Locked doors** (`ovl_196b`, menu 0x10): a room whose RESID entry names someone gives four choices:
  - *Knock* (sound 0x11): if the resident is in (`_TimCalc` on their hours, not removed in `_npcsta`, and the RESID event conditions hold) → "A voice from within asks: Whom do you seek?" — type a word; if it matches the resident's name (`_WMatch` against `gwrds`) → "That's me! Would you like to come in?" (yes = enter), else "There is no one here by that name. Goodbye!". Nobody home → "There is no response." If the resident is in your party → "I have a key. Shall we go in?".
  - *Pick lock*: impossible when `doorstn == 0xFF`; needs a Pick (0x50); `min(99, dex/2 + lockpick) > RndCo(100)` → "The lock clicks open!" (entered with `rmdata+5 = 1`), else the pick breaks.
  - *Break*: impossible when `doorstn == 0xFF`; succeeds if `doorstn < h_strngth` of the acting hero → "%h breaks open the door!" (`rmdata+5 = 2`), else "The door withstands %h's assault." `doorstn` is one value per location (`LOCTYPE+56`).
  - *Leave*. "%h resists the urge to break into a quiet private home." guards rooms with nothing in them.
- **Keys**: using a key item (`_useditem & 0x7F`, e.g. Crystal/Iron Key) runs `spdoors`: every record's tile is swapped (`ovl_0d70`), i.e. all the matching doors in the location open at once.
- **Lockpick on things** (`ovl_1044`): mark a square; it must be a `spetbl` type-2 spot ("%h can not use a lockpick on that!" otherwise); same pick roll as above, lockpick skill-up, then the spot's `treasptr` group ("Who will take the treasure?", `_chests` bit). *Search* (`ovl_1131/1198`) does the same on type-3 spots without a pick ("%h finds nothing." when there is none). A spot with `sub ≠ 0` first runs V02 service 0x15 (trapped chest, `spells.md`).
- **Map flask** (`ovl_13c4`, locations with `pearlsw`): the *Map* command needs a Pearl (or asks to use a Blu Pearl); the pearl is dropped into the flask and the minimap is shown. With a plain Pearl there is a 1-in-10 roll where `h_dextrty ≤ RndCo(20)` shatters the flask ("The map flask shatters!", −1 Map Flask).

## World map (`P01`, region records `R32`–`R47`)

The world map is one 256×256 map; the party is always inside one of 16 **region records** (`_curreg`, `Rnn.MCV`, same 20-pointer `LOCTYPE` layout but several slots are reused — `tools/worldspots.py original` prints everything below):

| slot | content |
|---|---|
| `roomptr` | **features** `{x, y, pgmidx, rmid, type}` until `x == 0` (`ovl_0c1e`): mushroom patches (program 4), temples (`P09 D59`, ids 192–206, type 3), dungeon gates (`P09 D14` "A Gate", ids 208–215, type 4/20), the Oolau shrine (`P08 D36`) |
| `exitptr` | **town entrances** `{x, y, pgmidx, tx, ty}` until `x == 0`: stepping on it loads the town (`pgmidx` → PGM list → program 2 + D-file) at `(tx, ty)` |
| `locptr` | **spots** `LOCSPOT{x, y, pgmidx, rmid, a, b, c, ev, tx, ty}` until `0xFF` (`ovl_0c28`): `ev == 0xFE` always, else index of a `locevptr` list of `{event, ?}` pairs — the spot exists once any listed event bit is set (`ovl_0c64`). Carries the 16 **strongholds** (`P05 D19`, ids 0x5C–0x6B, the Assign destinations; "secure from all threats while inside"), the hunt (0x59, N. Misor 60,27) and track (0x53, S. Misor 62,47) schools, piers (`P05 D36` ids 1–4, `[9,0,0]`), teleportals (`P09 D61` ids 0xA9–0xB6) and event-gated towns (Demonspine 88,36 after event 4 or 8; the Tundra nomad town at one of four places by events 12/33) |
| `gwrds` | 8 **guard spots** `{x, y, ?}` (zero = none); `_grdsta` bit `region·8 + n` marks a cleared guard; `newsr` = the encounter group number for each of the 8 |
| `weathr` | 4 seasons × 4 `{threshold, weather, duration}` (`time_weather.md`) |
| `loctext` | 0 "A mushroom patch!", 1 "A port of ethereal travel!", 2–5 ship names |

`ovl_1070/1098` handle ship captains (`_curcap`, `_capsta`, `_capdays`, `_boatx/y`) — TODO.

### Mushroom patches (program `P04`, data `D04`, map `G00E00.MCM`)

30 patches (feature ids 0–29) across 14 regions; the item grown at patch `id` is `D04.gwrds[id]` (0x33 Sermin, 0x34 Gonshi, 0x35 Nift, 0x36 Mirget, 0x37 Luffin, 0x3C Loka — Turpin is never grown). The patch map is variant `_curter` (terrain under the party) of the 16 11×9 maps in `G00E00.MCM`. State: `_mushsta` (DS:7067, 32 bytes, one **nibble per patch**: even id = high nibble) = mushrooms left, 0–15, all 15 in a new game; **regrowth** +1 every 8th day (`_juldate & 7 == 0`, `P92 ovl_02cb`). Entering draws `count` mushrooms at the first `count` of 15 fixed positions (P04 file 0x88/0x97: x `[3,3,4,6,7,7,8,8,8,7,6,3,2,2,1]`, y `[2,1,1,1,1,2,2,3,5,7,7,6,6,5,4]`, placed with `_PlacePerson` so occupied cells shift); stepping on one asks "%h may pick %b %as" and gives `amount[kind]` = Sermin 6, Gonshi 4, Nift 3, Mirget 2, Luffin 3, Turpin 2, Loka 2 (file 0x72) to the acting member (`_IncObj`; a full pack refuses and the mushroom stays), then `count−1` is written back. Empty patch: "No more mushrooms are growing here."

## Still to extract
Town `spetbl` types other than 2/3 and the callers of `ovl_1926` (0x1082, 0x1105, 0x119E, 0x18CA); `spdoors` first/last bytes; lock types 2–5 and the `lkdata` 4-byte stride in P07; `P04`/`P05` (dungeon map programs: traps, pits, teleportals, mindstones); `P08` court scenes; `P09` engraved-word puzzles; the `notyet0` pointer.
