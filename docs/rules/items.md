# Items

Names: `_w_objects` DS:3BB7, index = item code (hero inventory `h_invitem[40]` holds codes, `h_invamt[40]` counts, `h_wears[6]` and `h_inhand` hold **inventory slot indexes**, 0xFF = none).

| code | name | code | name | code | name | code | name |
|---|---|---|---|---|---|---|---|
| 00 | Coin | 18 | Orcbane | 30 | Furs | 48 | Flute |
| 01 | Pearl | 19 | Rhokadur | 31 | Food | 49 | Orb |
| 02 | Blu Pearl | 1A | Ashbow | 32 | Potion | 4A | Horn |
| 03 | Jade | 1B | Brombow | 33 | Sermin | 4B | Conch |
| 04 | Topaz | 1C | Bonebow | 34 | Gonshi | 4C | White Scroll |
| 05 | Ruby | 1D | Elvenbow | 35 | Nift | 4D | Gray Scroll |
| 06 | Sapphire | 1E | Darkfinder | 36 | Mirget | 4E | Pink Scroll |
| 07 | Emerald | 1F | Leather armor | 37 | Luffin | 4F | Blue Scroll |
| 08 | Diamond | 20 | Ring mail | 38 | Turpin | 50 | Pick |
| 09 | Shortsword | 21 | Chain mail | 39 | Fireglobe | 51 | Arrow |
| 0A | Scimitar | 22 | Elven chain | 3A | Cylinder | 52 | Blanket |
| 0B | Longsword | 23 | Dwarven chain | 3B | Cone | 53 | Sabano |
| 0C | Broadsword | 24 | Bronze plate | 3C | Loka | 54 | Ishban |
| 0D | Greatsword | 25 | Steel plate | 3D | Medicin | 55 | Demaro |
| 0E | Elvensword | 26 | Pearl plate | 3E | Map Flask | 56 | Zoxinn |
| 0F | Brightsword | 27 | Methreal | 3F | Map | 57 | Vannex |
| 10 | Dreadslayer | 28 | Bronze helmet | 40 | Mindstone | 58 | Emenad |
| 11 | Brennix | 29 | Iron helmet | 41 | Cube | 59 | Felmis |
| 12 | Smallaxe | 2A | Steel helmet | 42 | Sphere | 5A | Crystal key |
| 13 | Hammeraxe | 2B | Elvenspun | 43 | Pyramid | 5B | Bandore |
| 14 | Battleaxe | 2C | Suede outfit | 44 | Lyre | 5C | Iron Key |
| 15 | Doubleaxe | 2D | Cotton robe | 45 | Lute | | |
| 16 | Greataxe | 2E | Silk robe | 46 | Shovel | | |
| 17 | Nalanduir | 2F | Wool outfit | 47 | Rope | | |

`h_invamt` entries above 0x80 mark a **damaged** item (high bit + damage count; repaired one point at a time by the camp *Fix* activity, `camp.md`); on the four Scrolls (0x4C–0x4F) the same bit means **deciphered** by library research (`services.md`). Weapons always carry the bit; their wear count rises in combat and breaks them (`combat.md`, *Weapon wear and breaking*).

Instruments 0x44 Lyre, 0x45 Lute, 0x48 Flute, 0x5B Bandore each carry two combat songs (`encounters.md`). Teleportal pieces 0x3A Cylinder, 0x3B Cone, 0x41 Cube, 0x42 Sphere, 0x43 Pyramid and spell books 0x53–0x59 (one per spell group) are consumed/used by the special rooms (`special_rooms.md`, `services.md`).

Every item has a base **value** in `_lootvalues` (DS:2E72, `docs/rules/economy.md`) used for loot accounting and hireling shares; shop prices come from the merchant's conversation record instead.

Weapons 09–1E map to `WEAPDATA` rows `code − 9` (table in `combat.md`). `_GetWpnSkl`: in-hand item < 0x12 → sword skill, < 0x1A → axe, < 0x1F → archery, else fist.

## Consumables (*Use*: `_DoUse`, handler table `UVECTBL` EXE 0C2F:0521, handlers FFRE 0C2F:0561–0760)
*Use* offers items 0x31–0x50 and 0x5B; `_DoUse` runs the item's handler and, if it returns non-zero, removes **one** of the item from the user's pack — instruments (Lyre, Lute, Flute, Bandore) are never used up. A handler that finds nothing to do still returns 1, so **a wasted Potion or Sermin is consumed** ("%o uses a %l.").

| item | effect |
|---|---|
| 0x31 Food | `h_lastmeal −= min(h_lastmeal, HUNGERHOURS[race])` (one meal), hunger flags updated (`time_weather.md`) |
| 0x32 Potion | **heal to full** (`h_hitpts = h_hpmax`); if Ill only up to 10 HP; **no effect if Poisoned**. In combat it also gets a knocked-down member back up (clears `h_cond1` bit 0, restores the combat record's agility/dexterity). The same routine is the *Zengrl* spell (20): `HP += magic · hpmax / 100`, capped |
| 0x33 Sermin | energy to 99, or only up to 15 while Poisoned or Ill |
| 0x34 Gonshi | `HERO+0xA5 |= 0x80`: the member gets **4 actions every round** (P94) for the current or next fight; used in combat it also sets this round's actions to 4 |
| 0x35 Nift | `HERO+0xA5 |= 0x40`: **3 shield charges** (blows fully absorbed, `combat.md` *Attack* step 4) at the start of the next fight, or at once in combat |
| 0x36 Mirget | `HERO+0xA5 |= 0x20`: the next melee hit does triple damage |
| 0x37 Luffin | `HERO+0xA5 |= 0x10`: the next attack cannot be dodged |
| 0x38 Turpin | `HERO+0xA5 |= 0x08`: the next spell is cast with magic skill 99 (`_GetMagSkl`) |
| 0x3C Loka | cures Poisoned (`h_cond1 &= ~0x08`, also on the combat record) |
| 0x3D Medicin | cures Ill (`h_cond1 &= ~0x02`) |
| 0x40 Mindstone | only the player ("only Lukas"); not in combat; runs *Recall* (P88 entry 1, `assignments.md`) |
| 0x44 Lyre, 0x45 Lute, 0x48 Flute, 0x5B Bandore | play a song (`encounters.md`, *Combat songs*; outside combat FFFAR service 0x12); not in the fight overlay's own *Use* |
| everything else (scrolls, keys, Rope, Shovel, Pick, Orb, Horn, Conch, Map, Fireglobe, shapes…) | nothing here; location programs react to the *used* item themselves (`open-questions.md` item 7) |

The 0x80 and 0x40 flags are cleared after a fight (`P95`, unless the party fled — `_endcmbt 4`); 0x20/0x10/0x08 are one-shot and cleared when consumed.

## Armour (`V06 INT61_00`, combatant built from a hero)

`c_armor = Σ armor_value[item − 0x1F]` over every worn item in 0x1F–0x2A; `c_shield = h_shield`, `c_hitpts = h_hitpts`, `c_energy = h_energy`, `c_magskl = h_magic`, weapon = `h_invitem[h_inhand]`. The value table is `D06.MCV` pointer 9 (file 0x1BA):

| Leather | Ring | Chain | Elven chain | Dwarven chain | Bronze plate | Steel plate | Pearl plate | Methreal | Bronze helm | Iron helm | Steel helm |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 1 | 2 | 3 | 4 | 5 | 6 | 8 | **10** | **15** | 1 | 2 | 4 |

Armour subtracts flat from each hit (`DAM = max(0, HIT − c_armor)`, combat.md). Nothing in the EXE or V06 restricts armour by race or strength; the camp *Put* command (`camp.md`) checks none either. Weapons do have equip checks (race, strength, broken — `combat.md`, weapon table). `LOCTYPE.pearlsw` is unrelated to Pearl plate: it marks locations whose **map** command needs a Pearl (item 1) instead of the free minimap (`P02 ovl_13c4`).

## Clothing
Items 0x2B–0x30 only matter on the world map (energy per step by weather, `time_weather.md`); a tailor's work (`_tailorcharm`) reduces the penalty.
