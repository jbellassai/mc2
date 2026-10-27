# Combat resolution

Evidence: P06 (combat room program, loaded at `1CA8:2000` by `_DoACmbt`; readable decompile `decomp/overlays/P06.c`), P96 (combat loop), P94 (combat UI / spell casting), FFFAR (`FAR_SKILLUP`), EXE `_DecSta`, `_IsHeTr`, `_RndCo`. Combatant record = `struct CMBTNT` (33 bytes, `docs/structs.h`); up to 24 records (`G_crecs`), slots 0–5 are the party. `G_rec1` = attacker copy, `G_rec2` = target copy (`GetRec`/`PutRec` copy them in and out).

All percentage rolls are `_RndCo(100)` = uniform 0‥99 (`ovl_04af` is `RndCo(AX)`; the three attack-related call sites load AX=100).

## Attack (`P06` slot 17 `_Attack` → `ovl_050a`, resolution in `ovl_0cde`)

**Result codes** (`G_ARESULT`): 0 target dodged, 1 hit, 2 hit and knocked down, 3 target already dead, 4 no target, 0xFF target killed.

1. **Target selection**: `EXE_Target` cursor; range check `EXE_ChkRng` with `G_wrkamt` = 1 for melee, 100 if `c_rdywpn` (+15) ≥ 0x1A (bow). Attacking a friendly/non-hostile asks a yes/no.
2. **Dodge check** — skipped when the attacker has the one-shot "sure hit" flag (`HERO+0xA5 & 0x10`, consumed), when the target is in state `c_health & 0x70`, attacker is invisible, target race is 0x20 (Doombeast), Timestop is active, **or the target's race is in the weapon's hit-list** (`wp_hitlist`, e.g. Dreadslayer vs Dreadknight, Orcbane vs Orc/Troll/Goblin/Domug). Otherwise:
   ```
   skill  = c_wpnskl(attacker) + wp_sklbonus(weapon)      ; halved if target is invisible
   thresh = skill + 50 − 8·c_agility(target)                 (byte arithmetic)
   dodge  if skill+50 < 8·agility, or thresh == 0, or thresh < RndCo(100)
   ```
   A dodging target jumps to a free adjacent square along the attack direction (`ovl_0fcf`), `ARESULT=0`.
3. **Hit value** (`G_HIT`): weapon type `wpnt` 1 sword, 2 axe, 3 bow (from `WEAPDATA.wp_type`); 0/other = unarmed/magic.
   ```
   armed:   HIT = (wp_stbonus + c_strngth − wp_minst)·2 + wp_basedam
            ×4 when target race 36 (Dreadknight) and weapon 16 (Rhokadur)
            melee only: if attacker hero has flag HERO+0xA5 & 0x20 (one-shot): HIT += 2·HIT, flag cleared
   unarmed: HIT = c_strngth
   ```
4. **Shield spell on a hero target**: if `c_renspl3` (+29, remaining shield charges) > 0 it is decremented, the blow does **0 damage** (`G_SWNIFT=1`); when it reaches 0 the hero's shield flag (`HERO+0xA5 & 0x40`) clears.
5. **Armour**: `DAM = max(0, HIT − c_armor(+16))`.
6. **Apply**: 16-bit HP at +10 `−= DAM`. If ≤ 0: `ARESULT=0xFF`, HP=0, `c_state |= 0x80` (dead); a target with `c_alignmnt != 0` and `c_state & 4` triggers a cross-overlay death event.
7. **Knockdown** (only on a real hit with DAM > 0, target not already down (`c_health & 1`), target race ≠ 28 (Vankruh), attacker not casting):
   ```
   if c_wpnskl(attacker)/8 + c_dext(attacker) > RndCo(100):  ARESULT=2,
      target: c_health |= 1, c_agility = 0, c_dext = 0, c_removes = 1;  hero target also gets HERO+0xBD |= 1
   ```
   A downed target therefore cannot dodge (agility 0) until it recovers.

## Magic damage (`P06` slot 32 `_MDamage` → `ovl_0fa9`, called with the damage in AX)
Shield points (`c_shield`, +12) absorb first: `DAM = max(0, AX − shield)`, `shield −= min(AX, shield)`. Then steps 6–7 above apply unchanged (the knockdown roll uses the *caster's* weapon skill/dexterity).

## Weapons (`_weapons`, DS:2CF6, 9-byte `WEAPDATA`; names `_w_wpns`)

| id | name | min str | base dmg | type | unbreakable | str bonus | skill bonus | race restr. | hit-list |
|---|---|---|---|---|---|---|---|---|---|
| 0 | Shortsword | 1 | 8 | sword | | 0 | 0 | any | |
| 1 | Scimitar | 2 | 16 | sword | | 0 | 0 | any | |
| 2 | Longsword | 4 | 28 | sword | | 0 | 0 | any | |
| 3 | Broadsword | 5 | 32 | sword | | 0 | 0 | any | |
| 4 | Greatsword | 8 | 44 | sword | | 0 | 0 | any | |
| 5 | Elvensword | 6 | 40 | sword | | 1 | 0 | any | |
| 6 | Brightsword | 6 | 48 | sword | yes | 0 | 0 | any | |
| 7 | Dreadslayer | 9 | 52 | sword | yes | 2 | 0 | any | Dreadknight (36) |
| 8 | Brennix | 4 | 48 | sword | yes | 1 | 0 | race 0 (Human) | |
| 9 | Smallaxe | 2 | 16 | axe | | 0 | 0 | any | |
| 10 | Hammeraxe | 3 | 24 | axe | | 0 | 0 | any | |
| 11 | Battleaxe | 5 | 32 | axe | | 0 | 0 | any | |
| 12 | Doubleaxe | 6 | 36 | axe | | 0 | 0 | any | |
| 13 | Greataxe | 8 | 44 | axe | | 0 | 0 | any | |
| 14 | Nalanduir | 9 | 48 | axe | yes | 0 | 20 | any | |
| 15 | Orcbane | 10 | 52 | axe | yes | 0 | 10 | race 4 (Dwarf) | Orc, Troll, Goblin, Domug |
| 16 | Rhokadur | 11 | 60 | axe | yes | 1 | 15 | race 4 (Dwarf) | |
| 17 | Ashbow | 2 | 8 | bow | | 0 | 0 | any | |
| 18 | Brombow | 4 | 14 | bow | | 0 | 0 | any | |
| 19 | Bonebow | 8 | 22 | bow | | 0 | 0 | any | |
| 20 | Elvenbow | 6 | 18 | bow | | 0 | 0 | any | |
| 21 | Darkfinder | 5 | 24 | bow | yes | 1 | 20 | race 2 (Elf) | |

"min str" (`wp_minst`) is subtracted in the hit formula, so strength above the minimum is what counts. Whether it is also an equip requirement is TODO (`_WeapSel`).

## Races (`DS:409x` name table; `h_race` / `c_race`)
0 Human, 1 Wizard, 2 Elf, 3 Halfling, 4 Dwarf, 5 Orc, 6 Zorlim, 7 Tekhir, 8 Troll, 9 Goblin, 10 Sandgu, 11 Slime, 12 Minotaur, 13 Domug, 14 Skeleton, 15 Zombie, 16 Kurdazi, 17 Jerrah, 18 Barg, 19 Zebani, 20 Gragan, 21 Mongor, 22 Fermigon, 23 Gnoll, 24 Ogre, 25 Gaem, 26 Zumagin, 27 Hibliss, 28 Vankruh, 29 Naur, 30 Zakhad, 31 Urgodot, 32 Doombeast, 33 Mizigu, 34 Aciden, 35 Flamebelly, 36 Dreadknight … Party races are 0–5 (six rows in `_maxtbl`). Monster stat records (`MSTATS`, 23 bytes) are reached as `_monsptr[race − 5]`.

## Skill advancement (`FAR_SKILLUP`, INT 62h AH=0x30; called after a successful attack or a skill spell)
```
idx   = weapon type − 1  (sword 0, axe 1, archery 2, magic 3 when casting, fist 4 when unarmed)
skill = HERO[0x17 + idx]               (h_sword, h_axe, h_archry, h_magic, h_fist)
only once per skill per combat (G_sklbits mask); only if skill < _MaxSkill(hero, idx)
chance = base[idx]                     (FFFAR-local table, unverified: 20,25,20,20,10)
         + (50 − skill)/4   if skill < 50
         − (skill − 50)/2   otherwise (min 1)
if RndCo(100) < chance: skill += 1, message "skill improves", sound 0x0D
```
`_MaxSkill` returns `_maxtbl[idx·6 + h_race]` (DS:2C7E, 36 bytes = 99,40,75,60,60,75 / 75,10,25,50,99,50 / 80,25,99,80,75,50 / 75,99,75,0,0,0 / 99,40,99,50,75,99 / 99,30,99,99,10,30) and 0 for magic when `h_magic == 0`. Row order = skill (sword, axe, archery, magic, fist, ?), column = race (Human, Wizard, Elf, Halfling, Dwarf, Orc) — e.g. only Wizards have magic cap 99; Dwarves cap axes at 99 and magic at 0.

## Energy and fatigue
`_DecSta(hero, field, amount)` subtracts with floor 0. `_IsHeTr(hero)`: energy 0 → `HERO+0xBD |= 0x10` (exhausted); energy < 15 → `HERO+0xBE |= 0x20` (tired), else cleared.

## Open items
- `ovl_0a2b/ovl_0394`: weapon → type lookup table is built at run time (P06 private data).
- P96 loop: initiative/turn order, monster AI (`ovl_05fd`, `ovl_020a`), fleeing, bribes (`G_BRIBEAMT`).
- INT 61h calls from P06 (`ovl_09df`) reach the location-half overlay; handler not yet identified.
