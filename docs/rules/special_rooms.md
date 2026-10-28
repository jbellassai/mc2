# Special rooms: casinos, teleportals, temples, gates (program P09)

Sources: `P09.MCO` (`decomp/overlays/P09.c`, asm via `tools/dis.py`), room files `D13` (casino), `D61` (teleportal), `D59` (temple), `D14` (gate), `D74` (meeting hall). Room ids come from the door/feature record (`services.md`, *How a door becomes a room*); P09 uses the same boundary table as P05 (file 0x66) so `_rmtyp` = 7 casino (ids 0x90–0x97), 10 teleportal (0xA8–0xBA), 11 meeting hall (0xBB–0xBF), 12 world temple (0xC0–0xC7), 13 dungeon temple (0xC8–0xCF), 14 gate (0xD0–0xD7); index-in-kind = `id − base`.

## Entering and leaving (`ovl_0202`)

- `OV_0x181` = `id − base` (the index within the kind). The room map is G-file chunk `maps[OV_0x181 + 1]`, plus 8 for a dungeon temple (`OV_0x158`, `_rmtyp 13`); the exit, NPC and townsfolk lists are skipped the same way (`ovl_16cd`), so dungeon temples use entries 8–15 of D59's lists.
- Party placement (`ovl_1720`): base `(P09[0x0F + rmtyp], P09[0x18 + rmtyp])` = (4,5) for every kind except the gate, (4,6), plus the formation cell offsets (file 0x28 / 0x31, as in P05).
- World-map rooms (temples, gates) are features of the region record (`roomptr`, program 9); their exit records name pgm 1 (the world) with the window `tx, ty`, so the party comes back at `tx + 5, ty + 4`, not necessarily where it went in.
- Stepping onto an exit (`_RMove` 2) asks "Do you want to leave now?" (`_comtxtptr`, comtxt 0x23); Yes follows the exit record.

## Casino (`_rmtyp 7`, D13 "Gambling H", ids 0x90 Telermain, 0x91 Ussa, 0x92 Glusaga, 0x93 Deadwood, 0x94 Hugda-Hag, 0x95 Drakhelm)

- House bank `_casino[idx]` (8 words): +200 per month up to 1000 (`P92 ovl_02ac`). Bank 0 → "The house tables are closed."; player gold 0 → "You can't be bold without some gold."
- Bet `b` = `GetNum(1 … min(gold, bank))`. Dealer rolls `RndCo(6)+1 + RndCo(6)+1`, player rolls the same 2d6. **Player wins if player == 2 or player > dealer**: `gold += b, bank −= b`; else `gold −= b, bank += b`. Bank reaching 0 → "%h has broken the bank!"; gold 0 → "So goes the last of %h's gold." Loop "Will %h play again?".
- It runs on *Talk* (`_swgreet == −3`, L_066f) with the acting member's gold. Order: no gold → text 2; bank 0 → text 1; else "Good %a, sport. Care to try your luck?" (0; No ends silently), Yes → the rules (3), then "How much will %h bet (0-%i)?" (4, 0 stops), "The gambler rolls %i." (5), "%h rolls %i." (6), wins/loses (7/8). Leaving the table: "Good %a, sport." (12) plus " Come again soon!" (13) when the hero has less gold than on sitting down. `%a` = `_SetTxtToD`: the word `TODWORDS[hour]` (EXE DS:0x38F2: hours 1–11 morning, 12–17 afternoon, 18–23 and 0 evening) from the list at DS:0x41E0 (morning, afternoon, evening, day, night).

## Teleportals (`_rmtyp 10`, D61, 17 rooms: towns Wanasol 0xAA, 0xAB…, dungeons Cellars 1 0xA8, Shann 6 0xAB, Katarra 0xAC, Dorak 2 0xAE, Dorak 7 0xAF, Catacombs 0xB0, Maratul 1 0xB1, Namaz 2 0xB2, Drakhelm 1 0xB7, Ruz 1 0xB8; world map 0xA9 Krum, 0xAD Tundra, 0xB3 Altesia, 0xB4 Kar'lomug, 0xB5 Isle of Winds, 0xB6 Rhon)

Three pedestals at `(4,3) (5,3) (6,3)`. *Use* one of the five pieces — Cylinder 0x3A, Cone 0x3B, Cube 0x41, Sphere 0x42, Pyramid 0x43 — and *Mark* a pedestal within reach (`ChkRng 1`): the piece is consumed (`DecObj0`) and drawn (tiles file 0x50). When all three are set the triple `{left, middle, right}` is looked up in **D61's `hroomptr`** (13-byte rows `{p0,p1,p2, curlev, curseg, locspec, currm, curmpg, curtils, curvar, ?, x, y}`); a hit plays the tile-explosion effect and teleports the party; a miss prints the common "nothing happens" text and clears the pedestals (pieces lost). All 20 combinations lead to the **world map** (`locspec 1`, program 1):

| left,middle,right | x,y | | left,middle,right | x,y |
|---|---|---|---|---|
| Cube Cube Cube | 48,19 | | Sphere Pyramid Cube | 78,47 |
| Pyramid Pyramid Sphere | 18,48 | | Cube Cylinder Cylinder | 71,3 |
| Cone Sphere Cone | 97,49 | | Pyramid Sphere Cube | 158,7 |
| Sphere Cone Cone | 158,49 | | Cylinder Pyramid Sphere | 152,85 |
| Cube Sphere Sphere | 211,60 | | Cylinder Cone Cylinder | 241,79 |
| Sphere Pyramid Cone | 230,71 | | Pyramid Cube Cube | 233,49 |
| Cone Cone Pyramid | 235,34 | | Sphere Pyramid Cylinder | 226,5 |
| Cone Cone Sphere | 210,25 | | Cube Cylinder Pyramid | 212,5 |
| Cone Cube Pyramid | 121,48 | | Cylinder Pyramid Cone | 121,36 |
| Pyramid Cylinder Pyramid | 211,54 | | Pyramid Cone Cone | 203,35 |

(`curseg` in the row = destination region, used to pick the region record.) Meeting-hall rumour: "Dulgamir … knows a teleportal combination!"

## Temples (D59; gods 0–7 Nerelnes, Oraniana, Marior, Rhokan, Balene, Fronnoxx, Senvara, Ghartel)

- Temple `id − 0xC0` / `id − 0xC8` = god `g`. **World temples** (`_rmtyp 12`, ids 192–199 on the world map: Tundra, Sariss, Oshcrun, Demonspine, Krum, Mandarg, Altesia, The Throat): *Look* at the altar tiles (0x39/0x3C/0x47) from an adjacent cell → "There is a tiny word engraved on it. The word on it is: <secret name>" (D59 `gwrds[g]`: Asharim, Kirrak, Ranalamma, Shadguram, Kimyabin, Azavaz, Urumaen, Banishahbat); from afar "%o suggests that %h move closer". Looking at the statues (tiles file 0x3D) names the god and its domain (texts 24–32: Opportunity, the Forests, the Sea, Wealth, Furious Vengeance, Jubilant Destruction, the Altesens, Glorious Death).
- **Awakening** (`_rmtyp 13`, ids 200–207: Maratul 4, Sariss, Cellars 2, Dorak 7, Isle of Winds, Mt Mandarg, Altesia, Ruz 2): *Whisper* the secret name whose index equals `g`. The god's demand (handler table P09 file 0xFCB):

| g | god | demand | effect |
|---|---|---|---|
| 0 | Nerelnes | a member already blessed by gods 1, 2 and 3 (`h_godseen & 0x0E == 0x0E`), else a Halfling | blessing only |
| 1 | Oraniana | an Elf in the party | blessing only |
| 2 | Marior | none | blessing only |
| 3 | Rhokan | a Dwarf in the party | blessing only |
| 4 | Balene | **Brennix** (0x11) in anyone's pack | the sword is taken ("my long-lost Brennix!") |
| 5 | Fronnoxx | **Somona** (NPC 31) in the party | she leaves into the god's service (assignment task 100, event 96) |
| 6 | Senvara | none | blessing only |
| 7 | Ghartel | the strongest member (`_HighStat(strngth)`) with strength ≥ 8, "a mighty warrior" | that member leaves into the god's service (task 100) |

Unmet demand → "You dare to waken me without offering <X>! 'Begone, mortals!' With a great clap of thunder" every member's HP and energy drop to 1 (`ovl_123e`). Met: "Welcome, mortals. I demand the sacrifice of <X>. Your companion %o would suit me. Do you agree?" — *No* → the same thunder; *Yes* → the sacrifice is made (`ovl_1290` builds the assignment record, drops the member's Mindstone, runs P97 with `_swass = 2`), then every party member **without** bit `g` of `h_godseen` gets the god's **blessing** (D59 `hroomptr`, lists `8+g` of `{stat offset, amount}` pairs; amount `|0x80` = only if the stat is non-zero; endurance also adds `8 × amount` to `h_hpmax`) and the bit is set:

| god | blessing |
|---|---|
| Nerelnes | dexterity +1, charm +2, intelligence +1, lockpick +9 |
| Oraniana | dexterity +1, agility +2, intelligence +1, resist +2 |
| Marior | bravery +1, strength +1, endurance +1, agility +1, resist +1, swim +9 |
| Rhokan | bravery +1, strength +2, dexterity +1, endurance +1, smith +9 and gemcut +9 (only if already > 0) |
| Balene | strength +1, dexterity +2, endurance +1, intelligence +1 |
| Fronnoxx | strength +2, endurance +1, agility +1 |
| Senvara | endurance +1, agility +1, intelligence +2, resist +1 |
| Ghartel | bravery +1, strength +2, endurance +2 |

"%o's %a increases (+%b) to %i." then "<god> returns to slumber." Gods 4, 5 and 7 add "But beware, puny mortals! %o is now in my service! Begone!".

## Gates (`_rmtyp 14`, D14 "A Gate", ids 0xD0–0xD7 on the world map)

| id | gate (text) | password (D14 `gwrds`) | where |
|---|---|---|---|
| 0xD0 | Caverns of Mandarg | suuvdaun | R33 Mt Mandarg 178,51 (Katarra road) |
| 0xD1 | Mines of Dorak | zaradenak | R43 Demonspine 95,26 |
| 0xD2 | Labyrinth of Ruz | jimmelkin | R45 Krum 231,15 |
| 0xD3 | Mines of Dorak | waharnial | R43 Demonspine 87,20 |
| 0xD4 | Tower of Shann | frilkenatz | R37 S. Misor 67,79 |
| 0xD5 | Tower of Maratul | ruandair | R47 Mandarg 216,57 |
| 0xD6 | Tower of Namaz | vumakleh | R39 Altesia 222,122 |
| 0xD7 | Drakhelm Mines | nokarvahim | R47 Mandarg 140,51 |

*Whisper* the password (its word index must equal the gate index): `_dnggates` (DS:7425) bit set, the door tiles slide open ("The gate of the %a slowly creaks open!"), and the gate stays open for the rest of the game (`ovl_15ee` re-opens it on entry). Otherwise "The gate is magically locked." Entering: "Will the party enter the %a?" → the room's exit record leads into the dungeon.

The gate is the room's exit records 1 and 2 (record 0, at (4,8), leads back to the world). Opening writes D14 `hroomptr` (4 bytes per gate: tile, ?, tile, ?; every gate uses 0x2E) onto those two squares; `spetbl` (4 bytes per gate) is the screen rectangle the opening scroll animates (`_ScrlUD`). While shut, stepping onto them prints text 10 (`OV_0x159 == 1`); open, text 9 and Yes/No (`ovl_15c9`).

## Meeting halls (`_rmtyp 11`, D74, ids 0xBB Ketrop, 0xBC Glusaga, 0xBD Drakhelm, 0xBE Llendora)

Rumour rooms: ordinary NPC dialogue from the hall's text block (D74 texts 1–13: Delfina's song, Bolumar's pearl plate, the three magic axes, Darkfinder in Deadwood catacombs, Munaks, Eldens in Tfarcdnim…).

## Port notes

Built in the web port (`web/src/special.ts`): entering from town doors and world features, placement, leaving, the casino (with the monthly refill) and the gates (Whisper is the port's H key). Talk in a casino starts the game unless it is aimed at one of the gamblers, who keep their rumours (an assumption: where the original's Talk goes is not traced). A whispered word nothing answers prints "Nothing happens." (comtxt 0x83; P09 prints `_comtxtptr`, value not traced). Not yet: teleportals, temples, the elven prince.

## Elven prince (NPC 113, `ovl_0611`)

First meeting: event 8 clear → "The elven prince glares at %h. 'Begone, and tell no one of this place!'"; event 8 set → "The elf greets %h" (C-file response 24), event 4 set and `_met[113]`.
