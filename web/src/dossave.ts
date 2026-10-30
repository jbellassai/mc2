// DOS saved games (docs/formats.md, DOS saved games): `FFSAVx.MCS` is the raw image of MC2.EXE's DS:4CF6..774D
// (`_startsvdta`..`_endsvdta`, 0x2A57 bytes; _RestoreGame 07fa:0fae reads it straight back, no header or check).
// `fromDos` turns one into the port's save snapshot (main.ts `snapshot()`/`restore()`); `toDos` writes a snapshot
// into a copy of a real save, which supplies every byte the port does not model. No DOM: Node runs this file.
//
// Globals (file offset = DS − 0x4CF6). M = mapped both ways, D = derived when writing, C = carried from the template.
//  M _minute _hour _date _month _juldate _weather  clock.ts (time_weather.md; month 0-11 as the port's)
//  D _year       10 + (181 + juldate) div 360: new game day 2 of month 6, year 10 (new_game.md), P92 ovl_01cd rolls it
//  D _daynite    'L'/'D' as Clock.daylight() (P92 hour tick sets it at sunrise/sunset, time_weather.md)
//  D _remdays    max(0, 1000 − juldate): 1000 at a new game, −1 a day (P92 ovl_01cd)
//  C _tempert    dead (time_weather.md)
//  D _season     SEASON[month] (P92 file 0x24D, ovl_0265; = world.ts SEASON)
//  M _ssnwthrs   world.ssn (12 bytes)
//  M _party _member0 _formatn   party.members: _party[slot] = num (0xFF free), _member0[slot] = rec, _formatn[cell] = slot
//                (npcs.md Joining). The port has no holes: members go to slots 0.. in order; free slots keep their bytes
//  D _psize      _CntPar (EXE 1166:029e counts _party ≠ 0xFF); a cache, stale in some saves (FFSAVH)
//  D _p1x _p1y   party squares: town origin + (cell mod 3, cell div 3) (_NewPXY 0a31:00ef), world all = leader
//                (P01 ovl_154f); both recomputed from _pwinxy when P02/P01 starts. Free slots keep their bytes
//  D _curloc     level loc.locnum (D01 = 1)       D _currm 0xFF   D _curmpg 2 level, 1 world   D _inroom 0
//  M _curreg     world.region (kept in towns: FFSAVF Dorak 7 has 0x0B)
//  C _curlev     always 0 in every save
//  D _curseg _curmap  town: the first block whose 32×34 square holds _pwinxy (P02 ovl at 0x560), world: the same from
//                world.seg on (P01 ovl_13f1/ovl_141b); _curmap = that block's M number. P01/P02 set _curmap = 0xFF and
//                recompute both on entry
//  D _curtils _curvar  level.ts and the level's D number (world: 1 and 0xFF)
//  D _locnm      the level's (world: the region record's) name, 10 bytes (FFSAVA "Telermain ", FFSAVB "Oshcrun I.")
//  D _curpla     0: the port's acting member is the leader
//  M _beenflg    been (word, bit 15 = stronghold 0)
//  C _savdat _savmpg  the location saved on entering a room (_SavLocD/_ResLocD); stale on a level
//  M _member6    party.roster: the 31 companions' stored records (npcs.md Leaving); absent = R90 (companions.json)
//  D _mapx _mapy D01 block world.seg's origin (P01 ovl_147c); in towns it keeps the template's unless world.seg differs
//  C _mapix      always 0
//  D _pwinx _pwiny  leader − (4,3) on a level, − (5,4) on the world map (new_game.md, CLAUDE.md party squares)
//  M _wildx _wildy  wild
//  M _rents      rent (service.ts, ids 0x40-0x47)
//  C _rmdata     the door / room being entered (scene.ts, combat.ts); scratch outside rooms
//  M _capsta _boatx _boaty _capdays _curcap   world.ships (ships.md); D _sailsw = curcap ≥ 0 (ships.md Boarding)
//  C _capcost    unused (ships.md)
//  C _knpcstats  zero in every save, no reference found in the decompiles (guess: unused)
//  M _npcsta     party.away, bit n = NPC n (LSB first, as _FindBit; FFSAVE: Ralle 7, Polo 24)
//  M _events     events (bit n = event n; event 0 = night, FFSAVF)
//  M _dunrms _duntre  dunrms/duntre 'Dnn:id', bit = HROOM id, one bitmap for all levels (locations.md); hroom ids are
//                unique but 251 (D65, D93), so bit 251 maps to both; their group-0xCA stand-in is id 0xFC (P02 0x947).
//                A bit no pack level has an HROOM (or treasure group, for _chests) for is dropped by fromDos
//  M _ambush     ambushed, bit = ambush id (spot d2)
//  C _met        NPCs met (FFFAR FirstMeet/SecondMeet, P91 ovl_045d); not modelled by the port: greeting texts only
//  M _chests     chests 'Dnn:g', bit = treasure group g (spot d2; groups are unique across levels)
//  M _grdsta _ptrlsta _ptrleng _lastgen _ptrlxy  world.cleared/dead/engaged/lastgen/ptrl (encounters.md Patrols)
//  M _mushsta    patches.left, a nibble per patch, even id high (locations.md Mushroom patches); bytes 15-19 carried
//  M _curwthrs   world.wthrs {weather, hours} ×16
//  C _setupxy    the combat formation table (P81 init; FFSAVF has one byte changed)
//  M _assgn0     assigns (31 × 25, empty = all 0xFF; an empty record keeps the template's bytes when they are empty)
//  C _workx _worky _tiles _hroomrec _cmbtyp _exitdir _lastdir _armcnt _locdata _curter _hroomtype  scratch of rooms,
//                fights and steps (locations.md, combat.md); recomputed before use
//  M _detectsw   detect          M _casino casino          M _dnggates gates (bit = gate index, special_rooms.md)
//  D _wlkwcount  0: the port does not save Walkwater (P02 zeroes it outside dungeons)
//  C _kmhero     Ralle's look variant from an imported Keys to Maramon hero (P81)
//  M _indisguise disguise        D _tailorcharm Σ h_tailor >> 5 of the members (party.ts; P97 0x728 sums every _member0
//                slot whose name is set, stale ones too, when the party changes; edited saves hold stale values)
//  M _snakes _snakelocs _snakeptr  snakes [level, x, y, tile]: {x, y} + the level's D number (_curvar, 0xFF unused),
//                next entry in _snakeptr (V02 INT60_06/07); INT60_14 re-applies every entry of the level on entry, so
//                unused entries are cleared. The tile is not saved: the first aniptr record for the tile under it
//  M _disasterday _scrollonfloor   disasterday, scroll
//  D _lastp02var _spetbldone  on a level _lastp02var = its D number; _spetbldone (remarks spoken, cleared by V02 when
//                _curvar ≠ _lastp02var) is kept only when that did not change, else zeroed like the port's
//  Not in the save: _VANKRUHXY (DS:EA1E) → vankruhxy [0, 0]; P02's step counters → walk [0, 0].
import { HERO, ASSIGNMENT, decode, type Field } from './convert';
import type { HeroRecord } from './hero';
import type { Location } from './pack';

/** Reads a pack file as JSON (pack.ts `json`, or the files in out/pack under Node). */
export type Load = <T>(path: string) => Promise<T>;
type Rec = Record<string, number>;

/** The port's save snapshot (main.ts `snapshot()`), as `restore()` takes it. */
export type DosSnapshot = {
  v: number; when: string; place: string;   // v 1
  clock: { minute: number; hour: number; date: number; month: number; weather: number; juldate: number };
  events: number[];
  party: { members: { rec: HeroRecord; cell: number; num: number }[]; away: number[]; roster: [number, HeroRecord][] };
  level: { id: string; ts: number }; at: { x: number; y: number };
  world: {
    region: number; wthrs: { weather: number; hours: number }[]; ssn: number[]; cleared: number[]; ptrl: number[][];
    dead: number[]; engaged: number[]; lastgen: number[]; seg: number;
    ships: { sta: number[]; days: number[]; x: number[]; y: number[]; cur: number };
  };
  patches: number[]; dunrms: string[]; duntre: string[]; chests: string[]; ambushed: number[]; rent: number[];
  walk: number[]; casino: number[]; gates: number[]; detect: number; snakes: [string, number, number, number][];
  scroll: number; disasterday: number; vankruhxy: [number, number]; assigns: (Rec | null)[]; wild: { x: number; y: number };
  been: number; disguise: number;
};

export const SIZE = 0x2a57;
/** Every saved global's file offset (docs/symbols.txt, DS − 0x4CF6); each runs to the next. */
export const GLOBALS: [string, number][] = [['_minute', 0x0], ['_hour', 0x2], ['_date', 0x4], ['_month', 0x6], ['_year', 0x8],
  ['_daynite', 0xa], ['_remdays', 0xb], ['_juldate', 0xd], ['_weather', 0xf], ['_tempert', 0x11], ['_season', 0x13],
  ['_ssnwthrs', 0x15], ['_party', 0x21], ['_psize', 0x2d], ['_formatn', 0x2f], ['_p1x', 0x38], ['_p1y', 0x3e],
  ['_curloc', 0x44], ['_curreg', 0x46], ['_curlev', 0x48], ['_curseg', 0x4a], ['_currm', 0x4c], ['_curmpg', 0x4e],
  ['_curtils', 0x50], ['_curvar', 0x52], ['_curmap', 0x54], ['_inroom', 0x56], ['_locnm', 0x58], ['_curpla', 0x62],
  ['_beenflg', 0x64], ['_savdat', 0x66], ['_savmpg', 0x70], ['_member0', 0x78], ['_member6', 0x5a0], ['_mapx', 0x2044],
  ['_mapy', 0x2046], ['_mapix', 0x2048], ['_pwinx', 0x2049], ['_pwiny', 0x204a], ['_wildx', 0x204b], ['_wildy', 0x204c],
  ['_rents', 0x204d], ['_rmdata', 0x2055], ['_capsta', 0x205d], ['_boatx', 0x2063], ['_boaty', 0x2069], ['_sailsw', 0x206f],
  ['_curcap', 0x2070], ['_capdays', 0x2071], ['_capcost', 0x2077], ['_knpcstats', 0x2078], ['_npcsta', 0x2171],
  ['_events', 0x2191], ['_dunrms', 0x21b1], ['_ambush', 0x21d1], ['_met', 0x21f1], ['_chests', 0x2211], ['_grdsta', 0x2231],
  ['_ptrlsta', 0x2241], ['_ptrleng', 0x2251], ['_lastgen', 0x2261], ['_ptrlxy', 0x2271], ['_mushsta', 0x2371],
  ['_curwthrs', 0x2385], ['_setupxy', 0x23a5], ['_assgn0', 0x23d5], ['_workx', 0x26dc], ['_worky', 0x26de], ['_tiles', 0x26e0],
  ['_detectsw', 0x26e1], ['_hroomrec', 0x26e3], ['_cmbtyp', 0x26f0], ['_exitdir', 0x26f1], ['_casino', 0x26fd],
  ['_wlkwcount', 0x270d], ['_duntre', 0x270e], ['_kmhero', 0x272e], ['_dnggates', 0x272f], ['_lastdir', 0x2730],
  ['_armcnt', 0x2732], ['_locdata', 0x2733], ['_curter', 0x273d], ['_indisguise', 0x273e], ['_hroomtype', 0x2740],
  ['_tailorcharm', 0x2741], ['_snakes', 0x2742], ['_snakelocs', 0x2942], ['_snakeptr', 0x2a42], ['_disasterday', 0x2a43],
  ['_scrollonfloor', 0x2a45], ['_lastp02var', 0x2a46], ['_spetbldone', 0x2a47]];
const O = Object.fromEntries(GLOBALS) as Record<string, number>;
/** The global holding file offset `o`. */
export const globalAt = (o: number) => GLOBALS.reduce((g, e) => e[1] <= o ? e : g)[0];

const SEASON = [0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 0];   // P92 file 0x24D, by month
const SUNRISE = [8, 8, 7, 7, 7, 6, 6, 6, 7, 7, 7, 8], SUNSET = [18, 18, 19, 19, 19, 20, 20, 20, 19, 19, 19, 18];   // clock.ts
const HSIZE = 220, ASIZE = 25;
const two = (n: number) => String(n).padStart(2, '0');
const num = (id: string) => Number(id.slice(1));
const name10 = (s: string) => s.slice(0, 10).padEnd(10);
const clean = (s: string) => s.replace(/\s*[MX]$/, '').trim();

// ---- bytes ----
const u16 = (d: Uint8Array, o: number) => d[o] | d[o + 1] << 8;
const put16 = (d: Uint8Array, o: number, v: number) => { d[o] = v & 0xff; d[o + 1] = v >> 8 & 0xff; };
/** Bit numbers set in an n-bit map (bit k = byte k >> 3, mask 1 << (k & 7), as _SetBit/_FindBit). */
const bits = (d: Uint8Array, o: number, n: number) => [...Array(n).keys()].filter(k => d[o + (k >> 3)] >> (k & 7) & 1);
const putBits = (d: Uint8Array, o: number, n: number, set: Iterable<number>) => {
  d.fill(0, o, o + (n >> 3));
  for (const k of set) if (k >= 0 && k < n) d[o + (k >> 3)] |= 1 << (k & 7);
};
/** The inverse of convert.ts `decode`; a string equal to the bytes' own keeps them (the bytes after its NUL too). */
function encode(d: Uint8Array, o: number, fields: Field[], obj: Record<string, unknown>) {
  for (const [field, off, kind, dims] of fields) {
    const v = obj[field];
    if (kind === 'str') {
      const s = String(v ?? '');
      if ((decode(d.subarray(o + off), [[field, 0, 'str', dims]])[field]) === s) continue;
      d.fill(0, o + off, o + off + dims[0]);
      for (let i = 0; i < Math.min(s.length, dims[0]); i++) d[o + off + i] = s.charCodeAt(i) & 0xff;
      continue;
    }
    const vals = (dims.length ? (v as unknown[]).flat() : [v]) as number[];
    vals.forEach((x, i) => kind === 'u16' ? put16(d, o + off + 2 * i, x) : d[o + off + i] = x & 0xff);
  }
}

// ---- pack data ----
interface Maps { blocks?: Record<string, string>; tiles: Map<number, { walkable: number[]; anim: string }>; maps: Map<Location, Grid> }
type Grid = { w: number; at: (x: number, y: number) => number };
const unhex = (s: string) => Uint8Array.from(s.match(/../g) ?? [], h => parseInt(h, 16));
/** A level's composed map (level.ts `Level.load`). */
async function cells(load: Load, loc: Location, m: Maps): Promise<Grid> {
  if (m.maps.has(loc)) return m.maps.get(loc)!;
  const w = Math.max(loc.mapsize[0], ...loc.blocks.map(b => b.x + 42)), h = Math.max(loc.mapsize[1], ...loc.blocks.map(b => b.y + 42));
  const c = new Uint8Array(w * h).fill(0xff);
  m.blocks ??= await load('blocks.json');
  for (const b of loc.blocks) {
    if (!b.block) continue;
    const t = unhex(m.blocks![`M${two(b.block)}E${two(b.tileset)}`] ?? '');
    for (let y = 0; y < 42; y++) for (let x = 0; x < 42; x++) c[(b.y + y) * w + b.x + x] = t[y * 42 + x];
  }
  const g: Grid = { w, at: (x, y) => x >= 0 && y >= 0 && x < w && y < h ? c[y * w + x] : 0xff };
  m.maps.set(loc, g);
  return g;
}
async function tiledata(load: Load, ts: number, m: Maps) {
  if (!m.tiles.has(ts)) m.tiles.set(ts, await load(`tiledata/B${two(ts)}.json`));
  return m.tiles.get(ts)!;
}
/** Every level D-file in the pack (D02-D99 that load), for the bitmaps keyed by level. */
async function levels(load: Load): Promise<Map<string, Location>> {
  const out = new Map<string, Location>();
  for (let n = 2; n < 100; n++) {
    const id = `D${two(n)}`;
    try { const l = await load<Location>(`locations/${id}.json`); if (l && !Array.isArray(l) && l.kind === 'level') out.set(id, l); } catch { /* none */ }
  }
  return out;
}
/** The tileset a program-2 PGM record gives level D`n` (as the door that leads there), else its blocks' commonest. */
function tilesetOf(all: Map<string, Location>, id: string): number {
  for (const l of all.values()) for (const p of l.pgms) if (p.program === 2 && p.datafile === num(id)) return p.tileset;
  const counts = new Map<number, number>();
  for (const b of all.get(id)?.blocks ?? []) counts.set(b.tileset, (counts.get(b.tileset) ?? 0) + 1);
  return [...counts].sort((a, b) => b[1] - a[1])[0]?.[0] ?? 0;
}
/** P02 ovl at 0x560 / P01 ovl_141b: the first block, searching from `from`, whose 32×34 square holds the window. */
function segOf(blocks: Location['blocks'], wx: number, wy: number, from: number): number {
  for (let k = 0; k < blocks.length; k++) {
    const i = (from + k) % blocks.length, b = blocks[i];
    if (wx >= b.x && wx < b.x + 32 && wy >= b.y && wy < b.y + 34) return i;
  }
  return -1;
}

/** A DOS save → the port's snapshot. Saves made on a level or the world map map exactly; a save made in a P05 room
 *  (a building) puts the party next to the room's door instead (the square before the door is not saved; the first
 *  walkable of S, N, E, W is a guess; the location's D file is taken to be its `_locspec`, true for towns). Other
 *  programs (P07 chambers, P08/P09 rooms, fights) are refused. */
export async function fromDos(b: Uint8Array, load: Load): Promise<DosSnapshot> {
  if (b.length !== SIZE) throw new Error(`a DOS saved game is ${SIZE} bytes, not ${b.length}`);
  const w = (g: string, i = 0) => u16(b, O[g] + 2 * i), at = (g: string, i = 0) => b[O[g] + i];
  const hero = (o: number) => decode(b.subarray(o), HERO) as HeroRecord;
  const maps: Maps = { tiles: new Map(), maps: new Map() };
  let all: Map<string, Location> | null = null;
  const index = async () => all ??= await levels(load);

  // the party: slots in use, the leader (cell 0) first
  const formatn = [...b.subarray(O._formatn, O._formatn + 9)];
  const slots = [0, 1, 2, 3, 4, 5].filter(s => w('_party', s) !== 0xff);
  const free = [...Array(9).keys()].filter(c => !slots.includes(formatn[c]));
  const members = slots.map(s => ({ rec: hero(O._member0 + HSIZE * s), cell: formatn.includes(s) ? formatn.indexOf(s) : free.shift() ?? 0, num: w('_party', s) }))
    .sort((a, c) => (a.cell === 0 ? -1 : 0) - (c.cell === 0 ? -1 : 0));
  const roster = Array.from({ length: 31 }, (_, i) => [i + 1, hero(O._member6 + HSIZE * i)] as [number, HeroRecord]);

  // the place
  const mpg = w('_curmpg'), pwx = at('_pwinx'), pwy = at('_pwiny');
  const d01 = await load<Location>('locations/D01.json');
  const origin = (bx: number, by: number) => d01.blocks.findIndex(k => k.x === bx && k.y === by);
  let id: string, ts: number, pos: { x: number; y: number }, seg: number;
  if (mpg === 1) {
    id = 'D01'; ts = 1; pos = { x: pwx + 5 & 0xff, y: pwy + 4 & 0xff }; seg = w('_curseg');
  } else if (mpg === 2) {
    id = `D${two(w('_curvar'))}`; ts = w('_curtils'); pos = { x: pwx + 4 & 0xff, y: pwy + 3 & 0xff };
    seg = Math.max(0, origin(w('_mapx'), w('_mapy')));
  } else if (mpg === 5) {
    // the door the room was entered by: `_rmdata[7]` = its location (_locspec), `_currm` = its room id
    const loc = at('_rmdata', 7), room = w('_currm');
    seg = Math.max(0, origin(w('_mapx'), w('_mapy')));
    if (loc === 1) { id = 'D01'; ts = 1; pos = { x: at('_wildx'), y: at('_wildy') }; }   // P01 0x865: _wildxy = the feature
    else {
      id = `D${two(loc)}`;
      const lv = (await index()).get(id), d = lv?.doors.find(e => e.id === room);
      if (!lv || !d) throw new Error(`the room ${room} of location ${loc} has no door the port knows`);
      ts = tilesetOf(all!, id);
      const map = await cells(load, lv, maps), walk = new Set((await tiledata(load, ts, maps)).walkable);
      const step = [[0, 1], [0, -1], [1, 0], [-1, 0]].find(([dx, dy]) => walk.has(map.at(d.x + dx, d.y + dy))) ?? [0, 1];
      pos = { x: d.x + step[0], y: d.y + step[1] };
    }
  } else throw new Error(`saved in program P${two(mpg)} (a room or fight the port cannot start in)`);
  const lv = id === 'D01' ? d01 : (await index()).get(id) ?? await load<Location>(`locations/${id}.json`);
  const region = w('_curreg') === 0xff ? 0 : w('_curreg');
  const rname = (await load<Location>(`locations/R${32 + region}.json`)).name;

  // bitmaps keyed by level
  const dunkeys = async (g: string) => {
    const set = bits(b, O[g], 256), out: string[] = [];
    if (!set.length) return out;
    for (const [lid, l] of await index()) for (const h of l.hrooms ?? []) {
      if (set.includes(h.id)) out.push(`${lid}:${h.id}`);
      if (h.group === 0xca && set.includes(0xfc)) out.push(`${lid}:${0xfc}`);
    }
    return out;
  };
  const chestBits = bits(b, O._chests, 256), chests: string[] = [];
  if (chestBits.length) for (const [lid, l] of await index())
    for (const g of new Set((l.spots ?? []).filter(p => p.type === 2 || p.type === 3).map(p => p.d2))) if (chestBits.includes(g)) chests.push(`${lid}:${g}`);

  // Pierce/Repel log: the new tile from the first aniptr record of the tile under it (V02 INT60_14, every entry)
  const snakes: [string, number, number, number][] = [];
  for (let i = 0; i < 256; i++) {
    if (at('_snakelocs', i) === 0xff) continue;                     // unused (P81: 0xFF); _snakeptr wraps at 256
    const sid = `D${two(at('_snakelocs', i))}`, x = at('_snakes', 2 * i), y = at('_snakes', 2 * i + 1);
    const l = (await index()).get(sid);
    if (!l) continue;
    const t = (await cells(load, l, maps)).at(x, y), a = unhex((await tiledata(load, tilesetOf(all!, sid), maps)).anim);
    let tile = -1;
    for (let k = 0; k < a.length && a[k] !== 0xff; k += 7) if (a[k] === t) { tile = a[k + 1]; break; }   // V02 INT60_14
    if (tile >= 0) snakes.push([sid, x, y, tile]);
  }

  const mush = [...Array(30).keys()].map(i => at('_mushsta', i >> 1) >> (i & 1 ? 0 : 4) & 15);
  const assigns = Array.from({ length: 31 }, (_, i) => b[O._assgn0 + ASIZE * i] === 0xff ? null : decode(b.subarray(O._assgn0 + ASIZE * i), ASSIGNMENT) as Rec);
  return {
    v: 1, when: new Date().toISOString(), place: clean(id === 'D01' ? rname : lv.name),
    clock: { minute: w('_minute'), hour: w('_hour'), date: w('_date'), month: w('_month'), weather: w('_weather'), juldate: w('_juldate') },
    events: bits(b, O._events, 256),
    party: { members, away: bits(b, O._npcsta, 256), roster },
    level: { id, ts }, at: pos,
    world: {
      region, wthrs: Array.from({ length: 16 }, (_, i) => ({ weather: at('_curwthrs', 2 * i), hours: at('_curwthrs', 2 * i + 1) })),
      ssn: [...b.subarray(O._ssnwthrs, O._ssnwthrs + 12)], cleared: bits(b, O._grdsta, 128),
      ptrl: Array.from({ length: 128 }, (_, i) => [at('_ptrlxy', 2 * i), at('_ptrlxy', 2 * i + 1)]),
      dead: bits(b, O._ptrlsta, 128), engaged: bits(b, O._ptrleng, 128), lastgen: [...b.subarray(O._lastgen, O._lastgen + 16)], seg,
      ships: { sta: [...b.subarray(O._capsta, O._capsta + 6)], days: [...b.subarray(O._capdays, O._capdays + 6)],
        x: [...b.subarray(O._boatx, O._boatx + 6)], y: [...b.subarray(O._boaty, O._boaty + 6)], cur: at('_curcap') === 0xff ? -1 : at('_curcap') },
    },
    patches: mush, dunrms: await dunkeys('_dunrms'), duntre: await dunkeys('_duntre'), chests, ambushed: bits(b, O._ambush, 256),
    rent: [...b.subarray(O._rents, O._rents + 8)], walk: [0, 0], casino: Array.from({ length: 8 }, (_, i) => w('_casino', i)),
    gates: bits(b, O._dnggates, 8), detect: w('_detectsw'), snakes, scroll: at('_scrollonfloor'), disasterday: w('_disasterday'),
    vankruhxy: [0, 0], assigns, wild: { x: at('_wildx'), y: at('_wildy') }, been: w('_beenflg'), disguise: w('_indisguise'),
  };
}

/** The port's snapshot → a DOS save: `template` (a real save) with every modelled global written over it. */
export async function toDos(sv: DosSnapshot, template: Uint8Array, load: Load): Promise<Uint8Array> {
  if (template.length !== SIZE) throw new Error(`the template is ${template.length} bytes, not ${SIZE}`);
  const d = Uint8Array.from(template), put = (g: string, v: number, i = 0) => put16(d, O[g] + 2 * i, v);
  const set = (g: string, v: number, i = 0) => { d[O[g] + i] = v & 0xff; };
  const lid = sv.level.id, wild = lid === 'D01';
  const loc = await load<Location>(`locations/${lid}.json`), d01 = wild ? loc : await load<Location>('locations/D01.json');

  // the clock
  const c = sv.clock;
  put('_minute', c.minute); put('_hour', c.hour); put('_date', c.date); put('_month', c.month); put('_juldate', c.juldate);
  put('_weather', c.weather); put('_year', 10 + Math.floor((181 + c.juldate) / 360)); put('_remdays', Math.max(0, 1000 - c.juldate));
  set('_daynite', c.hour >= SUNRISE[c.month] && c.hour < SUNSET[c.month] ? 0x4c : 0x44); put('_season', SEASON[c.month]);
  d.set(sv.world.ssn.slice(0, 12), O._ssnwthrs);

  // the party, in slots 0.. in order
  const ms = sv.party.members.slice(0, 6), wx = sv.at.x - (wild ? 5 : 4) & 0xff, wy = sv.at.y - (wild ? 4 : 3) & 0xff;
  d.fill(0xff, O._formatn, O._formatn + 9);
  for (let s = 0; s < 6; s++) {
    const m = ms[s];
    put('_party', m ? m.num : 0xff, s);
    if (!m) continue;
    encode(d, O._member0 + HSIZE * s, HERO, m.rec);
    set('_formatn', s, m.cell);
    set('_p1x', wild ? sv.at.x : sv.at.x + m.cell % 3, s); set('_p1y', wild ? sv.at.y : sv.at.y + Math.floor(m.cell / 3), s);
  }
  put('_psize', ms.length); put('_curpla', 0);
  set('_tailorcharm', ms.reduce((t, m) => t + (m.rec.h_tailor as number), 0) >> 5);
  putBits(d, O._npcsta, 256, sv.party.away);
  const roster = new Map(sv.party.roster);
  const r90 = roster.size < 31 ? await load<HeroRecord[]>('companions.json') : [];
  for (let n = 1; n <= 31; n++) { const r = roster.get(n) ?? r90[n - 1]; if (r) encode(d, O._member6 + HSIZE * (n - 1), HERO, r); }

  // the place
  set('_pwinx', wx); set('_pwiny', wy);
  put('_curloc', loc.locnum); put('_curreg', sv.world.region); put('_currm', 0xff); put('_curmpg', wild ? 1 : 2); put('_inroom', 0);
  put('_curtils', wild ? 1 : sv.level.ts); put('_curvar', wild ? 0xff : num(lid));
  const name = wild ? (await load<Location>(`locations/R${32 + sv.world.region}.json`)).name : loc.name;
  for (let i = 0; i < 10; i++) set('_locnm', name10(name).charCodeAt(i), i);
  const wseg = Math.min(Math.max(0, sv.world.seg), d01.blocks.length - 1);
  const putMap = (s: number) => { put('_mapx', d01.blocks[s].x); put('_mapy', d01.blocks[s].y); };
  if (wild) {
    const s = segOf(d01.blocks, wx, wy, wseg), k = s < 0 ? wseg : s;
    put('_curseg', k); put('_curmap', d01.blocks[k].block); putMap(k);
  } else {
    const k = Math.max(0, segOf(loc.blocks, wx, wy, 0));
    put('_curseg', k); put('_curmap', loc.blocks[k]?.block ?? 0);
    const was = d01.blocks.findIndex(b => b.x === u16(d, O._mapx) && b.y === u16(d, O._mapy));
    if (Math.max(0, was) !== wseg) putMap(wseg);
    if (d[O._lastp02var] !== num(lid)) d.fill(0, O._spetbldone, O._spetbldone + 16);
    set('_lastp02var', num(lid));
  }
  set('_wildx', sv.wild.x); set('_wildy', sv.wild.y);

  // the world map
  const W = sv.world;
  W.wthrs.slice(0, 16).forEach((r, i) => { set('_curwthrs', r.weather, 2 * i); set('_curwthrs', r.hours, 2 * i + 1); });
  putBits(d, O._grdsta, 128, W.cleared); putBits(d, O._ptrlsta, 128, W.dead); putBits(d, O._ptrleng, 128, W.engaged);
  d.set(W.lastgen.slice(0, 16), O._lastgen);
  W.ptrl.slice(0, 128).forEach(([x, y], i) => { set('_ptrlxy', x, 2 * i); set('_ptrlxy', y, 2 * i + 1); });
  const sh = W.ships;
  for (let i = 0; i < 6; i++) { set('_capsta', sh.sta[i], i); set('_capdays', sh.days[i], i); set('_boatx', sh.x[i], i); set('_boaty', sh.y[i], i); }
  set('_curcap', sh.cur < 0 ? 0xff : sh.cur); set('_sailsw', sh.cur >= 0 ? 1 : 0);

  // flags and counters
  putBits(d, O._events, 256, sv.events);
  const ids = (keys: string[]) => keys.map(k => Number(k.split(':')[1]));
  putBits(d, O._dunrms, 256, ids(sv.dunrms)); putBits(d, O._duntre, 256, ids(sv.duntre)); putBits(d, O._chests, 256, ids(sv.chests));
  putBits(d, O._ambush, 256, sv.ambushed);
  putBits(d, O._dnggates, 8, sv.gates);
  for (let i = 0; i < 15; i++) set('_mushsta', (sv.patches[2 * i] & 15) << 4 | sv.patches[2 * i + 1] & 15, i);
  sv.rent.slice(0, 8).forEach((r, i) => set('_rents', r, i));
  sv.casino.slice(0, 8).forEach((r, i) => put('_casino', r, i));
  put('_detectsw', sv.detect); set('_wlkwcount', 0); put('_disasterday', sv.disasterday); set('_scrollonfloor', sv.scroll);
  put('_beenflg', sv.been); put('_indisguise', sv.disguise);
  const sn = sv.snakes.slice(-256);                                  // V02 INT60_06/07 wrap: the newest 256
  d.fill(0, O._snakes, O._snakes + 512); d.fill(0xff, O._snakelocs, O._snakelocs + 256);
  sn.forEach(([s, x, y], i) => { set('_snakes', x, 2 * i); set('_snakes', y, 2 * i + 1); set('_snakelocs', num(s), i); });
  set('_snakeptr', sn.length & 0xff);

  // assignments
  for (let i = 0; i < 31; i++) {
    const r = sv.assigns[i], o = O._assgn0 + ASIZE * i;
    if (r) encode(d, o, ASSIGNMENT, r);
    else if (d[o] !== 0xff) d.fill(0xff, o, o + ASIZE);
  }
  return d;
}

/** `FFSAV.MCI`: the load/save menu's labels, 8 × 16 bytes (slots A-H; EXE _getgnames 07fa:0e52 reads it, NUL-ending
 *  each at byte 15; a missing file reads as all empty). _RestoreGame does not look at it: a slot loads without a label. */
export const mciNames = (mci: Uint8Array) =>
  Array.from({ length: 8 }, (_, i) => String.fromCharCode(...mci.subarray(16 * i, 16 * i + 15)).split('\0')[0]);
/** `mci` (or a new one) with slot 0-7's label set, as P98 ovl_027b stores a typed name (up to 15 characters). */
export function mciWith(mci: Uint8Array | null, slot: number, label: string): Uint8Array {
  const d = new Uint8Array(128);
  if (mci) d.set(mci.subarray(0, 128));
  d.fill(0, 16 * slot, 16 * slot + 16);
  for (let i = 0; i < Math.min(15, label.length); i++) d[16 * slot + i] = label.charCodeAt(i) & 0xff;
  return d;
}
