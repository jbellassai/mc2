# The Magic Candle II — reverse engineering project

Goal: fully document the game's rules/data formats, with an eye to a faithful port (web/TS/WASM or native).

## Layout
- `original/` — pristine, read-only copy of the installed game directory (v2.00 patch, see below). Never edit; copy elsewhere to experiment. Run the game in DOSBox or a Boxer gamebox.
- `tools/` — analysis scripts. Python via `.venv/bin/python -I` (python-idb installed).
- `docs/` — findings: file formats, game rules, decisions, handoffs.

## What we know (verified 2026-10-27)
- Version 2.00 "VGA only, mouse" patch (see `original/Readver2.txt`, `README.TXT`). Publisher Mindcraft, 1991.
- `MC2.EXE` 323,931 bytes, 16-bit real-mode DOS MZ, **Borland C++ 1991**. Uses Creative CTVDSK driver (VOC playback).
  `MC2BLAH.EXE` = same file with 3 bytes changed ("uit"→"UIT" at 0x197C7); ignore.
- Code is split: EXE + 25 `*.MCO` **code overlays** (`P90.MCO` starts with a jmp table, `FFFAR.MCO` starts with `push bp; mov bp,sp`). Any disassembly must load overlays too.
- `MC2.idb` (IDA 6-era, June 2013) is auto-analysis only: 645 funcs, 0 user names/comments. No value; gitignored.
- **`MC2.EXE` contains full Borland TDInfo debug symbols** (v3.16, appended after the load module): 29 modules, ~1000 named functions, ~2000 data labels, 246 typedef'd structs with member names. `tools/tdinfo.py` parses it; `tools/tdinfo_export.py` writes `docs/symbols.txt`, `docs/structs.h`, `ghidra/symbols.tsv`. Overlays (`*.MCO`) have no symbols.
- Ghidra project: `ghidra/MC2.gpr` (gitignored, regenerate: import `original/MC2.EXE` with `x86:LE:16:Real Mode`, then run `ghidra/scripts/ApplyTdinfo.java ghidra/symbols.tsv` headless). TDInfo segment + 0x1000 = Ghidra segment.
- Data formats: see `docs/formats.md` (single source of truth). Status 2026-10-27: VGA/EGA tilesets **done**; map blocks **150/170 render**; locations (`D` files) compose blocks into full maps (`tools/loc.py original out/locs`) — world map + all towns/dungeons render (`.venv/bin/python -I tools/render_all.py original out/maps`); open: `E80` maps have no tileset, `GnnE00.MCM` = 16 × 11×9 mini-maps (`docs/formats.md`).
- Render anything to check a hypothesis: `tools/render.py tileset|map ...`. Guess a grid width with `tools/rowwidth.py FILE:offset`.

- Overlays (`P*.MCO`): mechanism in `docs/overlays.md`, API table `docs/overlay_api.md`, roles `docs/overlay_index.md`. Readable decompiles committed under `decomp/overlays/` (regenerate with `tools/ovl_batch.sh` + `tools/ovl_pp.py`). Full EXE decompile: run `DecompileAll.java` (10 MB, kept in `out/`, not committed).

- Game rules: `docs/rules/*.md` (combat, spells, time_weather, npcs, items, economy, dialogue, camp, locations, skills, assignments, services, special_rooms, quest_scenes, encounters, ships, new_game), each citing the decompiled source. FFFAR INT 62h dispatch: `ghidra/fffar_dispatch.json`, `ghidra/int62.json`; combat INT 61h = `V06.MCO`: `ghidra/int61_v06.json`, `decomp/overlays/V06.c`; town INT 60h = `V02.MCO` (`ghidra/int60_v02.json`, `decomp/overlays/V02.c`, Ghidra base 3100), `V05.MCO` (3200). `tools/vdispatch.py` maps a V-module's AH services.
- Saves `FFSAVx.MCS` = raw DS image from 0x4CF6 (`_startsvdta`); parse globals straight from them. Location sub-tables: `tools/locdump.py original out/locs` (per-location NPC/room/text dump + `npcs.txt`). Conversation files `Cnn.MCV` (NPC n → C(n>>3) slot n&7): `tools/convdump.py original` (trade skill, shop prices, gift quests); `tools/talkdump.py original out/talk` (every keyword → response tree, P91 script format); `tools/events.py original decomp/overlays > docs/events.md` (event-bit cross-reference); `tools/doors.py original` (every town door → overlay, room D-file, room id; `pgmnum` n = `P0n.MCO`, P06 = dungeon level program whose rooms run P07).
- Gotchas: `ROOM.pgm` is an index into the location's PGM list, not an overlay number; room D-files (D05–D18…) are not towns, `locdump` mis-parses their room/pgm rows but their `loctext` is right. `OV_0xNNN` in decompiles = file offset NNN−0x100 (DI = load offset − 0x100). FFFAR runs 4 bytes above its file image: an absolute `cs:[0xNNNN]` in `FFFAR.c` is file offset NNNN−4 (verified on its string table). Ghidra's decompile drops register-passed args in overlay code; read the asm with `tools/dis.py` for formulas. `echo ====` breaks in zsh (`=word` expansion).

## Tooling plan
- Ghidra 12.2 installed via `brew install ghidra` (formula, not cask): `ghidraRun`; headless via `analyzeHeadless` (under Ghidra's `support/`). No IDA.
- DOSBox/Boxer for runtime; DOSBox-X if we need a debugger.
- Python scripts in `tools/` for data-format parsing; validate every format guess by rendering/round-tripping real files.
