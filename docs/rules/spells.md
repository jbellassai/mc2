# Spells

Evidence: `_Magic` (EXE, FF module, `out/decomp/MC2_all.c`), tables in the data segment (`_enetbl` DS:2BC6, `_splocs` DS:2BF0, `_spellshere` DS:2C1A, `SKLSPLS` DS:390C, `SPLVECS` DS:3924), spell names at DS:3DA6 (item names 0–41 precede them; spell *id* = string index − 42), combat casting in `decomp/overlays/P94.c` (`ovl_1740`, `ovl_1721`).

## Spell table

| id | spell | energy | castable (mask) | trains magic skill | implemented in |
|---|---|---|---|---|---|
| 0 | Fear | 40 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 1 | Confuse | 25 | wilderness(1) (0x01) |  | combat: P94 table / location overlay slot |
| 2 | Shatter | 20 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 3 | Repel | 10 | town(2), town-dungeon(4) (0x06) |  | combat: P94 table / location overlay slot |
| 4 | Locate | 20 | wilderness(1) (0x01) | yes | combat: P94 table / location overlay slot |
| 5 | Assess | 15 | prog 6(16) (0x10) |  | combat: P94 table / location overlay slot |
| 6 | Fireball | 20 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 7 | Teleport | 30 | wilderness(1) (0x01) |  | combat: P94 table / location overlay slot |
| 8 | Heal | 10 | anywhere (0xff) |  | FFFAR HEAL |
| 9 | Weaken | 20 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 10 | Vision | 15 | town-dungeon(4) (0x04) |  | combat: P94 table / location overlay slot |
| 11 | Freeze | 50 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 12 | Energy | 20 | anywhere (0xff) |  | FFFAR ENERGY |
| 13 | Pierce | 15 | town(2), town-dungeon(4) (0x06) |  | combat: P94 table / location overlay slot |
| 14 | Disappear | 25 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 15 | Walkwater | 15 | town-dungeon(4) (0x04) |  | combat: P94 table / location overlay slot |
| 16 | Shield | 15 | anywhere (0xff) |  | FFFAR SHIELD |
| 17 | Resurrect | 90 | bit32 (0x20) |  | combat: P94 table / location overlay slot |
| 18 | Zofir | 60 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 19 | Zapall | 40 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 20 | Zengrl | 40 | anywhere (0xff) |  | FFFAR ZENGRL |
| 21 | Zishoxe | 30 | anywhere (0xff) |  | FFFAR ZISHOXE |
| 22 | Zefoar | 30 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 23 | Zutyun | 90 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 24 | Jump | 20 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 25 | Detect | 25 | town(2), town-dungeon(4) (0x06) |  | combat: P94 table / location overlay slot |
| 26 | Glamour | 25 | anywhere (0xff) |  | combat: P94 table / location overlay slot |
| 27 | Drain | 45 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 28 | See | 45 | prog 6(16) (0x10) |  | combat: P94 table / location overlay slot |
| 29 | Disguise | 20 | never via Magic (0x00) |  | FFFAR DISGUISE |
| 30 | Betray | 70 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 31 | Summon | 80 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 32 | Destroy | 60 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 33 | Terrify | 75 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 34 | Double | 20 | prog 6(16) (0x10) |  | combat: P94 table / location overlay slot |
| 35 | Timestop | 20 | prog 6(16) (0x10) |  | combat: P94 table / location overlay slot |
| 36 | Acidball | 20 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 37 | Forget | 30 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 38 | Courage | 25 | prog 6(16) (0x10) | yes | combat: P94 table / location overlay slot |
| 39 | Sense | 25 | town(2), town-dungeon(4) (0x06) |  | combat: P94 table / location overlay slot |
| 40 | Restsoul | 20 | prog 6(16), bit64 (0x50) |  | combat: P94 table / location overlay slot |
| 41 | Soulspeak | 20 | bit64 (0x40) |  | combat: P94 table / location overlay slot |

`_spellshere[program]` = [0, 1, 2, 0, 8, 8, 16, 8] — the bit a location program contributes: program 1 (wilderness) → 1, program 2 (town) → 2, plus 4 when `_InDungeon()`; programs 4, 5, 7 → 8; program 6 → 16. A spell is castable outside combat when `_splocs[spell] & _spellshere[__curmpg]` is non-zero. Bits 32/64 (Resurrect, Restsoul, Soulspeak) never match, so those are combat-only / scripted.

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
A combatant record (`CMBTNT`, 33 bytes) may cast `G_curspl` when: state flags (`c_state` +5) & 0x98 == 0; `c_invis` (+14) == 0; it is a hero (`c_recno` +31 < 6); `_EneUsg(spell, hero) ≤ c_energy` (+13); and the hero has the spell memorised (`h_spells[spell] != 0`). The effect is then dispatched through P94's private table (`OV_0x189C`), not `SPLVECS`.

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

## Still to extract
P94 combat spell effects (Fireball, Fear, Freeze, Zapall, Acidball …) and the location-overlay effects (Teleport, Locate, Walkwater …).
