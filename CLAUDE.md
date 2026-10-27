# The Magic Candle II — reverse engineering project

Goal: fully document the game's rules/data formats, with an eye to a faithful port (web/TS/WASM or native).

## Layout
- `original/` — pristine, read-only copy of the game dir from `~/DOS Games/Mc 2.boxer/C.harddisk/mc2/` (Boxer gamebox; run the game by opening that gamebox). Never edit; copy elsewhere to experiment.
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
- Data formats: see `docs/formats.md` (single source of truth). Status 2026-10-27: VGA/EGA tilesets **done**; map blocks **150/170 render**; locations (`D` files) compose blocks into full maps (`tools/loc.py original out/locs`) — world map + all towns/dungeons render (`.venv/bin/python -I tools/render_all.py original out/maps`); open: `E80` maps have no tileset, `G*` files are not maps.
- Render anything to check a hypothesis: `tools/render.py tileset|map ...`. Guess a grid width with `tools/rowwidth.py FILE:offset`.

## Tooling plan
- Ghidra 12.2 installed via `brew install ghidra` (formula, not cask): `ghidraRun`; headless at `$(brew --prefix ghidra)/libexec/support/analyzeHeadless`. No IDA on this machine.
- Boxer gamebox for runtime; DOSBox-X (`brew install --cask dosbox-x-app`) if we need a debugger.
- Python scripts in `tools/` for data-format parsing; validate every format guess by rendering/round-tripping real files.
