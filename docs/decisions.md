# Decisions

Numbered, never reused. Status: DECIDED (not yet built) or IMPLEMENTED (with commit).

## 1. The web port ships no game data; the player's own copy is imported in the browser

**Decision:** Host the port publicly (GitHub Pages) with code only; on first run the player selects their own Magic Candle II folder, a TypeScript importer parses the original files in the browser into the engine's JSON game data, and the result is cached locally (IndexedDB).

**Context:** The repository is public and the game data is copyrighted (`original/` is gitignored, renders stay out of git). The goal is a URL a fan can open and play, which rules out any step that needs Python or a command line on the player's machine.

**Alternatives rejected:**
- *Ship the extracted data or renders on Pages* — redistributes the game; the repo is public.
- *Server-side import or a backend holding the data* — the same redistribution problem, plus hosting cost.
- *Run the Python tools in the browser (Pyodide)* — ~10 MB runtime and slow start for a few hundred lines of parsing.
- *A local CLI that builds a data pack for the player* — too much friction for a casual player.

**Consequences:** Every format parser exists twice: the Python tools in `tools/` stay the reverse-engineering reference and emit **golden JSON** locally; the TS importer must reproduce it exactly. That parity test needs `original/`, so it runs locally only; CI can run unit tests on synthetic fixtures. The importer reads a directory via `<input webkitdirectory>` / drag-and-drop (works in all major browsers; the File System Access API is Chromium-only). The JSON schema becomes the contract between data and engine.

**Status:** DECIDED.

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
