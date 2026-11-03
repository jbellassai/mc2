# Port status (audit 2026-11-02)

What the original does that the web port does not, by area, judged from `docs/rules/*.md` and the decompiles against
`web/src/`. Everything not listed is implemented (each area's "done" summary below). Update this file when a gap is
closed; delete a row rather than marking it done.

Fixed during the audit: **events 31/32** (the Slow Death decoy rooms, V02 `INT60_12`) were never set, so Zidoni could
not be freed and the game could not be finished (`rules/locations.md`, Dark Candle rooms). Fixed after it: the
key-NPC talk events (P91 `ovl_05af`, which gate the Dorak guides' chain), the season events and the month's weather
table (P92 `ovl_0265`), songs taught in conversation (P91 `ovl_0c57`), volunteer morale (P95 `ovl_0fc0`, P92 `ovl_02ed`), the resident's "I have a key" (P02 0xA16), event 30 on
buying from NPC 88 (P90 0x989), room remarks to a companion (P91 `ovl_0a95`), the Map and Map Flask (P02 `ovl_13ab`/`ovl_13c4`, `_ShowMiniMap`), the notepad (P70, `rules/notepad.md`), auto-heroes casting (P94 `ovl_157b`), the acting member (`_curpla`: keys 1–6 or a click on the party list; Talk, Buy/Sell, Pick/Break, ship days and the Disguise gate act as it).

## Gaps that change play

None known (2026-11-03). The last four (auto-hero casting, the Map, the notepad, the acting member) are closed.

## Smaller differences

- **Acting member:** the menus where `_Parser` allows the switch (`_chpmens` = menus 5, 10, 12, 13, 16, 21, 22) are approximated as "no panel open" (plus the aftermath screen, assumed); P07/P08 rooms move `_curpla` like P05 (assumed).
- **World:** Teleport doesn't highlight valid squares; Assign is on the sheet, not Talk (Dismiss too).
- **Combat AI:** flee has no leader handover or panic spread; no friendly-fire prompt; target-on-death event (P06 `ovl_0cde` step 6) untraced; Head asks no speed digit.
- **Spells:** Assess uses the port's own text; See plays one sound (original 10 then 9), Confuse/Locate one (original three).
- **Talk:** `%k` dropped.
- **Notepad:** not logged yet: the Whisper "Nothing happens." quirk (P02 0x403), P95's fountain copy; event 153 (notes saved) is not kept.
- **Rooms:** ghost stays drawn after Restsoul until the next hour/re-entry; teleportal pedestal out of reach prints nothing; elden answers 2–6 untested (event 115 has no known setter); casino Talk routing is assumed; Library task days `− research>>4` unverified.

## Done (summary)

- **World:** clock, sunrise/sunset, hunger, energy, weather rolls, regions, step time and fatigue, swimming, entrances and features, spots, guards, patrols, mushroom patches, ships and captains, Teleport rules, camp (all activities, ambush, aboard), assignments (travel, wages, study, captures, morale, Recall, rescue).
- **Towns:** NPC placement, charm and armed checks, keyword talk, news, invite/hire/dismiss, paydays, shops and haggling, buy/sell/give/offer, Orb, transfer, use, Look, Whisper, sheet, wear, knock, pick/break, key doors, digging, inns, schools, jobs, libraries, lodges, new game, save/load.
- **Combat:** setup, arena placement, Doombeast, barbarians, attitude, advice, pre-fight menu, rally, greet/truce/bribe, attacks, bows, wear and breaking, skill-ups, rounds, monster AI (except above), auto-hero items, flee, fireglobes, songs, every spell in and out of combat, loot, searching, aftermath, Resurrect, effects, sound and both music engines.
- **Quest:** dungeon rooms, guards, chests, fountains, the three Dark Candle rooms, freed elden, Vankruh, prison cells, barriers, chutes and teleportals, remarks, key doors, Yommanis, every P08 scene (King's gifts, Ziyx, Maalaq, ghosts, scrolls, White Scroll disaster, Altesen priest, elden brothers, Marked Ones, bird, Jemil, ending, epilogue), gates, casinos, teleportal rooms, temples, meeting halls.
