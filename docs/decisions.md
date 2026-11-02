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

**Status:** IMPLEMENTED (this commit; amended 2026-10-27: in-browser import moved from prerequisite to pre-launch step). `web/src/convert.ts` ports the exporter line for line and matches it on every file (`web/scripts/convert.mjs` + `tools/packdiff.py`: JSON by value, PNG by pixels, WAV by frames). With no `./pack/` on the server the game opens an import screen (`importer.ts`): the player picks the installed game folder, only the game's own file kinds are read, an `MC2.EXE` other than version 2.00's 323,931 bytes is refused, and a trial conversion must pass before anything is kept. The browser keeps the **original files** (IndexedDB `mc2`/`files`, a few MB) rather than the pack and converts them at every start (about a quarter second), so the pack always matches the running code and an update never asks for the folder again. The Game panel can forget the files. Rejected: keeping the converted pack (it would go stale when the converter changes, forcing a re-import) and a service worker serving `./pack/` (more moving parts than `packFetch`/`packUrl`).

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

## 7. The scenario editor edits save snapshots; dev builds and /sandbox/

**Decision:** The scenario editor (`web/src/scenario.ts`, F2 or Scenario in the Game panel) works on a snapshot of the game in the save format (decision 4) and applies it through the game's own `restore`. It sets the place (any location and square, picked on a map of it), the time, the party (companions, vitals, conditions, attributes, skills, pack, spells) and the event bits (labelled from `docs/events.md`). A scenario is therefore just a save file, downloaded, uploaded or stored in a slot. It is in dev builds and, in the public build, at `/sandbox/` (a page that forwards to the game with `?sandbox`); the plain game has no F2 and no Scenario button.

**Context:** The user wanted a way to jump to any place, party, equipment and game state to try scenarios, first for a friend's testing.

**Alternatives rejected:**
- *Editing the live game objects directly* — every field would need its own update path (level loading, people, region state); the restore path already does all of it and stays the single way state enters the game.
- *A separate editor page* — it would need its own baseline state; starting from the running game's snapshot needs none.
- *Dev builds only* — the first choice; the user then asked to host it in the main build too, at a subpath.
- *A copy of the game page at `/sandbox/`* — duplicates the markup; a forwarding page and a query flag do the same.

**Consequences:** Anything a save does not hold (a fight in progress, a room's state) cannot be set; the editor opens only where saving is allowed. Event labels are only as good as the cross-reference in `docs/events.md`, with the quest milestones named by hand. Dev builds serve `docs/` at `/docs/`; the public build does not ship `docs/events.md`, so there the events show their numbers and the named milestones only.

**Status:** IMPLEMENTED (42d7b7d; /sandbox/ in this commit).

## 8. A command sidebar with hotkeys, after the original frame

**Decision:** Beside the map, a sidebar styled after the original frame (`VSCRA.MCE`: grey stone with bevels, gold lettering) shows the party numbered 1–6 with health and energy bars and every command as a button with its key (Look L, Talk T, Use U, Magic M, Whisper H, Camp C, Party I, Game G). Every button in the bottom panel shows a key too: the first letter of a word of its label that is still free, else another letter or a digit (`panel.ts`). In a fight the letters are the commands, so moving in combat uses the arrows only. Esc presses a panel's End button (the menus' way out).

**Context:** The user wanted the original's command panel recreated in a modern way, attractive and in keeping with the theme, with the hotkeys visible for keyboard players.

**Alternatives rejected:**
- *Fixed digits for panel buttons* — conflict-free but unmemorable; the original's menus were letter-driven.
- *Reserving W/A/S/D in fights* — gave poor keys (Attack → T, Draw → 1).

**Consequences:** W/A/S/D no longer move in a fight. The layout is sized from the window height so map and sidebar sit side by side, and stacks below 760 px. The title font (Cinzel) loads from Google Fonts, falling back to Georgia.

**Status:** IMPLEMENTED (this commit).

## 9. A private single-file build, with the data and the dev tools, for personal sharing

**Decision:** `npm run bundle` (in `web/`) builds `out/bundle/Magic Candle II.html` plus a `README.txt`, zipped: one page that opens straight from disk (file://) with no server, install or network. It embeds the data pack and `docs/events.md` (`virtual:bundle`, `vite.config.ts`), inlines the script, styles and title font, and turns the dev tools on (`TOOLS` in `web/src/env.ts`: the scenario editor on F2, the URL aids, `dbg`). It is for handing to one friend (Burton, on Windows, not technical): unzip, double-click.

**Context:** The user wanted Burton to play the port, including the scenario editor, on his own Windows machine with no setup. The converted pack is small (3.9 MB), every data read goes through `packFetch`, and saves already live in `localStorage`, so the page can carry everything.

**Alternatives rejected:**
- *S3/CloudFront hosting with the data* — an unlisted URL is not private (links get forwarded and indexed), so it needs access control and an AWS setup for one person.
- *An unsigned Windows .exe (Electron, a compiled server)* — Windows SmartScreen's "Windows protected your PC" warning stops a non-technical user; a page has no such warning.
- *The public build with the import screen* — Burton would have to locate and import the game files himself, and the dev tools would be hidden.

**Consequences:** Amends decision 1 for this build only: it carries game data, so it is never published or committed (`out/` is gitignored); the public build is unchanged (no data; the editor only via `/sandbox/`). Saves stay in that browser on that PC (opening the page in another browser starts without them). Building it needs the pack (`tools/export_json.py`) and one network fetch of the Cinzel font.

**Status:** IMPLEMENTED (this commit).

## 10. The private bundle hosted as a Cloudflare Worker behind Cloudflare Access

**Decision:** `MC2_WORKER=<name> npm run deploy:private` (in `web/`) builds the decision 9 bundle and deploys it as `index.html` of a Cloudflare Worker with static assets (`scripts/deploy-private.mjs`: wrangler pinned, config generated in gitignored `out/deploy`, `preview_urls` off). Cloudflare Access on the Worker's workers.dev route admits only an **Emails** allow-list by One-time PIN. Burton opens a URL instead of unzipping each new version; an update is the same command.

**Context:** Decision 9's zip has to be re-sent for every update. The user wanted cheap hosting that Burton can use with no game files of his own.

**Alternatives rejected:**
- *S3/CloudFront* — private access needs signed URLs/cookies or an auth layer; Access gives email login on the free plan.
- *Classic Cloudflare Pages* — wrangler 4.151 delegates `pages project create` to Workers (and fails on Vite 5); classic Pages needs an undocumented `--force`.
- *Building from the Git repo or CI* — the bundle carries game data, which never goes through the public repo.
- *An unlisted URL with no Access* — links get forwarded and indexed (decision 9).

**Consequences:** The data leaves the machine only to Cloudflare, behind Access. Setup order (done 2026-11-02): register the account's workers.dev subdomain, deploy `--placeholder` (no data), enable Access on the workers.dev route, check an anonymous request gets a 302 to `*.cloudflareaccess.com`, then deploy the bundle. Gotchas: the Worker's quick "Enable Cloudflare Access" only offers domain rules and the Cloudflare-account login; the Emails rule is set in the Zero Trust policy editor and One-time PIN is added under Integrations → Identity providers (never a `gmail.com` domain rule). Access sends no PIN to addresses outside the policy. The Worker and subdomain names stay out of the repo. Saves live in the browser per origin, so saves made in the zip do not carry over (move them via the scenario editor's Files tab). The zip stays the offline fallback.

**Status:** IMPLEMENTED (this commit).
