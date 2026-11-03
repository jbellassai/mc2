# Port status (audit 2026-11-02)

What the original does that the web port does not, by area, judged from `docs/rules/*.md` and the decompiles against
`web/src/`. Everything not listed is implemented (each area's "done" summary below). Update this file when a gap is
closed; delete a row rather than marking it done.

Fixed during the audit: **events 31/32** (the Slow Death decoy rooms, V02 `INT60_12`) were never set, so Zidoni could
not be freed and the game could not be finished (`rules/locations.md`, Dark Candle rooms). Fixed after it: the
key-NPC talk events (P91 `ovl_05af`, which gate the Dorak guides' chain), the season events and the month's weather
table (P92 `ovl_0265`), songs taught in conversation (P91 `ovl_0c57`), volunteer morale (P95 `ovl_0fc0`, P92 `ovl_02ed`).

## Gaps that change play

| gap | original | note |
|---|---|---|
| Auto-heroes never cast | P94 `ovl_157b`/`ovl_1553` | Head/Will heroes with no target step at random |
| Map command / Map Flask (Pearl) | P02 `ovl_13c4` | no minimap |
| Notepad | P70 (`NOTES000.MCN`, event byte 19 0x2) | |
| Resident in the party opens a locked door ("I have a key…") | P02 `ovl_196b` text 5 | port says no response |
| Buying from NPC 88 sets event 30 | P90 (`_events+3 & 0x40`) | |
| Room remarks by a companion (loc+26 {npc, text}) | P91 `ovl_0a95` | |
| Acting member (`_curpla`) | P90 Buy/Sell, P02 Pick/Break, captains, patch moves | port always uses the player (leader) |

## Smaller differences

- **World:** captain countdown and Amos's theft run at midnight instead of 08:00 / 07:00, and Amos zeroes `h_gold` instead of taking Coin items; event bit 0 (day/night) never set; Teleport doesn't highlight valid squares; Assign is on the sheet, not Talk (Dismiss too).
- **Combat AI:** monsters cast without spending energy, never Restsoul undead, never re-arm (D06 ptr12), "magic-user" criterion never matches (`c_magicused` untracked); flee has no leader handover or panic spread; a hit does not clear the routed bit 0x40; bump-attack also with a bow; no friendly-fire prompt; target-on-death event (P06 `ovl_0cde` step 6) untraced; Head asks no speed digit.
- **Spells:** Drain on a hero only lowers the combat record; Forget on a monster keeps its spell; Assess uses the port's own text; See plays one sound (original 10 then 9), Confuse/Locate one (original three).
- **Talk:** location default greeting/farewell (loc+60/+61) skipped; `_met` not kept (elven prince); `%k` dropped.
- **Rooms:** ghost stays drawn after Restsoul until the next hour/re-entry; teleportal pedestal out of reach prints nothing; elden answers 2–6 untested (event 115 has no known setter); casino Talk routing is assumed; Library task days `− research>>4` unverified.

## Done (summary)

- **World:** clock, sunrise/sunset, hunger, energy, weather rolls, regions, step time and fatigue, swimming, entrances and features, spots, guards, patrols, mushroom patches, ships and captains, Teleport rules, camp (all activities, ambush, aboard), assignments (travel, wages, study, captures, morale, Recall, rescue).
- **Towns:** NPC placement, charm and armed checks, keyword talk, news, invite/hire/dismiss, paydays, shops and haggling, buy/sell/give/offer, Orb, transfer, use, Look, Whisper, sheet, wear, knock, pick/break, key doors, digging, inns, schools, jobs, libraries, lodges, new game, save/load.
- **Combat:** setup, arena placement, Doombeast, barbarians, attitude, advice, pre-fight menu, rally, greet/truce/bribe, attacks, bows, wear and breaking, skill-ups, rounds, monster AI (except above), auto-hero items, flee, fireglobes, songs, every spell in and out of combat, loot, searching, aftermath, Resurrect, effects, sound and both music engines.
- **Quest:** dungeon rooms, guards, chests, fountains, the three Dark Candle rooms, freed elden, Vankruh, prison cells, barriers, chutes and teleportals, remarks, key doors, Yommanis, every P08 scene (King's gifts, Ziyx, Maalaq, ghosts, scrolls, White Scroll disaster, Altesen priest, elden brothers, Marked Ones, bird, Jemil, ending, epilogue), gates, casinos, teleportal rooms, temples, meeting halls.
