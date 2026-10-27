# Code overlays (`P*.MCO`, `FFFAR.MCO`) and how to read them

`MC2.EXE` is only the engine; most scripted game logic lives in 22 code overlays `Pnn.MCO` that the engine swaps into a 16 KB buffer (`FFOVL` module, Ghidra segment `1CA8`). Loaded by `_LoadOvly(num, offset, buf)`:

- offset 0 → location program (`_LocPgm` = `1CA8:0000`), overlay number recorded in `_locovl`/`__curmpg`
- offset 0x2000 → room program (`_RoomPgm` = `1CA8:2000`), recorded in `_roomovl`
- overlay 0x51 is special-cased to 16 KB; others sized by `_AreaSize`.

`FFFAR.MCO` (0x5000 bytes) is loaded once at startup into a malloc'd segment (`_farrtn`) and uses the same convention.

`V*.MCO` ("variable overlays", `_LoadVvly`) are **code+data modules reached through software interrupts**: `Vnn` is loaded into `_lvarbuf` (0xF000 bytes, location) or `_rvarbuf` (0x6000, room) and pointer-fixed by `_AdjVFile` (header: `jmp entry`, u16 reloc count at +3, u16 reloc offsets from +5). `_InstVarVecs` stores the three buffer far pointers into **interrupt vectors 60h = `_lvarbuf`, 61h = `_rvarbuf`, 62h = `_farrtn`** (`FFFAR.MCO`), so `INT 60h/61h/62h` with a function number in AH jump straight to the V-file / FFFAR entry. The entry is an AH dispatcher (`cmp ah,N / call / jmp epilog`) whose epilog copies the handler's carry into the saved flags. `_DoACmbt` loads `V06` as the room V-file, so **INT 61h in combat = V06** (combat spell effects and monster AI; `ghidra/int61_v06.json`, `decomp/overlays/V06.c`); `P02` (town) calls INT 60h = `V02`.

## Binary layout of a P overlay
- Starts with a jump table: consecutive 3-byte `JMP` instructions, one per entry point (`P90` has 3). `_LocPgm(n)` enters at entry *n*.
- Raw code, no header, no relocations. Code is position-dependent on segment `1CA8` only through near calls.
- Overlay-private data and tables are addressed as `CS:[DI+n]` with **DI = load offset − 0x100** (`_FarLocEntry`: `lea di,[0FF00h]` for the location half at offset 0, `_FarRoomEntry`: `lea di,[1F00h]` for the room half at 0x2000; a V-file computes `di = buffer.off − 0x100` itself). So **`OV_0xNNN` in the decompiles = file offset NNN − 0x100**, and jump tables stored as `cs:[di+...]` hold code offsets + 0x100 (P94's spell-predicate table at file 0x179C is one).

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
- `_FarLocEntry` / `_FarRoomEntry` (`FFOVL` 0c04:01a4 / 01f4, stored in `_locvec` / `_roomvec`) are the EXE-side trampolines: they save the return address in `_farreturn[_farstackptr]`, set DI as above, and far-call `0CA8:(base+CX)`. Overlays call each other's entries with `CX = entry offset` through these vectors (`ovl_07da` in V06 = `lcall [_roomvec]`).
- Where the EXE pokes IVT 3E/3F is still unlocated (not via `_setvect`). The values are inferred from the symbols and verified by the resulting semantics.

## Tooling
1. `tools/ovl_batch.sh` imports every `P*.MCO` into the Ghidra project at `1CA8:0000`, runs `DumpOverlay.java` (entry points, outgoing-call census) and `DecompileAll.java` → `out/decomp/Pnn_all.c`.
2. `tools/ovl_pp.py out/decomp/Pnn_all.c > decomp/overlays/Pnn.c` (set `OVL_SEG=3000` for `V06`, imported at `3000:0000`) rewrites the decompiler output: `EXE_<name>(...)` for vector calls, `G_<global>` for `[SI+n]`, `OV_0xNNN` for overlay-private data, `ovl_XXXX` for internal functions.

Example (`P90`, entry 0): builds a message with `EXE_AddScrap`, prints it with `EXE_PrtScrap`, asks `EXE_SetYN`, then checks `heroptr[curpla]->h_gold` (`+0xCC`) against `price*quantity` before `EXE_DecObj`/`EXE_IncObj` move inventory — a shop/trade dialogue.

3. `tools/dis.py FILE start[:end] ...` — capstone 16-bit disassembly of raw byte ranges (handy where Ghidra's decompile of register-passed arguments is lossy; most V06 handlers were read this way). `tools/exesym.py <file offsets>` names the TDInfo function containing an `MC2.EXE` file offset.
