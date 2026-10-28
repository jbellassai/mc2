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

## Casting in combat — P94 (`ovl_1721` → `ovl_1740`)
A combatant record (`CMBTNT`, 33 bytes) may cast `G_curspl` when: state flags (`c_state` +5) & 0x98 == 0; `c_invis` (+14) == 0; it is a hero (`c_recno` +31 < 6); `_EneUsg(spell, hero) ≤ c_energy` (+13); and the hero has the spell memorised (`h_spells[spell] != 0`). The effect is then dispatched through P94's jump table (slot = `SPLVECS` offset / 3): each P94 spell entry is a 3-instruction stub `call prolog; mov ah,N; int 61h; jmp epilog`, and INT 61h is **V06.MCO** (see *Combat spell effects* below).

## Timed effects — `_DecSpells()` (called once per game hour/day tick, TODO confirm)
- `_detectsw` (Detect) counts down; at 0 `_DetectOff()`.
- For each of the 6 party slots: while `h_glamcnt` (HERO+0x2A, Glamour) > 0, decrement it **and** `h_charm` (HERO+0x13) — Glamour's charm bonus decays one point per tick.

## Random numbers
`_RndCo(n)` = `rand()·n / 0x8000`, i.e. uniform 0‥n−1 (`rand()` is Borland's LCG, `(seed·0x15A4E35+1) >> 16 & 0x7FFF`).

## Skill caps — `_MaxSkill(?, hero, skill)`
`_maxtbl` DS:2C7E (6 skills × 6 races): [99, 40, 75, 60, 60, 75, 75, 10, 25, 50, 99, 50, 80, 25, 99, 80, 75, 50, 75, 99, 75, 0, 0, 0, 99, 40, 99, 50, 75, 99, 99, 30, 99, 99, 10, 30]. Index = `skill*6 + h_race`; skill 3 (magic) is 0 for a hero with `h_magic == 0`. Race/skill order TODO.

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
| Vision (10) | 3 → `ovl_1a7a` | `INT60_00` | `_Target` a tile within 13; if it is a door in `loc.roomptr`: room types outside 6–9 → message by door-id band (thresholds V02 @0x8C → texts 220/221/222/223); types 6–9 (hire rooms) → `HROOM` lookup, message 0xE1–0xE6 by whether the room was visited (`_dunrms` bit) and its reward field. Not a door → 0xE0. |
| Walkwater (15) | 7 → `ovl_1a6c` | `INT60_01` | dungeons only (`_InDungeon`), else message 0x95. `_wlkwcount = magic/20 + 2` water tiles may be crossed; message 0xC9 with the count. Reset to 0 on entering a town. |
| Detect (25) | 1 → `ovl_1a2e` | `INT60_03` | `_detectsw += magic/16` (ticks of 5 min, decremented by `_DecSpells`); if it was 0 the map is re-initialised so hidden specials show; message 0xF6 with `detectsw·5` minutes. `INT60_0d` (slot 11) animates the hidden `SPECIAL` records of type 1 while it runs. |
| Pierce (13) | 8 → `ovl_1a52` | `INT60_06` | `_Target` within 13; if the tile has a `B`-record of class **'C'** in the tileset's `aniptr` list (`{tile, newtile, class, …}`, 7 B), the tile becomes `newtile` and the change is logged in `_snakes/_snakelocs` (restored by `INT60_14` when the location is re-entered). Otherwise fail text. |
| Repel (3) | 9 → `ovl_1a5f` | `INT60_07` | same as Pierce for class **'B'** records. |
| Sense (39) | 6 → `ovl_1ad4` | `INT60_13` | nearest `SPECIAL` record of type 0 (traps / ambush spots not yet in `_ambush`): if `(magic/4)² ≥ dx²+dy²` its direction (16-way table) is reported, else fail. The found spot is remembered: walking into that ambush is then never a surprise (`locations.md`, *Special spots*). |

Other V02 services are town helpers, not spells: 02/08 door and tile lookups, 09 trap explosion (`_bangstg`: energy −(10+RndCo(10)) or HP), 0A reset, 0B/0C flood-fill `_blobmap` pathing, 0E/0F/12 set event bits on entering listed locations, 10 **disguise gate** (towns 51, 52, 58 refuse entry unless Disguise is the ready spell and cast), 11 nearest exit, 15 **trapped chest**: `skill < RndCo(120)` → Poisoned (0x08) or Ill (0x02), energy and HP halved, 16 special-table reset. `V05.MCO` (dungeon programs) has only two services (exit letters, a name patch) — no spells.

## Non-combat spell effects — wilderness (`P01` slots)
- **Confuse (1)**, slot 13 `ovl_1ae3`: `_ptrleng[curreg] = 0` — the current region's monster patrol is scattered.
- **Locate (4)**, slot 14 `ovl_1ac2`: for the next `magic/4` moves (`OV_0x1bb`) `ovl_076c` draws every live patrol (`_ptrlxy`, 128) and the region's 8 guard posts (`R` record +18) on the map.
- **Teleport (7)**, slot 15 `ovl_1b02`: not while sailing or camping. Loads `P89` (the teleport picker): tier = highest of `[10,30,50,70,90]` ≤ magic; the player marks any tile inside the tier's window rectangle `x 4–6/3–7/2–8/1–10/0–10, y 3–5/2–6/1–7/0–8/0–8` (window is 11×9, party at 5,4) and the party is moved there.
- Slot 17 is empty.

## Resurrect (17) — `P95` entry 3 (`ovl_0ce0`, file 0xCFA), post-combat screen only
`SPLVECS[17]` = `0CA8:0009` = the 4th 3-byte slot of whatever location program is loaded; only P95 fills it. Flow: if the party already looted (`[si-0x6752] == 1`) → "While you were looting that corpse… you lost your chance to cast resurrect" (P95 text 6). `_SpelTarg` picks a combat record (≥ 24 = cancelled). Not dead (`c_state & 0x80 == 0`) → "%a does not need resurrection."; record flagged removed → "%h decides not to resurrect the %l.". Otherwise **it always succeeds** (energy cost 90 − magic/4 is the only price): HP = 1, energy = 1, dead bits cleared, sound 12. A party member (index < 6) is re-tiled and gets `h_energy = h_hitpts = 1`, `cond1 &= ~Dead`, "Done.". A **monster** (index ≥ 6) is redrawn, then `ovl_0eaf`: "The %l thanks %h kindly, giving %d <its treasure>" (`IncObj` of the record's loot) and leaves (`c_state |= 0x10`) — resurrecting an enemy is a way to collect its loot peacefully.

## Glamour (26) — FFFAR `ovl_3440`
Target charm (`h_charm`) must be ≤ 11; `gain = min(charm, 12 − charm)`; `h_charm += gain`, `h_glamcnt += gain` (then decays one point per tick together with charm, see above). So Glamour doubles charm up to the cap of 12, temporarily.

## Still to extract
message texts for the V02 numbers (0x95, 0xC9, 0xE0–0xE6, 0xF6, 220–223) — which text file `_SetTxtWnd`/`PrtScrap` read in towns; the combat text numbers (messages 0x59 Fear, 0x5A Freeze, …) come from the combat text file.
