# Economy: trading, haggling, gifts, hireling pay

Sources: `P90.MCO` (trade overlay, loaded by `_BuySell` as overlay 0x5A; entries 0 = Buy `ovl_0792`, 1 = Sell `ovl_09b8`, 2 = Give `ovl_037c`), `FFFAR` `FAR_INCOBJ`/`FAR_OK2GIVE`, `P92 ovl_09ff` (paydays), `P95 ovl_0fc0` (post-combat loyalty), `Cnn.MCV` conversation files (merchant data, `tools/convdump.py`). Message texts quoted from the common text block `DS:09F8`.

## Who trades
`_BuySell` (EXE 2128:03E0): party members refuse ("I don't trade with my companions"). A town NPC (`_npccat == 3`) trades only if their conversation record has a shop list (`convbuf[0x34 + 2·convix]` → first byte ≠ 0xFF); otherwise "I am not interested in trade". NPC number 'D' (68) is a special case handled by `_StartGraf`.

## Merchant data (`Cnn.MCV`, see `docs/formats.md`)
NPC number *n* → file `C(n>>3)`, slot `n & 7`. Per slot: **trade skill** (byte at 0x54+slot, 0–70 in the data), **no-buy flag** (0x5C+slot: 1 = "I am not buying anything today"), and a **shop list** of 5-byte records `{item, pays_hi, pays_lo, charges_hi, charges_lo}` terminated by 0xFF. Prices are `hi·100 + lo`: the first pair is what the merchant **pays** when you sell, the second what they **charge** when you buy. All 24 files decode cleanly; e.g. C05 (town with every shop type): Shortsword 50/75, Longsword 200/300, Elvenspun 200/300, Methreal (C15) 900/1400, spell books 1200–3000/1400–4000, Food 15/30 per pouch, Arrow 15/20 per bundle.

## Lots ("a pouch")
`P90` table at file 0x0F2, pairs `{item, lot}`: Food 12, Potion 12, Sermin 18, Gonshi 12, Nift 6, Mirget 6, Luffin 12, Turpin 12, Fireglobe 6, Arrow 24. Everything else is lot 1. Weapons, armour, clothing (codes 09–30) and spell books (53–59) are traded one at a time with a yes/no ("Would you like to buy it?"); other items ask "How many will you buy?" (0–99 lots). `lot × count` must be < 100 or "That's too many!" (`ovl_0f41`).

## Haggling (`ovl_0eb1` + `ovl_0f5e`)
```
diff   = h_trade(buyer/seller hero) − merchant_skill        (signed byte)
step, div = P90 table @0x038 [item]                          (per-item pair, below)
adj    = (|diff| / div) · step                               (0 if div == 0 or diff == 0)
if hero skill < merchant: charges += adj ; pays −= adj   (floor 1)
else:                     pays    += adj ; charges −= adj (floor 1)
clamp:  charges ∈ [pays₀, 2·pays₀]      pays ∈ [charges₀/2, charges₀]      pays ≤ charges
```
(`pays₀`, `charges₀` = list prices.) So a skilled trader can push the buying price down to the merchant's own buying price, and the selling price up to the list price, never beyond. Per-item `{step, div}`:

| step/div | items |
|---|---|
| 1/5 | Food, Potion, Fireglobe, Cylinder, Cone, Loka, Medicin, Cube, Sphere, Pyramid, Pick, Arrow |
| 1/4 | Shortsword, Sermin, Gonshi, Nift, Shovel, Rope |
| 1/3 | Pearl, Scimitar, Smallaxe, Cotton robe, Mirget, Luffin |
| 1/2 | Blu Pearl, Longsword, Hammeraxe, Suede outfit, Turpin |
| 1/1 | Jade, Topaz, Broadsword, Battleaxe, Ashbow, Leather armor, Bronze helmet, Wool outfit, Map, Mindstone, Orb, Horn, Conch, the four Scrolls, Blanket, Crystal key, Iron Key |
| 2/1 | Ruby, Sapphire, Greatsword, Doubleaxe, Brombow, Bonebow, Ring mail, Iron helmet, Silk robe, Map Flask, Lyre, Lute, Flute, Bandore |
| 3/1 | Emerald, Elvensword, Greataxe, Elvenbow, Chain mail, Elven chain, Dwarven chain, Bronze plate, Steel helmet, Elvenspun, Furs |
| 4/1 | Diamond, Steel plate, Pearl plate |
| 5/1 | Brightsword, Dreadslayer, Brennix, Nalanduir, Orcbane, Rhokadur, Darkfinder, Methreal |
| 10/1 | Sabano, Demaro |
| 11/1 | Ishban |
| 12/1 | Zoxinn, Vannex, Felmis |
| 20/1 | Emenad |

Example: Methreal listed 900/1400, hero trade 45 vs merchant 45 → no change; hero 75 → adj = 30·5 = 150 → buy for 1250, sell for 1050.

Trading does **not** call `_SkillUp`; the trade skill only changes through learning (camp, P93) and scripts.

## Buying (`ovl_0792`)
List = merchant's shop list (`ListSel`). Total = charges × count; needs `h_gold ≥ total` ("%h doesn't have that much!"). Then `IncObj(hero, item, lot×count)` (fails if the 40-slot inventory is full / stack > 99) and `DecObj(hero, Coin, total)`. Buying from NPC 'X' (88) sets event bit `_events+3 & 0x40`.

## Selling (`ovl_09b8`)
List = merchant's shop list filtered to items the hero carries (`SearchInv`), excluding the slot in hand (`h_inhand`) and worn slots (`h_wears`). Count offered = `count / lot` lots ("I'll pay N coins a pouch (12)"). A Wizard (race 1) may not sell a spell book if it is the only book slot they hold ("Wizards must keep at least one book."). On "Do we have a deal?" yes: `IncObj(hero, Coin, total)`, `DecObj(hero, slot, lot×count)`.

## Item values (`_lootvalues`, DS:2E72, 93 words indexed by item code)
```
Coin 1 | Pearl 25, Blu Pearl 200, Jade 50, Topaz 100, Ruby 200, Sapphire 300, Emerald 500, Diamond 800
swords 09–11: 40, 80, 150, 200, 400, 800, 1000, 1000, 0(Brennix)
axes 12–19: 50, 120, 200, 250, 400, 800, 1000, 1000
bows 1A–1E: 80, 250, 350, 500, 800
armour 1F–2A: 75, 125, 220, 250, 250, 300, 400, 500, 800, 50, 100, 180
clothing 2B–30: 200, 80, 30, 100, 80, 100
31–3D: Food 2, Potion 3, Sermin 2, Gonshi 4, Nift 10, Mirget 10, Luffin 4, Turpin 5, Fireglobe 20, Cylinder 10, Cone 10, Loka 50, Medicin 40
3E–4F: Map Flask 200, Map 10, Mindstone 0, Cube 1, Sphere 1, Pyramid 1, Lyre 100, Lute 200, Shovel 50, Rope 35, Flute 100, Orb 0, Horn 500, Conch 500, scrolls 1, 1, 1, 1
50–5C: Pick 50, Arrow 1, Blanket 60, books 1000, 1250, 1000, 1500, 1500, 2000, 1250, Crystal key 1, Bandore 200, Iron Key 250
```
Used for `partybucks` (loot found) and `mybucks` (value of everything handed to a hireling), not for shop prices.

## Giving (`ovl_037c`, `FAR_OK2GIVE`)
Only a player/volunteer (relation < 2) can give; never Brennix (0x11), the item in hand ("%h can't give what is in hand", msg 0x31) or a worn item (0x30); a short item list cannot be given to non-party NPCs (msg 0x2F). Coins ask for an amount (≤ `h_gold`). Giving to a companion (npc < 0x20) puts the item in their hero record, or adds coins to their assignment record's `as_gold` if they are away on a job. Giving to a town NPC checks the NPC's **gift list** (`convbuf[0x24 + 2·convix]`, 5-byte records `{item, min_qty, msg_if_fewer, msg_if_enough, event_bit}`): enough → sets `_events` bit and prints the "thanks" text, else the "not enough" text; an item not on the list → common message 0xD4. The Orb (0x49) skips `FAR_OK2GIVE` (P90 `ovl_0621`): "%h gives the Altesen's orb to %o." (P90 text 0, texts at file 0x113); to Prince Jemil (NPC 166) " As the prince takes the orb in his hands, its glow becomes more intense." (18), event 123 and the Orb leaves the pack; to a Marked One (P90 0x10B `[137, 152, 77]`, bits 0x10E `[4, 8, 16]` of `_events+4` = events 34–36) not yet marked: the bit, then either the silvery glow when it completes all three (15, 16) or the blaze in that one's colour (5, 6+k golden/crimson/cerulean, 9, 10, 11+k, 14), the Orb handed back; anyone else, or a Marked One again: " %o looks at the orb and hands it back to %h. " (1) + `RndCo(3)` of 2–4. `FAR_OK2GIVE`'s refusal list is FFFAR file 0x2235 (8 bytes: Brennix, Orb, the White/Gray/Pink/Blue Scrolls, Crystal key, Iron key → comtxt 0x2F); `_BookChk`: a Wizard keeps at least one book (0x2E "Wizards must keep at least one book."), and giving the book being learnt from (`h_actvty` 1, `h_actmisc` in its six spells) stops the learning. The prompt is comtxt 0xD3 "What will %h offer?"; equipment (9–0x30) goes whole, coins and stacks ask a count (0 cancels). The item leaves the giver's pack even when the person has no use for it. Port: *Offer* in a conversation (`main.ts` *offer*, `Talk.gift`); the count prompt's text (`ovl_1097`) is not traced. Gift lists are how quests like "a ruby for the orphans of Ussa" (C10 npc 80, event 45) or "50 coins for a round for the house" (npc 85, event 47) are scripted — `tools/convdump.py` lists all of them.

## Hirelings: the fair share (`P92 ovl_09ff`, run from the hour tick)
Companions with `h_relatn == 2` (Eldai, Kruga, Madir, Nimmo, Argas) join "for a fair share of the treasure we find". On hire (`P97 ovl_0612`) `h_paydays[4]` = hire date −1, +6, +13, +20 (mod 30) and `h_partybucks = h_mybucks = 0`. Then:
- `h_partybucks` += loot value found by the party (combat loot P95, dungeon chests P07, town finds P02; cap 30000) for every hired member present.
- `h_mybucks` += `lootvalue[item] × count` for everything given to that member (`FAR_INCOBJ` → `ovl_2402`, cap 30000).
- On a payday at **17:00** the new attitude is previewed; if it would be ≤ 5: "This has not been a profitable week for me, %o. I may have to seek other employment."
- At **18:00** it is applied and both counters reset; if the result is ≤ 3 the member gets `h_attitude = 0xFF` and leaves ("Farewell, %o. I'm off to seek my fortune elsewhere.", dismissal via `_ChkDepartures`/P97).
```
if mybucks < 100:  attitude' = min(mybucks, attitude × mybucks / 120)
else:  share = partybucks / 4
       if (share & ~31) == (mybucks & ~31): attitude unchanged
       else attitude' = min(200, attitude × mybucks / share)      (share floored to 1)
```
So a hireling expects roughly a quarter of the party's take; giving them less than ~5 coins' worth in a week sends attitude to ≤ 3 and they leave. Attitude is 0–200 (`FFSAVA`: Buzbazgut 200, Somona 20).

## Volunteers after combat (`P95 ovl_0fc0`)
For each volunteer (`h_relatn == 1`) after a fight: `attitude = max(0, attitude + h_loyalty − 20)`. If attitude ≤ 40 and `RndCo(80) ≥ attitude` and `RndCo(12) ≥ h_loyalty`, the member leaves the party (P95 local text 0x10D, slot freed, `_swass = 3`). Loyalty is 0–12 per companion, so every fight costs 8–20 attitude; nothing in the trade code raises it; the only increase is +1 per day in the party up to 100 (`npcs.md`, *Attitude*).

## Other gold sinks
- `P01 ovl_0fcc`: a ship captain's anchored-wait days, `days × rate` (`ships.md`).
- `P05`: 200 coins to rent a spell-book group at a wizards' lodge (`services.md`).
- `P09` puzzle rooms compare `h_gold` against a local price `OV_0x767`.
- Captive ransom (`_capcost`) is not referenced by any decompiled code.
