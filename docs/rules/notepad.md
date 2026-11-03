# The notepad (P70, `_WriteNote`)

A message printed with `_PrtScrap(level)` is also appended to the notepad (EXE `_WriteNote` 1a95:0f06, via FFFAR `FAR_PRTSCRAP`) when `level ≤ _e_notelev` (the installed game's setting: 0 None, 1 Minimum, 2 Normal, 3 Maximum; level 0xFF = never). Each entry keeps `_date`, `_month`, `_year`, `_minute`, `_hour`, the acting member's square (`_p1x/_p1y[_curpla]`; on the world map slot 0) and the 10-byte `_locnm`, then the text (at most 400 bytes); a full notepad drops new entries. Writing clears event bit 153 (`_events` byte 19 mask 0x2), which P70 sets when the notepad is saved to disk. The notepad is far memory, not part of the saved game.

P70 (menu 0x13: Look, Save, Print, Clear, Amount, End): *Look* shows one entry at a time from the latest (arrows, Home, End; Enter/Space/Esc ends) as place, `x,y`, month and date, `h:mm`, "Year n", then the text; *Save* ("Save the Notepad?") writes `NOTESnnn.MCN` (the first free number) as text lines ending CR LF; *Print* writes the same to `LPT1:` (or "The game has been configured for no printer."); *Clear* ("Clear the Notepad?") empties it; *Amount* = A None, B Minimum, C Normal, D Maximum. The header shows "Notepad Size: %u" and "Notepad Used: %u" (bytes).

Port (`web/src/notes.ts`, Game panel → Notes): the notes live in localStorage, Save downloads `mc2-notes.txt`, no Print; the default amount is Normal (assumption: MC2INST's default is unknown). The sites below were traced from the asm (not checked in a running game); the port's `note(level, text)` calls cite them.

Method: every `FF 9F EC 00` (`_PrtScrap`), `FF 9F 6C 04` (`_PrtScrapX`) and `FF 9F F4 02` (`_WriteNote`) in all `*.MCO`, plus EXE far calls `9A 12 00 28 11` / `9A 17 00 28 11` / `9A 06 0F 95 0A`; the level push traced in the asm (`tools/dis.py`), helper routines followed to their callers. In V02/V06/FFFAR the `8B 9C 76 8D` before the call is `mov bx,[si-0x728a]` (the EXE API table), not the level; the level is the push before it.
Text tables: comtxt = `out/pack/comtxt.json`; loctext = the current location's `texts` (`out/pack/locations/*.json`); "own text n" = the overlay's NUL-separated table.

Not sites (the mechanism itself): EXE `_PrtScrap` 1128:0012 = `mov ah,7; int 62h` → FFFAR `FAR_PRTSCRAP` (file 0xC6C); EXE `_PrtScrapX` (EXE file 0x12A97, `_WriteNote` call at 0x12B1A with its own arg); FFFAR `FAR_INT62_1a` `_WriteNote` calls (file 0xD21, 0xDE0, level = caller's arg; no caller with a constant found). No overlay calls `_WriteNote` or `_PrtScrapX` with a level other than 0xFF.

## Level 1 (Minimum)

| site (file offset) | level | text | situation | rules doc |
|---|---|---|---|---|
| P01 0x15A3 (`ovl_1576`, called from 0x1650 with `OV_0x234 = 1`) | 1 | region loctext 44 "All the party's coins have been stolen! Captain Amos promises to look into the matter." | world-map step, captain state 7 → 5 (`ovl_15e4`) | ships.md *Captain states* |
| P05 0xF59 (in `ovl_0771` body, loop) | 1 | V05 string n for each entry of the subject's text list (P05 file 0x28B; lists 1–11 = V05 strings 9…47) | Library, a days-0 subject read aloud: one notepad line per string | services.md *Library* |
| P07 0x51F (`ovl_04ef`) | 1 | `_Offer1` speaker + D98 loctext `npcno − 0x87` (9–12, Zifar…Zidoni) or 13 "You may pass." (Vankruh, npc > 0x93) | Talk to a freed elden / Vankruh in a P07 room (`_swgreet` 2) | locations.md *Dark Candle rooms* |
| P07 0xC0B (`ovl_0969`) | 1 | P07 own text 6 " It contains %b %as. Will %h take them?" or 14 " It contains a %a. Will %h take it?" (appended to the chest line already in the scrap) | chest opened with a Pick | locations.md *Opening a chest* |
| P95 0x153E (`ovl_129c`) | 1 | same as P07 0xC0B (P95's copy of the P07 texts, file 0x1139) | Pick on the chest from the aftermath screen | spells.md *The Pick on the aftermath screen* |
| P08 0x1877 (`ovl_1855`, `OV_0x1d0 = 1` set at 0x7FD) | 1 | D36 room 5 loctext 3 "Suddenly the demon Zakhad appears!…", 4 "%o says: 'A trap!…'", then event 123 set: 7, 8, 9, 10, 11, 12 (Jemil banishes Zakhad … "the party is magically transported!"); clear: 5 "…The orb shatters into powder!", 6 "One by one, the demon blasts…" | the ending (L_0772): leaving the Oolau bird's room with event 120 | quest_scenes.md *The ending* |
| P08 0x1877 via 0x1862 (`ovl_12ce`, `OV_0x1d0 = 1` at 0x11F4/0x120B/0x129B/0x12A8/0x12B5) | 1 | `_Offer1` + D60 room 8 loctext 1 (Katarra / "Suuvdaun"), 0 (the Blue Scroll), and 6, 7, 8 (Zidoni to the King: Jemil in the Oolau egg, bring the Orb, whisper "Jemil") | the elden brothers in Wanasol Hall (`ovl_1034` body); texts 2–5 of the same scene go out at 0xFF | quest_scenes.md *The elden brothers* |
| P08 0xF95 (`ovl_0f20`) | 1 | room loctext 3 "%h is magically transported! %r18" | White Scroll transport (`OV_0x1c9 == 0x4C`; the Orb's transport prints nothing here) | quest_scenes.md *The scroll on the floor* |
| P08 0x169A (entry 1 `ovl_15d5`, Restsoul) | 1 | room loctext 1 ("…leaving behind a %a"), speaker = `SetTxtObj(OV_0x1c5)` | Restsoul on a ghost whose Soulspeak event is set | quest_scenes.md *The ghosts* |
| P08 0x17E1 (`ovl_16e9`) | 1 | room loctext 2 (the scroll's description) + P08 text 17 " %o says: 'We had better ask Ziyx about this scroll.'" | a scroll on the floor picked up | quest_scenes.md *The scroll on the floor* |
| P09 0x4D5 (dx = 1 from `ovl_1413` 0x149C) | 1 | (look line already in the scrap) + P09 text 1 " The word on it is: " + D59 `gwrds[g]` (secret name) | Look at a world-temple altar from an adjacent square; from afar the same site prints at 0xFF | special_rooms.md (temples, *Look*) |
| P09 0xE68 (`ovl_0611` body) | 1 | D59 loctext 19 "Welcome, mortals. I demand the sacrifice of " + (10+g) "my long-lost Brennix!" / "the sorceress Somona!" / "a mighty warrior!" (+ 20 " Your companion %o would suit me." for g 7) + 21 " Do you agree?" | an awakened god with a demand (Balene, Fronnoxx, Ghartel) | special_rooms.md *Awakening* |
| P81 0x1AED | 1 | P81 text 19 "%h has landed in Telermain." | new game, after the intro | new_game.md step 6 |
| P90 0x604 (`ovl_037c` → 0x5EC) | 1 | P90 text 0 "%h gives the Altesen's orb to %o." + 18 " As the prince takes the orb in his hands, its glow becomes more intense." | Give the Orb to Prince Jemil (NPC 166) | economy.md (Give, the Orb) |
| P90 0x78B (`ovl_0621`) | 1 | P90 text 0 + either 15 + 16 (silvery glow, last Marked One) or 5, 6+k, 9, 10, 11+k, 14 (the blaze in that one's colour) | Give the Orb to a Marked One not yet marked; the hand-back (1 + 2–4) prints at 0xFF (0x6A3) | economy.md (Give, the Orb) |
| P91 0x4D1 (`ovl_045d` FirstMeet / `ovl_0546` SecondMeet, shared print at 0x4A4) | 1 | conversation text: the slot's greet byte (first meeting) or second byte (met before); else loctext `loc+60` / `loc+61` | Talk: the NPC's greeting | dialogue.md *Greetings, farewells* (see note 3) |
| P91 0x88D (`ovl_05e2`) | 1 | speaker (`_RoomPgm` or `_Offer1`) + conversation response text `_talkrsp`; + comtxt 0x16 " (%b charm is needed.)" when the answer came from a 'C' charm fallback (`_swcharm`) | Talk: a named NPC's keyword reply | dialogue.md (script codes, 'C') |
| P91 0xCFE (`ovl_0c57`) | 1 | (reply + song text 0 " %o takes a %l and begins to play '%f'." in the scrap) + song text 1 "%h listens intently." (one member) or 3 "The party pays close attention." | an NPC performs a song | dialogue.md 'S' song |
| P91 0xD57 (`ovl_0c57`) | 1 | song text 2 "%w begins to sing along." or 4 "After a while, they join in the music." | same | dialogue.md 'S' song |
| P92 0xC32 (`ovl_0c13`; callers 0xA59 ax 0, 0xA94 ax 1) | 1 | speaker + P92 text 0 "This has not been a profitable week for me, %o. I may have to seek other employment." / 1 "Farewell, %o. I'm off to seek my fortune elsewhere." | hireling payday check (17:00 warning, 18:00 departure) | economy.md (hirelings, paydays) |
| FFFAR 0x30C6 (`ovl_308e`) | 1 | comtxt 0x13 "The " + type name + 0x14 " ignores %h." + 0x16 " (%b charm is needed.)" | Talk to a generic townsperson with too little charm | dialogue.md *Charm to talk* |

## Level 2 (Normal)

| site | level | text | situation | rules doc |
|---|---|---|---|---|
| P02 0xE2B (`ovl_0d70`) | 2 | key carrier (`SetTxtObj`) + loctext `spdoors[0].text` ("'I have the %a.' It opens the door to Deraum!") | key door opened | locations.md *Towns* → Keys |
| P02 0xE5F (`ovl_0d70`) | 2 | loctext `spdoors[0].text + 1` ("The crystal door to Deraum is magically locked.") | key door, no key | same |
| P02 0x13A3 (`ovl_1366`) | 2 | P02 text 16 "The scroll reads: " + loctext n | a `treasptr` entry with item 0x80 (search/dig spot) | locations.md `treasptr`, *Town searches* |
| P02 0x1892 (`ovl_1852`) | 2 | speaker (`_RoomPgm`) + loctext `d3` | companion remark (special spot type 6) | locations.md *Special spots* |
| P07 0x7F3 (`ovl_07c7`, `OV_0x125 = 2` at 0x718) | 2 | D98 loctext 6 "%h unrolls the %a…", 7 "…burning it to shreds of greasy ash!", 8 "%o has been set free!" (texts 4/5 before it print at 0xFF; the flag stays 2 until the next P07 entry) | Dark Candle freed with its scroll | locations.md *Dark Candle rooms* |
| P07 0xE01 (`ovl_0d54`) | 2 | P07 text 12 "%h gains %b %a spells." | fountain gives spell charges | locations.md *Fountains* |
| P95 0x1734 (`ovl_164e` body) | 2 | P95 copy of P07 text 12 "%h gains %b %a spells." | P95's copy of the fountain code (aftermath screen); trigger not traced | (none; spells.md mentions only the P95 chest copy) |
| P08 0x1877 (`ovl_1855` from 0xCE9 / 0xD28 in `ovl_0c92`, `OV_0x1d0 = 2`) | 2 | D36 room 0 loctext 1 "Ziyx exclaims: 'Good news! … Book of Emenad!…'" / 0 "The Great Ziyx beams in welcome. … Ziyx gives %d a book of Demaro." | Ziyx's spell books | quest_scenes.md *Ziyx's spell books* |
| P08 0xDF7 (`ovl_0d8e`) | 2 | comtxt 0x83 "Nothing happens." + P08 text 15 " %o wonders: 'Are we sure that all three Marked Ones have touched the Orb?'" | Use the Orb at the Oolau bird without the three marks | quest_scenes.md *The Oolau bird* |
| P90 0x5E3 (`ovl_037c`) | 2 | conversation text `msg_if_fewer` / `msg_if_enough` of the gift list, or comtxt 0xD4 "You are most kind, %y." | Give/Offer an item to a town NPC | economy.md (Give) |
| P91 0x53D (`ovl_045d`) | 2 | comtxt 0x17 "Well met, adventurer." + 0x19 " My name is " + name + 0x10 "." | first greeting when neither the slot nor the location has a greet text | dialogue.md *Greetings* |
| P91 0x834 (`ovl_05e2`) | 2 | `_UseMindstone` speaker + loctext n (`peopr` response) | Talk: generic townsperson's keyword reply | dialogue.md *Generic townsfolk* |
| P91 0xD92 (`ovl_0c57`) | 2 | song text 5 "'%f' is now in the repertoire." | song learnt | dialogue.md 'S' song |
| P97 0x3C7 (`ovl_02e8`) | 2 | speaker + P97 text 6 "'Thank you, %h. Please accept these tokens of my appreciation.' Subia removes some emeralds…" | dismiss Lady Subia (0x1D) at the castle (`_locspec` 3/0x14/0x15) | npcs.md (dismiss) |
| P97 0x4F1 (`ovl_03f7`) | 2 | speaker + comtxt 0x21 "I am honored." | Invite: a companion joins | npcs.md (Invite) |
| EXE `_Look` 0x13549 (1166:049B; `LOOKNOTE`) | 2 | the whole look line ("%h sees …" + tile/person + ".") + loctext `lkdata.text` | Look at a look spot in sight; without a look spot `LOOKNOTE = 0xFF` | locations.md *Look* |
| FFFAR 0x2CCE (`ovl_2c1b`, level `cs:[0x2c03]`) | 2 (see note 2) | comtxt 0x11 "%h talks to " + tile + "." + loctext `lkdata.text` | Talk aimed at an empty square that is a look spot | locations.md *Look* |

## Level 3 (Maximum)

| site | level | text | situation | rules doc |
|---|---|---|---|---|
| P01 0x15A3 (`ovl_1576`, called from 0xB85 with `OV_0x234 = 3`) | 3 | region loctext `noticetexts[type]` (0 "A mushroom patch!", 27 "A patch of magical herbs!", 1 "A port of ethereal travel!", 28 "A temple!", 29 "An ominous gateway!", 30 "A small hut!", 31 "A brick building!") or a `LOCSPOT`'s own text (0xFE = none) | world map: a feature/spot next to the party is drawn | encounters.md step 7 (*Engage*), locations.md *World map* |
| P02 0x103D via `ovl_1010` (callers 0x1557, 0x1614, 0x162E) | 3 | comtxt 0x7B "The party is swept into a teleportal!" / 0x7D "The party stumbles into a pit!" / 0x7E "The party slides through a hidden chute!" | special spots 1, 4, 5 (`ovl_100b` = same helper at 0xFF: 0x80–0x82, 0x84, 0x8F, 0x90) | locations.md *Special spots* |
| P02 0x16F3 | 3 | comtxt 0xBB "%o detects an ambush!" | ambush spot detected (Sense or tracking) | locations.md *Special spots* type 0 |
| P07 0x623 (`ovl_0572`) | 3 | P07 own string at file 0x539 "The prisoner says: 'Many thanks for the rescue!'" | captive companion found in a dungeon room | locations.md *Prisoners* |
| P09 0xD39 (`ovl_0611` body) | 3 | D59 loctext 9/10 "The god "/"The goddess " + god name (0–7) + 8 " awakens!" | Whisper wakes a god | special_rooms.md *Awakening* |
| P81 0x2BE8 | 3 | P81 text 26 "%o has arrived in Telermain from Maramon, and has settled in at the Eastern Breeze Tavern." | MC1/Keys hero import (not a port gap per memory) | new_game.md (import) |
| P88 0xAB5 (`ovl_0a97`; callers 0x75C, 0x858, 0x90C) | 3 | companion name + comtxt 0x15 " says: " + 0x74 "Where do you want me to go?" / 0x72 "How many days shall I stay here and wait (1-30)?" / 0x73 "What stronghold shall I go to afterwards, if you don't return?" | Assign questions | assignments.md |
| P91 0x5A6 (`ovl_0546` SecondMeet) | 3 | `_Offer1` + comtxt 0x18 "Greetings, %h, it's good to see you again." | NPC met before with no second greet byte and no `loc+61` | dialogue.md *Greetings* (note 3) |
| P91 0xA56 (`ovl_0a08`) | 3 | conversation slot's `+0x64` reply, else comtxt 0x1B "I can't help you with that." | Talk: unknown keyword | dialogue.md *Greetings* |
| P97 0x2A1 (`ovl_01fd`) | 3 | speaker + comtxt 6 "Good luck, %h, I'll be seeing you." | dismiss a companion (not after a plea) | npcs.md (dismiss) |
| P97 0x353 (`ovl_02e8`) | 3 | speaker + P97 text 3 / 4 / 5 (Buzbazgut's plea, Subia "not explored Llendora yet!", Subia "escort back to the castle") + 2 " Dismiss %d anyway?" | dismiss plea | npcs.md (dismiss) |
| V02 0x78F (INT60 0x13, `0x6d2`) | 3 | comtxt 0x9D "%h senses an ambush to the " + 0x9E–0xA5 direction | Sense spell | spells.md (Sense) |
| V02 0xD41 (INT60 0x10, `0xcbd`) | 3 | V02 text 0 "Disguises are needed to enter this town." | orc town gate, leader's ready spell not Disguise | spells.md (Disguise, P02 start) |
| V02 0xD6B (same) | 3 | V02 text 0 + 1 " Will %h cast Disguise?" | same, ready spell is Disguise (0x1D) | same |
| FFFAR 0x2DD3 (`FAR_GREET`) | 3 | `_RoomPgm` speaker + comtxt 0x22 "Yes, my friend?" | Talk to another party member (to oneself: `_IComTxt(0xC)` "%h mumbles something to %dself.", not logged) | dialogue.md |
| FFFAR 0x2F49 (`FAR_GREET`) | 3 | `_UseMindstone` speaker + loctext `loc+59`, else comtxt 0x17 "Well met, adventurer." | greeting by a generic townsperson (charm OK) | dialogue.md *Generic townsfolk* |
| FFFAR 0x2F9D (0x2F7E, from 0x2E52) | 3 | `_AssSays` + comtxt 0x18 "Greetings, %h, it's good to see you again." | Talk to an assigned companion where they wait | assignments.md |
| FFFAR 0x317F (`FAR_ICANT`) | 3 | comtxt 0x1F "I can't do that."; Jemil (NPC 166): 0x63 "Yes, let's go back to the Castle, %h." + 0x64 " But first, could I look at that pretty Orb?" (event 123 clear) | Invite a non-companion | npcs.md (Invite) |
| FFFAR 0x36EF (`FAR_SKILLUP0`) | 3 | comtxt 0x60 "%h's %l skill +1" | any skill-up roll that succeeds | skills.md (Learning), combat.md *Skill advancement* |
| EXE `_BuySell` 0x12F31 (1166:0000) | 3 | speaker + comtxt 0xC6 " I don't trade with my companions." (party member) / 0xBC " I am not interested in trade." (town NPC without trade data; NPC 0x44 instead opens a graphic) / 0x1F "I can't do that." (anyone else) | Buy/Sell refused | economy.md `_BuySell` |
| EXE `_Offer` 0x12F83 (1166:00DE) | 3 | speaker + comtxt 0xD5 " Use 'Transfer'." | Offer/Give to a party member | economy.md (Give) |

## Quirks and unresolved

1. **P02 0x403 (Whisper, `ovl_0830`)**: comtxt 0x83 "Nothing happens." is printed with `push ax` as the level, where ax = `_whspnum | _locspec << 8` on the no-match path (0x840 → stc). `_WriteNote` takes a byte, so the level is the **whisper word index**: logged only when that index ≤ `_e_notelev`. locations.md line 75 says an unmatched word in a town/dungeon level "prints nothing" — the asm prints it (0x3CE `call 0x830; jb 0x3D6`). Not verified at runtime.
2. **FFFAR 0x2CCE**: the level word `cs:[0x2c03]` (file 0x2BFF) is 0 in the file and is only ever written with 2 (0x2CB6), never reset. So "%h talks to …" at an empty square is logged at **level 0 (even with notetaking None)** until the first time it hits a look spot; from then on it is level 2 for the rest of the session. EXE `_Look` does reset its `LOOKNOTE` to 0xFF each time.
3. **P91 entry 5 (`ovl_0546`)**: dialogue.md calls it the farewell, but FFFAR `FAR_GREETKNPC` calls it as `_SecondMeet` (API slot 0x41C) when the NPC's `_met` bit is set; its default text is "Greetings, %h, it's good to see you again." So the "bye" byte is the greeting for a second meeting.
4. **P08 `OV_0x1d0`** is reset to 0xFF only at entry 0 (0x462) and after `ovl_12ce`/`ovl_0c92`; inside the ending everything printed through `ovl_1855` after 0x7FD is level 1. `OV_0x1d0` is 0 in the file, so entry 1 (Soulspeak/Restsoul slot) before any entry-0 run would print its `ovl_1855` texts at level 0 — no such text found on that path (0x169A uses a constant 1).
5. **P07 `OV_0x125`**: stays 2 after a candle is freed until P07 is re-entered; any later `ovl_07c7` text in the same visit ("The scroll is blank." etc.) is then logged at 2.
6. **P95 0x1734**: the fountain copy's trigger in P95 was not traced (the level and text are certain).
7. Everything else prints at 0xFF (never logged), including all of P04, P06, P70, P93, P94, P96, V06, the P02/P05/P07/P08/P09 `5B 58 53 50` helpers (all 0xFF except P02 `ovl_1010`), and EXE `_PrtScrap(0xff)` sites (treasure lines 20A8:06xx, etc.).
