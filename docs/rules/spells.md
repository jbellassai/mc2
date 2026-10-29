# Spells

Evidence: `_Magic` (EXE, FF module, `out/decomp/MC2_all.c`), tables in the data segment (`_enetbl` DS:2BC6, `_splocs` DS:2BF0, `_spellshere` DS:2C1A, `SKLSPLS` DS:390C, `SPLVECS` DS:3924), spell names at DS:3DA6 (item names 0–41 precede them; spell *id* = string index − 42), combat casting in `decomp/overlays/P94.c` (`ovl_1740`, `ovl_1721`).

## Spell table

| id | spell | energy | castable (mask) | trains magic skill | implemented in |
|---|---|---|---|---|---|
| 0 | Fear | 40 | prog 6(16) (0x10) | yes | combat: V06 `INT61_0d` (see below) |
| 1 | Confuse | 25 | wilderness(1) (0x01) |  | location overlay (not castable in combat) |
| 2 | Shatter | 20 | prog 6(16) (0x10) | yes | combat: V06 `INT61_10` (see below) |
| 3 | Repel | 10 | town(2), town-dungeon(4) (0x06) |  | location overlay (not castable in combat) |
| 4 | Locate | 20 | wilderness(1) (0x01) | yes | location overlay (not castable in combat) |
| 5 | Assess | 15 | prog 6(16) (0x10) |  | combat: V06 `INT61_0c` (see below) |
| 6 | Fireball | 20 | prog 6(16) (0x10) | yes | combat: V06 `INT61_11` (see below) |
| 7 | Teleport | 30 | wilderness(1) (0x01) |  | location overlay (not castable in combat) |
| 8 | Heal | 10 | anywhere (0xff) |  | FFFAR HEAL |
| 9 | Weaken | 20 | prog 6(16) (0x10) | yes | combat: V06 `INT61_13` (see below) |
| 10 | Vision | 15 | town-dungeon(4) (0x04) |  | location overlay (not castable in combat) |
| 11 | Freeze | 50 | prog 6(16) (0x10) | yes | combat: V06 `INT61_0e` (see below) |
| 12 | Energy | 20 | anywhere (0xff) |  | FFFAR ENERGY |
| 13 | Pierce | 15 | town(2), town-dungeon(4) (0x06) |  | location overlay (not castable in combat) |
| 14 | Disappear | 25 | prog 6(16) (0x10) | yes | combat: V06 `INT61_14` (see below) |
| 15 | Walkwater | 15 | town-dungeon(4) (0x04) |  | location overlay (not castable in combat) |
| 16 | Shield | 15 | anywhere (0xff) |  | FFFAR SHIELD |
| 17 | Resurrect | 90 | bit32 (0x20) |  | location overlay (not castable in combat) |
| 18 | Zofir | 60 | prog 6(16) (0x10) | yes | combat: V06 `INT61_06` (see below) |
| 19 | Zapall | 40 | prog 6(16) (0x10) | yes | combat: V06 `INT61_03` (see below) |
| 20 | Zengrl | 40 | anywhere (0xff) |  | FFFAR ZENGRL |
| 21 | Zishoxe | 30 | anywhere (0xff) |  | FFFAR ZISHOXE |
| 22 | Zefoar | 30 | prog 6(16) (0x10) | yes | combat: V06 `INT61_04` (see below) |
| 23 | Zutyun | 90 | prog 6(16) (0x10) | yes | combat: V06 `INT61_05` (see below) |
| 24 | Jump | 20 | prog 6(16) (0x10) | yes | combat: V06 `INT61_16` (see below) |
| 25 | Detect | 25 | town(2), town-dungeon(4) (0x06) |  | location overlay (not castable in combat) |
| 26 | Glamour | 25 | anywhere (0xff) |  | location overlay (not castable in combat) |
| 27 | Drain | 45 | prog 6(16) (0x10) | yes | combat: V06 `INT61_41` (see below) |
| 28 | See | 45 | prog 6(16) (0x10) |  | combat: V06 `INT61_0b` (see below) |
| 29 | Disguise | 20 | never via Magic (0x00) |  | FFFAR DISGUISE |
| 30 | Betray | 70 | prog 6(16) (0x10) | yes | combat: V06 `INT61_0f` (see below) |
| 31 | Summon | 80 | prog 6(16) (0x10) | yes | combat: V06 `INT61_0a` (see below) |
| 32 | Destroy | 60 | prog 6(16) (0x10) | yes | combat: V06 `INT61_1a` (see below) |
| 33 | Terrify | 75 | prog 6(16) (0x10) | yes | combat: V06 `INT61_19` (see below) |
| 34 | Double | 20 | prog 6(16) (0x10) |  | combat: V06 `INT61_09` (see below) |
| 35 | Timestop | 20 | prog 6(16) (0x10) |  | combat: V06 `INT61_1b` (see below) |
| 36 | Acidball | 20 | prog 6(16) (0x10) | yes | combat: V06 `INT61_12` (see below) |
| 37 | Forget | 30 | prog 6(16) (0x10) | yes | combat: V06 `INT61_18` (see below) |
| 38 | Courage | 25 | prog 6(16) (0x10) | yes | combat: V06 `INT61_40` (see below) |
| 39 | Sense | 25 | town(2), town-dungeon(4) (0x06) |  | location overlay (not castable in combat) |
| 40 | Restsoul | 20 | prog 6(16), bit64 (0x50) |  | combat: V06 `INT61_17` (see below) |
| 41 | Soulspeak | 20 | bit64 (0x40) |  | location overlay (not castable in combat) |

`_spellshere[program]` = [0, 1, 2, 0, 8, 8, 16, 8] — the bit a location program contributes: program 1 (wilderness) → 1, program 2 (town) → 2, plus 4 when `_InDungeon()`; programs 4, 5, 7 → 8; program 6 → 16. A spell is castable outside combat when `_splocs[spell] & _spellshere[__curmpg]` is non-zero. `_spellshere` is really indexed by the *program number* and extends past the 8 location programs: entry 0x5D (P93 camp) = 8, **0x5E (P94 fight) = 0x10, 0x5F (P95 aftermath) = 0x20**, 0x60 (P96) = 8 (DS:2C1A+n). So the combat spells (bit 0x10) are castable in the fight overlay and **Resurrect (bit 0x20) only on the post-combat screen**. Bit 0x40 is set nowhere: **Soulspeak (41) can never be cast** — its vector is P95 slot 1, which is an empty `00 00 00` entry — and Restsoul works only through its combat bit.

## Casting outside combat — `_Magic()` (invoked from the main menu, `_Main5` case 3)

1. Spell = the hero's readied spell `h_rdyspl` (HERO+0xCB). 0xFF → "can't" message, fail.
2. **Energy cost** = `_EneUsg(spell, hero)` = `_enetbl[spell] − (h_magic / 4)`, minimum 1 (`h_magic` = HERO+0x1A is the Magic skill). The hero's `h_energy` (HERO+0xBA) must be ≥ cost or the cast fails.
3. **Location check** as above. Exception: Disguise (29) is also allowed when `_indisguise != 2`.
4. Spells 30–35 (Betray, Summon, Destroy, Terrify, Double, Timestop) fail if their bit in `_magbits` is already set (effect already active — the bit is set by `MABITON` after a successful cast).
5. `_swcast = hero+1`; the caster's tile is redrawn (except in wilderness or for Disguise); then the spell routine `SPLVECS[spell]` runs. In combat (`__curmpg == 0x5E`) there is a 500 ms delay/“no” path if a counter hits 0x1C.
6. On success: `MABITON` (set active bit); if the spell is in `SKLSPLS` (ids 0,2,4,6,9,11,14,18,19,22,23,24,27,30,31,32,33,36,37,38) the caster's Magic skill gets a `_SkillUp` chance.
7. The memorised count `h_spells[spell]` (HERO+0x7B+spell) is decremented; at 0 the readied spell is cleared (`h_rdyspl = 0xFF`).
8. `_DecSta(hero, h_energy, cost)` subtracts the energy (floors at 0); `_IsHeTr` updates the "tired" flags: energy 0 → flag 0x10 in HERO+0xBD; energy < 15 → flag 0x20 in HERO+0xBE; `_SumStat` refreshes the status display.

Memorised copies: `h_spells` (HERO+0x7B) is 42 counts, read as spell id = index (the TDInfo type is `[6][7]`, so row·7 + column). Spell names: DS:3EDC, 42 NUL-terminated strings in id order. Combat Recall (`_RecSpl`, menu value 0x23) only sets `h_rdyspl` and takes no action.

## Casting in combat — P94 (`ovl_1721` → `ovl_1740`)
A combatant record (`CMBTNT`, 33 bytes) may cast `G_curspl` when: state flags (`c_state` +5) & 0x98 == 0; `c_invis` (+14) == 0; it is a hero (`c_recno` +31 < 6); `_EneUsg(spell, hero) ≤ c_energy` (+13); and the hero has the spell memorised (`h_spells[spell] != 0`). The effect is then dispatched through P94's jump table (slot = `SPLVECS` offset / 3): each P94 spell entry is a 3-instruction stub `call prolog; mov ah,N; int 61h; jmp epilog`, and INT 61h is **V06.MCO** (see *Combat spell effects* below).

## Timed effects — `_DecSpells()` (every 5-minute tick, from `_CalUpd1`)
- `_detectsw` (Detect) counts down; at 0 `_DetectOff()`.
- For each of the 6 party slots: while `h_glamcnt` (HERO+0x2A, Glamour) > 0, decrement it **and** `h_charm` (HERO+0x13) — Glamour's charm bonus decays one point per tick.

## Random numbers
`_RndCo(n)` = `rand()·n / 0x8000`, i.e. uniform 0‥n−1 (`rand()` is Borland's LCG, `(seed·0x15A4E35+1) >> 16 & 0x7FFF`).

## Skill caps — `_MaxSkill(?, hero, skill)`
`_maxtbl` DS:2C7E (first 6 of 20 skills × 6 races): [99, 40, 75, 60, 60, 75, 75, 10, 25, 50, 99, 50, 80, 25, 99, 80, 75, 50, 75, 99, 75, 0, 0, 0, 99, 40, 99, 50, 75, 99, 99, 30, 99, 99, 10, 30]. Index = `skill*6 + h_race`; skill 3 (magic) is 0 for a hero with `h_magic == 0`. The full 20 × 6 table with skill and race names is in `skills.md`.

## Resident spell effects (FFFAR, INT 62h; `decomp/overlays/FFFAR.c`)
All go through `ovl_3228`: pick a target (`EXE_SpelTarg`), play sound 10 and effect `Spef4`, then:
- **Heal (8)** and **Zengrl (20)**: target HP set to **maximum** (`h_hpmax`, or the monster's `mshp`); outside combat via `_UpHitptsHook`. Zengrl applies it to every party member (6) or every combatant (24) in combat. A downed hero target is also stood up (dext/agility restored from the race record).
- **Energy (12)**: `_UpEnergyHook` on the target.
- **Shield (16)**: shield points = caster's Magic skill (`_GetMagSkl`, which returns 99 once if the one-shot flag `HERO+0xA5 & 8` is set); stored in `c_shield`, absorbs magic damage (see combat.md). **Zishoxe (21)** = Shield on everyone at half strength.
- **Disguise (29)**: `_indisguise = 1`.
Failure (target dead, `HERO+0xBD & 0x80`) prints message 0x95.

## Combat spell effects — `V06.MCO` via `INT 61h` (`decomp/overlays/V06.c`)

How the call gets there: `_DoACmbt` loads `P06` at `0CA8:2000` (room half: `_Attack`, `_MDamage`…), `V06.MCO` into `_rvarbuf`, and `P96`/`P94`/`P95` in turn at `0CA8:0000`. `_InstVarVecs` points interrupt vectors 60h/61h/62h at `_lvarbuf`/`_rvarbuf`/`_farrtn`, so during combat **INT 61h = V06** (`ghidra/int61_v06.json` maps AH → handler; `docs/overlays.md`). V06's dispatcher (`ovl_050c`) compares AH against 59 cases and returns the handler's carry flag to the caller.

Shared pieces (asm offsets in V06):
- **Caster magic** `INT61_01` (0x0f10): `rec1.c_magskl`; if the caster is a hero whose `HERO+0xA5 & 8` is set, 99 is used instead and the flag is cleared (one-shot "perfect cast").
- **Spell power** `INT61_43` (0x0ecf): `max(0, magic/8 − target.c_resist)`.
- **Target pick** `_SpelTarg` (EXE/FFFAR) fills `G_rec2`, `G_curtar` (0x18 = none). `ovl_0e43` additionally fails with the "resists" message when power is 0.
- **Damage delivery**: V06 computes a number, then calls room slot 0x4E = `P06 ovl_0fa9` (`_MDamage`, shield absorbs first, then `HP −= dmg`, see combat.md) and slot 0x51 = `P06 ovl_0828` (death/knockdown bookkeeping, `_MAttend`).
- **Missiles**: room slot 0x4B = `P06 ovl_1144` flies a missile of type AX (1 fire, 2 acid, 6 shatter) along a Bresenham line from caster to target; `G_ARESULT` = 1 if it reached the target square (0 = blocked en route), `G_TILEXY` = where it stopped. `_Bang`/`_AcidBang`/`_Spef*` in FFFAR are pure tile animations.
- **Race 32 (Doombeast) is immune** to Zapall/Zefoar/Zutyun (`ovl_13ee`: message 0x100, skip).

| spell | AH | handler | effect (combatant record = `CMBTNT`, hero record = `HERO`) |
|---|---|---|---|
| Fireball (6) | 11 | 0x1b83 | missile 1; if it arrives: `dmg = magic/2 + 5` → MDamage |
| Shatter (2) | 10 | 0x1b0d | missile 6; `dmg = RndCo(magic) + 5` |
| Acidball (36) | 12 | 0x1bdd | missile 2; `dmg = max(0, magic − 4·c_resist)` (no +5) |
| Zapall (19) | 03 | 0x1240 | room slot 0x6C (`P06 ovl_10a7`) marks every living, visible enemy with a clear line of fire; each marked target takes `((magic/2)+5)/2` |
| Zefoar (22) | 04 | 0x12f9 | missile 1 to the target; `_BigBang` at the impact square; every living visible combatant (any side) within the 3×3 around the impact takes `magic/2` |
| Zutyun (23) | 05 | 0x1405 | every living visible combatant with `c_alignmnt != 0` (non-party): `c_armor = 0`, `c_shield = 0` |
| Weaken (9) | 13 | 0x1c3f | target `c_armor = 0`, `c_shield = 0` |
| Fear (0) | 0d | 0x1994 | needs power > 0; `c_itspc1` high nibble = power (turns), `c_state |= 0x20` (feared), `c_removes = 0` |
| Freeze (11) | 0e | 0x19fd | needs power > 0; `c_itspc1` low nibble = power/2 + 1 (turns), `c_health |= 0x20` (frozen) |
| Zofir (18) | 06 | 0x248f | if target `c_health & 0x20` (frozen): clear it, `c_itspc1 = 0`, `c_removes = 1`; else "not frozen" |
| Courage (38) | 40 | 0x18fc | target `c_bravery = min(12, c_bravery + 5)` (hero: `HERO+0xD` too); clears fear (`c_state &= 0x9F`, fear nibble cleared, `c_removes = 1` if it was feared) |
| Terrify (33) | 19 | 0x21cd | for every living enemy: if `RndCo(12) < power(that target)` → `c_bravery = 0`, `c_state |= 0x40` (routed) |
| Betray (30) | 0f | 0x1a82 | needs power > 0 and target `c_resist ≤ 8`; `c_qaspc2` low nibble = Spef7 result, **`c_alignmnt ^= 1`** (switches sides), `c_target = 0xFF` |
| Forget (37) | 18 | 0x2149 | hero target: readied spell `h_rdyspl` → 0xFF and its memorised count → 0; monster: `c_spell1 = 0xFF` |
| Drain (27) | 41 | 0x2584 | `n = magic/10` if the caster is on the party side, else 1; `c_wpnskl` and `c_magskl` each: if ≥ 16 → `max(15, skill − n)`. Hero targets get `h_magic` and the weapon-skill slot of their readied weapon (sword +0x17 / weapon ≥ 0x12 → +0x18 / ≥ 0x1A → +0x19 / unarmed → +0x1B) written back |
| Disappear (14) | 14 | 0x1c95 | target `c_invis = magic/8`; tile hidden |
| See (28) | 0b | 0x17c9 | radius 1 around the target square (+1 if magic > 49, +1 more if magic > 74): every invisible non-party combatant inside gets `c_invis = 0` |
| Jump (24) | 16 | 0x1d96 | `_Target(…, 0x65)` picks a square; the target (hero or monster) is moved there (`c_xpos/ypos`, `_p1x/_p1y` for heroes) |
| Double (34) | 09 | 0x14d7 | "Clone": target must be a hero; record 22 becomes a copy of the target with `c_spell1/2 = 0xFF`, `c_itspc1/qaspc2/magskl/magicused = 0`, `c_recno = 22`, `c_removes = 1`, placed next to the caster; combatant count +1; `_cloneno` = target |
| Summon (31) | 0a | 0x14e1 | target must be a monster whose race entry in the V06 table at file 0x14AE is 0xFF (Sandgu, Slime, Skeleton, Zombie, Kurdazi, Barg, Zebani, Gragan, Mongor, Fermigon, Urgodot, Mizigu, Aciden, Flamebelly, Dreadknight); record 23 = copy of it with full HP (`_MAXHPTS[recno]`), `c_energy = 99`, `c_alignmnt = 0` (fights for the party), `c_recno = 23` |
| Destroy (32) | 1a | 0x22a8 | target must be non-party; **the caster forgets all 42 memorised spells**; if the race is flagged 1 in the table at file 0x2466 (all monsters except Vankruh 28, Zakhad 30, Doombeast 32): target `c_state = 0x98`, position −1 (gone); else "resists" |
| Restsoul (40) | 17 | 0x1f4d | target with `c_state & 0x82 == 0x82` (dead undead?): `c_state = (c_state & ~2) | 8`, position −1 — removed from the field |
| Timestop (35) | 1b | 0x2530 | `_timestop = 1` (attacks auto-hit, see combat.md) |
| Assess (5) | 0c | 0x102c | prints every living monster's name, HP (`c_hitptl/h`), armor, shield — no state change |
| — | 15 | 0x1d6b | unreferenced stub: clears `c_health & 0x20` of the target (cure-freeze variant) |

Heal (8), Energy (12), Shield (16), Zengrl (20), Zishoxe (21) are FFFAR (above) and are reached from P94 through `SPLVECS` as everywhere else. Confuse, Repel, Locate, Teleport, Vision, Pierce, Walkwater, Resurrect, Detect, Glamour, Sense, Soulspeak have no combat handler.

### Spell AI — when the game casts for you (`P94 ovl_15f8`)
`ovl_15f8(G_curspl)` finds a legal target: `G_curtar` if one is set, else the first of the 24 combatants that passes `ovl_1721`. A combatant passes when `c_state & 0x98 == 0`, `c_invis == 0`, the caster can pay (`_EneUsg ≤ c_energy`, hero must have the spell memorised), the sides match the spell's **target alignment** (`TALIGN` table, P94 file 0x1529: 0 = same side as caster, 1 = other side, 0xFF = not a combat spell), and the spell's **worth-it predicate** (jump table at P94 file 0x179C, entries +0x100) accepts:

| spells | predicate (accept when) |
|---|---|
| Fear, Freeze | target not already feared/frozen and `INT 61h/43` power > 0 |
| Fireball, Shatter, Acidball | a missile from the caster to the target would arrive (`_PATHBLK == 0`) |
| Heal | `c_health & 1`, or HP ≤ max HP / 2 |
| Weaken | `c_shield + c_armor ≥ 1` |
| Energy | `c_energy ≤ racetable[c_race]` (DS:B86D) |
| Disappear | `c_invis == 0` and nearest enemy within 2 squares (0 squares only if `c_strngth > 15`) |
| Shield | `c_shield ≤ 30` |
| Zofir | target is frozen (`c_state & 0x20`) |
| Zengrl / Zishoxe / Zutyun / Zapall | group spells: at least **5** living visible combatants of the right side pass the Heal / Shield / Weaken / Fireball predicate respectively |
| Forget | target has a readied spell (`h_rdyspl != 0xFF`, monster `c_spell1 != 0xFF`) |
| everything else | target has `c_wpnskl > 15` or `c_strngth > 15` |

## Casting gate and cost (`_Magic`, EXE 1166:09E6)
- Spell = caster's `h_rdyspl` (0xFF = none). Energy cost `_EneUsg` = `max(1, _enetbl[spell] − h_magic/4)` (the *cost* column above is `_enetbl`); refused if `h_energy` is lower.
- Place gate: `_splocs[spell] & _spellshere[curmpg]` must be non-zero; `_spellshere` by program = `[0, 1 (P01 wilderness), 2 (P02 town), 0, 8, 8, 16 (P06 combat), 8]`, and inside a town program the dungeon bit 4 is OR-ed in when `_InDungeon()`. So in P04/P05/P07 (mask 8) only "anywhere" spells work. Disguise (29) only when `_indisguise == 2` (the town asked for it, V02 `INT60_10`). Spells 29–35 are also blocked while their `_magbits` bit is set.
- Then `SPLVECS[spell]` runs (FFFAR stub → location overlay slot → V02/V06 service), `MABITON`, a skill-up roll if the spell is in `SKLSPLS` = {0,2,4,6,9,11,14,18,19,22,23,24,27,30,31,32,33,36,37,38}, and the hero's copy count `h_spells[spell]` is decremented (0 → ready spell cleared).

## Non-combat spell effects — towns and town dungeons (`P02` slots → `V02.MCO` via `INT 60h`, `decomp/overlays/V02.c`, map `ghidra/int60_v02.json`)

| spell | P02 slot | V02 service | effect |
|---|---|---|---|
| Vision (10) | 3 → `ovl_1a7a` | `INT60_00` | `_Target` (a cursor anywhere in the 11×9 window; the 0x0D is its prompt "Mark the target.", not a range); cancelling returns carry (nothing spent). Prints comtxt 0xDB "%h envisions " + the result: a door in `loc.roomptr` there of a type outside 6–9 → by the band of its id (thresholds V02 file 0x8C `[64,72,108,124,128,132,144,152,160,168,187,192,200,208,216,255]`, the first above the id picks the text at 0x9C: ids 168–186 → 220 "a teleportal.", 200–207 → 221 "a powerful presence!", 208–215 → 222 "a dungeon gate.", every other → 223 "something special."); types 6–9 (guarded rooms) → its `HROOM` (from `hroomptr`, 13 B, by id) and its `_dunrms` bit: guards not beaten 0xE1 "a room of rampant creatures!" / 0xE2 "monsters carrying a treasure chest!" / 0xE3 "monsters guarding a fountain!", beaten 0xE4 "an empty room." / 0xE5 "a room with a chest." / 0xE6 "a room with a fountain." by the reward word (0 / < 0x80 / ≥ 0x80). No door → 0xE0 "nothing. Try a door." |
| Walkwater (15) | 7 → `ovl_1a6c` | `INT60_01` | dungeons only (`_InDungeon`: `_curmpg ≠ 1` and `_loc.locdiff` ≠ 0), else comtxt 0x95 "The spell has no effect." (still spent: the slot returns `clc`). Sound 10, `_wlkwcount = magic/20 + 2`, "Walkwater is in effect for %b steps." (0xC9). A step refused by `_ChkWlk` is allowed while `_wlkwcount > 0` when the tile is in the tileset's segment-4 list up to its first 0xFF (V02 `INT60_02`, `tdata+8`; the same list is the door-tile list of room tilesets, and in the dungeon tileset B60 it holds water and rock tiles). Every successful step decrements the count. P02 zeroes it on entry (`P02.c` line 52), so it never survives a level change. |
| Detect (25) | 1 → `ovl_1a2e` | `INT60_03` | `_detectsw += magic/16` (5-minute ticks, decremented by `_DecSpells`; saved); if it was 0 the window is redrawn; "Detect is in effect for %u minutes." (0xF6, `%u` = `_detectsw·5`). While it runs, `INT60_0d` (slot 11, from the town loop) draws every special spot of **type 1** (teleportal) in the window with ctile 10 + `RndCo(2)`, so hidden teleportals flicker. At 0 `_DetectOff` redraws. |
| Pierce (13) | 8 → `ovl_1a52` | `INT60_06` | `_Target`; cancelling → carry, nothing spent. If the tile has a record of class **'C'** in the tileset's `aniptr` list (scanned in steps of 7: `{tile, newtile, class, cycle…, FF}`), the square becomes `newtile` (byte 1: B60 0x00, B16 0xFF), it is logged in `_snakes`/`_snakelocs` (square, `_curvar`; `INT60_14` re-applies the log when the location is entered; saved, up to 256), effect `Spef5`, "The energy field has been pierced." (0xE7). Otherwise "The spell has no effect." (0x95), still spent. |
| Repel (3) | 9 → `ovl_1a5f` | `INT60_07` | the same for class **'B'** records (spiders, snakes; B60 → 0x00, B61 → 0x42, B62 → 0x46): "The vermin have been repelled." (0xE8). |
| Sense (39) | 6 → `ovl_1ad4` | `INT60_13` | sound 0x0F; the nearest special spot of type 0 (ambush) whose `_ambush` bit is clear, by squared distance from the leader, counting only distances below 255; if none, or `(magic/4)²` is below it: "%h senses nothing." (0x9C). Else "%h senses an ambush to the " (0x9D) + direction 0x9E + n (west, north, east, south, northwest, northeast, southeast, southwest) from `ovl_082e`: dx = spot − leader, dy = leader − spot (north positive); flags 8 if dx < 0, 4 if dy < 0, then with a = \|dx\|, b = \|dy\|: 2 if b + 2 ≤ 3a, 1 if 3b ≤ a + 1; n = V02 table 0x7FE (words) `[1,–,5,2,3,–,6,2,1,–,4,0,3,–,7,0]` by flags. The spot is returned to P02, which keeps it (cs:0x133): stepping into that ambush is always detected (`locations.md`). Always spent. |

Other V02 services are town helpers, not spells: 02/08 door and tile lookups, 09 barrier bump (`_bangstg`: energy −(10+RndCo(10)) or −1 HP, `locations.md` *A step*), 0A reset, 0B/0C flood-fill `_blobmap` pathing, 0E/0F/12 set event bits on entering listed locations, 10 **disguise gate** (towns 51, 52, 58 refuse entry unless Disguise is the ready spell and cast), 11 nearest exit, 15 **trapped chest**: `skill < RndCo(120)` → Poisoned (0x08) or Ill (0x02), energy and HP halved, 16 special-table reset. `V05.MCO` (dungeon programs) has only two services (exit letters, a name patch) — no spells.

## Non-combat spell effects — wilderness (`P01` slots)
- **Confuse (1)**, slot 13 `ovl_1ae3`: sound 0x0F three times, `_ptrleng[curreg] = 0` (the byte holding the region's 8 patrols' *chasing* bits: they wander again until they next come next to the party), comtxt 0x43 "Enemy patrols' sense of direction is all confused!".
- **Locate (4)**, slot 14 `ovl_1ac2`: sound 0x0F three times, `OV_0x1bb = _GetMagSkl/4`, then a draw. `ovl_076c` (each world-map step and on entering the map) draws every live patrol (`_ptrlxy`, 128) and the region's live guard posts (`R` record +18) while event 105 is set or `OV_0x1bb` is non-zero, counting it down by one per draw: `magic/4` draws in all, the cast's own included. Without it **guard posts are never drawn** (`ovl_076c` is their only draw) and a patrol only when it stands next to the party (`ovl_0a94`). `OV_0x1bb` is overlay-private: leaving the world map or reloading ends the spell. No text.
- The P01 jump table (file 0) holds these as slots 13–15 (file 0x27/0x2A/0x2D); the camp's cross-overlay calls 6 and 9 are `ovl_169e` (patrol moves) and `ovl_0846` (fight check).
- **Teleport (7)**, slot 15 `ovl_1b02`: not while sailing ("It's impossible to teleport from a moving ship.", region text 0x1A) or camping ("End camp activities first.", 0x19); both refusals return carry set, so nothing is spent. Loads `P89` (the teleport picker, `ovl_0147`): tier = highest of `[10,30,50,70,90]` (P89 file 0x09) ≤ magic; below 10 the index becomes −1 and reads an empty rectangle, so nothing can be picked. The squares of the tier's window rectangle `x 4–6/3–7/2–8/1–10/0–10, y 3–5/2–6/1–7/0–8/0–8` (window is 11×9, party at 5,4; file 0x10/0x15 lower bounds, 0x1A/0x1F exclusive upper bounds) that are valid targets are highlighted (`ovl_0392`, `_OrTile`); the player marks one (`_Mark`, comtxt 0x0D). A valid target (`ovl_03d3`) is not the party's square, passes P01 slots 0x48 (no live patrol), 0x45 (no live guard post), 0x4B (no town entrance) and 0x4E (no feature), lies outside the three no-teleport rectangles (count file 0x10A, rectangles 0x10C: world `[25–29, 41–43]`, `[68–76, 20–30]` and `[147–255, 95–255]`, the south-east beyond the rough sea, `ships.md`) and is walkable (`_ChkWlk`). Then sound 0x14, the window moves so the party stands on it, and P01 runs the region update (`ovl_14fd`), `ovl_13f1`, the feature check (`ovl_0d01`), engage (`ovl_0a94`) and draw (`ovl_076c`); no patrol moves and no time passes. A bad target plays sound 0x0E and redraws.
- Slot 17 is empty.

## Resurrect (17) — `P95` entry 3 (`ovl_0ce0`, file 0xCFA), post-combat screen only
`SPLVECS[17]` = `0CA8:0009` = the 4th 3-byte slot of whatever location program is loaded; only P95 fills it. Flow: if the party already looted (`[si-0x6752] == 1`) → "While you were looting that corpse… you lost your chance to cast resurrect" (P95 text 6). `_SpelTarg` picks a combat record (≥ 24 = cancelled). Not dead (`c_state & 0x80 == 0`) → "%a does not need resurrection."; record flagged removed → "%h decides not to resurrect the %l.". Otherwise **it always succeeds** (energy cost 90 − magic/4 is the only price): HP = 1, energy = 1, dead bits cleared, sound 12. A party member (index < 6) is re-tiled and gets `h_energy = h_hitpts = 1`, `cond1 &= ~Dead`, "Done.". A **monster** (index ≥ 6) is redrawn, then `ovl_0eaf`: "The %l thanks %h kindly, giving %d <its treasure>" (`IncObj` of the record's loot) and leaves (`c_state |= 0x10`) — resurrecting an enemy is a way to collect its loot peacefully.

**The aftermath screen** (P95 `ovl_072d`, after the loot roll and the hirelings' share): only while a party record (`c_alignmnt` 0) is dead and still on the board (`ovl_0c36`: `c_state & 0x80`, not `& 0x18`). It prints comtxt 0x110 "Combat is over: this is your only opportunity to resurrect your dead." once and loops on menu 0x15: Use (`_UseItem`; item 0x50 runs `ovl_129c`), Recall (`_RecSpl`), Magic (`_Magic`, where only `_spellshere` 0x20 = Resurrect passes), Done, and moving (a step onto a door sets the member's `_exitdir`; a step off the board asks to leave, comtxt 0x23). The loop ends as soon as nobody in the party is dead, so a monster can only be resurrected while a member still lies dead. Done while someone is dead: `ovl_0c87` refuses when a dead member in slots 1–5 holds something INT61_4a flags ("%h refuses to part with the %a.", comtxt 0x114; the test is the flee check's, not traced), else P95 text 0 "Are you sure you've resurrected everyone that you want to?" — Yes goes on to the search (`ovl_0a06`), No back to the menu. P95's texts 0–6 start at file 0x27 (`G_txtptr` = OV_0x127).

Port (`main.ts` *raise*, *resurrect*): the screen with Recall, Magic and Done (the acting member asked when several live), the Done prompt, Resurrect on a hero (HP and energy 1, "Done.") or a monster (", giving %d " + "n Item" in the search's format, `_IncObj` to the caster, then off the board). Assumptions: one copy, the energy and the magic skill roll as for any spell. Not built: Use and moving on this screen, the quest-item refusal, text 3 (a record byte +9 not traced) and text 6 (the port searches after this screen).

## Glamour (26) — FFFAR `ovl_3440`
Target charm (`h_charm`) must be ≤ 11; `gain = min(charm, 12 − charm)`; `h_charm += gain`, `h_glamcnt += gain` (then decays one point per tick together with charm, see above). So Glamour doubles charm up to the cap of 12, temporarily.

## Still to extract
The combat text numbers (messages 0x59 Fear, 0x5A Freeze, …) come from the combat text file. (The V02 message numbers above are common texts, comtxt.)

## Port notes (outside combat)
Built in the web port (`main.ts` *magic outside combat*, key M): the caster, a memorised spell (Recall and Magic in one step), the energy and place gates (`_spellshere` exported as `combat.json` `spells.here`), the cost, the copy and the magic skill roll; Heal, Zengrl, Energy, Shield, Zishoxe, Glamour (and its decay in `_DecSpells`), Confuse, Locate, Teleport (marked with a direction key or a click on the map); in towns and dungeon levels Vision, Walkwater, Detect, Pierce, Repel, Sense, with the barrier bump, the `_snakes` log and the sensed ambush. Assumptions: a Teleport target that is not valid, or cancelling, casts nothing ("The spell fails.", comtxt 0x119; P89's carry is not traced); the valid squares are not highlighted. Not yet: Disguise, Soulspeak, Restsoul. Resurrect is on the aftermath screen (below).
