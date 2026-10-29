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

### Weapon wear and breaking (`P06` 0x785–0x826, 0xA6E)
A weapon's `h_invamt` byte is `0x80 | wear` (all weapons in the shipped saves carry the bit; 0x80 = like new). Only a party member's readied weapon (`h_inhand`) is affected, and never an *unbreakable* one (`wp_unbreakable`):
- **Break check** after an attack that lands (result 1, 2 or 0xFF): `wear ≥ 90` → breaks; `25 ≤ wear < 90` → breaks if `wear/2 ≥ RndCo(100)`; below 25 never. Breaking sets the byte to `0xE2` (wear 98), sheathes the weapon (`_Sheathe`) and prints "%h's weapon breaks!" (comtxt 0x76).
- **Wear** +1 after every attack except a dodge (result 0) or no target (4).
- *Draw* refuses only a byte above `0xE3` ("It's broken!"), so a broken weapon (wear 98) can be drawn again and will break on its next landed blow; camp *Fix* lowers wear by one per successful smith roll (`camp.md`). Whether the +1 wear of the breaking blow itself is applied (98 → 99) was not traced; either way a broken weapon is still usable until wear passes 99.

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

"min str" (`wp_minst`) is subtracted in the hit formula, so strength above the minimum is what counts. It is also the equip requirement: drawing a weapon (`_DrawWeap`, EXE 0957:07F0; the list from `FAR_WEAPSEL` offers inventory items 9–0x1E) refuses when `wp_race ≠ 0xFF` and `≠ h_race` ("Only a %a can wield that.", comtxt 0x103), when the item's `h_invamt ≥ 0xE4` ("It's broken!", 0x39), or when `h_strngth < wp_minst` ("%h is not strong enough to wield that!", 0x69). Otherwise `h_inhand` = that slot ("%h draws …"). *Sheathe* sets `h_inhand = 0xFF` (fists) for one member or the whole party.

## Races (`DS:409x` name table; `h_race` / `c_race`)
0 Human, 1 Wizard, 2 Elf, 3 Halfling, 4 Dwarf, 5 Orc, 6 Zorlim, 7 Tekhir, 8 Troll, 9 Goblin, 10 Sandgu, 11 Slime, 12 Minotaur, 13 Domug, 14 Skeleton, 15 Zombie, 16 Kurdazi, 17 Jerrah, 18 Barg, 19 Zebani, 20 Gragan, 21 Mongor, 22 Fermigon, 23 Gnoll, 24 Ogre, 25 Gaem, 26 Zumagin, 27 Hibliss, 28 Vankruh, 29 Naur, 30 Zakhad, 31 Urgodot, 32 Doombeast, 33 Mizigu, 34 Aciden, 35 Flamebelly, 36 Dreadknight … Party races are 0–5 (six rows in `_maxtbl`). Monster stat records (`MSTATS`, 23 bytes) are reached as `_monsptr[race − 5]`.

## Skill advancement (`FAR_SKILLUP`, INT 62h AH=0x30; called after a successful attack or a skill spell)
```
idx   = weapon type − 1  (sword 0, axe 1, archery 2, magic 3 when casting, fist 4 when unarmed)
skill = HERO[0x17 + idx]               (h_sword, h_axe, h_archry, h_magic, h_fist)
only once per skill per combat (G_sklbits mask); only if skill < _MaxSkill(hero, idx)
chance = base[idx]                     (FFFAR file 0x372A: sword 30, axe 15, archery 25, magic 20, fist 25; 0 for every other skill)
         + (50 − skill)/4   if skill < 50
         − (skill − 50)/2   otherwise (min 1)
if RndCo(100) < chance: skill += 1 (`_IncSta`, capped), message "skill improves", sound 0x0D
```
The same roll serves every non-combat skill through `_SkillUp0` (INT 62h AH=0x31) with `_zp_0A` = skill index (0x17+idx = the HERO field): base 0, so a skill below 50 improves with chance `(50−skill)/4` % per successful use and one at 50 or above with 1 %. The once-per-combat masks (file 0x3725: 0x80,0x40,0x20,0x10,0x08) apply only to the five combat skills.
`_MaxSkill` returns `_maxtbl[idx·6 + h_race]` (DS:2C7E, 120 bytes = 20 skills × 6 races, full table in `skills.md`; first rows 99,40,75,60,60,75 / 75,10,25,50,99,50 / 80,25,99,80,75,50 / 75,99,75,0,0,0 / 99,40,99,50,75,99 / 99,30,99,99,10,30) and 0 for magic when `h_magic == 0`. Row order = skill index (sword, axe, archery, magic, fist, swim, trade, …, leadership), column = race (Human, Wizard, Elf, Halfling, Dwarf, Orc); see `skills.md` for the whole table.

## Energy and fatigue
`_DecSta(hero, field, amount)` subtracts with floor 0. `_IsHeTr(hero)`: energy 0 → `HERO+0xBD |= 0x10` (exhausted); energy < 15 → `HERO+0xBE |= 0x20` (tired), else cleared.

## Combat flow (`_DoACmbt` → P96 setup → P94 fight → P95 aftermath)
1. `_DoACmbt` loads P06 at 0CA8:2000 (room half), V06 into `_rvarbuf` (INT 61h), then runs **P96** at 0CA8:0000: builds the 24 `CMBTNT` records (`ovl_020a`: party slots 0–5 from the heroes via `ovl_0f2a`, monsters from the encounter group `_grpsptr[grpno−60]` or `_monstlist`, count = `ptr8[7·diff] + seed mod (ptr8[7·diff+1] − ptr8[7·diff])` when the group gives none (`encounters.md`)), places them on the 11×9 arena (*Arena placement* below), rolls the monsters' attitude (`ovl_0b5c`) and, unless it is an ambush or a street fight, shows the pre-fight menu (*Talk before a fight* below).
2. If `_endcmbt == 0`, **P94** runs the fight (`ovl_00b4` → `ovl_02e8`, rounds until `_endcmbt != 0`), then **P95** handles the aftermath (loot, resurrection prompts).
3. INT 61h/08 (`V06 INT61_08`) sets `_endcmbt` after every action: 1 = no living monster left (win), 2 = every party member dead, 3 = every party member fled/removed.

### Arena placement (P96 `ovl_0f2a` heroes, `ovl_1037` monsters)
`_cmbtyp` tells where the fight started: 1 = wilderness (`P01`), 0 = town street (`P02`), ≥ 2 = a dungeon/room fight (5 = the special stronghold fights checked by the EXE). The **side code** `_rmdata+6` (6–9; always 6 in the wilderness, otherwise the `type` byte of the entrance/spot record the party came through, also used by `P07` when the party enters a dungeon room) picks a formation `f = side − 6`.
- Heroes: wilderness → formation 0; town → each hero keeps its street position relative to the view (`p1x/p1y − OV_0x18c`); rooms → formation `f`. `_setupxy` (48 B, written at new game from P81 file 0x162F) = 24 x then 24 y bytes, member `m` of formation `f` at index `6f+m`:

| f (side) | x | y | party stands |
|---|---|---|---|
| 0 (6) | 4,4,4,3,3,1 | 2,4,6,3,5,4 | left |
| 1 (7) | 3,5,7,4,6,5 | 3,3,3,2,2,1 | top |
| 2 (8) | 6,6,6,7,7,9 | 2,4,6,3,5,4 | right |
| 3 (9) | 3,5,7,4,6,5 | 5,5,5,6,6,7 | bottom |

- Monsters (P96 file 0x19 = x ranges, 0x29 = y ranges, `{lo,hi}` **byte** pairs, 8 each: sides 6–9 melee, then sides 6–9 casters; a random cell in the rectangle moved by `_PlacePerson`, re-rolled until the square is free and reachable from the first hero (`_blobmap` < 100, flood-filled over the background; P96 `ovl_10ec`). Wilderness fights (`_cmbtyp` 1) use side 6's rectangles like rooms; only **street** fights (`_cmbtyp` 0, ambushes) take a cell of the whole 11×9 view: index `RndCo(99)`, then +17 mod 99 until a free reachable one (correction: this scan was earlier attributed to the wilderness). Heroes: wilderness formation 0, rooms formation `side − 6` (both via `_PlacePerson`), street = their squares relative to the view (`_p1x/_p1y − _winxy`):

| side | melee monsters | casters (`c_magskl ≠ 0`, except Vankruh and Doombeast) |
|---|---|---|
| 6 | x 6–10, y 0–8 | x 10, y 0–8 |
| 7 | x 0–10, y 5–8 | x 0–10, y 8 |
| 8 | x 0–4, y 0–8 | x 0, y 0–8 |
| 9 | x 0–10, y 0–3 | x 0–10, y 0 |

So the party always enters from one wall, melee monsters fill the far half and spellcasters hug the far wall. Monster records also get `c_alignmnt = 1`, `c_energy = 99`, `c_target = 0xFF`, the leader rank (file 0x39) and the undead flag (file 0x62 → `c_state |= 2`).

### Talk before a fight (P96 `ovl_0b5c`, menu 10, `ovl_06e7`)
Texts are V06's own table (`_txtptr` = V06 word 5 = file 0x0B, `ModTxt(n)`); `%l` is the last `SetTxt…` word (the kin name or the attitude).

**Who talks.** `OV_0x192` = the group's starred fourth entry, the leader added on top of the count (`ovl_06b8`, `encounters.md`); a group without one has no speaker (0). **Attitude** `OV_0x197`, rolled once at set-up, `_w_attitudes` = Panicky, Frightened, Nervous, Cautious, Greedy, Eager to fight, Hostile, Enraged:
- no speaker → 6; speaker race ≥ 25 (Gaem and up) → 7;
- else M = Σ over the monsters (`c_alignmnt` 1, not `c_state & 8`) of `hp + c_magskl` (+10 when `c_rdywpn` ≥ 0x1A, a bow), P = Σ over the party of a worth by race (P96 file 0xB3F: Human 40, Wizard 60, Elf 30, Halfling 0, Dwarf 50, Orc 20); `M / P` ≥ 2 → 5; = 1 → `[3,4,4,5,5,5][RndCo(6)]` (file 0xB56); 0 → `T[(M mod P) / (P / 8) + RndCo(4)]` with T = file 0xB4B `[0,1,0,1,2,2,1,3,2,5,3]` (the index can run on into the 0xB56 table). An all-Halfling party (P = 0) would divide by zero.

**Advice** (`_Advice`; not in street fights (`_cmbtyp` 0), not against Vankruh, and only while DS:0x79E6 is set, which P01 sets for every world-map fight — other callers not traced, the port assumes every non-street fight): `RndCo(100)` ≤ the party's best **soul reading** (`_HighStat` 0x20) → "The monsters appear to be %l." (30) when that member is the acting one, else "%o thinks the monsters seem %l." (29), `%l` = the attitude.

**Menu 10**: Draw, Recall, Talk, Look, Begin, Sheathe; direction keys move the heroes (`_RMove`). Begin starts the fight. **Talk** opens menu 14: Rally, Greet; both start the fight except the first Rally case.
- **Rally**: fewer than 2 in the party → "There is no one to rally!" (0), back to menu 10. Else `RndCo(2)` = 0 → "The enemy attacks!!" (4), `_ambflg` = 1 (the monsters move first). Else "%h rallies the team with a moving speech!" (1) and `RndCo(100) < h_ldrshp` of the acting member: every other member's bravery `+= RndCo(3)+1` and agility `+= 4`, each then capped at 12 (a higher agility drops to 12), "All members get a temporary (+%b) boost of courage and (+%i) agility!" (2); P95 restores both from `_savcrg`/`_savagi` after the fight. Failure: "Unfortunately, they are not impressed!" (3).
- **Greet** (hail the leader). Attitude 6 → "The monsters do not understand %h." (5), 7 → "The %a leader will not discuss a truce!" (6); both then "The enemy attacks!!" with `_ambflg`. Otherwise "%h hails the %a leader." (7), "The %l glowers at the party." (8) and the attitude's handler (tables file 0x94B, Yes-handlers 0x957; `_SetYN` 0 = Yes):

| attitude | handler | text | Yes |
|---|---|---|---|
| 0 Panicky | every monster `c_state |= 0x40` (routed), `_ambflg` | "Suddenly, the %l begins to gibber in panic!" (31) | — |
| 1 Frightened | `_endcmbt` = 1: a won fight, P95 loots every monster still on the board | "…falls to its knees. 'We beg you to spare our miserable lives…'" (33) | — |
| 2 Nervous | ransom = 3 × monsters (`_BRIBEAMT` = +amount) | "If we give you %i coins, will you let us depart?" (34) | `_IncObj` coins to the acting member |
| 3 Cautious | truce | "'We have no quarrel with you at this time…' What say you to a truce?" (35) | — |
| 4 Greedy | bribe = min(100 × party members, the party's coins) (`_BRIBEAMT` = −amount) | "For a price, we will ignore this meeting… %i coins?" (36) | members pay in slot order until it is paid |
| 5 Eager to fight | `_ambflg` | "Then the %l grins and points at %h. The monsters rush to the attack!" (32) | — |

Yes on 2–4: "The monsters leave." (37), every monster `c_state |= 0x10` off the board, `_endcmbt` = 4; No: the fight begins. P95 turns `_endcmbt` 4 into 1 (so the guard or patrol counts as beaten), skips "VICTORY!", keeps Gonshi/Nift, and finds no loot (no monster left; `_BRIBEAMT` ≠ 0).

**Vankruh** (first monster race 28): Greet passes only if no party member has a weapon ready (`c_rdywpn` 0xFF, so Sheathe first): comtxt 0x108 (the rhyme), events 66 and 150, `_endcmbt` 4; otherwise comtxt 0x107 "Vankruh's eyes widen in affront and it attacks!" with `_ambflg`.
**Sheathe** (`_Sheathe`, EXE 0957:0930): `_AllDoit` ("Is this order for everyone?", comtxt 0x3C, with 2+ members): Yes every member, No the acting member; `h_inhand` = 0xFF and in a fight `c_rdywpn` = 0xFF and the fist skill, then "Done." (0x37). Draw and Recall here are the combat menu's, for the acting member.

Port (`main.ts` *prefight*, *sheathe*, *greet*): Draw, Recall, Talk (Rally, Greet with Vankruh), Begin, Sheathe; Draw and Recall ask which member acts. Look and moving before the fight are not built.

### Wilderness fights (P01 `ovl_0846`)
After a world-map step P01 checks the party's square for an uncleared **guard spot** (region `gwrds` `{x, y, group}`, `_grdsta` bit `region·8 + n`, `_ctype` 0) or else a living patrol (`_ptrlxy`/`_ptrlsta`, `_ctype` 1, group `newsr[n & 7]`, `encounters.md` *Patrols*). Either way: `_grpno` = the group, `_terrain` = terrain class of the square, `_diff` = P01 file 0x33A `[region]` = `[0,7,3,4,2,1,5,6,4,3,3,4,5,7,6,5]`, `_cmbtyp` 1, side `_rmdata+6` = 6, the window stays (`_pwinxy = _winxy`, so after the fight the party stands on that square), and the tileset is the terrain's from P01 0x36A (`ovl_09bf`, the same as a mushroom patch); `_ambflg` = 1 when camping (`_swcamp`) and no party member is on watch (`h_actvty` 9). The arena is G00 chunk `_terrain` (`formats.md`). P01 draws each uncleared guard spot in view as E00 icon 0x0F (a skull, `ovl_0833`). Victory sets the guard's `_grdsta` bit.

### The combat menu (`_Menu(11)`, P94 `ovl_015e` by `_mnusel`)
Attack (7), Draw (0x0E, `_DrawWeap`, no action used), Head (0x13, auto-combat with a speed digit), Look (0x19), Magic (0x1B), Pass (0x1E: `c_removes = 1`, then the action is spent), Recall (0x23), Use (0x2B: only items 'J', 'H', 'D', 'E', '[' and '9' do something), Will (0x2E: this member fights on auto). Moving is a direction key (`_RMove`), one action per step. `_RMove` returns 1 when the step runs into someone: a hostile monster is then attacked (P94 `ovl_01ad` → `ovl_09e8`, unless the weapon is a bow); it returns 2 for a step off the 11×9 arena: the flee prompt (P94 `ovl_1c80`/`ovl_1b32`, then Yes/No), and Yes takes the hero off the board (`c_state |= 0x10`, position −1, `_p1x/_p1y` = 0xFF). When the player character flees, `ovl_09a8` first checks every other member (`ovl_0a6f`) and refuses with comtxt 0x114 "%h refuses to part with the %a." — the item test was not traced. `_endcmbt` 3 = no party member left on the board and not all dead.

**Flee squares** (`_fleetbl`, wilderness, P96 `ovl_0c5c`/`ovl_0c6f`): the arena's edge squares (row 0, column 0, row 8, column 10, each moved one step inward where `_ChkDoor` reports a door) whose `_blobmap` value from the first hero is below 100, the flood-fill run on the background only (`_bkonly`). A routed monster standing on one leaves (P94 `ovl_10ef`: "%a flees!", comtxt 0xCA).

### Messages of a blow (P06 `ovl_0bc2`)
`"%a" " hits " "%a" "."` (comtxt 0x46, 0x47, 0x46, 0x10), then `" -"` (0x4A) and the hit value when the line has room; a new line `"Dam:"` (0x4B) damage, `" (A-%b)"` (0x4C) armour — or `" (SH:%b)"` (0x57) shield for magic, `" (NF:%b)"` (0x58) Nift charges left —, `" HP:"` (0x4D) the target's HP. A knockdown adds `"CRITICAL HIT!"` (0x48) and, unless the target is a Dreadknight, `"%a is wounded."` (0x49). A dodge prints nothing (only the side-step shows).

### Attack direction and the dodge step (P06 `ovl_0b2b`, `ovl_0fcf`)
Directions 0–7 = W, N, E, S, NW, NE, SE, SW (dx P06 file 0x93 `[-1,0,1,0,-1,1,1,-1]`, dy 0x9B `[0,-1,0,1,-1,-1,1,1]`). With `dx = target.x − attacker.x`, `dy = attacker.y − target.y`, the index `(dx<0)·8 + (dy<0)·4 + (3|dx| ≥ |dy|+2)·2 + (3|dy| ≤ |dx|+1)` selects from P06 file 0xB0B `[1,–,5,2,3,–,6,2,1,–,4,0,3,–,7,0]` (– never occurs). A dodging target tries direction `D06 ptr10[dir·2 + 1]`, then `[dir·2]` (e.g. attacked from the south it side-steps E, else W), taking the first free square without a globe; if neither is free it stays.

### After a blow (P06 `ovl_050a`)
A hero's attack costs **2 energy** (`h_energy −= 2`, floor 0, `_IsHeTr`). A target that was hit (result 1/2) and is still alive turns on the attacker (`c_target`, `c_targx`, clears Terrify 0x40) when `RndCo(100)` exceeds its `c_intel`. A killed target becomes `c_health 0x80`, `c_state` 0x80 (keeping the undead bit), energy 0, and every record targeting it forgets its target (`ovl_0adb`).

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
| 4 (0x1A2) | auto-hero (P94 `ovl_0a98`, indexed by the side leader's race `_LDRACE`, so the party leader's race decides for everyone): chance % to eat a **Gonshi** each action when not already under it: `[45, 60, 30, 25, 40, 25]`; the checks run Gonshi, then Potion, then Sermin, each only when the item is carried (`ovl_148f`), and use one action |
| 5 (0x1A8) | auto-hero eats a **Sermin** when `h_energy <` this: `[20, 30, 20, 10, 5, 5]` |
| 6 (0x1AE) | auto-hero drinks a **Potion** when HP `≤` this: `[20, 25, 15, 35, 10, 10]` |
| 8 (0x22B) | monster count table (7 bytes per location difficulty; bytes 0/1 = min/max+1 of a group without its own count) |
| 9 (0x1BA) | armour values for items 0x1F–0x2A (`items.md`) |
| 10 (0x1C6) | dodge-step directions by attack direction (P06 `ovl_0fcf`, entry `CURDIR·2 + n`, tried in turn) |
| 12 (0x263) | weapon preference per race, 22 item numbers each (item − 9 = weapon index) |

## Open items
- `ovl_0a2b/ovl_0394`: weapon → type lookup table is built at run time (P06 private data).
- Song effects: `encounters.md`. Monster stats, groups, loot: `encounters.md`.
- INT 61h = V06 (see spells.md / overlays.md). The services P06 itself calls are small helpers: 0x00 builds a combatant from a hero (armour, `items.md`); 0x22 `_OrTile` at the current square; 0x23 index (0–23, 24 = none) of the combat record standing at square DX; 0x27/0x28 redraw the attacker/target sprite (`_PDraw`), 0x29/0x2A restore the background under the attacker/target; 0x2B idle animation of living records (random 0–50 tick timers); 0x25 fills `_blobmap` (walkable cells for movement and pathing); 0x2C a table lookup; 0x24 the Doombeast rule below.

### Doombeasts (race 32: P96 `ovl_1405`, V06 `INT61_24`)
Every Doombeast placed in an arena brings **five images** (six records; `_doombstlst[record]` = group number, with bit 0x80 on the real one). Attacks on a Doombeast never miss (dodge skipped, see *Attack*). Hitting an **image** makes it vanish (record removed, `c_state = 8`); killing the **real** one removes all of its images. P96 `ovl_064d` re-places each living real Doombeast together with its images (effect `MultiThing(9)`); exactly when in the round it runs was not traced.
