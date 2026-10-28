# Data pack schema (decision 1)

Built by `.venv/bin/python -I tools/export_json.py original out/pack`; never commit or publish the output. The engine reads only this. Byte strings are lowercase hex; lists are in file order; field names follow `docs/structs.h` where one exists. Meanings live in `docs/formats.md` and `docs/rules/*.md`.

| file | content |
|---|---|
| `locations/<id>.json` | one location record (below). `<id>` = `Dnn` (plain file), `Dnn_rr` (entry `rr` of a LOCTYPE bank = room id `rr`), `Rnn` (world region) |
| `blocks.json` | `{"MbbEtt": hex(42×42 tile ids)}` — map blocks (`formats.md`, *Locations are mosaics*) |
| `rooms.json` | `{"Gnn": [hex(11×9 tile ids) per chunk]}` — room interiors (*Room maps*) |
| `tilesets/Vnn.png` | 16 tiles per row, 16×16 px, opaque |
| `tiledata/Bnn.json` | `names`, `nameindex` (per tile), `walkable`, `walkable_los` (tile ids), `anim`/`doors` (hex, raw), `colors` (minimap colour per tile) |
| `sprites/E0n.png` | creature tile *k* at cell *k*, 32 per row, 16×16 RGBA (colour 2 = transparent); E00 heroes/companions, E01 combat (weapons, monsters), E02 town NPCs, E03 companions from party index 0x18 |
| `conversations/Cnn.json` | `texts`, `words`, `slots[8]` = `{script, gifts[{item, min, fewer, enough, event}], shop[{item, pays, charges}], greet, bye, skill, nobuy, unknown}` (`formats.md`, *Cnn.MCV*; NPC *n* = file `n >> 3`, slot `n & 7`) |
| `comtxt.json` | the EXE's common message texts, message *n* at index *n* |
| `sprites.json` | `columns`, `counts` per sheet, `npc[tile] = {start, frames}` — the E02 frames of NPC sprite id `tile` (the `tile` byte of GEN/KNPC records) |

## Location record

Always: `kind` (`level` = town or dungeon level, `room` = 11×9 interior, `region` = world-map region, `world` = D01), header fields `locnum roomno name lcharm mapsize[2] doorstn locdiff pearlsw greet[3]`, `pointers` (the 20 raw offsets), `tables` (each sub-table's raw bytes by `LOCTYPE` pointer name, empty when unused — lossless, for anything not decoded yet), `blocks` `[{block, tileset, x, y}]`, `words` (`gwrds`), `texts` (`loctext`), `doors` `[{x, y, pgm, id, type}]` (to the first `x == 0`), `pgms` `[{program, tileset, datafile, disk}]`, `exits` `[{x, y, pgm, tx, ty}]`.

Not for regions: `townsfolk` `[{x, y, type, tile, num}]`, `npcs` `[{x, y, type, tile, num, name, appear, disappear, ifevent, ifnevent}]`, `residents` (indexed by room id) `[{name, num, appear, disappear, ifevent, ifnevent}]`, `script` (the townsfolk conversation, `peopr`), `news` `[{npctype, event, text}]`. A script is `[{word, resp, cmds[{op: 'E'|'C', arg, alt} | {op: 'S', song}]}]` (`rules/dialogue.md`).

Rooms: `roommap` `{g, chunks}` = `maps[0]` and the chunk list (`formats.md`, *Room maps*, for which chunk a door uses); `exits`, `townsfolk` and `npcs` are **lists of lists**, one per room index (`id − boundary`, or entry 0 of a bank record); room exits add `datafile` (the town to return to).

Levels: `look` `[{x, y, text}]`, `spots` `[{x, y, type, d1, d2, d3}]`, `keydoor` `[{unused, x, y, newtile, text}]`, `hrooms` `[{id, group, reward, amount, map, xy[4]}]` (`rules/locations.md`).

Regions keep their reused slots (features, spots, guards, weather) in `tables`; see `rules/locations.md`, *World map*.
