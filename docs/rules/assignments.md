# Assignments: sending companions away (P88 Assign/Recall, P92 daily update, P05 service rooms)

Sources: `P88.MCO` (`_ToAssign` loads overlay 0x58 then `P97`; `decomp/overlays/P88.c`, asm via `tools/dis.py`), `P92.MCO ovl_0561…ovl_0bdc` (hour tick), `P05.MCO` (rooms that create tasks, `services.md`), EXE `_AssignedHere`, `_FindAss`. Field names from `ASSIGNMENT` in `docs/structs.h`.

## Data model

- `ASSIGNMENT` (25 B, 31 records `_assgn0`, record `n−1` belongs to NPC `n`, so only NPCs 1–31 can be assigned):
  `as_npc as_loc as_room as_x as_y as_task as_done as_gowildx as_misc as_race as_tile as_hroom as_region as_wildx as_wildy as_goreg as_gowildy as_gold(u16) as_date as_daysleft as_hour as_goloc as_goroom as_godays`. Empty = `as_npc == 0xFF`.
- A companion who stays **in the party** can do the same work: the task is kept in the hero record instead (`h_actvty` task, `h_actmisc`, `h_actdate`, `h_acthour`, `h_actroom`, `h_actdays` = `HERO+0xB9, 0xD7…0xDB`). `h_actvty == 0xFF` = nothing pending.
- Placement: a record is "here" when `as_loc == _locspec && as_room == _currm && as_task != 8` and `as_hroom` matches the dungeon room (`_AssignedHere`); the NPC is then drawn at `(as_x, as_y)`.

### Task codes (`as_task` / `h_actvty`)

| code | meaning | created by | daily effect (P92) |
|---|---|---|---|
| 7 | waiting at a spot, then travel | Assign *Stay* | `as_daysleft--`; at 0 becomes task 8 |
| 8 | travelling | Assign *Go to*, Recall, end of any task | `as_daysleft--`; 10 % chance per day of a stealth check (captures, below); at 0 arrives: `as_x,as_y = 5,2`, `as_wildx/y = as_gowildx/y`, task 0xFF |
| 10–28 (0x0A–0x1C) | training skill `code − 10` (sword … hunt; 29 = leadership never occurs) | school room (`services.md`) | countdown; on completion `skill += as_misc` (P92 `ovl_07b0`, no cap; in-party path caps at 99) |
| 30–33 (0x1E–0x21) | researching the White/Gray/Pink/Blue Scroll (item `code + 0x2E` = 0x4C–0x4F) | library room | countdown; on completion the scroll's `h_invamt |= 0x80` ("deciphered") |
| 40–46 (0x28–0x2E) | memorising spell book `code − 0x28` (items 0x53–0x59 Sabano … Felmis) | wizards' lodge | each day up to 150 learn-ticks of charges (below) |
| 90–93 (0x5A–0x5D) | working as carpenter / metalsmith / gemcutter / tailor | job room | `as_gold += as_misc` (wage) per day, cap 9999 |
| 100 (0x64) | in jail | scripted | skipped by the morale check |
| 101 (0x65, `'e'`) | captured on the road | stealth failure (below) | rescued by entering the dungeon room (`locations.md`) |
| 0xFF | arrived / idle at `(as_loc, as_room)` | | |

Tasks 1–11 also appear in the library's subject table but those subjects finish immediately (see `services.md`).

## Assign (P88 entry 0, conversation menu 9 *Assign*, `_ToAssign`)

Assign is a conversation command: the party talks to one of its own members (FFFAR's talk loop, menu value 3). Preconditions: the person spoken to is in the party (`ovl_0abc`, else comtxt 0x6F "Only companions can be assigned tasks."), `h_relatn == 1` (volunteer; hirelings and the King are refused with `_OnlyCompanions`), the party is not in disguise (`_indisguise`, P88 text 56 "Not while in disguise."), NPC number < 0x20. The questions are common texts: 0x72 "How many days shall I stay here and wait (1-30)?", 0x73 "What stronghold shall I go to afterwards, if you don't return?", 0x74 "Where do you want me to go?", 0x75 "Should %o get going now?". Once a record is made `_ToAssign` runs P97 with `_swass = 1`: the member leaves the party; the companion keeps their own Mindstone, which is what Recall looks for.

1. **In a service room whose pending task is set** (`_curvar` = the room's D-file number 8 school, 9 job, 10 library, 11 lodge; with `h_actvty == 0xFF` the answer is comtxt 0x70 + `_chartypes[_curvar + 12]` + 0x71, "%o must talk to the instructor / artisan / librarian / registrar first."): the hero fields are copied into the record (`as_task = h_actvty`, `as_misc = h_actmisc`, `as_date/as_hour = h_actdate/h_acthour`, `as_daysleft = h_actdays`), `h_helped |= 0x80`, then (except jobs, file 9) the player picks a destination for afterwards ("What stronghold shall I go to afterwards, if you don't return?") (`as_goloc = 1`, `as_goroom = 0x5C + dest`, `as_godays` = travel days). `as_gold = h_gold` and the hero's gold is zeroed: the companion takes their purse along.
2. **Anywhere else** menu *Go to* / *Stay*:
   - *Go to*: pick a destination, "Should %o get going now?" *Yes* → `as_task = 8`, `as_daysleft = days`, `as_loc = 1`, `as_room = 0x5C + dest`, `as_hroom = 0xFF`; `as_godays/goloc/goroom` are not written (whatever the `_crecs` scratch record held), so the traveller's square (below) is not meaningful.
   - *Stay*: "How many days shall I stay here and wait (1-30)?", then pick a destination → `as_task = 7`, `as_daysleft = n`, `as_goloc/goroom/godays` as above.
   Common fields: `as_loc/as_room = _locspec/_currm`, `as_x/y` = member's position, `as_race`, `as_tile = FirsTil(member)`, `as_hroom = _hroomrec` when in a dungeon (`_curmpg == 7`) else 0xFF, `as_region = _curreg`, `as_wildx/y = _wildxy`, `as_date/as_hour = now`, `as_done = 0xFF`.

**Destinations** (P88 file 0x24 names, 0xAB table `{code, x, y}`): destination n is region n's stronghold, so the names are the region names (`formats.md`) and entry 1 (Mt Mandarg) is empty with no stronghold. A bit of `_beenflg` (DS:4D5A, bit 15 = entry 0) must be set; it is set when the party enters the stronghold (P05 room ids 0x5C–0x6B, `services.md`), which stands on a world-map spot at the table's square (`locations.md`, *World map*). New game: entry 0 only.

| n | name | room code | world x,y |
|---|---|---|---|
| 0 | Oshcrun | 0x5C | 31,51 |
| 1 | (Mt Mandarg: none) | 0x5D | 0,0 |
| 2 | Isle of Winds | 0x5E | 128,55 |
| 3 | Sariss | 0x5F | 166,80 |
| 4 | North Misor | 0x60 | 60,29 |
| 5 | South Misor | 0x61 | 56,61 |
| 6 | Kar'Lomug | 0x62 | 234,81 |
| 7 | Altesia | 0x63 | 171,118 |
| 8 | Rhon | 0x64 | 225,41 |
| 9 | The Throat | 0x65 | 124,41 |
| 10 | Ruul | 0x66 | 96,63 |
| 11 | Demonspine | 0x67 | 93,23 |
| 12 | The Tundra | 0x68 | 163,13 |
| 13 | Krum | 0x69 | 231,7 |
| 14 | Farsum | 0x6A | 201,61 |
| 15 | Mandarg | 0x6B | 188,53 |

Each square lies in its region's rectangle (the capture table below), which is how the order was checked.

**Travel days** (`P88 0x76f`): `dx = |x − wildx|, dy = |y − wildy|, big = max, small = min; days = (big + (small+2)/4) >> 4`, saturating at 255 before the shift, minimum 1. The companion arrives in camp room `0x5C+n` at `(5,2)`.

## Recall (P88 entry 1, camp *Recall* command)

Using the Mindstone (only the player, `items.md`) lists NPCs 1–31 who are not in the party and carry a **Mindstone** (item 0x40) in their `_member6` record; the chosen one's **Assignment Report** (P88 0xEB2, texts from file 0x2D9) is:

- heading "Assignment Report", the name;
- task 8 or 0xFF: "Traveling to" (days left) or "Arrived at" + the stronghold name (`as_room − 0x5C`), then "Arrives in: %b days." while travelling;
- task 7: "Waiting at" + the region name (`as_loc == 1`, by `as_region`) or the place name (P88 file 0x1EE by `as_loc` → names at 0xDB), "Finishes in: %b days.";
- tasks 10–29: "Training in" + the skill; 30–39: "Researching a" + the scroll; 40–89: "Learning from" + the book (item `0x53 + task − 0x28`); each with "Finishes in" and, when `as_goroom != 0xFF`, "When done, %o will travel to X, a %b day journey." (`as_godays`); "Upon arrival, %o" (text 50) is never used;
- tasks 90–93: "Working as a" + the trade, "in" + the place;
- task 0x65: "In jail";
- then "Location: (as_wildx, as_wildy)" (not while on the road), "Gold: as_gold", and, unless jailed, "What will %o do?" with the menu {*Go to*, *Continue*} (P88 file 6 words 0 and 2; a prisoner gets *Continue* only). An NPC without a record is reported at a fixed home (P88 table 0x24B, index = NPC): Sakar 9 (Oshcrun Cellars), Fiz 0 (Castle Oshcrun), Nehor 1 (Neirwood), Tuff 2 (Ketrop), Ben 3 (In Jail), Crys 0, Ralle 4 (Telermain), Durin 5 (Demonspine), Eflun 6 (Drakhelm), Eldai 3, Gil 1, Grolf 0, Gus 0, Jimbo 2, Kruga 6, Lupi 1, Stref 5, Madir 7 (Ussa), Perin 2, Nimmo 4, Buz 3, Nazim 5, Orbo 0, Polo 4, Argas 4, King 0, Rexor 0, Rogga 3, Subia 0, Tamas 3, Mona 8 (In Flight). NPCs 5, 10, 30, 28 show "In Jail" until events 40, 42, 43, 44 (table 0xDBD; the FindBit result is clobbered by `add sp`, so in practice they are always reported at Castle Oshcrun once listed — original bug).

*Go to* ("Where will %o go?", text 57) **redirects** anyone but a prisoner — whatever the task, so a pupil or worker abandons it: the record becomes task 8 to the new stronghold from the companion's *current* position (interpolated as below; `as_region` from the rectangles), `as_daysleft = as_godays` = the new journey, fresh `as_date/as_hour`. Costs nothing. *Continue* changes nothing.

## Daily update (P92 `ovl_0561`, every hour tick)

For each record with `as_npc != 0xFF && as_date != _date && as_hour == _hour` (i.e. once a day at the hour it was created):

- task < 0x5A → `ovl_05b1`:
  - if `as_daysleft > 0`: `as_daysleft--`; task 8 → stealth check (`ovl_0716`, returns if captured); task 0x28–0x2E → spell study (`ovl_0828`); if still > 0 stop.
  - `as_done = task`. Task 8 → arrive (above). Tasks 10–29 → `skill[task−10] += as_misc`. Tasks 30–33 → scroll `|= 0x80`. Then the record becomes task 8 towards `as_goloc/as_goroom` with `as_daysleft = as_godays`; if `as_godays == 0` it arrives immediately.
- task ≥ 0x5A: `as_date++`; task < 0x5E → `as_gold = min(9999, as_gold + as_misc)`.
- then the **morale check** `ovl_08f7` (not for 0x64/0x65):
  - tasks 7, 8: always; jobs: only once `as_gold >> 10 ≥ h_loyalty` (and `as_gold ≥ 9999` quits outright); other tasks: only when `h_loyalty ≤ as_daysleft`.
  - `attitude = max(0, attitude + loyalty − 15)`; if `attitude > 40` stop; if `RndCo(80) ≤ attitude` stop; if `RndCo(12) < loyalty` stop; else **quits**: record freed, `h_gold += as_gold` (via `_IncObj`), `h_actvty = 0xFF`, `_npcsta` bit cleared (the NPC goes home, `npcs.md`).

Spell study (`ovl_0828`, task 0x28+g, every day of the countdown): budget 150; repeatedly pick a random spell of group g (6 spells, `h_spells[6g..6g+5]`) whose charge count < 99, cost = `_LrnTim(spell, hero)` (`camp.md`); stop when the cost exceeds the remaining budget; charge++ and subtract. If all 6 are at 99 the task ends early.

### Captures on the road (`ovl_0716`, `ovl_0b40`, `ovl_06b3`)

Each travel day, with probability 1/10, roll `RndCo(100)`; if it is ≥ the companion's **stealth** they are caught:
1. Position = `as_wildx/y + (as_wildx/y − as_gowildx/y) · elapsed / as_godays` (sic: the original interpolates *away* from the destination; a port should use `+ (go − from)·elapsed/total`).
2. Region = first rectangle `{x0,y0,x1,y1}` (16 rects, P92 file 0xC2 = P88 file 0x26B) containing the position: `[0,0,39,255] [162,50,190,58] [114,52,131,59] [147,69,184,95] [40,0,79,43] [40,44,79,255] [224,60,255,111] [147,95,255,255] [217,33,255,74] [103,0,136,255] [80,54,102,255] [80,0,102,53] [137,0,205,43] [206,0,255,32] [137,61,255,255] [0,0,255,255]`.
3. Candidate prisons per region (file 0x64E, 4 bytes each, 0xFF = none): r1 `[29,247]`, r2 `[253,18,254,21]`, r3 `[29,247]`, r4 `[21,246,18]`, r5 `[253,254]`, r6 `[29]`, r8 `[247,73,29]`, r9 `[21,246,18]`, r10 `[253,254,21,246]`, r11 `[21,246,18]`, r12/13 `[73,74,247]`, r14 `[29,247]`, r15 `[29,247,21,246]`, r0/r7 none → no capture. The first candidate not already holding a captive is used (the occupancy test compares `as_room` instead of `as_hroom`, so it never matches: always the first).
4. Record: `as_hroom = candidate`, `as_loc` = dungeon, `as_room = 0xFF`, `as_x,as_y = 2,2`, `as_task = 0x65`, `as_done = 0xFF`, `as_gold = 0`, `as_wildx/y` = dungeon entrance. Prison table (candidate → location, world x,y): 21→D29 Dorak 1 (87,20); 246→D29 (87,20); 18→D29 (87,20); 29→D38 Maratul 2 (216,57); 73→D25 Ruz 1 (231,15); 74→D25 (231,15); 247→D44 Maratul 8 (214,48); 253→D45 Shann 1 (67,79); 254→D45 (67,79). Rescue: `locations.md`, *Dungeon rooms*.

## Doing the task while the party waits (P05 `ovl_17bd`)

In a service room the party can *Pass* time instead of leaving the member: every 5-minute tick, for each party member with `h_actvty != 0xFF` whose `h_actdate != _date && h_acthour == _hour`: tasks < 0x5A → `h_actdays--`, at 0 the reward is applied in the room (school: `skill = min(99, skill + h_actmisc)`, text "Your training is now complete"; library: scroll `|= 0x80`) and `h_actvty = 0xFF`; jobs → `h_actdays++` and `h_gold += h_actmisc` daily. Leaving the room with a task pending asks "leave without completing?" and the task is simply dropped unless the member was assigned.

## Rejoining

Talking to an assigned companion where they stand and *Invite* (P97 `ovl_03f7`) frees the record: `as_gold` is added to their coins and a training or research task (10–39) carries on in the party (`ovl_0511`: `h_actvty/h_actmisc/h_actdate/h_acthour/h_actdays` from the record, `h_actroom = _currm`); any other task is dropped (`h_actvty = 0xFF`).

## Port notes

Built in the web port (`web/src/assign.ts`, `main.ts` *assign*, *recallAway*): Assign from the character sheet (I, a companion, *Assign*: the port's stand-in for talking to a member), Go to / Stay / the service-room path, the records drawn where they stand (towns, rooms, dungeon cells; not on the world map), the daily update with captures, spell study, rewards, wages and the morale check (a companion who quits goes home with the record's coins), Recall by using the Mindstone, redirecting, rejoining by Invite, the rescue on entering a cell, the four starting captives (P81 file 0x167F), `_beenflg` and the world-map spots that lead to the strongholds. Departures from the original: a traveller's square interpolates towards the destination, and *Go to* sets `as_godays` to the journey. The party prints "<name> leaves the party." when the member goes (the original's wording is not traced).
