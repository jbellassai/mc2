# Dialogue: talking to NPCs

Sources: `P91.MCO` (town small talk / dialogue overlay; entry 3 = `ovl_05e2` the script interpreter, entry 4 = `ovl_045d` greeting, entry 5 = `ovl_0546` farewell), `_Tobo` (loads `Cnn.MCV`), `Dnn.MCV` sub-tables `gwrds`/`peopr`/`newsr`/`loctext`. Decoder: `tools/talkdump.py original out/talk` → one file per location plus `npcs.txt` (every named NPC's full keyword/response tree, 698 lines).

## Two kinds of speakers
- **Named NPCs** (`_npcno < 0xFA`, KNPC/RESID rows with a number): conversation data comes from `C(n>>3).MCV` slot `n & 7`. Typed words are matched (`_WMatch`) against **that file's word list** (pointer 1 → 2, NUL strings: `...`, `Other`, `End`, `Advice`, `Rumors`, then quest words), and responses are strings of the file's text block (pointer 0).
- **Generic townsfolk** (`_npcno ≥ 0xFA`, placed by GEN rows): words come from the location's `gwrds`, the script is the location's `peopr` table and responses are `loctext` strings. The menu's *News* entry picks a random `newsr` line: 3-byte records `{npctype | 0xFE = any, event | 0xFE = any, loctext}` filtered on the speaker's type and (`_FindBit`) the event (`ovl_0b0e`, up to `RndCo(count)` candidates). *Weather* picks a line from P91's own `{weather, line}` pairs (file 0x48, 0xFF at 0x7E; lines = the NUL strings from file 0x7F): the run of pairs for the current `_weather`, one chosen with `RndCo(run length)` — Clear → lines 0/14 ("Yes indeed, nice weather for this time of year."), Rain → 4/5/6/14, Gale → 9/10/11, … (`ovl_08xx`, menu item 1). Line 15 is the charm-failure "%o gives %h some good advice.".

## Script format (both kinds)
```
entry := word resp cmd* 0        word = index into the word list, resp = text index (0xFF = end the conversation)
cmd   := 'E' ev alt              unless event bit ev is set, answer alt instead   (FindBit(_events, ev) == 0 → alt)
       | 'C' need alt            if h_charm + _tailorcharm < need − _chrmods[slot], answer alt and count a charm failure
       | 'S' song                the NPC performs: every party member gets h_songs bit `song`; clock +15 min ("'%f' is now in the repertoire")
script ends with 0xFF
```
**Word matching** (`_WMatch` → `_MCSTRICMP`, 10A8:07BE): the typed word is compared with each list word in order, case-insensitively, and matches as soon as the *list* word is exhausted — the typed word must **begin with the whole list word** ("researching" matches `research`, "res" does not); the first match's index is used. Lookup (`ovl_05e2` L_06bf): compare the typed word's index with the entry word; on mismatch skip to the next 0 (or stop at 0xFF). A match sets `_TALKRSP = resp`, then the commands run left to right; the final `_TALKRSP` is printed (`AddScrap(textblock, rsp)`), with the extra "%o gives %h some good advice" (P91 local text 15) after a charm failure. No match → `ovl_0a08` (shrug). Typing a word is menu item 2 (`_WordIn`); 0 = News, 1 = Weather, 3+ = leave.

Example (C10 slot 0, Tomak's tribute collector): `tribute → "All visitors are encouraged to contribute one ruby…"`, `nomad → text 3 unless event 45 is unset → "I don't recall collecting the customary tribute"`; event 45 is set by the gift list when you hand him a Ruby (`economy.md`).

## Greetings, farewells, side effects
- Greeting (`ovl_045d`): marks `_met[npcno]`, then prints the slot's **greet** text = first byte of the 0xFF-terminated `{greet[, bye]}` list at C-file pointer 34+slot; if that is 0xFF, the location default `loc+60`; if that is 0xFF too (most locations), common texts 0x17 + 0x19 + the NPC's name + 0x10: "Well met, adventurer. My name is Sefil." An unknown word gets the slot's `+0x64` reply or common text 0x1B (`ovl_0a08`). Farewell (`ovl_0546`) uses the second byte (default `loc+61`).
- Talking to one of ten key NPCs sets an event bit (`ovl_05af`, P91 table @0x16/@0x20): npc 113→event 24, 164→38, 168→50, 169→53, 170→56, 172→60, 163→79, 171→82, 21→95, 175→100.
- Location-specific remarks (`ovl_0a95`): inside a **room** location (`_curmpg > 2`; never in towns, dungeon levels or the wilderness), when the talking member is not the player (`_curpla ≠ 0`) and the person spoken to (`_npcno`) is listed in `loc+26` byte pairs `{npc, loctext}` (until npc 0), `loctext[n]` is printed instead of the normal conversation.
- Player's own lines: `_PlaSays`/`_TypSays`/`_KNPCSays` are the room-program entries 0–2 of P91 (text output helpers).

## Text format codes
Expanded at print time by `FAR_PRTAWRD` (FFFAR file 0xE8C; jump table file 0xEF9, entries are runtime addresses = file + 4). Parameters come from `_deftxtparms` (DS:B77D), filled by `_SetTxtObj`/`_SetTxtSpell`/`_SetTxtMonst` etc. before printing. "Hero" = `heroptr[_curpla]`; "female" = `h_sex == 1`.

| code | prints |
|---|---|
| `%a` | the near string at `_deftxtparms+4` (item/spell/monster name) |
| `%l` | the same string with its first letter lower-cased |
| `%f` | the far string at `_deftxtparms+6` |
| `%b` | the byte `_deftxtparms+2` as a decimal number |
| `%i` | the word `_deftxtparms+0` as a signed decimal number |
| `%u` | the word `_deftxtparms+0` as an unsigned decimal number |
| `%c` | the byte `_deftxtparms+3` as a character |
| `%h` | the hero's name |
| `%o` | `_othername` (the NPC or other member being dealt with) |
| `%d` | her / him (hero's sex) |
| `%p` | her / his |
| `%w` | She / He |
| `%y` | ma'am / sir |
| `%n` | line break (when printing to the screen: new line, page pause when the window is full) |
| `%q` | character 5 (the font's quotation-mark glyph) |
| `%k` | wait for a key or mouse click, with a blinking prompt |
| `%rNN` | "[Read Paragraph NN.]" — a reference to the printed paragraph booklet |

Any other letter is not a code (its jump-table slot prints a stray glyph); a `%` before a non-letter prints that character. A carriage return (0x0D) in the text is a line break. If a message starts with a letter, or with a code, its first letter (upper-cased) is stored in `_firstletter`.
