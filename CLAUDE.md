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
- Data files (519 total), by extension — formats NOT yet decoded unless noted:
  - `MCM` (170) maps. `MnnEee.MCM` mostly 1766 B = `"**"` + 42×42 bytes. `Gnn`E00 are N×101 bytes (world-map strips?). A few M files 5042/5120 B.
  - `MCT` (64) tilesets: `Vnn` = VGA (66,310 or 33,542 B), `Enn` = EGA (16,896 B).
  - `MCV` (161) text/variable-length records with an offset table: `Dnn` NPC/dialog names, `Bnn` object names ("a plant", "a barrel"), `Cnn`, `Rnn`.
  - `MCO` (25) code overlays; `MCE` (12) screens; `MCC` (5) `E00/E01` large, unknown; `MCS` (9) save slots, `MCI` save index; `CMF`/`MID` music, `VOC` sfx.

## Tooling plan
- Ghidra (free, x86-16 real mode + decompiler) for `MC2.EXE` + overlays. Not installed yet (`brew install --cask ghidra`). No IDA on this machine.
- Boxer gamebox for runtime; DOSBox-X (`brew install --cask dosbox-x-app`) if we need a debugger.
- Python scripts in `tools/` for data-format parsing; validate every format guess by rendering/round-tripping real files.
