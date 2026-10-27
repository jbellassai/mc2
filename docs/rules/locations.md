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
Companions captured earlier are stored as assignment records with task 0x65 at this location/room/hroom (`_AssignedHere` compares `as_loc/as_room/as_hroom`). On entry each such record is cleared, the companion is placed at (2,4) and says "Many thanks for the rescue!"; four specific captives (P07 table @0x56A) also set an event bit. Leaving clears their `_npcsta` bit so they re-appear per the normal placement rules (`npcs.md`).

## Town searches (`P02`, *Search* command)
At a `spetbl` spot of type 2/3: same pick formula as chests (`dex/2 + lockpick` vs d100, failure breaks a Pick), lockpick skill-up, then the spot's `treasptr` group lists `{item, amount}` pairs; "%h will take…" picks a hero (`HeroSel`) and sets the spot's bit in `_chests`. A `sub ≠ 0` spot first runs the V02 service (trap).

## Still to extract
Town `spetbl` types other than 2/3 and the callers of `ovl_1926` (0x1082, 0x1105, 0x119E, 0x18CA); `spdoors` first/last bytes; lock types 2–5 and the `lkdata` 4-byte stride in P07; `P04`/`P05` (dungeon map programs: traps, pits, teleportals, mindstones); `P08` court scenes; `P09` engraved-word puzzles; the `notyet0` pointer.
