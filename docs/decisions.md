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
