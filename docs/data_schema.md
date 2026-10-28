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
| `items.json` | item names by code (`_w_objects`, 0x00–0x5C) |
| `companions.json` | the 31 companions' starting `HERO` records from `R90.MCV` (index = `h_orinum` − 1, plain gold) |
| `p93text.json` | camp texts (P93 file 0x3D): 0 "Is everyone going to sleep?", 1 "%o will sleep.", … 8 "Camp activities are in progress." (`rules/camp.md`) |
| `p93.json` | `hunt` = `terrain[10]` (P93 file 0x03, by terrain class) and `weather[12]` (0x0D): signed hunting odds, −1 = impossible (`rules/camp.md`) |
| `exetables.json` | small EXE tables: `hungerhours[race]` (DS:3AA8), `nousetext[item]` (`_NoUse` comtxt number, DS:2D9A), `weathers` (names, `_w_weather` DS:424E), `lootvalues[item]` (DS:2E72, `economy.md`), `useall` (items whose *Use* asks "Is this order for everyone?", DS:8AE), `tod` = `words` (`_SetTxtToD` list, DS:41E0: morning … night) and `hour[24]` (TODWORDS, DS:38F2), `attribs[29]` (`_w_attrib` + `_w_skills`, DS:3AAE, by HERO offset − 13), `speltim[42]` (`_speltim` DS:2B8F, `_LrnTim`) |
| `conds.json` | `_w_conds`: 0 "OK", then names for bits 15…5 of `h_cond1<<8 \| h_cond2` (Dead … Tired); `_SumStat` shows the highest set bit |
| `p92text.json` | hireling payday texts: 0 "This has not been a profitable week…" (17:00 warning), 1 "Farewell, %o…" (leaving) |
| `p97.json` | P97: `texts` (file 0x17: 0 the King's refusal, 1 the hireling's offer, 2 " Dismiss %d anyway?", 3–6 dismissal replies), `events[npc]` = the event bit set on joining and cleared on dismissal (file 0x68E/0x69D) |
| `heroes.json` | the five new-game profiles A–E as `HERO` records (field names from `structs.h`; `h_gold` is `{hundreds, units}` here) |
| `npctypes.json` | what *Look* calls a person, by GEN/KNPC `type` (DS:2296: man, woman, wizard, …) |
| `commands.json` | command words (`_menucommands`: End, Quit, None, Yes, No, … Knock, … Pick …) |
| `p90.json` | trade tables: `haggle[item] = [step, div]`, `lots[item] = lot size` (`rules/economy.md`) |
| `p01.json` | world map: `terraintime[curter]` (14 entries: 10–13 are the following bytes, read for a swim), `weathertime[weather]` (signed: Clear/Overcast −1), `terrainenergy[curter]` (14, likewise), `swimweather[weather]` (0x2F6, `rules/skills.md` Swimming), `clothing[row][weather]` (rows Elvenspun…Furs, then none), `regions[16]` `{x0,y0,x1,y1}` (first containing rectangle = `_curreg`), `patchtiles[curter]` (mushroom-patch tileset, P01 0x36A), `patrols[128]` `[x, y]` start squares (P01 0x136, patrol n in region n >> 3), `respawn[16]` months (0x32A), `steps` = `dirs[8]`, `side1[8]`, `side2[8]` `[dx, dy]` (0x1790/0x17A0/0x17B0) and `order[10]` direction indexes for wandering (0x18B7) (`rules/encounters.md`, Patrols), `ships` = `weather[12]` signed sailing ticks added to 4 (0x28C), `rate[6]` coins a day (0x34A), `homex[6]`/`homey[6]` home ports (0x350/0x356) (`rules/ships.md`) |
| `combat.json` | `monsters[code − 5]` (`_monstats` row + `leader` rank, `undead`), `groups[n − 60]` `{count, m0..m3}`, `weapons[item − 9]` (`WEAPDATA` + `hitlist` races), `setupxy` (P81 0x162F), `maxtbl` (`_MaxSkill`), `ranges` x/y (P96 0x19/0x29), `guarddiff` (P01 0x33A), `d06` AI tables (`cast`, `crit`, `crit2`, `prey`, `gonshi`/`sermin`/`potion`, `counts`, `armor`, `dodge`, `prefs`), `loot` (P95 tables), `spells` (`names` DS:3EDC, `energy` `_enetbl`, `where` `_splocs`, `side` P94 TALIGN, `skill` SKLSPLS), `parley` (`texts` V06 table, `kins` `_w_kins`, `attitudes` `_w_attitudes`, `worth[race]` P96 0xB3F, `rolls` P96 0xB4B–0xB5B) — `rules/combat.md`, `encounters.md` |
| `p81.json` | new game: `texts` (P81 string table from 0x15, strings 0-39), `scenes` (string 40: the intro's lists of string numbers) — `rules/new_game.md` |
| `p07.json` | dungeon rooms: `texts` (P07 0x806, 15 strings), `trap` condition bits by `hrmid & 1`, `doorx`/`doory` (the four doors' squares) |
| `spots.json` | `ambush` ids/events (P02 0x1743/0x1749), `remarks` ids/events/locspecs (V02 0xBDB) |
| `p04.json` | mushroom patches, by kind = item − 0x33: `amount` picked per mushroom, `icon` (E00 frame); `x`/`y` the 15 growing places (`rules/locations.md`) |
| `p05.json` | service rooms (`rules/services.md`), lists indexed by room id − kind base: `leave[_rmtyp]` (room text asked on leaving with a pupil, 255 = comtxt 0x23); `inn.price` (0x40–0x47); `school` `skill`/`cost`/`days` (0x48–0x5A), `gain`/`cap[skill][race]` by skill; `job.trade` (0x6C–); `library` `subjects[lib]` (word indexes), `research`/`days`/`task` per subject, `lists[task]` (book string numbers), `texts` (the V05 book strings); `lodge` `mask`, `cost` |
| `p09.json` | special rooms (`rules/special_rooms.md`): `pieces[5]` teleportal piece items (0x4B) and `piecetiles[5]` their pedestal tiles (0x50), `altars[3]` world-temple altar tiles (0x3A), `icons[8]` god-icon name indexes by god (0x3D), `wake[8]` members checked for a missing blessing (0xC86), `offer[2]` Brennix / Somona (0x92), `texts[6]` P09's own strings (0xFB: altar, advice, elven prince) |
| `p91text.json` | small talk: `lines` (P91 file 0x7F) and `weather` `[weather, line]` pairs (`rules/dialogue.md`) |
| `p02text.json` | the town program's own texts (P02 file 0x67: locked doors, map flask, scrolls) |
| `sprites.json` | `columns`, `counts` per sheet, `npc[tile] = {start, frames}` — the E02 frames of NPC sprite id `tile` (the `tile` byte of GEN/KNPC records) |

## Location record

Always: `kind` (`level` = town or dungeon level, `room` = 11×9 interior, `region` = world-map region, `world` = D01), header fields `locnum roomno name lcharm mapsize[2] doorstn locdiff pearlsw greet[3]`, `pointers` (the 20 raw offsets), `tables` (each sub-table's raw bytes by `LOCTYPE` pointer name, empty when unused — lossless, for anything not decoded yet), `blocks` `[{block, tileset, x, y}]`, `words` (`gwrds`), `texts` (`loctext`), `doors` `[{x, y, pgm, id, type}]` (to the first `x == 0`), `pgms` `[{program, tileset, datafile, disk}]`, `exits` `[{x, y, pgm, tx, ty}]`.

Not for regions: `townsfolk` `[{x, y, type, tile, num}]`, `npcs` `[{x, y, type, tile, num, name, appear, disappear, ifevent, ifnevent}]`, `residents` (indexed by room id) `[{name, num, appear, disappear, ifevent, ifnevent}]`, `script` (the townsfolk conversation, `peopr`), `news` `[{npctype, event, text}]`. A script is `[{word, resp, cmds[{op: 'E'|'C', arg, alt} | {op: 'S', song}]}]` (`rules/dialogue.md`).

Rooms: `roommap` `{g, chunks}` = `maps[0]` and the chunk list (`formats.md`, *Room maps*, for which chunk a door uses); `exits`, `townsfolk` and `npcs` are **lists of lists**, one per room index (`id − boundary`, or entry 0 of a bank record); room exits add `datafile` (the town to return to).

Levels: `look` `[{x, y, text}]`, `spots` `[{x, y, type, d1, d2, d3}]`, `keydoor` `[{unused, x, y, newtile, text}]`, `hrooms` `[{id, group, reward, amount, map, xy[4]}]` (`rules/locations.md`).

Regions keep their reused slots (features, spots, guards, weather) in `tables`; see `rules/locations.md`, *World map*.
