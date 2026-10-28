# Camp: sleep, learn, hunt, watch, repair

Source: `P93.MCO` (`ovl_0271` camp loop; helpers `ovl_07e5` HP, `ovl_0813` energy, `ovl_0849/0886` repair, `ovl_1099` campsite, `ovl_1137` shelter). Menu = EXE menu 13 (`_menuaddr` DS:2AC2 → command words Use, Recall, Sleep, Magic, Learn, Off, Fix, Watch, Hunt, Put, **Begin**, End; the parser index is the case number in `ovl_0271`); where camping is impossible menu 22 (Use, Recall, Put, Off, End; `ovl_11d2` maps its index through P93 file 0x11CD). While the loop runs, menu 15 (Stop, …).

The commands only **set** each member's activity (`h_actvty`) and print what they will do; **Begin** runs the loop. Aboard a ship Begin does nothing: instead each sailing step taken from the camp menu (digit keys 1–9 except 5, P01 cross-overlay entries 0x0C + 3k, then 0x18) runs **one pass** of the loop (`SUB_04d4` is called, and returns after `_CalUpd` when `_CAMPSITE & 4`), in place of the step's own time (`ships.md`).

## Where you can camp (`ovl_1099` → `_CAMPSITE` bits)
| `_curmpg` | site | bit |
|---|---|---|
| 1 wilderness | open camp (sailing: 4) | 2 |
| 7 dungeon | dungeon camp | 8 |
| 5 town, rooms 0x40–0x47 | rented inn room (`_RENTPTR` = nights left; camp ends when it hits 0) | 0x20 |
| 5 town, rooms 0x5C–0x6B, or `_locspec 0x14` room 9 | guest room | 0x10 |
| anything else | no camping: menu 22 | 1 |

Only an open camp (bit 2) rolls wilderness encounters while camping (P01 cross-overlay calls 6 and 9 every tick); if a fight starts it is an **ambush** unless some member is on *Watch* (`P01 ovl_0790`: `_ambflg = 1` when no `h_actvty == 9`). Watch is only offered when bits 1|2 are set.

## Setting activities (acting member `_curpla`)
| command | refused when | sets | text (P93) |
|---|---|---|---|
| Sleep | "Is everyone going to sleep?" (0) Yes = every member, No = the acting member; each one (`ovl_0bd5`): seasick (21), `cond1 & 8` poisoned (9), `cond1 & 4` starving (10), `cond2 & 0x40` hungry (11) | 0 | "%o will sleep." (1) |
| Learn | not a magic user (`_ChkMag`, comtxt 0x2D); any condition (`cond1|cond2`, 3); no spell book 0x53–0x59 in the pack (18). Not refused when seasick | 1, `h_actmisc` = spell, `h_lrncnt = _LrnTim` | "%h will learn %a." (2) |
| Fix | seasick (21); any condition (3) | 6 | (6) |
| Watch | `_CAMPSITE & 3 == 0` → "No need to stand watch here." (12); seasick; any condition | 9 | (5) |
| Hunt | not an open camp (`_CAMPSITE & 2`) → comtxt 0x24 "%h can't do that here!"; seasick; `cond1 ≠ 0` (3) | 3 | (4) |

Learn lists the six spells of every book in the pack (`ovl_0a15`): book *b* holds spells `6·(b − 0x53) … +5` (Sabano: Fear…Assess, Ishban: Fireball…Freeze, Demaro: Energy…Resurrect, Zoxinn: Zofir…Zutyun, Vannex: Jump…Disguise, Emenad: Betray…Timestop, Felmis: Acidball…Soulspeak), indexing `h_spells` (HERO +0x7B) flat by spell id. Seasickness (`ovl_1027`): a Dwarf (`h_race 4`) while `_sailsw`.

## The loop
Every 5-minute `CalUpd` tick, for each party member (`h_actvty`):
- **0 / sleeping** (`Sleep` sets everyone to 0 after "Is everyone going to sleep?" — *Yes* = every member, *No* = the acting member only; each prints "%o will sleep."): on ticks whose minute is even (`_minute & 1 == 0`, i.e. every 10 minutes) `hp += 1` up to a cap and `energy += 1` up to a cap (`_IsHeTr` re-evaluates tired/exhausted). Caps: indoors or with a **Blanket** (0x52) in the sleeper's pack: `hpmax` and 99. Open camp without a blanket: `min(hpmax, hpmax/2 + shelter)` and `min(99, 50 + shelter)`, where `shelter = HighStat(carpentry)/2` — the party's best carpenter halves the penalty (`ovl_1137`). Poisoned or Ill (`cond1 & 0x0A`) halves the caps.
- **1 learn**: any condition (`cond1|cond2`) stops it (`ovl_1061`). Otherwise each tick decrements `h_lrncnt`; a tick that finds it at 0 adds a charge (cap 99), prints "%o memorized %a." (13) and restarts the timer at `_LrnTim(spell, hero) = _speltim[spell] − h_intellg`, 2 when that is below 3. So a charge takes `_LrnTim + 1` ticks: 3 ticks (15 minutes) at best. `_speltim` (DS:2B8F, 42 bytes, one per spell id): `10,16,12,6,10,5,8,12,6,12,5,16,8,5,12,6,8,35,20,20,12,20,16,50,10,25,15,25,20,10,30,35,25,25,10,10,15,22,18,15,10,10`.
- **3 hunt**: `cond1 ≠ 0` stops it. On the hour and half hour, `RndCo(100)`; success if the byte sum `terrain[curter] + weather[weather] + h_hunt/2` is not negative (signed byte) and ≥ the roll → `+1 Food` (`_IncObj`, lost when the pack is full), "%o found food." (20), then a hunt skill-up roll (`_SkillUp0`, skill index 0x11 = h_hunt). A terrain class ≥ 10 reads past the 10-byte terrain table into the weather table (P93 file 0x03 + class). Tables (P93 @0x003 / @0x00D, −1 = hunting impossible): terrain `[–, –, +18, +5, 0, +25, −25, −35, −15, +10]`; weather `Clear +10, Overcast 0, Fog −40, Rain −30, Thunderstorm −60, Snow −20, Blizzard –, Freezing 0, Gale –, Sweltering +10, Sandstorm –, Hurricane –`. Not while seasick.
- **6 fix**: any condition stops it. Each tick repairs one point, and a second one when `RndCo(100) ≤ h_smith` (`ovl_0849` is called before the roll and again on success): the first inventory amount byte `> 0x80` (**damaged flag** in `h_invamt`: high bit + damage count) is decremented, searching the repairer's pack first, then the other members round-robin.
- **9 watch**: no effect except preventing the ambush above; `cond1 ≠ 0` stops it.
- A stopped activity prints "%o can't continue the current activity." (7) and becomes 0xFF (`ovl_1061`). Seasickness never stops a running activity; it only refuses new ones (above).
Camping ends on a key/mouse press, when the rented room expires (`_RENTPTR` byte 0, checked after each tick), or when combat starts; all activities reset to 0xFF. Members are processed 5…0, then `_CalUpd` runs (so `_DecEnergy` still drains anyone not asleep). Texts: P93 file 0x3D, NUL-separated (data pack `p93text.json`).

## Other camp commands
- `Magic`: cast a spell from camp (`_Magic`, the usual gate in `spells.md`).
- `Put`/`Off`: wear/remove armour and clothing (0x1F–0x30) — the only place equipment is changed. Six `h_wears` slots; each item has a **garment class** (`ovl_0d25`): 1 = body armour 0x1F–0x27, 2 = helmet 0x28–0x2A, 4 = clothing 0x2B–0x30. Putting on an item whose class is already worn replaces that item (text 0x11); otherwise it takes the first free slot (text 0x0E). No race or class restriction is checked.
- `Use`: `_UseItem` → FFFAR `ovl_173e`: Rope, Orb, Horn, Conch, the four Scrolls, Pick, Arrow and Flute only **show the item's picture** here (window set-up + `_StartGraf`); scripted effects live in location programs.
- `Assign`: give a companion a job/task (assignment records, `npcs.md`).

## Port notes
Built in the web port (`web/src/camp.ts`, `main.ts` *campCmd*): the campsites (world map, ship, P07 dungeon room, inn room, camp rooms 0x5C–0x6B), every activity, Begin/Stop, the open-camp caps, patrols walking into the camp (ambush unless someone watches), the ship's one pass per sailing step (End from the camp menu; landing is refused meanwhile), seasickness. Not yet: Recall and Magic in the camp menu, the camp formation (`ovl_1151`: the party redrawn on fixed squares in dungeon, inn and guest rooms), `_locspec` 0x14 room 9 as a guest room.
