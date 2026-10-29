# Encounters: monsters, groups, where fights come from, loot

Sources: EXE tables `_monstats` (DS:308E, 23 B × 37, names `_w_monstrs` DS:40A4), `_grps` (DS:340B, 5 B × 163), `_monsptr`; `P96.MCO` (combat setup, `decomp/overlays/P96.c`), `P95.MCO` (loot `ovl_09xx`), `P01.MCO` (world-map guards/patrols), `P02` (town ambush), `P07` (`HROOM.hrmgrp`), region records (`tools/worldspots.py`). Combat itself: `combat.md`.

## Monster codes

Monster race codes continue the hero races (0 Human … 5 Orc): code = name index + 5. `_monstats` row (23 B) → `CMBTNT` (`combat.md`): `[0..1]` hit points (u16), `[2]` shield, `[3]` weapon item (0xFF none), `[4]` armor, `[5]` bravery, `[6]` strength, `[7]` dexterity, `[8]` agility, `[9]` resist, `[10]` intellect, `[11]` weapon skill, `[12]` magic skill, `[13..15]` spells 1–3 (0xFF none), `[16..18]` three bytes **no code reads** (P96 copies rows 0–15 into the `CMBTNT`, FFFAR and the EXE only re-read the HP word and bytes 7–8; values per monster below), `[19]` 1, `[20..21]` tile index (u16), `[22]` tile flags (8/5/2). P96 extras: **leader rank** (file 0x39, higher = leads the group; `c_state |= 4`) and **undead** flag (file 0x62: Skeleton, Zombie, Ghoul rise again with 1 HP, see `combat.md`).

Unused bytes 16/17/18 per monster (probably design notes — the first grows with natural-weapon strength, the third with overall level): Orc 0/6/2 Zorlim 1/10/6 Tekhir 2/14/3 Troll 0/16/4 Goblin 0/6/3 Sandgu 4/9/4 Slime 4/12/4 Minotaur 3/10/6 Domug 5/8/5 Skeleton 0/0/7 Zombie 3/0/8 Kurdazi 2/12/6 Jerrah 7/10/7 Barg 4/5/6 Zebani 5/15/6 Gragan 2/10/7 Mongor 6/20/7 Fermigon 4/12/9 Gnoll 0/18/5 Ogre 5/75/10 Gaem 7/20/10 Zumagin 6/10/8 Hibliss 7/15/10 Vankruh 7/0/11 Naur 7/25/11 Zakhad 7/0/12 Urgodot 4/15/7 Doombeast 8/0/12 Mizigu 4/10/6 Aciden 7/25/5 Flamebelly 10/20/7 Dreadknight 1/25/9 Farazu 1/30/9 Kazih 1/15/6 Ghoul 3/0/9 Munak 4/10/7 Barbarian 0/8/2.


| code | name | HP | shield | weapon | armor | brav | str | dex | agi | res | int | wskl | mskl | spells | u16 | u17 | u18 | tile | tflag |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 5 | Orc | 20 | 0 | 10 | 0 | 10 | 5 | 5 | 4 | 2 | 1 | 35 | 0 | — | 0 | 6 | 2 | 27 | 8 |
| 6 | Zorlim | 40 | 40 | 10 | 6 | 2 | 6 | 6 | 6 | 4 | 6 | 30 | 40 | 6,8,16 | 1 | 10 | 6 | 38 | 8 |
| 7 | Tekhir | 35 | 10 | 26 | 3 | 8 | 4 | 4 | 8 | 3 | 5 | 40 | 0 | — | 2 | 14 | 3 | 49 | 8 |
| 8 | Troll | 75 | 0 | 19 | 4 | 6 | 7 | 3 | 3 | 1 | 1 | 40 | 0 | — | 0 | 16 | 4 | 60 | 8 |
| 9 | Goblin | 35 | 0 | 18 | 3 | 4 | 5 | 7 | 7 | 3 | 2 | 45 | 0 | — | 0 | 6 | 3 | 71 | 8 |
| 10 | Sandgu | 40 | 0 | — | 7 | 6 | 16 | 7 | 8 | 1 | 2 | 50 | 0 | — | 4 | 9 | 4 | 82 | 2 |
| 11 | Slime | 45 | 10 | — | 0 | 5 | 13 | 3 | 3 | 3 | 2 | 50 | 0 | — | 4 | 12 | 4 | 85 | 2 |
| 12 | Minotaur | 90 | 0 | — | 3 | 9 | 21 | 8 | 6 | 4 | 5 | 50 | 0 | — | 3 | 10 | 6 | 88 | 8 |
| 13 | Domug | 40 | 20 | — | 4 | 5 | 14 | 6 | 8 | 4 | 6 | 45 | 0 | — | 5 | 8 | 5 | 99 | 8 |
| 14 | Skeleton | 55 | 20 | 12 | 5 | 12 | 6 | 4 | 4 | 6 | 5 | 55 | 0 | — | 0 | 0 | 7 | 110 | 8 |
| 15 | Zombie | 70 | 40 | — | 6 | 12 | 25 | 6 | 4 | 6 | 5 | 60 | 0 | — | 3 | 0 | 8 | 121 | 8 |
| 16 | Kurdazi | 60 | 10 | 26 | 4 | 6 | 6 | 8 | 9 | 1 | 3 | 60 | 0 | — | 2 | 12 | 6 | 132 | 8 |
| 17 | Jerrah | 70 | 50 | — | 6 | 7 | 4 | 5 | 5 | 7 | 6 | 50 | 50 | 6,18,0 | 7 | 10 | 7 | 143 | 2 |
| 18 | Barg | 60 | 20 | — | 0 | 8 | 23 | 9 | 5 | 3 | 0 | 65 | 0 | — | 4 | 5 | 6 | 146 | 2 |
| 19 | Zebani | 45 | 25 | — | 5 | 5 | 16 | 7 | 7 | 5 | 7 | 55 | 0 | — | 5 | 15 | 6 | 149 | 8 |
| 20 | Gragan | 70 | 30 | — | 6 | 7 | 4 | 6 | 8 | 7 | 7 | 40 | 60 | 37,36,0 | 2 | 10 | 7 | 160 | 2 |
| 21 | Mongor | 70 | 20 | — | 3 | 5 | 20 | 7 | 5 | 4 | 5 | 50 | 0 | — | 6 | 20 | 7 | 163 | 5 |
| 22 | Fermigon | 120 | 30 | — | 6 | 9 | 28 | 3 | 4 | 6 | 4 | 50 | 0 | — | 4 | 12 | 9 | 171 | 2 |
| 23 | Gnoll | 50 | 10 | 11 | 3 | 5 | 6 | 4 | 7 | 2 | 7 | 60 | 0 | — | 0 | 18 | 5 | 174 | 8 |
| 24 | Ogre | 500 | 0 | — | 2 | 8 | 32 | 2 | 6 | 2 | 6 | 60 | 0 | — | 5 | 75 | 10 | 185 | 8 |
| 25 | Gaem | 120 | 60 | — | 7 | 8 | 7 | 7 | 7 | 7 | 7 | 65 | 65 | 19,20,37 | 7 | 20 | 10 | 196 | 2 |
| 26 | Zumagin | 90 | 40 | — | 7 | 9 | 21 | 6 | 8 | 5 | 5 | 70 | 0 | — | 6 | 10 | 8 | 199 | 5 |
| 27 | Hibliss | 150 | 50 | — | 8 | 10 | 4 | 6 | 9 | 8 | 8 | 60 | 70 | 11,14,6 | 7 | 15 | 10 | 207 | 2 |
| 28 | Vankruh | 2000 | 90 | — | 40 | 12 | 34 | 12 | 10 | 12 | 10 | 90 | 85 | 8,11,19 | 7 | 0 | 11 | 210 | 2 |
| 29 | Naur | 700 | 99 | — | 10 | 10 | 10 | 10 | 10 | 11 | 11 | 70 | 80 | 19,11,18 | 7 | 25 | 11 | 213 | 2 |
| 30 | Zakhad | 800 | 99 | — | 20 | 12 | 12 | 12 | 12 | 12 | 12 | 99 | 99 | 37,19,36 | 7 | 0 | 12 | 216 | 5 |
| 31 | Urgodot | 120 | 0 | — | 6 | 8 | 21 | 4 | 9 | 3 | 6 | 60 | 0 | — | 4 | 15 | 7 | 224 | 2 |
| 32 | Doombeast | 200 | 30 | — | 8 | 8 | 28 | 7 | 7 | 6 | 7 | 65 | 80 | 27,27 | 8 | 0 | 12 | 227 | 5 |
| 33 | Mizigu | 50 | 0 | — | 4 | 7 | 18 | 10 | 10 | 2 | 2 | 60 | 0 | — | 4 | 10 | 6 | 235 | 2 |
| 34 | Aciden | 120 | 25 | — | 8 | 8 | 22 | 4 | 7 | 5 | 5 | 55 | 0 | — | 7 | 25 | 5 | 238 | 5 |
| 35 | Flamebelly | 135 | 30 | — | 7 | 6 | 25 | 4 | 8 | 4 | 5 | 60 | 0 | — | 10 | 20 | 7 | 246 | 5 |
| 36 | Dreadknight | 150 | 45 | 12 | 8 | 11 | 8 | 7 | 3 | 7 | 8 | 75 | 65 | 0,36,37 | 1 | 25 | 9 | 254 | 8 |
| 37 | Farazu | 200 | 60 | 15 | 9 | 10 | 9 | 9 | 7 | 8 | 8 | 50 | 75 | 14,2,11 | 1 | 30 | 9 | 265 | 8 |
| 38 | Kazih | 90 | 35 | 11 | 5 | 7 | 6 | 9 | 7 | 5 | 6 | 40 | 60 | 14,6,11 | 1 | 15 | 6 | 276 | 8 |
| 39 | Ghoul | 90 | 30 | — | 7 | 12 | 25 | 6 | 4 | 7 | 5 | 70 | 0 | — | 3 | 0 | 9 | 287 | 8 |
| 40 | Munak | 75 | 0 | — | 5 | 8 | 23 | 9 | 8 | 1 | 2 | 65 | 0 | — | 4 | 10 | 7 | 298 | 2 |
| 41 | Barbarian | 65 | 0 | 12 | 5 | 11 | 24 | 5 | 4 | 1 | 3 | 55 | 0 | — | 0 | 8 | 2 | 301 | 8 |

Leader rank (P96 file 0x39 + code, so Orc at 0x3E): Orc 5, Zorlim 40, Tekhir 10, Troll 15, Goblin 20, Minotaur 35, Domug 30, Jerrah 50, Gnoll 25, Ogre 55, Gaem 60, Zumagin 45, Hibliss 65, Naur 75, Farazu 70, Kazih 48, Barbarian 0; the others never lead (0xFF). Undead flag: P96 file 0x62 + code (Skeleton, Zombie, Ghoul = 1).

## Encounter groups (`_grps`, group numbers 60–222)

`_grpno < 60` means "n monsters of code `_grpno`" (`_monstlist = {g,g,g,g}`). Otherwise row `grpno − 60` = `{count, m0, m1, m2, m3}`; count 0 → the number is `row[0] + _semiranseed % (row[1] − row[0])` where row = `D06.ptr8[7·diff …]` (P96 0x334–0x370; correction: earlier read as `ptr8[7·diff + seed % 7]`), so `row[0] … row[1] − 1` monsters; the other five bytes of a row are not used here (D06 rows by difficulty 0–7: `3 6 0 0 0 0 0 | 4 6 0 3 0 4 5 | 4 7 1 5 1 7 6 | 5 7 1 7 1 8 9 | 5 8 1 9 2 10 10 | 6 8 2 12 2 11 12 | 7 10 2 16 2 13 13 | 8 12 2 20 3 15 15`). Each monster drawn picks one of the four entries at random (`ovl_1323`) until its quota (`OV_0x19b` counters) is spent. A fourth entry marked `*` (bit 0x80) adds **one extra monster of that code** on top of the count (six if it is a Doombeast) and makes it the group's leader (`ovl_06b8/06c7`).

| group | count | monsters |
|---|---|---|
| 60 | table | Orc, Orc, Orc, Zorlim |
| 61 | table | Orc, Tekhir, Tekhir, Zorlim |
| 62 | table | Troll, Troll, Domug, Zorlim * |
| 63 | table | Urgodot, Urgodot, Domug, Domug |
| 64 | table | Urgodot, Zorlim, Tekhir, Zorlim |
| 65 | table | Goblin, Goblin, Tekhir, Zorlim * |
| 66 | table | Kurdazi, Kurdazi, Slime, Slime |
| 67 | table | Sandgu, Sandgu, Troll, Zebani |
| 68 | table | Barg, Zumagin, Orc, Tekhir |
| 69 | table | Ghoul, Ghoul, Domug, Jerrah |
| 70 | table | Minotaur, Minotaur, Tekhir, Jerrah |
| 71 | table | Mizigu, Mizigu, Zebani, Zorlim |
| 72 | table | Ogre, Troll, Troll, Troll |
| 73 | table | Munak, Munak, Gaem, Zebani |
| 74 | table | Ghoul, Kurdazi, Kurdazi, Kazih |
| 75 | table | Kurdazi, Gragan, Gragan, Jerrah |
| 76 | table | Kazih *, Goblin, Zumagin, Zumagin |
| 77 | table | Kazih, Tekhir, Gragan, Zebani |
| 78 | table | Kurdazi, Kurdazi, Jerrah, Barg |
| 79 | table | Kurdazi, Gaem, Mongor, Ghoul |
| 80 | table | Troll, Troll, Jerrah, Ogre * |
| 81 | table | Zumagin, Mizigu, Mizigu, Munak |
| 82 | table | Zombie, Zombie, Mongor, Hibliss |
| 83 | table | Barg, Barg, Ogre, Hibliss |
| 84 | table | Fermigon, Fermigon, Zumagin, Hibliss |
| 85 | table | Gnoll, Gnoll, Aciden, Aciden |
| 86 | table | Skeleton, Skeleton, Slime, Slime |
| 87 | table | Domug, Skeleton, Skeleton, Jerrah |
| 88 | table | Fermigon, Zombie, Zombie, Gragan |
| 89 | table | Fermigon, Fermigon, Mongor, Zebani |
| 90 | table | Fermigon, Fermigon, Gaem, Domug |
| 91 | table | Dreadknight, Dreadknight, Hibliss *, Doombeast * |
| 92 | table | Tekhir, Ogre *, Ogre *, Doombeast * |
| 93 | table | Tekhir, Zebani, Domug, Aciden * |
| 94 | table | Kazih, Kazih *, Ghoul, Flamebelly |
| 95 | table | Aciden, Aciden, Ghoul, Flamebelly |
| 96 | table | Aciden, Barg, Doombeast *, Gaem * |
| 97 | table | Ghoul, Aciden, Doombeast *, Jerrah * |
| 98 | table | Urgodot, Barg, Gaem, Gragan * |
| 99 | table | Aciden, Ghoul, Flamebelly, Zumagin * |
| 100 | table | Doombeast *, Zebani, Gragan, Mongor * |
| 101 | 4 | Jerrah *, Gaem *, Zumagin *, Gragan |
| 102 | table | Aciden, Barg, Slime, Zebani |
| 103 | table | Skeleton, Zebani, Zebani, Slime |
| 104 | table | Skeleton, Zebani, Slime, Doombeast * |
| 105 | table | Skeleton, Zebani *, Slime, Urgodot * |
| 106 | table | Skeleton, Skeleton, Slime *, Zebani * |
| 107 | table | Skeleton, Zombie, Slime, Urgodot |
| 108 | table | Skeleton, Zombie *, Zombie *, Slime * |
| 109 | table | Skeleton, Skeleton, Zombie, Zombie |
| 110 | table | Slime, Slime, Zombie, Zombie |
| 111 | table | Skeleton, Zombie, Slime, Doombeast * |
| 112 | 3 | Skeleton *, Zombie, Doombeast *, Gaem * |
| 113 | table | Aciden, Zombie, Gnoll, Domug |
| 114 | table | Goblin, Mongor, Gnoll, Domug |
| 115 | table | Goblin, Troll, Urgodot, Domug |
| 116 | table | Ghoul, Jerrah *, Urgodot, Zebani * |
| 117 | table | Ghoul *, Skeleton *, Zombie *, Zumagin |
| 118 | table | Orc, Barg, Tekhir, Zumagin * |
| 119 | 2 | Doombeast *, Doombeast *, Doombeast *, Farazu * |
| 120 | table | Skeleton *, Skeleton *, Zombie *, Zombie |
| 121 | table | Zombie, Skeleton, Slime, Gaem * |
| 122 | table | Skeleton, Skeleton, Slime, Slime |
| 123 | 4 | Zumagin *, Ghoul *, Zorlim *, Zombie |
| 124 | table | Troll, Troll, Zumagin, Jerrah * |
| 125 | table | Ghoul, Zombie, Slime *, Zebani * |
| 126 | table | Flamebelly, Ghoul, Domug, Gaem * |
| 127 | 12 | Slime, Slime, Slime, Jerrah * |
| 128 | 4 | Jerrah, Jerrah, Jerrah, Gaem * |
| 129 | 4 | Gaem, Gaem, Zombie, Jerrah * |
| 130 | table | Fermigon, Flamebelly, Jerrah *, Skeleton |
| 131 | table | Fermigon, Fermigon, Aciden, Gaem * |
| 132 | table | Fermigon, Aciden, Tekhir, Gaem * |
| 133 | table | Fermigon, Urgodot, Skeleton, Zorlim * |
| 134 | table | Troll, Troll, Aciden, Gaem * |
| 135 | table | Aciden, Aciden, Fermigon, Zorlim * |
| 136 | table | Tekhir, Flamebelly, Domug, Ogre * |
| 137 | table | Tekhir, Zebani, Domug, Ogre * |
| 138 | 4 | Tekhir, Ogre *, Ogre *, Jerrah * |
| 139 | table | Mongor, Mongor, Ogre, Ogre * |
| 140 | table | Ogre *, Mongor, Gragan *, Zumagin |
| 141 | table | Zorlim, Zorlim, Ghoul, Ogre * |
| 142 | 4 | Zorlim, Jerrah *, Ogre, Kazih * |
| 143 | table | Domug, Zebani, Gragan, Zumagin |
| 144 | table | Orc, Tekhir, Domug, Zorlim |
| 145 | table | Zebani, Mongor, Zumagin, Jerrah * |
| 146 | 4 | Zumagin, Jerrah *, Kazih *, Kazih * |
| 147 | table | Ogre *, Ogre *, Zumagin *, Zebani |
| 148 | table | Tekhir, Troll, Mongor, Ogre |
| 149 | table | Tekhir, Flamebelly, Gragan, Jerrah * |
| 150 | table | Minotaur, Minotaur, Minotaur, Jerrah * |
| 151 | table | Domug, Tekhir, Zebani, Gragan |
| 152 | table | Domug, Ogre, Mongor, Zumagin |
| 153 | table | Gragan, Mongor, Zumagin, Jerrah * |
| 154 | table | Goblin, Goblin, Goblin, Jerrah |
| 155 | table | Goblin, Goblin, Barg, Gaem * |
| 156 | table | Slime, Slime, Goblin, Goblin |
| 157 | table | Goblin, Goblin, Minotaur, Zorlim |
| 158 | table | Goblin, Goblin, Skeleton, Skeleton |
| 159 | table | Goblin, Goblin, Skeleton, Gaem * |
| 160 | table | Goblin, Goblin, Barg *, Gaem * |
| 161 | table | Goblin, Goblin, Kazih, Kazih |
| 162 | table | Goblin, Goblin, Mongor, Gragan |
| 163 | table | Goblin, Goblin, Zebani, Gnoll |
| 164 | table | Goblin, Goblin, Slime, Mongor |
| 165 | 1 | Vankruh, Vankruh, Vankruh, Vankruh |
| 166 | table | Mizigu, Mizigu, Farazu, Gaem |
| 167 | table | Mizigu, Zombie, Farazu, Gragan |
| 168 | table | Mizigu, Mizigu, Mongor, Zebani |
| 169 | table | Mizigu, Mizigu, Gaem, Domug |
| 170 | table | Mizigu, Flamebelly, Jerrah *, Troll |
| 171 | table | Mizigu, Mizigu, Farazu, Gaem * |
| 172 | table | Troll, Mizigu, Ogre, Gaem * |
| 173 | table | Troll, Flamebelly, Ogre, Gaem * |
| 174 | table | Troll, Troll, Gaem, Farazu * |
| 175 | table | Troll, Farazu *, Ogre, Gaem * |
| 176 | 5 | Domug, Ogre, Gaem *, Gaem * |
| 177 | 5 | Ogre, Troll, Ogre *, Troll |
| 178 | 6 | Farazu *, Farazu *, Ogre, Troll |
| 179 | table | Domug, Troll, Flamebelly, Ogre * |
| 180 | table | Aciden, Hibliss *, Doombeast *, Jerrah |
| 181 | table | Zebani, Domug, Jerrah, Farazu * |
| 182 | table | Zumagin, Domug, Mongor, Doombeast * |
| 183 | table | Gragan, Zumagin, Farazu, Hibliss * |
| 184 | table | Hibliss, Aciden, Hibliss, Flamebelly |
| 185 | table | Farazu, Aciden, Aciden, Doombeast * |
| 186 | table | Flamebelly, Gragan, Domug, Farazu * |
| 187 | table | Flamebelly, Aciden, Zebani, Doombeast * |
| 188 | table | Zumagin, Aciden, Jerrah, Farazu * |
| 189 | table | Jerrah, Hibliss, Jerrah, Farazu * |
| 190 | table | Jerrah, Zebani, Domug, Hibliss * |
| 191 | table | Mongor, Jerrah, Zumagin, Doombeast * |
| 192 | table | Gragan, Flamebelly, Mongor, Farazu * |
| 193 | table | Domug, Zumagin, Jerrah, Hibliss * |
| 194 | table | Zumagin, Zumagin, Gragan, Farazu |
| 195 | table | Farazu, Farazu, Jerrah, Jerrah |
| 196 | table | Hibliss *, Hibliss, Gragan, Jerrah |
| 197 | table | Aciden, Hibliss, Farazu, Gragan |
| 198 | table | Zumagin, Zebani, Mongor, Gragan |
| 199 | table | Jerrah, Hibliss, Farazu, Doombeast * |
| 200 | 4 | Farazu, Farazu, Farazu, Farazu |
| 201 | 4 | Hibliss, Hibliss, Hibliss, Hibliss |
| 202 | 6 | Kazih, Hibliss, Gaem, Zakhad * |
| 203 | table | Kazih, Gaem *, Doombeast *, Naur * |
| 204 | table | Gragan, Jerrah, Kazih, Naur * |
| 205 | table | Dreadknight, Dreadknight, Gaem, Farazu |
| 206 | table | Dreadknight, Zumagin, Zorlim, Jerrah |
| 207 | table | Hibliss, Slime, Flamebelly, Dreadknight |
| 208 | table | Gnoll, Dreadknight, Mongor, Dreadknight |
| 209 | table | Mongor, Gragan, Dreadknight, Dreadknight |
| 210 | table | Farazu, Hibliss, Dreadknight, Doombeast * |
| 211 | table | Gaem, Jerrah, Dreadknight, Doombeast * |
| 212 | table | Zebani, Zebani, Dreadknight, Hibliss * |
| 213 | table | Domug, Dreadknight, Dreadknight, Zumagin |
| 214 | table | Domug, Flamebelly, Dreadknight, Hibliss * |
| 215 | table | Zebani, Tekhir, Flamebelly, Dreadknight |
| 216 | table | Jerrah, Jerrah, Dreadknight, Dreadknight |
| 217 | table | Doombeast *, Farazu *, Dreadknight, Dreadknight |
| 218 | table | Dreadknight, Hibliss, Gaem, Doombeast * |
| 219 | table | Mongor, Mongor, Dreadknight, Dreadknight |
| 220 | table | Gragan, Zumagin, Flamebelly, Dreadknight |
| 221 | table | Farazu, Ogre, Gaem *, Naur * |
| 222 | 10 | Orc, Orc, Orc, Orc |

Groups 120–222 are used by dungeon-room guards (`HROOM.hrmgrp`) and type-0 ambush spots; the table ends at 222 (DS:373A is `_animtilecount`). Group 0xCA (202) rooms are swapped for group 0xDE (222) until an event is set (`locations.md`, *Doors into dungeon rooms*).

## Where the group number comes from

| source | `_grpno` | `_diff` | notes |
|---|---|---|---|
| **world-map guard spot** (R `gwrds` 3-byte `{x, y, group}`, 8 per region) | record byte 2 | P01 table 0x33A per region `[0,7,3,4,2,1,5,6,4,3,3,4,5,7,6,5]` (R32…R47) | stepping on it; `_grdsta` bit `region·8+n` = cleared; `_ctype 0` |
| **patrol** (8 per region, start squares P01 file 0x136; patrol *n* belongs to region *n* >> 3) | `newsr[n & 7]` of the current region record | same table | moves after every world-map step, see *Patrols* below; reaching the party's square starts the fight (`_ctype 1`); victory sets the `_ptrlsta` bit |
| **camp ambush** | the patrol that walks into the camp | region | a member on *Watch* (`h_actvty 9`) prevents the ambush flag (`camp.md`) |
| **town / dungeon ambush** (`P02`, `spetbl` type-0 spots, `locations.md` *Dungeon levels*) | spot `d1` | `locdiff − 1` | `_ambush` bit per ambush id = already fought; best `track` vs `RndCo(200)`, or a *Sense* that pointed at the spot, detects it (`skills.md`); `_ambflg` → monsters act first |
| **dungeon room** (door type 6–9, `HROOM.hrmgrp`, then `P07`) | `hrmgrp` | `locdiff − 1` | `_dunrms` bit = guards cleared (`locations.md`) |
| scripted | P08/P09 scenes | | |

## Patrols (`P01 ovl_169e`, `ovl_17c0`, `ovl_18c1`, `ovl_1910`, `ovl_0a94`, `ovl_076c`)

State: `_ptrlxy` (128 squares, x 0 = no patrol), `_ptrlsta` (bit *n* = destroyed), `_ptrleng` (bit *n* = chasing the party), `_lastgen` (16 months, 0 in a new game). A world-map step runs, in order: the party's move, the region update (`ovl_14fd`), **`ovl_169e`** (respawn, then patrol moves), **`ovl_0846`** (fight check), **`ovl_0a94`** (engage), **`ovl_076c`** (draw). Entering the world map runs `ovl_169e`, `ovl_0a94` and `ovl_076c` once. `ovl_169e` also runs while time passes on the map (parser result 6, the camp loop's cross-overlay call), which is where a camp ambush comes from.

1. **Respawn**: for each region *r*, if `(_lastgen[r] + interval[r]) mod 12 == _month` (interval = P01 file 0x32A `[6,1,3,3,3,3,3,2,2,3,3,3,2,2,1,2]`), then `_lastgen[r]` = that month, the region's `_ptrlsta`, `_grdsta` and `_ptrleng` bytes are cleared and its 8 patrols go back to their start squares. Every region is tested on every call, wherever the party is; with a new game's zeros a region first respawns in the month equal to its interval (region 0 in month 6, the start month).
2. **Moves**: every live patrol inside the party's map block moves once. The party's block (`_curseg`, `ovl_141b`) is the first `D01` block, searching from the current one, whose 32×34 square from its origin holds the party; a patrol is inside it when that block's 42×42 square holds the patrol (`ovl_1416`). A chasing patrol steps toward the party (`ovl_17c0`); if it cannot, it stops chasing and wanders in the same move.
3. **Free square** (`ovl_1910`): inside the party's block, in the patrol's own region (`ovl_14d6`), walkable (`_ChkWlk`), and not a town entrance (`exitptr`), a feature (`roomptr`), a live guard spot of the current region or a live patrol. The party's square is allowed.
4. **Chase** (`ovl_17c0`): one step (sign dx, sign dy) toward the party. If that square is not free, the direction's two side steps (P01 file 0x17A0 / 0x17B0, indexed by the direction's place in the 8-direction table at 0x1790) are tried, each only if it is free **and** ends next to the party (`_ChkRng` 1). If none works the `_ptrleng` bit is cleared.
5. **Wander** (`ovl_18c1`): `RndCo(8)` picks a start in the order table (P01 file 0x18B7: directions 0, 6, 2, 3, 7, 1, 5, 4, then 0, 6 again); the first of three consecutive directions whose square is free is taken, else the patrol stays.
6. **Fight** (`ovl_0846`): a live guard spot under the party wins over a patrol; otherwise a live patrol on the party's square fights with group `newsr[n & 7]`, the guard's terrain, difficulty and arena rules (`combat.md`). A chasing patrol whose square the party steps on stays put (`ovl_17c0` returns at once), so the fight follows; an idle one may wander off first.
7. **Engage** (`ovl_0a94`): a live patrol on one of the 8 squares around the party is drawn and its `_ptrleng` bit is set. So a patrol starts chasing only once it has been next to the party.
8. **Draw** (`ovl_076c`): every live patrol and the region's live guard posts in view are drawn (E00 icon 0x0F, the skull) only while event 105 is set (`_events` byte 13 bit 1) or a *Locate* spell's `magic/4` draws last (`OV_0x1bb`, `spells.md`). Otherwise the party sees a patrol only when it is next to it, and a guard post not at all.

## Loot (`P95 ovl_09xx`, per slain monster, not for bribed fights)

Vankruh (code 28) sets events 150/61 instead of loot. Otherwise a coin flip: **heads** → `RndCo(6)+5` = 5–10 Coins; **tails** → only if `RndCo(20) + diff > 10`: roll `RndCo(100)` against the race's cumulative thresholds and take that item, amount from the triple table (Coin 10–40; Pearl 2–4; Blu Pearl 2–4; Jade 2–3; Topaz 1–3; Ruby 1–2; Food 2–6; Potion 1–4; Sermin 2–6; Gonshi 3–5; Nift 1–3; Mirget 1–3; Luffin 2–4; Turpin 1–3; Fireglobe 1–3; Loka 1–3; Medicin 1–3; Cube 1–4; Sphere 1–4; Pyramid 1–4; 0x51 5–20), else 1:

| race | item by d100 band |
|---|---|
| Orc | Coin 0–59%; Scimitar 60–74%; 0x29 75–89%; Food 90–99% |
| Zorlim | Coin 0–49%; Sermin 50–74%; Longsword 75–84%; Blu Pearl 85–99% |
| Tekhir | 0x51 0–59%; Gonshi 60–79%; 0x1a 80–89%; Pearl 90–99% |
| Troll | Coin 0–69%; Food 70–79%; Hammeraxe 80–89%; 0x29 90–99% |
| Goblin | Coin 0–39%; Smallaxe 40–54%; Jade 55–74%; Potion 75–99% |
| Minotaur | Coin 0–74%; Nift 75–99% |
| Domug | Coin 0–49%; Luffin 50–74%; Pearl 75–89%; Blu Pearl 90–99% |
| Kurdazi | 0x51 0–64%; Gonshi 65–79%; 0x1b 80–89%; Jade 90–99% |
| Jerrah | Coin 0–49%; Sermin 50–74%; Topaz 75–89%; Sphere 90–99% |
| Zebani | Coin 0–59%; Food 60–79%; Topaz 80–89%; Cube 90–99% |
| Gragan | Coin 0–49%; Potion 50–74%; Pyramid 75–99% |
| Mongor | Coin 0–39%; Sphere 40–59%; Cube 60–79%; Pyramid 80–99% |
| Gnoll | Coin 0–59%; Shortsword 60–79%; Fireglobe 80–89%; 0x50 90–99% |
| Ogre | Coin 0–49%; Hammeraxe 50–69%; 0x29 70–84%; Ruby 85–99% |
| Gaem | Coin 0–24%; Sermin 25–49%; 0x51 50–74%; Blu Pearl 75–99% |
| Zumagin | Coin 0–49%; 0x50 50–74%; Cube 75–89%; Loka 90–99% |
| Vankruh | Ruby 0–59%; Mirget 60–99% |
| Flamebelly | Topaz 0–74%; Broadsword 75–99% |
| Dreadknight | Sapphire 0–49%; Nift 50–74%; Greatsword 75–94%; Blu Pearl 95–99% |
| Farazu | Ruby 0–24%; 0x51 25–49%; Turpin 50–74%; Fireglobe 75–99% |

Races without a table (Sandgu, Slime, Skeleton, Zombie, Barg, Fermigon, Hibliss, Naur, Zakhad, Urgodot, Doombeast, Mizigu, Aciden, Kazih, Ghoul, Barbarian) drop nothing on tails. The value `Σ _lootvalues[item] × amount` is credited to `h_partybucks` for the hireling fair-share rule (`economy.md`). Treasure chests use `HROOM.hrmreward` (`locations.md`).

Tables (P95 file offsets): d100 band ends at 0x21E + race·4, the matching items at 0x17A + race·4 (a race whose first band is 0 has no table), `{item, lo, hi}` amounts at 0x13A until 0xFF. Vankruh: `_events+18 |= 0x40` (event 150) and, if it was slain, `_events+7 |= 0x20` (event 61). The value is added to every hireling present (`h_relatn` 2) at once (`ovl_164e`).

**Searching** (`ovl_0a06`/`ovl_0a78`, after the resurrection menu): while some monster record is unsearched, "Would you like to search for valuables?" (comtxt 0xC8, Yes/No); Yes → "Who is going to search?" (0x10F, a living member). Then corpse by corpse: "%h searches " (0xA7) + "a %l" / "an %l" (0xA8/0xA9; "an" for Elf, Orc, Ogre, Urgodot, Aciden — P95 0xCDB) + " and finds nothing." (0xAA) or " and finds: " (0xAB) and the treasure (`_PrtTreasure`). An item 9–0x30 (weapon, armour, clothing) is given worn: amount byte `0x80 | RndCo(20)`. `_IncObj` puts Coins in `h_gold` (≤ 9999); when it refuses (comtxt 0x32 / 0x33) the search stops at that corpse and the question is asked again for the rest.

## Combat songs (`V06 INT61_1d`, combat *Use* of an instrument)

Instruments (V06 file 0x28FF) and their two songs (`_w_songs` DS:4014, index `8·instrument + {0,1}`; the party learns a song from an NPC `S` dialogue line, `dialogue.md`, stored as bits 0/1 of `h_songs[instrument]`). Playing needs `h_music > 0` ("%h doesn't know how to play music."); knowing no song for that instrument just plays 'The Happy Traveller'. Each known song is played and **charms every living, visible monster of one race**: `RndCo(200) ≤ music + 100` → `c_state |= 0x21` — the creature is flagged *feared* (0x20) for the rest of the fight: the song sets no fear-turn counter (`c_itspc1` high nibble), so the flag never times out, and bit 0 (cleared when the creature is attacked, `P06 ovl_050a`) changes nothing while 0x20 stays set. Charmed monsters still count as alive for the win check. Each known song is played once per use (V06 `INT61_1d` at 0x290C: song 0, then song 1 if any monster of its race is present); the song → race table is V06 file 0x4EC + 8·instrument (`[10,31] [11,33] [18,22] [32,40]`). Texts: comtxt 0x117 (no music skill), 0x118 'The Happy Traveller' (no song known), 0xF3 "%h plays '%a'." (correction: the loop that repeats `music/20 + 1` times, V06 0x2860, is the **Horn**'s handler — it ends with comtxt 0x62 "The call of the horn is answered." — not the songs').

**The Horn** (V06 `INT61_1e`, 0x2819): song 13, then only in regions 12, 33, 35, 38, 40, 41, 44, 45, 46, 47 (V06 file 0x280E, 0-terminated) and once per V06 load (flag at file 0x280D), else "Nothing happens." (0x83). For `music/20 + 1` records from 17 up: `c_state = 0`, `_PlacePerson(q, r)` with `RndCo(45) = 9q + r`, `c_removes = 1`; then `ovl_0fcd` and "The call of the horn is answered." (0x62). What fills records 17 onward before this (and so which side answers) is not traced, so the port does not build the Horn.

| instrument | song 0 → race | song 1 → race |
|---|---|---|
| Flute (0x48) | 'Lullaby of Gu' → Sandgu | "Urg's Dream" → Urgodot |
| Lyre (0x44) | "Mage's Joy" → Slime | 'Rondo Miz' → Mizigu |
| Lute (0x45) | 'Morning Mist' → Barg | 'Wind Song' → Fermigon |
| Bandore (0x5b) | 'Sambali' → Doombeast | 'Firedance' → Munak |
