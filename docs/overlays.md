# Code overlays (`P*.MCO`, `FFFAR.MCO`) and how to read them

`MC2.EXE` is only the engine; most scripted game logic lives in 22 code overlays `Pnn.MCO` that the engine swaps into a 16 KB buffer (`FFOVL` module, Ghidra segment `1CA8`). Loaded by `_LoadOvly(num, offset, buf)`:

- offset 0 → location program (`_LocPgm` = `1CA8:0000`), overlay number recorded in `_locovl`/`__curmpg`
- offset 0x2000 → room program (`_RoomPgm` = `1CA8:2000`), recorded in `_roomovl`
- overlay 0x51 is special-cased to 16 KB; others sized by `_AreaSize`.

`FFFAR.MCO` (0x5000 bytes) is loaded once at startup into a malloc'd segment (`_farrtn`) and uses the same convention.

`V*.MCO` ("variable overlays", `_LoadVvly`) are **data**, not code: 0xF000 bytes into `_lvarbuf` (location) or 0x6000 into `_rvarbuf` (room), pointer-fixed by `_AdjVFile`. Not yet decoded.

## Binary layout of a P overlay
- Starts with a jump table: consecutive 3-byte `JMP` instructions, one per entry point (`P90` has 3). `_LocPgm(n)` enters at entry *n*.
- Raw code, no header, no relocations. Code is position-dependent on segment `1CA8` only through near calls.
- Overlay-private data lives past the end of the file at `CS:1F00+` (zero-filled buffer), addressed as `CS:[DI+n]`.

## Calling convention (every overlay function starts with this prolog)
```
xor ax,ax ; mov es,ax            ; ES = 0 (interrupt vector table)
mov di,4FCh ; mov bx,es:[di]     ; BX = IVT[3Fh].offset  -> DS:25E6 (_BSSstart), the vector table
sub di,4    ; mov ax,es:[di]     ; AX = IVT[3Eh].offset
add ax,1F00h ; mov di,ax         ; DI = overlay data base
mov si,[bx]                      ; SI = [DS:25E6] = 0x4CF6 = BSS start: globals are [SI+disp]
mov [si+8D76h],bx                ; _savebx = BX
```
- **EXE calls**: `CALLF [BX+slot]` — slot table in `docs/overlay_api.md` (285 named functions, slot 4 = `_rdfile`). The callee receives the saved BX as a bogus first "argument"; real arguments follow.
- **Globals**: `[SI+disp]` → DS offset `disp + 0x4CF6`. All resolve to named BSS variables (`_curpla`, `_heroptr`, `_comtxtptr`, `_events`, …).
- Where the EXE pokes IVT 3E/3F is still unlocated (not via `_setvect`; probably assembler code in `CRAFTASM`/`FFA`). The values are inferred from the symbols and verified by the resulting semantics.

## Tooling
1. `tools/ovl_batch.sh` imports every `P*.MCO` into the Ghidra project at `1CA8:0000`, runs `DumpOverlay.java` (entry points, outgoing-call census) and `DecompileAll.java` → `out/decomp/Pnn_all.c`.
2. `tools/ovl_pp.py out/decomp/Pnn_all.c > out/decomp/Pnn_pp.c` rewrites the decompiler output: `EXE_<name>(...)` for vector calls, `G_<global>` for `[SI+n]`, `OV_0xNNN` for overlay-private data, `ovl_XXXX` for internal functions.

Example (`P90`, entry 0): builds a message with `EXE_AddScrap`, prints it with `EXE_PrtScrap`, asks `EXE_SetYN`, then checks `heroptr[curpla]->h_gold` (`+0xCC`) against `price*quantity` before `EXE_DecObj`/`EXE_IncObj` move inventory — a shop/trade dialogue.
