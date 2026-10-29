# Ships and captains

Sources: `P01.MCO` (world-map program: `ovl_0cb2` step handler @0xD7D–0xF3B, `ovl_0f5c/0f95/0fcc` hire and payment, `ovl_1070` boat lookup, `ovl_1098/126a` captain name, `ovl_1349` conch, `ovl_15e4` per-step state machine, `ovl_1664` voyage-home days), `P92.MCO` (`ovl_040d` daily countdown, `ovl_0447` Amos), EXE `_ShowMap` (boat sprite), `_CapAtLiberty`; texts from any `Rnn.MCV` region record (`loctext` 2–0x16, 0x23–0x27, 0x29–0x2C; all 16 regions carry the same strings).

There is no ship the party owns. Six independent captains sail the world map; the party hires one by the day, sails it like a vehicle, and leaves it anchored or sends it home.

## Data

Saved state (all in the save image, see `formats.md`):

| global | DS | meaning |
|---|---|---|
| `_capsta[6]` | 6D53 | captain state (below) |
| `_boatx[6]`, `_boaty[6]` | 6D59, 6D5F | world-map position of each boat |
| `_sailsw` | 6D65 | 1 while the party is aboard |
| `_curcap` | 6D66 | index of the boat the party is on, 0xFF ashore |
| `_capdays[6]` | 6D67 | days: credit left (states 1, 5) or days until the boat is home (state 0) |
| `_capcost` | 6D6D | unused |

Captains (index = `_capsta` slot; rate table P01 file 0x34A, home port x/y P01 file 0x350/0x356; names are region text 9+i, ship names 2+i):

| i | captain | ship | coins/day | home port (world x,y) | nearest place |
|---|---|---|---|---|---|
| 0 | Garlin | Destiny | 20 | 33,58 | Oshcrun I. (Telermain) |
| 1 | Martin | Red Shark | 45 | 118,37 | The Throat (Ussa) |
| 2 | Amos | Fortune | 15 | 116,35 | The Throat (Ussa) |
| 3 | Turgut | North Star | 25 | 46,61 | S. Misor |
| 4 | Pavlos | Champion | 35 | 238,55 | Rhon |
| 5 | Kuhna | Misty | 40 | 166,88 | Sariss (Wanasol) |

Private, not saved (P01 overlay data): `OV_0x1c5` days just bought, `OV_0x1c6` passage mode (0 paid, 1 working for passage, 2 "time is up" prompt already shown), `OV_0x1b3` text to print after the move (0x0F welcome / 0x24 ready to sail).

## Captain states (`_capsta`)

| state | meaning | `_capdays` |
|---|---|---|
| 0 | sailing home, boat not on the map | days until home; at 0 → 3 |
| 1 | anchored, waiting for the party | prepaid days; at 0 → 2 |
| 2 | waiting expired (transient) | → state 0 with days = voyage home |
| 3 | at home port, available for hire | — |
| 4 | hired but credit ran out while the party is aboard | 0 |
| 5 | party aboard | credit; at 0 → 4 |
| 6, 7 | Amos only: theft pending / theft done (see below) | |

New game: every captain is in state 3 at home (a fresh save shows `_capsta = 3×6`; the first world-map step copies the home coordinates into `_boatx/y`).

**Daily (`P92 ovl_040d`, at the day change):** for each captain, `if capdays > 0: capdays -= 1`; then if `capdays == 0`: state 0 → 3, 1 → 2, 5 → 4 (other states unchanged).

**Every world-map step (`P01 ovl_15e4`, also on entering the world map):**
- state 2 → state 0, `capdays = voyage_home(i)`;
- state 3 → `boatx/y[i] = home[i]` (so a docked boat is always drawn at its port);
- state 4 and passage mode ≠ working → passage mode = 2 and run the *time is up* dialogue;
- state 7 → print "All the party's coins have been stolen! Captain Amos promises to look into the matter." and go to state 5.

`voyage_home(i)` (`ovl_1664`) = `(max(dx,dy) + (min(dx,dy)+2)/4) >> 4` with `dx,dy` = |boat − home| (same Chebyshev-ish formula as companion travel in `assignments.md`; a boat anchored 40 tiles from port is back in 2 days, saturating at 255/16).

A boat is drawn on the world map (EXE `_ShowMap`, sprite 0x12) whenever its state ≠ 0 and it is inside the 11×9 view.

## Boarding and hiring

Moving onto a tile that is not walkable on foot (`_ChkWlk == 0`) and is not a town entrance: if some boat with state ≠ 0 stands there (`ovl_1070`), it is boarded, otherwise the swim rule applies (`skills.md`, swim).

- State 1 (the party's own anchored boat): board at once; after the move "Captain *N* welcomes %h on board the '*ship*'" (text 0x0F). Remaining credit continues.
- Any other state (3 in practice): "Captain *N* says his ship, the '*ship*,' is available for hire. Will %h hire her?" (0x23). No → stay ashore. Yes → **buy days** (below); cancelling leaves the party ashore. Success sets `capdays = days`, then "says the '*ship*' is ready to sail" (0x24).
- Boarding sets `_sailsw = 1`, `_curcap = i`, state 5, passage mode 0; hiring **Amos (i = 2)** sets state 6 instead.

**Buy days (`ovl_0fcc`)**, payer = acting member `_curpla`:
1. "The cost, he says, is *rate* coins a day. How many days?" — `GetNum(0..99)`; 0 cancels.
2. `days + capdays > 99` → "can't wait for more than 99 days." (0x15), ask again.
3. "That will be *days×rate* coins. Do you accept?" (0x13); No → ask again.
4. `_Enough(total)` false → "%h doesn't have that much!" (comtxt 0x25), cancel. Else `_DecGold(total)` and return `days`.

## Sailing

- A ship enters only **water** (terrain class 13, `B01` name "water"). Every other tile a walker is refused (river 12, mountains, chasm, settlements) is refused silently (`ovl_0cb2` @0xEA1 → `stc`), and so are town entrances (@0xD1C) and features (@0xD49) while `_sailsw`. A walkable tile starts the landing (below). Leaving the loaded map area is refused with "The captain says it's unsafe to sail in that direction!" (0x14, `ovl_147c` returning −1; the same text answers a walker at the world edge).
- Each step moves the boat with the party (`boatx/y[curcap] = party x,y`), costs `4 + sailing_weather[weather]` five-minute ticks (`ovl_10f7` @0x114D; the table byte is added to 4 as a byte, so Clear and Overcast cost 3), none while a camp is running, and **no** energy; the land fatigue loop is skipped.
- Camping aboard is `_CAMPSITE` 4 (`camp.md`): no hunting, watching or patrols, and the loop does not run on its own; every sailing step taken from the camp menu makes one camp pass (one `_CalUpd`) instead of the step's time. Landing is refused until the camp ends (0x19). A **Dwarf** (`h_race == 4`) aboard is seasick: "%o is too seasick to do anything!" (P93 text 0x15) and cannot sleep, fix, watch or hunt (learning is allowed).
- Teleport spells: "It's impossible to teleport from a moving ship." (0x1A).
- **Rough sea barrier**: terrain class 13 on row `y == 101` is impassable while sailing — "The sea is unnaturally rough! The *ship* cannot sail to the south!" (0x29) — until event byte 12 bit 0x40 is set. Using the **Conch** (item 0x4B, command key 'K', `ovl_1349`) while aboard on row `y == 100` sets that bit: "When %h blows the conch, the seas calm!" (0x2A). Anywhere else the conch answers "Nothing happens." (comtxt 0x83).

## Landing

Moving onto a walkable tile while aboard (`ovl_0cb2` @0xD7D):
1. If a camp is running: "End camp activities first." (0x19), no move.
2. "Do you want to disembark?" (0x10). No → stay aboard, no move.
3. If `capdays > 0`: "Captain *N* says your credit is *capdays* days. Do you want him to wait longer?" (0x16); else "Do you want the captain to drop anchor here and wait?" (0x11).
   - Yes → buy days (cancel counts as No); state 1, `capdays += days`.
   - No with `capdays > 0` → state 1, credit kept.
   - No with `capdays == 0` → state 0, `capdays = voyage_home(i)`: the captain sails home (also the path when the party was working for passage).
4. `_sailsw = 0`, `_curcap = 0xFF`, the party steps ashore.

So an anchored boat waits exactly its prepaid days; when they run out it heads home and is hireable again from its port once it arrives.

## Credit running out at sea

The daily tick turns state 5 into 4; at the next step (`ovl_15e4`, `ovl_0f95`): "Captain *N* approaches. 'Your time is up. Will you pay for more days?'" (0x25).
- Yes → buy days; success → `capdays = days`, state 5.
- Success replaces the credit (`capdays = days`, @0xF80; it was 0 anyway). Hiring (`ovl_0f5c`) shares that code.
- No, or cancelling the purchase → "'Then you'll have to work for your passage. Agreed?'" (0x26). No → straight back to "How many days?" (@0xFC1 → 0xFA8; the loop only ends by paying or agreeing).
- Agreed → passage mode 1: sailing continues free of charge with state 4, but the camp command is refused with "Captain *N* has too much work for %h to do." (0x27). Landing then ends the hire (the captain sails home). Passage mode is overlay-private, so after a save/reload the "time is up" prompt returns.

## Amos (captain 2, the cheap one)

Hiring Amos sets state 6. At the next daily tick (`P92 ovl_0447`): state 7, `capdays = 0`, and every party member's **Coin** entries are removed (`_SearchInv` item 0 per slot, `_DecObj0`). At the next step the theft message prints and the state becomes 5 with zero credit, so the following day Amos demands payment the party can no longer make — working for passage is the usual outcome. The game never gives the coins back.

## Captains ashore

EXE `_CapAtLiberty`: a KNPC row of type 0x1D is shown only while the matching captain is in state 3; the row's `tile` byte is mapped to the captain index through the 6-byte key `35 51 52 8E 8F 94` (DS:0838). No shipped location file contains such a row, so this is dead data.

## Port notes

Built in the web port (`web/src/ships.ts`, `main.ts` *ships*): hiring, buying days, sailing, landing and anchoring, the daily countdown, time is up / working for passage, Amos, the rough sea and the Conch (on Use; the original's K command). the ship campsite and the seasick Dwarf (`camp.ts`; in the port Begin aboard closes the camp menu and the arrow keys sail, C reopens it to End). Teleport aboard is refused (`main.ts` *teleport*).

- Only `_capsta`, `_boatx/y`, `_capdays`, `_sailsw`, `_curcap` need to persist; everything else is derivable.
- Quirks a port may want to fix: passage mode not saved; the hire prompt for state 4/5 boats found at sea (unreachable in practice); the "unsafe to sail" text on foot; Amos' theft being irreversible and unexplained.
