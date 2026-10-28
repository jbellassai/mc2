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

`_grpno < 60` means "n monsters of code `_grpno`" (`_monstlist = {g,g,g,g}`). Otherwise row `grpno − 60` = `{count, m0, m1, m2, m3}`; count 0 → the number comes from `D06.ptr8[7·diff + _semiranseed % 7]` (D06 counts by difficulty 0–7: `3 6 0 0 0 0 0 | 4 6 0 3 0 4 5 | 4 7 1 5 1 7 6 | 5 7 1 7 1 8 9 | 5 8 1 9 2 10 10 | 6 8 2 12 2 11 12 | 7 10 2 16 2 13 13 | 8 12 2 20 3 15 15`). Each monster drawn picks one of the four entries at random (`ovl_1323`) until its quota (`OV_0x19b` counters) is spent. A fourth entry marked `*` (bit 0x80) adds **one extra monster of that code** on top of the count (six if it is a Doombeast) and makes it the group's leader (`ovl_06b8/06c7`).

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
| **patrol** (8 per region, start positions P01 file 0x136; group = R `newsr[n]`) | `newsr[n & 7]` | same table | patrols wander (`ovl_18c1`, random of 8 directions, 3 tries) or, once engaged (`_ptrleng` bit, set when the patrol is on screen), step toward the party (`ovl_17c0`); reaching the party starts the fight (`_ctype 1`); `_ptrlsta` bit = destroyed. Guards, patrols and `_ptrleng` of a region **respawn** when the party enters it and `_lastgen[region] + interval ≥ month` (interval per region P01 file 0x32A `[6,1,3,3,3,3,3,2,2,3,3,3,2,2,1,2]` months); patrols are drawn only while event 106 is set or a short `OV_0x1bb` timer runs |
| **camp ambush** | the patrol that walks into the camp | region | a member on *Watch* (`h_actvty 9`) prevents the ambush flag (`camp.md`) |
| **town / dungeon ambush** (`P02`, `spetbl` type-0 spots, `locations.md` *Dungeon levels*) | spot `d1` | `locdiff − 1` | `_ambush` bit per ambush id = already fought; best `track` vs `RndCo(200)`, or a *Sense* that pointed at the spot, detects it (`skills.md`); `_ambflg` → monsters act first |
| **dungeon room** (door type 6–9, `HROOM.hrmgrp`, then `P07`) | `hrmgrp` | `locdiff − 1` | `_dunrms` bit = guards cleared (`locations.md`) |
| scripted | P08/P09 scenes | | |

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

## Combat songs (`V06 INT61_1d`, combat *Use* of an instrument)

Instruments (V06 file 0x28FF) and their two songs (`_w_songs` DS:4014, index `8·instrument + {0,1}`; the party learns a song from an NPC `S` dialogue line, `dialogue.md`, stored as bits 0/1 of `h_songs[instrument]`). Playing needs `h_music > 0` ("%h doesn't know how to play music."); knowing no song for that instrument just plays 'The Happy Traveller'. Each known song is played and **charms every living, visible monster of one race**: `RndCo(200) ≤ music + 100` → `c_state |= 0x21` — the creature is flagged *feared* (0x20) for the rest of the fight: the song sets no fear-turn counter (`c_itspc1` high nibble), so the flag never times out, and bit 0 (cleared when the creature is attacked, `P06 ovl_050a`) changes nothing while 0x20 stays set. Charmed monsters still count as alive for the win check; the song is repeated `music/20 + 1` times per use (`combat.md`).

| instrument | song 0 → race | song 1 → race |
|---|---|---|
| Flute (0x48) | 'Lullaby of Gu' → Sandgu | "Urg's Dream" → Urgodot |
| Lyre (0x44) | "Mage's Joy" → Slime | 'Rondo Miz' → Mizigu |
| Lute (0x45) | 'Morning Mist' → Barg | 'Wind Song' → Fermigon |
| Bandore (0x5b) | 'Sambali' → Doombeast | 'Firedance' → Munak |
