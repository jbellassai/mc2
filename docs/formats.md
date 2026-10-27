# Magic Candle II — data file formats

Status legend: **confirmed** = parsed and visually/round-trip verified on all files; **partial** = works on most files, exceptions listed; **unknown** = not yet decoded.

All integers little-endian. Tiles are 16×16 pixels. Reference parser: `tools/mc2fmt.py`; renderer: `tools/render.py`, `tools/render_all.py`.

## `Vnn.MCT` — VGA tileset (confirmed, 25 files)

| offset | size | meaning |
|---|---|---|
| 0 | 768 | palette: 256 × (r,g,b), 8-bit values (VGA 6-bit ×4, e.g. `a8`, `fc`) |
| 768 | 2 | magic `0x0108` (unknown meaning, constant) |
| 770 | 2 | tile count N (256 for V01, 128 for all others) |
| 772 | 2 | tile width, height = 16, 16 |
| 774 | N×256 | tiles, each 256 bytes of 8-bit palette indices, row-major |

File size = 774 + 256·N exactly (66,310 or 33,542). No per-tile metadata; passability etc. must live elsewhere.

## `Enn.MCT` — EGA tileset (confirmed structure, 38 files, 16,896 B each)

| offset | size | meaning |
|---|---|---|
| 0 | 256 | 128 × uint16 tile offsets, relative to byte 256; always 0,130,260,… |
| 256 | 128×130 | tiles: 2-byte header `08 10` (8 bytes/row, 16 rows) + 128 bytes of 4bpp pixels (high nibble = left pixel) |

Rendered with the standard 16-colour EGA palette the tiles look right. Not needed for the port (VGA is the target) but documents the 2.00 "VGA only" split: E files are leftover from the original release.

## `*.MCM` — tile maps (partial, 170 files)

Naming: `M<map>E<set>.MCM` or `G<n>E00.MCM`. For `M` files the `E<set>` number selects the tileset `V<set>.MCT` — **verified by rendering** for sets 01, 02, 03, 23, 60–67, 92, 93 (148 maps render as coherent islands, towns, dungeons, strongholds).

Layouts:

| header | body | files | notes |
|---|---|---|---|
| `**` (0x2A2A) | 42×42 bytes | 150 | tile index per cell, row-major, top-left origin |
| `**` | 84×60 bytes | 4 (`M01/07/11/14E93`) | strongholds; dims not in file, inferred from size |
| `54 3C` (=84,60) | 84×60 bytes + 78 junk bytes | 1 (`M07E65`) | header is literal width,height; trailer looks like an uninitialised buffer |

Cell value = tile index into the tileset (0–127, or 0–255 for set 01). No layers, no flags in the file.

The repeated `**` marker is suspicious: 0x2A = 42. It may be a `(w,h)` header that happens to equal the map size, in which case the E93 files' header is wrong/ignored and the engine takes dims from a table. **To settle in Ghidra**: find the MCM loader and the per-map dimension source.

### Unresolved
- **`MxxE80.MCM`** (6 files, 42×42, `**` header): no `V80`/`E80` tileset exists. Cells are dominated by tiles 121, 49, 104, 31, 70 with low spatial coherence; content is *not* a function of the matching `E01` map (conditional entropy barely drops). Rendering with every VGA tileset gives nothing clean (`V92` least bad). Hypotheses: a non-visual layer (encounters/objects), or a tileset selected by code. Needs the loader.
- **`Gnn E00.MCM`** (14 files): N rows of `0x0B` + 100 bytes, no `**`; `G04E00` is 1766 B but has no `**` and row width 101 by autocorrelation. Rows have *no* vertical coherence → not a 2-D map. Possibly a table of prefab strips / world-map rows / something else. Unknown.

## Other extensions (unknown)
`MCV` text with offset table (D=NPC names, B=object names, C, R), `MCO` code overlays, `MCE` screens, `MCC` (`E00`, `E01` large), `MCS`/`MCI` saves, `CMF`/`MID` music, `VOC` sfx.
