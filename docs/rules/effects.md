# Visual effects

Sources: FFFAR effect routines (file 0x37A2–0x3F68, read from the asm with `tools/dis.py`: Ghidra drops their register
arguments), P06 `ovl_1144`/`ovl_138c`/`ovl_143f` (missiles), and each caller below. Port: `web/src/fx.ts` (the
routines as frame lists on one queue), drawn by `View.draw` over the map.

## Primitives
- **Square → pixels** (FFFAR 0x3F59, P06 `ovl_142f`): window cell (x, y) → (4 + 4x, 8 + 16y), x in 4-pixel units, in
  the 11×9 map window.
- **Delay** `ovl_3bdf(n)` = `_delay(n << 6)`: n × 64 ms.
- **Icon sequence** `ovl_3b52(x, y, list, n, reps)`: for `reps` rounds, each E00 icon of the 0-terminated `list` is
  drawn on the square (`_movectile`), shown, held n × 64 ms and erased (`_EraMrk`).
- **Multi-square** `ovl_3caa(list, n, sound)`: every combatant slot whose stage (`_bangstg`, DS −0x6E2D) is ≤ 5 shows
  `list[stage]` on its square (`_bangx/_bangy`) and advances. One pass every n × 64 ms until every stage runs off the
  list. The sound plays on the passes where some stage is still ≤ 4. Stage 5 = nothing. Stage 0x20 → 4 and 0x1F → 0
  are used by the missiles' trail.
- **Colour flash** `ovl_3abe` → `_movectileFX`: redraws a figure's tile with an EGA XOR colour code (AL) and colour
  (AH); `_egaeffectstimer` sets how long (units not traced). The port blends the EGA colour AH over the figure's own
  pixels (difference).

- **Dissolve** `_MultiFX` (EXE 2709:4551, after `_MFXInit`; `_mfxtnum` the tile, `_mfxcoords` the pixel position,
  `_mfxcflag` 1 = draw the tile in, 0 = restore the background): `FFAWRK` visits the 256 pixels of the 16×16 square
  from 0 by `n → ((n + 1)·37 mod 257) − 1` (y = n >> 4, x = n & 15), one `EGAEFFECTSDELAY` (`_egaeffectstimer`) each;
  pixels of the background colour are skipped. With `_egaeffectsflag` 7 each written pixel takes the colour of a running
  counter (DS 0xDE1F, & 15) instead of its own: a rainbow sparkle. Flag 3 writes the real colours.

## The routines (INT 62h)
| routine | picture | sound | timing |
|---|---|---|---|
| `_Spef1(x, y)` 0x3F2F | icons 0x0D, 0x0E, 4 rounds | 10 before each frame | paced by the sound |
| `_Bong(x, y)` 0x3DF6 | icons 3, 4, 1 round | 10 before each frame | (no caller found) |
| `_Spef2` 0x37A2 | the target's tile flashed (AL, AH) = (0x0B, 7), (0x1C, 0x0C), (7, 8), (2, 0x0F), 3 times, then restored | — | timer 1500 |
| `_Spef3` 0x3827 | colours 0x0C, 9, 0x0D, 0x0F, 64 ms apart, then restored | — | timer 1000 |
| `_Spef3Single(xy, colour, tile)` 0x38C3 | one flash in the colour, then restored | — | timer 2500 |
| `_Spef4(colour, who)` 0x3904 | 4 × (flash in the colour, 192 ms, restore, 64 ms) | — | timer 1 |
| `_Spef5(xy)` 0x398A | icons 0x27–0x2A, 64 ms, 3 rounds | 15 | |
| `_Spef5_a(xy)` 0x39B9 | icons 0x27–0x2A, 192 ms, 2 rounds | 10 | |
| `_Spef6(xy)` 0x39EE | icons 0x22–0x26 (shrinking rings), 128 ms, 2 rounds | 11 | |
| `_Spef7(xy, who)` 0x3A1D | 10 `_MultiFX` frames of the figure (flag 7) | 16 | timer 200 |
| `_Bang(x, y, from)` 0x3AEE | icons 0x1D–0x21 from index `from`, 192 ms, 1 round | 3 | |
| `_AcidBang(xy)` 0x3B23 | icons 0x2A–0x27, 256 ms, 1 round | 3 | |
| `_InvertWindow(w, sound)` 0x3BF8 | XORs text window `w` (tables at 0x3750/0x3764/0x3778/0x378C), plays the sound, waits for it, XORs back | arg | the sound's length |
| `_MultiBang(sound)` 0x3C7E | multi-square, icons 6, 7, 8, 64 ms | arg | |
| `_MultiThing(sound)` 0x3C93 | multi-square, icons 0x2A–0x27, 320 ms | arg | |
| `_BigBang(x, y)` 0x3D91 | marks the 3×3 around the square inside the 11×9 window (centre stage 1, the rest 0), then `_MultiBang(3)` | 3 | |
| `FAR_ZAP` 0x3E88 | icon 0x54 stepped through 8 squares | 3 per square | (no caller found) |

## Missiles (P06 `ovl_1144`)
A missile of type AX walks a Bresenham line from the attacker. `ovl_138c` erases and redraws it on each square
(`ovl_042f`). The tile (`ovl_143f`):
- Type 0 (an arrow) is `_weaptiles` row 2 entry `keypad(CURDIR)`, i.e. E01 tile 17 + keypad, with P06 0xA3 mapping
  CURDIR 0–7 to keypad 4, 8, 6, 2, 7, 9, 3, 1. `_LoadFolks` loads E01 tiles 0–26 into `_weaptiles`, three rows of nine.
- Other types use the table at P06 file 0x1479: 1 fire 3, 2 acid 0x30, 3 → 0x33, 4 → 0x37, 5 → 0x36, 6 shatter 0x2F,
  7 → 0x0B, 8 → 0x0A. Types 1–4 cycle through the tile and the next two at each square (`ovl_1482`).

The missile stops on the first unwalkable or occupied square; `G_TILEXY` is where it stopped.

## Callers
| where | effect |
|---|---|
| P06 `ovl_050a`/`_05db`/`_06b7`, a Barg's blow that lands | sound 11, `_Spef2` |
| P06 shots | missile type 0 (an arrow) |
| Fireball (V06 `INT61_11`) | sound 2, missile 1, `_Bang` where it stopped |
| Shatter (`_10`) | sound 2, missile 6 |
| Acidball (`_12`) | sound 2, missile 2, `_AcidBang` where it stopped |
| Zefoar (`_04`) | missile 1, `_BigBang` at the impact |
| Zapall (`_03` → P06 `ovl_10a7`) | marks every target with a clear line, `_MultiBang(3)` |
| Destroy (`_1a`) | `_blobmap` from the target over the background (`INT61_25`, `_terriflag`); every square at stage blob + 0x14 through `_MultiBang` (0x1F wraps to 0, so the burst closes in on the target from 11 steps out); if it works, the target flashed (flag 0x1001) and sound 4; if it resists, stages 0x20 − blob (0x20 → 4, nothing): the burst spreads out from the target |
| Double, Summon (`_09`, `_0a`) | the new record's tile flashed (`_movectileFX`, flag 0xF01, timer 0x1D4C), sound 9, redrawn (flag 3) |
| Fear (`_0d`) | sound 10, `_Spef3` |
| Freeze (`_0e`) | sound 15, `_Spef3Single` colour 9 |
| Zofir (`_06`) | sound 15, `_Spef3Single` colour 0x0C |
| Courage (`_40`) | `_Spef6` |
| Betray (`_0f`) | sound 10, `_Spef7` |
| Forget (`_18`) | `_Spef5` |
| Timestop (`_1b`) | `_InvertWindow(0, 11)` |
| Disappear, Restsoul (`_14`, `_17`) | `_MultiFX` of the target, `_mfxcflag` 0 (out), flag 3, timer 6000 |
| Jump (`_16`) | `_MultiFX` with two entries: the figure out of its square and into the new one (flag 3, timer 0x1D4C) |
| `INT61_47`, `INT61_ff` | `_MultiFX` (not traced) |
| `INT61_42`, `ovl_27d0` | `_Bang` on the target |
| `INT61_60` | `_MultiBang(3)` |
| Resident spells (FFFAR `ovl_3228`/`ovl_3240`) | sound 10, `_Spef4` on each target in `G_zp_16`: Heal 10, Energy 0x0C, Shield 9, Zengrl 0x0C, Zishoxe 9 |
| V02 `INT60_09`, a refused step | `_MultiBang(0x17)` on the members whose `_bangstg` is 1 (a Pierce barrier: icons 7, 8) or 2 (Repel: icon 8); 5 (a wall) shows nothing |
| V02 `INT60_06`/`_07`, Pierce/Repel removing a barrier | `_Spef5_a` on the square |
| V02 `INT60_00`, Vision | `_Spef6` on the door found there |
| P07 `ovl_06c2`, the Dark Candle | `_Bang` at the reader |
| P08 `ovl_0d8e`, the Orb and the bird | sound 10, `_Spef6` at the user |
| Teleportals (P02 `ovl_151a` type-1 spot, P09 0xC58 pedestals) | the members' tiles into `_mfxtnum`/`_mfxcoords`, then `_movetileFX` with flag 6, timer 10000: the party dissolves out. The spot plays 0x14 first and sets `_mfxfadein` = 6; after the next map is drawn, P02 `ovl_0e9a` sees it, plays 0x14 and runs `_movectileFX` on the members' new squares (the party dissolves in) and clears it. P09 plays 0x14 after the fade and waits 500 ms; it sets `_mfxfadein` only when the destination's `curmpg` is 2, and every D61 row has 1 (the world map), so a teleportal room has no arrival effect. Port: `FX.teleport` (one 1 s pass), `main.ts` *jump*, *fade*. |
| P08 the ending (L_0772) | `ovl_187e` = `_InvertWindow(0, 3)`; 0x1890 (`ovl_191b`) a person appears: four `_MultiFX` passes with flag 7 (timer 4000), then one with flag 3; 0x18B4 (`ovl_18cd`) a person vanishes: one pass, flag 3, timer 60000. Zakhad appears after the flash, vanishes when Jemil banishes him, then Zidoni appears. The doom (`ovl_0c41`): for each member from slot 5 down, then the room's first NPC, `0x1986`: the blob map around them (`ovl_1a52` clears the stages to 5; `ovl_1a8a` spreads 8-way from the square with `ovl_1b13`, whose wall test `ovl_1b64` is an empty stub, so the blob is the Chebyshev distance), stages blob + 0x14 through `_MultiBang(0)` as in Destroy, the figure flashed (flag 0x1001), thunder (29), the square restored |
| P09 `ovl_123e`, a god's thunder | `_Bang(x, y, 0)` on each member |
| P09 `FUN_1000_db88`, a god's blessing | `_Spef1` at a member whose first stat in the god's list rises (`local_4` still at the list's start, `_IncSta` accepted) |
| P96 `ovl_05fd`, the Doombeasts and their images at set-up | `_MultiThing(9)` |

## Port
`fx.ts` builds each routine as frames, each with icons, tints, an invert flag, a duration and an optional sound. They
play on one queue, so effects run in order and do not block the game logic. The monster phase waits for the queue
before each action.

Timings the original takes from `_egaeffectstimer` are assumed:
- Spef2: 80 ms a frame;
- Spef3Single: 400 ms;
- Spef7: 66 ms a frame.

The doom's and Destroy's flash is Spef3Single in white. `_MultiFX` in combat is one 600 ms pass (timers 6000 and 0x1D4C
assumed alike); while a figure dissolves in, its square's own drawing is held back (`Overlay.hide`).
Ending timings: the appear passes 300 ms each plus 600 ms, the vanish 2.5 s.

