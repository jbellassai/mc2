# Decisions

Numbered, never reused. Status: DECIDED (not yet built) or IMPLEMENTED (with commit).

## 1. The engine reads a converted data pack; the public site never serves game data

**Decision:** The engine reads only a friendly **data pack** (JSON for data, PNG for graphics) converted from the original files. For now the pack is built locally by the Python exporter (`tools/export_json.py`) and never committed or published. Before a public launch, an in-browser TypeScript converter builds the same pack from the player's own MC2 folder, so the public site (GitHub Pages) ships code only.

**Context:** The repository is public and the game data is copyrighted (`original/` is gitignored, renders stay out of git). Converting to another format does not change ownership, so what matters is who distributes the pack. Requiring the in-browser converter up front would block the first playable slice on rewriting every parser in TS.

**Alternatives rejected:**
- *The engine parses the original binary formats directly* — couples the engine to 1991 file layouts; the pack is the clean contract.
- *Publish the converted pack on Pages* — redistributes the game; the repo is public.
- *Build the in-browser converter first* — delays the first playable slice; the engine does not care who built the pack.
- *Run the Python tools in the browser (Pyodide)* — ~10 MB runtime for a few hundred lines of parsing.
- *Replace the content with original art/text/maps* — freely shareable but an enormous effort, and no longer Magic Candle II.

**Consequences:** The pack schema (`docs/data_schema.md`) is the contract between converter and engine. Until the TS converter exists the game is playable only where the pack was built (local dev, screen share, private sharing among owners). When it is written, the Python exporter's output is its golden test (local only, needs `original/`).

**Status:** DECIDED (amended 2026-10-27: in-browser import moved from prerequisite to pre-launch step).

## 2. First milestone: walk around Telermain from a fresh start

**Decision:** The first playable slice starts a new game's party in Telermain (no save loading) and supports walking with the original movement rules, the clock, townsfolk appearing by the hour, doors into room interiors, and talking to people.

**Context:** A small, showable slice that exercises the importer, the state model and the rendering on real data before combat, magic or the world map.

**Alternatives rejected:**
- *Start by loading a real save* — not needed to show the game; save loading comes later (`FFSAVx.MCS` is a raw DS image, `formats.md`).
- *Start with combat* — more rules, less to see and walk around in.

**Consequences:** Needs, in order: Telermain's map and tilesets (VGA, walkability), the party sprites, doors and rooms (`render_rooms.py` logic), NPC placement and hours (`npcs.md`), conversations (`dialogue.md`), the clock (`time_weather.md`). Original graphics first; modernized graphics are a later layer (see the port goal: same rules, modernized presentation).

**Status:** DECIDED.

## 3. Stack: TypeScript + Vite, canvas rendering, deployed by GitHub Actions to Pages

**Decision:** Write the port in TypeScript, built with Vite as a static site, rendering the tile view on a `<canvas>` with no game framework, deployed to GitHub Pages by a GitHub Actions workflow.

**Context:** The game is a tile grid plus menus; a static site is all Pages can host.

**Alternatives rejected:**
- *Phaser / PixiJS* — scene and physics machinery the tile view does not need; easy to add later if modern effects want it.
- *A UI framework (React etc.) from day one* — premature; menus can adopt one later.
- *WASM / C port* — the rules are being re-specified, not re-compiled; TS keeps them readable.

**Consequences:** Node is required only for development. The port lives in its own directory (`web/`) with its own `package.json`.

**Status:** DECIDED.

## 4. Saved games: the port's own JSON snapshot in the browser, three slots, between activities

**Decision:** The port saves its own state model as a JSON snapshot in `localStorage` (three slots, key `mc2.save.N`), from the Game panel (key G), and only while the party is on a town or dungeon level or the world map — not during a fight, in a P05/P07 room or in a mushroom patch.

**Context:** Nothing persisted, so the port could only be played in one sitting. The original saves a raw DS image (`FFSAVx.MCS`, `formats.md`); the port's state is spread over typed objects (party records, world regions, location sets) rather than one memory image, and rooms/fights hold transient state (overlay locals, combat records) that would all need a serial form.

**Alternatives rejected:**
- *Write `FFSAVx.MCS` images* — would require mapping every DS global the port does not model yet; worth doing as an **import** later (load a DOS save to continue it), not as the port's working format.
- *Save anywhere, including mid-fight* — every transient structure (combat records, P05 tasks, P07 chest state) would need serialising; the original's own save points are not traced yet, and saving between activities covers normal play.
- *IndexedDB* — a save is a few tens of KB; `localStorage` is simpler. It can fail (private windows), and the panel says so.

**Consequences:** `World`, `Party` have `snapshot()`/`restore()`; `main.ts` gathers clock, events, the location sets (`_dunrms`, `_duntre`, `_chests`, `_ambush`), mushroom counts, inn rent and the walk counters. New persistent state must be added to the snapshot (bump `v` when the shape changes). A DOS-save importer remains a separate later step.

**Status:** IMPLEMENTED (this commit).

## 5. Sound: the VOC effects as WAV, the music as CMF played by the port's own OPL2 model

**Decision:** The data pack carries the 28 sound effects converted to WAV (`sounds/n.wav` for `_GameSound(n)`, ADPCM decoded by the exporter) and the 14 songs as the original CMF files (`music/n.cmf`); the browser renders a song through `web/src/opl.ts`, a small OPL2 (YM3812) model written for the port, driven the way Creative's SBFMDRV drives the chip.

**Context:** The original plays digitised effects on a Sound Blaster (Creative `CT-VOICE.DRV`, VOC files with 8-bit PCM and 4-/2.6-bit ADPCM) and music on either an AdLib/Sound Blaster (CMF through SBFMDRV, `_adlibsong`) or a Roland MT-32 (`MC2nnT.MID`, `_RolandSoundPlay`). Browsers decode WAV but neither ADPCM VOC nor CMF.

**Alternatives rejected:**
- *Play the `T.MID` files through a General MIDI synth or soundfont* — they are written for the MT-32's own patches, so General MIDI instruments would sound wrong, and a soundfont is a large extra download.
- *Render the songs to audio files in the exporter* — the pack would grow by megabytes, and a Python OPL model would have to be kept in step with the browser's own anyway once the in-browser converter exists (decision 1).
- *Use an existing OPL emulator (Nuked-OPL3, DOSBox's DBOPL, opl3.js)* — exact, but their GPL/LGPL licences sit badly with the repo's own code, and the songs use only a small part of the chip (nine melodic voices, no rhythm mode).

**Consequences:** The music is close to, not identical with, a real OPL2 (envelope and level tables are modelled from the data sheet, not cycle-exact). A song renders in well under a second the first time it plays. Sound and music each have an on/off toggle in the Game panel (`localStorage` key `mc2.audio`). Browsers allow audio only after a key or click, so the title fanfare waits for the first one.

**Status:** IMPLEMENTED (this commit).

## 6. Modern music: the MT-32 arrangements played by the port's own synthesisers, by default

**Decision:** By default the music is the game's own Roland MT-32 arrangements (`MC2nnT.MID`, exported as `music/n.mid`) rendered in the browser by `web/src/modern.ts`: synthesised instruments by family (strings and pads, brass, flutes and reeds, plucks, timpani, orchestra hit), synthesised drums, the songs' pan, volume and pitch-bend controls, reverb and a stereo echo, normalised to the FM music's loudness. The Game panel's Music setting cycles Modern / Original FM (decision 5) / Off.

**Context:** The user wanted the music modernised while keeping the melodies. The MT-32 files are the composer's fuller arrangements of the same songs (real instrument choices and a drum track the FM versions lack), so playing them with new instruments keeps every melody and harmony.

**Alternatives rejected:**
- *A sampled orchestra (FluidR3_GM through the gleitz/midi-js-soundfonts CDN)* — built and compared on `web/preview.html`; the user preferred the synths in most songs, and the samples meant a runtime download from a third-party host and a CC BY credit.
- *Rearranging or re-recording the songs* — would not keep the original melodies exactly and needs a musician.
- *General MIDI playback of the MT-32 files* — the MT-32 presets do not match General MIDI's; the port maps the 16 presets the songs use to instrument families itself (`midi.ts` `MT32_GM`).

**Consequences:** A long song renders for a few seconds the first time it plays (cached afterwards). `web/preview.html` (dev only) plays each song both ways for tuning. Drums use the MT-32 rhythm keys the songs need (kick, snare, rim, toms, hats, crash, ride, tambourine, cabasa).

**Status:** IMPLEMENTED (this commit).
