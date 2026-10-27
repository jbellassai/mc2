# Service rooms: inns, schools, jobs, libraries, wizards' lodges (program P05)

Sources: `P05.MCO` (`decomp/overlays/P05.c`, asm via `tools/dis.py`), room D-files `D07` (inn), `D08` (school), `D09` (jobs), `D10` (library), `D11` (lodge) — each room's text block is that file's `loctext`; `tools/doors.py original` resolves every town door to its program, D-file and room id. Task mechanics continue in `assignments.md`.

## How a door becomes a room

`ROOM{x,y,pgm,id,type}` in a town's `Dnn.MCV`: **`pgm` indexes the location's PGM list** (`PGM{pgmnum,tilefile,datafile,diskside}`), which names the overlay (`_curmpg = pgmnum`), tileset (`_curtils`) and the room's own D-file (`_curvar = datafile`). `id` is the **room id** (`_rmdata[0]`); for P05 it selects every table below, and for ordinary houses it indexes `resids`. `_rmdata+6 = type`, `+7 = locspec`.

P05 classifies the id with the boundary table (file 0x2BA) `[40 48 6C 7C 80 84 90 98 A0 A8 BB C0 C8 D0 D8]`: `_rmtyp` = number of boundaries ≤ id, index-in-kind = `id − boundary`:

| ids | `_rmtyp` | kind | D-file |
|---|---|---|---|
| 0x00–0x3F | 0 | stores (merchant = NPC `id`, slot 0 of `C(id>>3)`) | D05 etc. |
| 0x40–0x47 | 1 | inn (8 rent counters `_rmdata − 8 + id`, DS:6D43…) | D07 |
| 0x48–0x5A | 2 | school for skill `id − 0x48` | D08 |
| 0x5C–0x6B | 2 → forced to **1** with `OV_0x10f = 1` | region camp `id − 0x5C` (Assign destination; entering sets `_beenflg` bit) | D80 |
| 0x6C–0x7B | 3 | job | D09 |
| 0x7C–0x7E | 4 | library (0x7C Telermain, 0x7D Oshcrun, 0x7E Wanasol) | D10 |
| 0x80–0x82 | 5 | wizards' lodge (Telermain, Llendora, Wanasol) | D11 |
| 0x84–0x89 | 6 | tavern | D12 |
| 0x90+ | 7… | other (casino 0x90 runs P09) | |

Rooms of kind 1–3 set `_swgreet = 1` (the keeper greets on entry). Only one member can be engaged per room at a time (`ovl_1742`: an assignment record here, else the first party member with `h_actvty != 0xFF`); a second request gets the "when I am through with your friend" text.

## Inn (`_rmtyp 1`, D07)

Price per day by room (file 0x283): ids 0x40–0x47 → `[6, 7, 8, 8, 8, 9, 10, 20]` coins. Rent `n` days (`GetNum`, total ≤ 99 incl. days left); cost `n × price` from the acting member's (`_curpla`) gold, else "%h doesn't have that much!" (comtxt 0x25). The counter `rent[id]` += n and is decremented at 12:00 (`P92 ovl_04b0`); at 0 the keeper says "time to check out". Sleeping = camp program P93 with `CAMPSITE` bit 0x20 (`camp.md`); inside a paid inn the camp command answers "%h can't do that here!" when the acting member stands at x ≥ 4, y ≥ 5 (the keeper's side); elsewhere in the room it runs P93.

## School (`_rmtyp 2`, D08) — "Greetings, brave adventurer, I teach <skill> at %i coins a lesson"

Tables (P05): cost = u16 at `0x4D + 2·id`, base days at `0xDD + id`, gain at `0x16D + skill`, cap at `0x17F + 6·skill + race` (race 0 Human, 1 Wizard, 2 Elf, 3 Halfling, 4 Dwarf, 5 Orc):

| skill | id | cost | base days | gain | cap H/W/E/Hf/D/O | where |
|---|---|---|---|---|---|---|
| sword | 48 | 125 | 4 | 4 | 60/40/50/40/50/50 | Telermain |
| axe | 49 | 150 | 4 | 3 | 50/35/40/40/70/40 | Drakhelm |
| archery | 4A | 150 | 5 | 4 | 60/30/70/50/40/30 | Llendora |
| magic | 4B | 225 | 7 | 4 | 50/70/60/0/0/0 | Telermain |
| fist | 4C | 100 | 4 | 5 | 70/25/40/40/40/60 | Telermain |
| swim | 4D | 75 | 2 | 9 | 70/40/70/70/10/20 | Ussa |
| trade | 4E | 180 | 4 | 7 | 60/20/40/70/60/10 | Ketrop |
| stealth | 4F | 200 | 4 | 9 | 60/15/60/70/40/10 | Telermain |
| research | 50 | 150 | 6 | 9 | 60/70/60/70/40/0 | Wanasol |
| soul reading | 51 | 150 | 6 | 9 | 50/50/40/70/50/10 | Wanasol |
| lockpick | 52 | 175 | 4 | 6 | 50/25/40/70/60/30 | Ketrop |
| track | 53 | 125 | 3 | 7 | 60/15/70/40/60/50 | — |
| music | 54 | 150 | 3 | 9 | 50/5/70/70/20/0 | Telermain |
| carpentry | 55 | 175 | 5 | 6 | 50/20/70/70/40/30 | Llendora |
| smith | 56 | 175 | 5 | 6 | 50/20/40/40/70/20 | Drakhelm |
| gemcut | 57 | 175 | 5 | 6 | 50/20/70/40/70/10 | Drakhelm |
| tailor | 58 | 175 | 5 | 6 | 50/20/50/70/20/10 | Ketrop |
| hunt | 59 | 125 | 4 | 4 | 50/20/70/20/50/40 | — |
| leadership | 5A | 100 | 8 | (60: reads past the 18-entry gain table) | 70/20/50/20/50/5 | no door |

Flow: current skill ≥ cap → "For a <race>, your <skill> skill is well developed" (cap 0: "You have no talent"). Else `days = max(1, base − max(0, (h_intellg − 4) / 2))`; "Your lesson will take %b days. Shall we start?"; cost deducted from the pupil's (`_curpla`) gold (else "doesn't have that much") and `h_actvty = 10 + skill`, `h_actmisc = gain`, `h_actdate/h_acthour = now`, `h_actroom = id`, `h_actdays = days`. Completion adds `gain` once (no cap check at completion; in-party path caps at 99). Skills rise by at most one lesson's `gain` per visit; repeat visits until the racial cap.

## Jobs (`_rmtyp 3`, D09) — "Your %a skill is such that I will pay you %b coins a day"

Trade per room (file `0x207 + id`): 0x6C Telermain gemcutter(2), 0x6D Ketrop tailor(3), 0x6E Telermain metalsmith(1), 0x6F Telermain carpenter(0), 0x70 Drakhelm metalsmith, 0x71 Drakhelm gemcutter, 0x72 Llendora carpenter. Wage per day = the member's trade skill (`h_carpent/h_smith/h_gemcut/h_tailor`); skill 0 → "no talent" (text 5). Only `h_relatn ≤ 1` (player or volunteers; hirelings get text 15). Accepting sets `h_actvty = 0x5A + trade`, `h_actmisc = wage`, `h_actdays = 0` (open-ended). Earnings accrue in `as_gold` (assigned) or `h_gold` (party waiting) and the worker quits at 9999 or by morale (`assignments.md`).

## Library (`_rmtyp 4`, D10) — "What is your subject of interest?"

The subject is a keyword (`WMatch` against the library's `gwrds`). Each library has 5 subjects (file 0x1F7, word indexes): 0x7C `[5,9,10,13,14]`, 0x7D `[7,15,16,17,21]`, 0x7E `[11,12,18,8,19]`; global subject index `s` = 0–4, 5–9, 10–14. Per subject (files 0x20B / 0x21F / 0x233):

| s | room | required research | days | result |
|---|---|---|---|---|
| 0 | 7C | 25 | 0 | read text list 1 |
| 1 | 7C | 50 | 2 | task 30 (White Scroll) |
| 2 | 7C | 60 | 3 | task 31 (Gray Scroll) |
| 3 | 7C | 35 | 0 | list 7 |
| 4 | 7C | 40 | 0 | list 6 |
| 5 | 7D | 25 | 0 | list 2 |
| 6 | 7D | 30 | 0 | list 9 |
| 7 | 7D | 30 | 0 | list 10 |
| 8 | 7D | 20 | 0 | list 4 |
| 9 | 7D | 25 | 0 | list 8 (task byte 8, days 3 — data inconsistency) |
| 10 | 7E | 60 | 4 | task 32 (Pink Scroll) |
| 11 | 7E | 70 | 0 | task byte 33 (Blue Scroll) with days 0 → reads list 33 = nothing (original data bug?) |
| 12 | 7E | 55 | 0 | list 5 |
| 13 | 7E | 45 | 0 | list 3 |
| 14 | 7E | 55 | 0 | list 11 |

`h_research < required` → "skill is not sufficient". Days 0: the party waits `(100 − research)/4 + 1` five-minute ticks and the text list (file 0x28B: NUL-separated lists of `loctext` numbers of that library's D-file: 1 `[9]`, 2 `[10,11,12]`, 3 `[13,14,15]`, 4 `[17,18,19]`, 5 `[20–24]`, 6 `[25–28]`, 7 `[33,34,35]`, 8 `[36–39]`, 9 `[40,41,42]`, 10 `[43,44]`, 11 `[45,46,47]`) is read aloud. Days > 0: the member must hold the matching scroll (`SearchInv(task + 0x2E)`, else "requires a magical %a"), then `h_actvty = task`, `h_actmisc = scroll item`, `h_actdays = days` and the scroll is "unrolled"; on completion `h_invamt[scroll] |= 0x80` ("places the %a in %p pack"). TODO: who reads the 0x80 flag on scrolls (quest scripts).

## Wizards' lodge (`_rmtyp 5`, D11) — "memorize spells up to 7 days"

Only wizards (`h_race == 1`, else text 15). Menu *Own* / *Rent*: *Own* lists the spell books the member carries (items 0x53–0x59 Sabano, Ishban, Demaro, Zoxinn, Vannex, Emenad, Felmis → group = item − 0x53) for free; *Rent* lists the groups in the lodge's mask (file `0x1C7 + id`: 0x80 Telermain `0x07` groups 0–2, 0x81 Llendora `0x0F` groups 0–3, 0x82 Wanasol `0x5F` groups 0–4 and 6) for **200 coins**. Either way `h_actvty = 0x28 + group`, `h_actdays = 7`, and each day the member memorises up to 150 learn-ticks of charges in that group (`assignments.md`, *Spell study*). The lodge keeper asks the player to "leave %d on assignment" — the in-party *Pass* path does not run the spell study.

## Taverns and stores

Also run by P05 (ids 0x84+, < 0x40) but their behaviour is ordinary NPC dialogue/trade (`dialogue.md`, `economy.md`); nothing in P05's tables applies to them beyond the greeting switch. TODO: pier/ship rooms (P05 `UseMindstone` paths, `_beenflg` for sea destinations).
