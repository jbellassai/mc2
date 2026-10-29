# Sound and music

Sources: FFFAR (`FAR_GAMESOUND`, the VOC name table, the effect routines), EXE (`_song`, `_adlibsong`, `_start_music`, `_cmffile`), every overlay's `_GameSound` call (found by scanning for `mov ax, n / push ax / lcall [bx+0xD0]`; `[bx+0x3CC]` is `_song`, `[bx+0x3D0]` `_finishsong`). Port: `web/src/sound.ts`, `web/src/opl.ts` (decision 5).

## Effects (`_GameSound(n)`)
`_GameSound` is INT 62h into FFFAR, which plays name table entry n − 1 (FFFAR file 0x3FB0, 13-byte names padded with `x`) through `CT-VOICE.DRV` when `_e_soundon` (else a `delay(1000)` stand-in for some calls). One DMA voice: a new effect replaces the one playing; `_WaitForSound` waits for it.

| n | file | n | file | n | file |
|---|---|---|---|---|---|
| 1 | hit | 11 | mag2 | 21 | snap |
| 2 | fball | 12 | resurect | 22 | creak |
| 3 | explo1 | 13 | announce | 23 | poison |
| 4 | explo2 | 14 | error | 24 | sick |
| 5 | swoosh | 15 | mag3 | 25 | drink |
| 6 | twang | 16 | invis | 26 | crack |
| 7 | step | 17 | knock | 27 | shatter |
| 8 | tick | 18 | dice | 28 | scream |
| 9 | blink | 19 | insert | 29 | thunder (no file) |
| 10 | mag1 | 20 | xport | | |

VOC files: blocks `{type, u24 length}`; type 1 `{time constant, codec, data}` (rate = 10⁶ / (256 − tc)), 2 more data, 3 silence `{u16 samples − 1, tc}`, 6/7 repeat (FBALL repeats 99 times; the port plays it once). Codecs: 0 8-bit unsigned PCM (13 files), 1 4-bit Creative ADPCM (17 blocks), 2 2.6-bit ADPCM (4); the first data byte is the reference sample. `tools/export_json.py` decodes them with DOSBox's `sblaster.cpp` tables.

### Where each is played
- **Moving**: a town step (P02 `ovl_02ab` 0x4C4, after the clock update) and a room or combat step (`_RMove`) → 7; a refused town step → 14, then the barrier bump (INT60_09); a world-map step on foot (P01 `ovl_10f7`, not while sailing) → 7.
- **Errors** (14): `_NoUse`, a full pack (`NOROOM`), `_Parser` refusing a change of the acting member (keys Alt-F2–F7: the menu is not in `_chpmens`, or in a room fight `_RoomPgm` says no), `_Invite` refusals, talking with a weapon drawn (FFFAR `FAR_GREET`), a bad Teleport target (P89 0x23E; a good one 20). In the overlays (every `mov ax, 0Eh; push ax; call far [bx+0D0h]`):
  - **Refused steps**:
    - P01 0x56D, a world step whose direction handler (table at file 0x5AF) sets carry: the map's edge (0x618) or `ovl_0cb2` refusing the square, e.g. too far to swim, or a ship onto land that is not a shore;
    - P02 0x4FC, in town;
    - P04 0x2F6, a mushroom patch (`_RMove` 1);
    - P05 0x685, P08 0x6F1, P09 0x570: rooms, a blocked square that is not in the room's door list;
    - P07 0x2D7, a dungeon room (`_ChkDoor` 0);
    - P94 0x1F9, a combat step that is not onto a monster (`_IsItMon` 0);
    - P95 0x87F, the aftermath;
    - P96 0x567, the pre-fight menu (`_RMove` 1).
  - **Text refusals**:
    - P05 0x543, "%h can't do that here!" (Camp on the keeper's side of an inn);
    - P90 0x108E, "Wizards must keep at least one book." (Sell `ovl_09b8`, a Wizard selling a spell book with at most one book slot; no merchant in the data buys books);
    - P91 0xA61, an unknown word (`ovl_0a08`, also News with nothing to tell);
    - P93 0xD70, "%h has nothing more to take off!" (Off).
  - **The transport** (P08 0xFEC, `ovl_0fb9`): window 0 cleared to `RndCo(0x100)` 80 times, 14 on each pass, when the White Scroll or the Orb sends the party to the council (`ovl_0f20`). **Tick** (8): `_Parser` (EXE 0681:063F), when a letter key picks a menu entry through `_MenuLookup`; Space/Enter, Esc, digits, mouse clicks and `_ChkArw`'s cursor keys (Home/End/arrows move `_mnuord`, 0681:0D80) are silent.
- **Combat blows** (P06 `ovl_050a` → `ovl_0468`): a swing 5, a shot 6 (after the arrow is spent); a blow that lands 1, preceded by 11 and `_Spef2` when the attacker is a Barg (race 0x12).
- **Combat spells** (V06): Fear `INT61_0d` 10, Shatter `_10` 2, Assess `_0c` 11, Fireball `_11` 2, Freeze `_0e` 15, Disappear `_14` 16, Zofir `_06` 15, Zefoar `_04` 2, Jump `_16` 14 and 16 (which when, not traced), Drain `_41` 24, See `_0b` 10 then 9, Betray `_0f` 10, Summon `_0a` 9, Destroy `_1a` 4, Terrify `_19` 15, Acidball `_12` 2, Restsoul `_17` 5; `INT61_ff` 13. Resurrect (P95) 12.
- **Effects** (FFFAR, with their pictures): `FAR_SPEF5` 15, `FAR_SPEF5_A` 10, `FAR_SPEF6` 11, `FAR_BANG` 3, `FAR_ACIDBANG` 3, `FAR_SKILLUP0` 13, `FAR_INVERTWINDOW` and `FAR_BONG` take theirs as an argument. Their pictures: `effects.md`.
- **Places**: P01 confuse/locate 15 (three times); P02 knock 17 (`ovl_08d8`), xport 20 (`ovl_0e9a`, `ovl_151a`), snap 21 (`ovl_1044`); P07 the Dark Candle incantation 5, a chest 21/22 and its trap 0x17 + kind (poison 23, sick 24), a fountain 25; P08 the Orb and the bird 10, the egg 26, Zakhad 28, his banishment 15, the Orb shattering 27, thunder 29 (`ovl_1976`); P09 dice 18, a teleportal piece 19, 20, creak 22; P95 chest 21/22/23–24, drink 25; V02 10 and 15 (Detect, `INT60_13`), a trapped chest 0x16 + n.

## Music (`_song(n)`, `_finishsong`)
`_song(n)` (EXE) does nothing unless `_e_soundon`; with an AdLib/Sound Blaster (`_e_musicboard` 1) `_adlibsong` loads `_cmffile[n]` (DS:3070 → `mc2NNa.cmf`) and `_start_music` plays it through SBFMDRV; with a Roland MT-32 (2) `_RolandSoundPlay` plays `mc2NNt.mid`. `_finishsong` waits for the end (`_wait_music_end`) after a 100 ms delay.

| n | where | n | where |
|---|---|---|---|
| 1 | the title (P81 `ovl_1343`, between the two title screens, then a 1.5 s pause) | 8 | Lute song 1, 'Wind Song' |
| 2 | the intro text (P81 0x1A42, after the names) | 9 | Bandore song 0, 'Sambali' |
| 3 | Flute song 0, 'Lullaby of Gu' | 10 | Bandore song 1, 'Firedance' |
| 4 | Flute song 1, "Urg's Dream" | 11 | the epilogue (P08 0x8A1) |
| 5 | Lyre song 0, "Mage's Joy" | 12 | 'The Happy Traveller' (an instrument with no song known, in or out of a fight; FFFAR `FAR_e249`, V06 `INT61_1d`) |
| 6 | Lyre song 1, 'Rondo Miz' | 13 | the Horn in a fight (V06 `INT61_1e`) |
| 7 | Lute song 0, 'Morning Mist' | 14 | the Conch's call (P01 `ovl_1349`, before its effect) |

The instruments' songs are V06 file 0x2904 (`3 + 2·instrument + song`).

CMF: `"CTMF"`, version 1.01, +6 instruments offset, +8 music offset, +0x0A ticks per quarter (48), +0x0C clock ticks per second (96, the event clock: `_start_music` sets the timer to 1193180 / it), +0x14 channels in use, +0x24 instrument count, then 16-byte instruments (OPL registers 0x20/0x23, 0x40/0x43, 0x60/0x63, 0x80/0x83, 0xE0/0xE3, 0xC0, 5 unused) and a MIDI-like stream. The songs use note on/off, program change, controller 7 (volume) and 10 (pan), pitch bend (song 14) and controller 0x67 = 0 (no rhythm mode); SBFMDRV acts on none of the controllers but 0x66–0x69 and ignores pitch bend and velocity.

Port: all of the above music; the effects at moves and bumps, `_NoUse`, a full pack (`_IncObj`), talking armed, Teleport, combat blows and spells, Resurrect, the Dark Candle, fountains, dungeon chests (snap, creak, trap) and trapped spots (V02 `INT60_15`), knocking and a broken Pick at town doors, the casino's dice, the teleportal pieces and transport, P09's two creaks (0x16: a god awakening, 0xCDB, and a gate opening, 0x153F), Confuse/Locate, the Orb, the egg and the ending, Walkwater 10, Detect and Sense 15 (V02 `INT60_01`, `ovl_0533` three times, `INT60_13`), a skill gained 13 (`FAR_SKILLUP0`, `FAR_SKILLUP`), a teleportal spot's 0x14 at the departure and again at the arrival (P02 `ovl_151a`, `ovl_0e9a`), P01's 9 when something next to the party is drawn (`ovl_09d1`, `encounters.md` *Engage*). the tick on a letter hotkey (`panel.ts`). every 14 listed above (the transport as `FX.flash`, 25 ms a pass, assumed). Not wired: `_Parser`'s refused member change (the port has no acting-member switch), and the FFFAR effect routines with their pictures.

Modern music (decision 6): `music/n.mid` (the `mc2NNt.mid` named after the CMF names, `_RolandLoad`) parsed by `web/src/midi.ts` and synthesised by `web/src/modern.ts`; the songs use MT-32 presets 24, 25 (Syn Brass), 32 (Fantasy), 48 (Str Sect 1), 51 (Pizzicato), 57, 58 (Harp), 61 (Elec Gtr 1), 75 (Piccolo 2), 77 (Pan Pipes), 84 (Oboe), 92, 93 (Fr Horn), 94 (Tuba), 112 (Timpani), 122 (Orche Hit) and rhythm keys 36–38, 42–44, 46–49, 51, 54, 69. `MC2.ALB` is not MT-32 data: `_loadbunch` only reads the 14 songs, so the presets are the MT-32's own.
