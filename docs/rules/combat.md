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

## Combat flow (`_DoACmbt` → P96 setup → P94 fight → P95 aftermath)
1. `_DoACmbt` loads P06 at 0CA8:2000 (room half), V06 into `_rvarbuf` (INT 61h), then runs **P96** at 0CA8:0000: builds the 24 `CMBTNT` records (`ovl_020a`: party slots 0–5 from the heroes via `ovl_0f2a`, monsters from the encounter group `_grpsptr[grpno−60]` or `_monstlist`, count = `D06 ptr8[7·diff + RndCo]` when the group gives none), places them on the 11×9 arena, and shows the pre-fight parley menu (`ovl_06e7`: *rally* = `RndCo(100) < h_ldrshp` of the acting leader (P96 0x789) gives every other party member `bravery += RndCo(3)+1` and `agility += 4`, both capped at 12; *hail the leader* = truce / bribe dialogue; `_ambflg` = ambush).
2. If `_endcmbt == 0`, **P94** runs the fight (`ovl_00b4` → `ovl_02e8`, rounds until `_endcmbt != 0`), then **P95** handles the aftermath (loot, resurrection prompts).
3. INT 61h/08 (`V06 INT61_08`) sets `_endcmbt` after every action: 1 = no living monster left (win), 2 = every party member dead, 3 = every party member fled/removed.

### A round (`P94 ovl_02e8`)
- `_curphase = 1`, `_timestop` cleared at the end of each round.
- **Party phase first** unless ambushed (`_ambflg`): then the monster phase runs first.
- `ovl_04a6` recomputes **actions for this round** for all 24 records into `c_removes` (really "moves left"):
  - 0 if the record is removed/fled (`c_state & 0x18`), dead or feared (`c_state & 0xA0`), frozen (`c_health & 0x20`), or is a Doombeast (race 32) whose `_curdoombst` entry is not active.
  - A dead record with `c_state & 2` **rises again** here with 1 HP (`c_state &= 0x7F`, `c_health &= 0x7F`, HP = 1).
  - Otherwise 1 action, plus from dexterity: `n = c_dext·8 + 4`; if `n ≥ 50` one extra action and `n −= 50`; one more if `RndCo(100) < n`. So dext 0 → 1 action, dext 6 → 2 (52), dext 12 → 3 (100). A hero with `HERO+0xA5 & 0x80` gets 4 actions flat.
- **Party phase** (`ovl_05ad`): heroes 0–5 in order; a hero may act when `ovl_05ea` passes (not `c_state & 0x99`, `c_removes > 0`, `c_itspc1 == 0` i.e. not feared/frozen). Each menu command (`ovl_015e`) consumes one action (`ovl_0613`); auto-combat (`_swauto`) runs the same AI as monsters.
- **End-of-side bookkeeping** (`ovl_0655(side)`): for every record of that side `c_invis−−` (reappears at 0); freeze turns (`c_itspc1` low nibble) −1, at 0 `c_health &= ~0x20`; fear turns (high nibble) −1, at 0 `c_state &= ~0x20`; heroes lose the 4-action flag and the fatigue flag `HERO+0xBD & 0x20` when unfrozen.
- **Monster phase** (`ovl_0b4b`): records 6–23 in order; a record keeps acting while `c_removes > 0`. Timestop (`_timestop`) makes side 1 (monsters) unable to act. The phase is run **twice** per round (`_ROUND1` 0 → 1): the second pass gives records with actions left their remaining moves.

### Monster (and auto-hero) decision each action (`ovl_0b4b` → `ovl_0db1` …)
1. `ovl_143d`: find the side's **leader** (`c_state & 4`; Doombeasts use their own record), `_LDRACE` = leader's race (own race if no leader). Terrified records (`c_state & 0x40`) go straight to *flee* (below).
2. Target: keep `c_target` unless it is now on our side. Otherwise pick one with `ovl_124a(criterion)`; the criterion comes from the combat AI record **`D06.MCV`** (loaded into `_loc` by P96 `_LoadVar('D',6)`): `ptr1[3·LDRACE] = {critA, chance%, critB}` → `critA` if `RndCo(100) < chance` else `critB`; if that finds nobody, `ptr2[...]`'s `critB` is tried; still nobody → a hero casts a spell (`ovl_157b`), a monster takes a random move.
3. Target criteria (`P94` table at file 0x122A; candidates must be alive, visible, on the other side — `+10` selects the same-side variants used for friendly spells). Ties are broken by `RndCo(count)` over all candidates that satisfy the criterion:

| id | name (V06 text) | accept / keep the best |
|---|---|---|
| 0 | Random target | anyone |
| 1 | Closest | minimum path distance (`_blobmap` flood-fill from the mover, `ovl_0118`) |
| 2 | Low hp | minimum `c_hitpt` |
| 3 | Low agi | minimum `c_agility` |
| 4 | Magic-user | `c_magicused != 0` (has cast this fight) |
| 5 | Archer | target's readied weapon is a bow (type 3) |
| 6 | By race | `c_race == D06 ptr3[LDRACE]` (prey race, 0xFF = none) |
| 7 | Leader | `c_state & 4` |
| 8 | Prot leader | target is attacking our leader (`c_target == OWNLDR`) |
| 9 | Attacker | target is attacking me (`c_target == c_recno`), lowest HP among those |
| 10–15 | friendly list | anyone / lowest HP / highest `c_strngth` / self / magic-user / leader |

4. **Spell or weapon**: `RndCo(100) < D06 ptr0[LDRACE]` (per-race casting chance, e.g. Wizard 90, Elf 40, Orc 20) → cast (`ovl_1553`: a monster's two known spells `c_spell1/2`, or Restsoul vs undead; the target search is the *Spell AI* in spells.md). Otherwise: unarmed/bow holders (weapon type 0 or 3 without arrows, item 0x51) re-equip from the per-race weapon preference list `D06 ptr12[22·race]` (first listed weapon in inventory with `wp_minst ≤ c_strngth`; bows only when the target is not adjacent).
5. **Move or attack**: with a bow (type ≥ 3) and a clear line of fire (`ovl_1af1` → `_PATHBLK == 0`) the record shoots; otherwise if the target is within Chebyshev distance 1 it attacks (`_Attack`), else it steps toward the target (`ovl_0ea6`: among the 8 neighbours keep those whose `_blobmap` distance is lower; pick one at random, `RndCo(count)`), or, when no path exists (`_blobmap == 0x7E`), moves at random (message "Random move").
6. **Flee** (`ovl_0f32`, `c_state & 0x40` set by Terrify or by `_fleetbl` squares): if the record stands on a flee square (`_fleetbl`, −1-terminated list of positions) it is removed (`c_state |= 0x10`, position −1, "flees"); else it heads for the arena exit opposite the enemies' centroid (quadrant table), and a fleeing leader hands leadership to another monster of its race (`ovl_1089`, `c_state |= 4`), after which, on a `RndCo(2)` roll, every other monster of that side with bravery < 12 has `c_bravery` set to 0 (panic spreads).
7. **Globe traps** (`INT61_1f/42`): a hero can drop item 0x39 (globe) on a square within 13; the first record to step on it takes `40 + RndCo(30)` (60 if the roll ≥ 25) through `_MDamage`.

### Combat AI record `D06.MCV` (743 bytes, same 20-pointer header as the location records)
| ptr | contents (indexed by race) |
|---|---|
| 0 (0x28) | spell-cast chance % per leader race: Human 50, Wizard 90, Elf 40, Halfling 70, Dwarf 25, Orc 20, Zorlim 60, … |
| 1 (0x52) | target criterion triples `{critA, chance%, critB}` |
| 2 (0xD0) | fallback criterion triples |
| 3 (0x14E) | prey race for *By race* (0xFF none): Dwarf→Orc, Orc→Dwarf, Zorlim→Wizard, Tekhir→Elf, Troll→Human … |
| 8 (0x22B) | monster count table (7 bytes per location difficulty) |
| 12 (0x263) | weapon preference per race, 22 item numbers each (item − 9 = weapon index) |

## Open items
- `ovl_0a2b/ovl_0394`: weapon → type lookup table is built at run time (P06 private data).
- Parley details: truce/bribe amounts (`G_BRIBEAMT`, V06 strings 0x337/0x3CB), song effects on monsters (`INT61_1d`, HERO+0x23 music skill).
- INT 61h = V06 (see spells.md / overlays.md); P06's own INT 61h uses (0x00, 0x2B, 0x25, 0x23, 0x27–0x2A, 0x22, 0x2C, 0x24) are the arena/blob-map helpers, not yet described.
