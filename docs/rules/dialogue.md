# Dialogue: talking to NPCs

Sources: `P91.MCO` (town small talk / dialogue overlay; entry 3 = `ovl_05e2` the script interpreter, entry 4 = `ovl_045d` greeting, entry 5 = `ovl_0546` farewell), `_Tobo` (loads `Cnn.MCV`), `Dnn.MCV` sub-tables `gwrds`/`peopr`/`newsr`/`loctext`. Decoder: `tools/talkdump.py original out/talk` → one file per location plus `npcs.txt` (every named NPC's full keyword/response tree, 698 lines).

## Two kinds of speakers
- **Named NPCs** (`_npcno < 0xFA`, KNPC/RESID rows with a number): conversation data comes from `C(n>>3).MCV` slot `n & 7`. Typed words are matched (`_WMatch`) against **that file's word list** (pointer 1 → 2, NUL strings: `...`, `Other`, `End`, `Advice`, `Rumors`, then quest words), and responses are strings of the file's text block (pointer 0).
- **Generic townsfolk** (`_npcno ≥ 0xFA`, placed by GEN rows): words come from the location's `gwrds`, the script is the location's `peopr` table and responses are `loctext` strings. The menu's *News* entry picks a random `newsr` line: 3-byte records `{npctype | 0xFE = any, event | 0xFE = any, loctext}` filtered on the speaker's type and (`_FindBit`) the event (`ovl_0b0e`, up to `RndCo(count)` candidates). *Weather* picks a line from P91's own `{weather, text}` table (file 0x48) — "Yes indeed, nice weather for this time of year." etc.

## Script format (both kinds)
```
entry := word resp cmd* 0        word = index into the word list, resp = text index (0xFF = end the conversation)
cmd   := 'E' ev alt              unless event bit ev is set, answer alt instead   (FindBit(_events, ev) == 0 → alt)
       | 'C' need alt            if h_charm + _tailorcharm < need − _chrmods[slot], answer alt and count a charm failure
       | 'S' song                the NPC performs: every party member gets h_songs bit `song`; clock +15 min ("'%f' is now in the repertoire")
script ends with 0xFF
```
Lookup (`ovl_05e2` L_06bf): compare the typed word's index with the entry word; on mismatch skip to the next 0 (or stop at 0xFF). A match sets `_TALKRSP = resp`, then the commands run left to right; the final `_TALKRSP` is printed (`AddScrap(textblock, rsp)`), with the extra "%o gives %h some good advice" (P91 local text 15) after a charm failure. No match → `ovl_0a08` (shrug). Typing a word is menu item 2 (`_WordIn`); 0 = News, 1 = Weather, 3+ = leave.

Example (C10 slot 0, Tomak's tribute collector): `tribute → "All visitors are encouraged to contribute one ruby…"`, `nomad → text 3 unless event 45 is unset → "I don't recall collecting the customary tribute"`; event 45 is set by the gift list when you hand him a Ruby (`economy.md`).

## Greetings, farewells, side effects
- Greeting (`ovl_045d`): marks `_met[npcno]`, then prints the slot's **greet** text = first byte of the C-file region at pointer 34+slot (`{greet, bye}`, 0xFF = use the location default `loc+60`, else "%o says nothing" style common text). Farewell (`ovl_0546`) uses the second byte (default `loc+61`).
- Talking to one of ten key NPCs sets an event bit (`ovl_05af`, P91 table @0x16/@0x29): 113→100, 164→1, 168→2, 169→3, 170→4, 172→255, 163→1, 171→1, 21→1, 175→1.
- A party member spoken to inside a location (`ovl_0a95`) may have a location-specific remark: `loc+26` word pairs `{npc, loctext}` (0-terminated).
- Player's own lines: `_PlaSays`/`_TypSays`/`_KNPCSays` are the room-program entries 0–2 of P91 (text output helpers).

## Text format codes
`%q` toggles quotes, `%h` current hero, `%o` the NPC, `%y`/`%w` other party names, `%f` song/item name, `%l` item in hand, `%a`/`%b`/`%i`/`%d`/`%p` numeric or pronoun parameters from `_deftxtparms`, `%rN` = newline/pause. (Exact table: `_PrtWrd`, EXE 0681:0147 — TODO.)
