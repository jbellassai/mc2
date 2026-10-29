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
| Destroy (`_1a`) | `_MultiBang` on the marked record |
| Fear (`_0d`) | sound 10, `_Spef3` |
| Freeze (`_0e`) | sound 15, `_Spef3Single` colour 9 |
| Zofir (`_06`) | sound 15, `_Spef3Single` colour 0x0C |
| Courage (`_40`) | `_Spef6` |
| Betray (`_0f`) | sound 10, `_Spef7` |
| Forget (`_18`) | `_Spef5` |
| Timestop (`_1b`) | `_InvertWindow(0, 11)` |
| Disappear, Jump, Restsoul (`_14`, `_16`, `_17`), `INT61_47`, `INT61_ff` | `_MultiFX` (not decoded) |
| `INT61_42`, `ovl_27d0` | `_Bang` on the target |
| `INT61_60` | `_MultiBang(3)` |
| Resident spells (FFFAR `ovl_3228`/`ovl_3240`) | sound 10, `_Spef4` on each target in `G_zp_16`: Heal 10, Energy 0x0C, Shield 9, Zengrl 0x0C, Zishoxe 9 |
| V02 `INT60_09`, a refused step | `_MultiBang(0x17)` on the members whose `_bangstg` is 1 (a Pierce barrier: icons 7, 8) or 2 (Repel: icon 8); 5 (a wall) shows nothing |
| V02 `INT60_06`/`_07`, Pierce/Repel removing a barrier | `_Spef5_a` on the square |
| V02 `INT60_00`, Vision | `_Spef6` on the door found there |
| P07 `ovl_06c2`, the Dark Candle | `_Bang` at the reader |
| P08 `ovl_0d8e`, the Orb and the bird | sound 10, `_Spef6` at the user |
| P08 `ovl_187e`/`_18cd`/`_191b`, Zakhad | `_InvertWindow(0, 3)`, `_MultiFX` (not built) |
| P09 `ovl_123e`, a god's thunder | `_Bang(x, y, 0)` on each member |
| P09 `FUN_1000_db88`, a god's blessing | `_Spef1` at a member (the condition is not traced) |
| P96 `ovl_05fd`, Doombeast images vanishing | `_MultiThing(9)` |

## Port
`fx.ts` builds each routine as frames, each with icons, tints, an invert flag, a duration and an optional sound. They
play on one queue, so effects run in order and do not block the game logic. The monster phase waits for the queue
before each action.

Timings the original takes from `_egaeffectstimer` are assumed:
- Spef2: 80 ms a frame;
- Spef3Single: 400 ms;
- Spef7: 66 ms a frame.

Not built:
- `_MultiFX` (Disappear, Jump, Restsoul, Zakhad);
- the gods' blessing `_Spef1`;
- the Doombeast images.
