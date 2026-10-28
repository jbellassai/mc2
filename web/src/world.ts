// The world map (P01, rules/locations.md World map, rules/time_weather.md): the leader alone stands at window + (5,4);
// the region (`_curreg`) is the first of 16 rectangles containing the party and selects the region record R(32+n),
// whose town entrances, features and spots live on its own tables. Weather is regional and hourly (P92 ovl_04c7).
import { json, hex, type Location } from './pack';
import type { Party } from './party';
import type { Clock } from './clock';
import type { Level } from './level';
import { Ships, type ShipData } from './ships';

interface P01 {
  terraintime: number[]; weathertime: number[]; terrainenergy: number[]; clothing: number[][]; regions: number[][]; patchtiles: number[];
  patrols: number[][]; respawn: number[]; steps: { dirs: number[][]; side1: number[][]; side2: number[][]; order: number[] };
  ships: ShipData;
}
const SEASON = [0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 0];   // P92 file 0x24D, by month
const rnd = (n: number) => Math.floor(Math.random() * n);

export class World {
  region = 0;                                          // new game `_curreg` 0 (Oshcrun Isle, Telermain's region)
  rec: Location | null = null;
  /** `_curwthrs`: {weather, hours left} per region; all {Clear, 0} in a new game (FFSAVA). */
  private readonly wthrs = Array.from({ length: 16 }, () => ({ weather: 0, hours: 0 }));
  /** `_ssnwthrs`: the current region's 4 {threshold, weather, duration} triples; new game [100, Clear, 0x8F]. */
  private ssn: number[] = [100, 0, 0x8f, 0, 0, 0, 0, 0, 0, 0, 0, 0];

  /** `_ptrlxy`: the 128 patrols' squares (8 per region, patrol n belongs to region n >> 3; x 0 = none). */
  ptrl: number[][];
  /** `_ptrlsta` (destroyed) and `_ptrleng` (chasing the party), bit = patrol number. */
  readonly dead = new Set<number>();
  readonly engaged = new Set<number>();
  /** `_lastgen`: the month each region last respawned (0 in a new game). */
  private lastgen = Array<number>(16).fill(0);
  /** `_curseg`: the world-map block the party is in. */
  private seg = 0;

  /** The six captains and their boats (ships.ts). */
  readonly ships: Ships;

  private constructor(private p01: P01) { this.ptrl = p01.patrols.map(p => [...p]); this.ships = new Ships(p01.ships); }
  static async create(): Promise<World> { return new World(await json<P01>('p01.json')); }

  /** P01 ovl_14d6 / ovl_14fd: entering another region loads its record and its season's weather table. */
  async at(x: number, y: number, clock: Clock) {
    const r = this.regionOf(x, y);
    if (r === this.region) { this.rec ??= await json<Location>(`locations/R${32 + r}.json`); return; }   // same region: no copy
    this.region = r;
    this.rec = await json<Location>(`locations/R${32 + r}.json`);
    this.ssn = [...hex(this.rec.tables.weathr).slice(12 * SEASON[clock.month], 12 * SEASON[clock.month] + 12)];
  }

  /** P92 ovl_04c7, hourly: every region's hours count down; when the current one's are spent, roll the next weather. */
  hour(clock: Clock) {
    for (const w of this.wthrs) if (w.hours) w.hours--;
    const cur = this.wthrs[this.region];
    if (cur.hours) return;
    const r = rnd(100);
    let i = 0;
    while (i < 3 && r >= this.ssn[3 * i]) i++;
    const dur = this.ssn[3 * i + 2], hi = dur >> 4;
    clock.weather = cur.weather = this.ssn[3 * i + 1];
    cur.hours = hi + rnd((dur & 15) - hi + 2);
  }

  /** Saved state (save.ts). */
  snapshot() {
    return { region: this.region, wthrs: this.wthrs.map(w => ({ ...w })), ssn: [...this.ssn], cleared: [...this.cleared],
      ptrl: this.ptrl.map(p => [...p]), dead: [...this.dead], engaged: [...this.engaged], lastgen: [...this.lastgen], seg: this.seg,
      ships: this.ships.snapshot() };
  }
  async restore(s: ReturnType<World['snapshot']>) {
    this.region = s.region; this.ssn = [...s.ssn];
    s.wthrs.forEach((w, i) => Object.assign(this.wthrs[i], w));
    this.cleared.clear(); for (const b of s.cleared) this.cleared.add(b);
    // saves from before patrols were built start with the new-game patrols
    this.ptrl = (s.ptrl ?? this.p01.patrols).map(p => [...p]); this.lastgen = [...(s.lastgen ?? this.lastgen)]; this.seg = s.seg ?? 0;
    this.dead.clear(); for (const b of s.dead ?? []) this.dead.add(b);
    this.engaged.clear(); for (const b of s.engaged ?? []) this.engaged.add(b);
    if (s.ships) this.ships.restore(s.ships);
    this.rec = await json<Location>(`locations/R${32 + this.region}.json`);
  }

  /** `_grdsta`: guard spots cleared, bit region·8 + n. */
  readonly cleared = new Set<number>();

  /** The region's 8 guard spots (`gwrds` {x, y, group}, x 0 = none) not yet cleared. P01 draws each as E00 icon 0x0F
   *  while it is in view (ovl_0833) and fights it when the party stands on it (ovl_0846, `_ctype` 0). */
  guards(): { x: number; y: number; group: number; bit: number }[] {
    const g = hex(this.rec?.tables.gwrds ?? '');
    return Array.from({ length: 8 }, (_, n) => ({ x: g[3 * n], y: g[3 * n + 1], group: g[3 * n + 2], bit: this.region * 8 + n }))
      .filter(s => s.x && !this.cleared.has(s.bit));
  }

  /** P01 ovl_14d6: the region of a square, the first of the 16 rectangles containing it. */
  regionOf(x: number, y: number): number {
    return this.p01.regions.findIndex(([x0, y0, x1, y1]) => x >= x0 && x <= x1 && y >= y0 && y <= y1);
  }

  /** P01 ovl_169e, after every world-map step (and each `_CalUpd` while time passes there): first each region whose
   *  `_lastgen + interval` (mod 12) is this month respawns - guards and patrols back, none chasing. Then every live
   *  patrol inside the party's map block (ovl_1416: the block's 42×42 square) moves: a chasing one steps toward the
   *  party (ovl_17c0), and if that fails it stops chasing and wanders like the others (ovl_18c1). */
  movePatrols(lv: Level, px: number, py: number, month: number) {
    for (let r = 0; r < 16; r++) {
      const m = (this.lastgen[r] + this.p01.respawn[r]) % 12;
      if (m !== month) continue;
      this.lastgen[r] = m;
      for (let n = 8 * r; n < 8 * r + 8; n++) { this.dead.delete(n); this.engaged.delete(n); this.cleared.delete(n); this.ptrl[n] = [...this.p01.patrols[n]]; }
    }
    const blocks = lv.loc.blocks;
    this.seg = this.block(blocks, px, py, 32, 34);
    for (let n = 0; n < 128; n++) {
      const [x, y] = this.ptrl[n];
      if (!x || this.dead.has(n) || this.block(blocks, x, y, 42, 42) !== this.seg) continue;
      if (!this.engaged.has(n) || !this.chase(lv, n, px, py)) this.wander(lv, n);
    }
  }

  /** P01 ovl_1416 / ovl_141b: the first block, searching from the current one, whose w×h square from its origin holds
   *  (x, y); -1 = none. */
  private block(blocks: Level['loc']['blocks'], x: number, y: number, w: number, h: number): number {
    for (let k = 0; k < blocks.length; k++) {
      const i = (this.seg + k) % blocks.length, b = blocks[i];
      if (x >= b.x && x < b.x + w && y >= b.y && y < b.y + h) return i;
    }
    return -1;
  }

  /** P01 ovl_1910: patrol n may step onto (x, y): inside the party's block and the patrol's own region, walkable, and no
   *  town entrance, feature, live guard spot or other live patrol there (the party's square is allowed). */
  private free(lv: Level, n: number, x: number, y: number): boolean {
    const rec = this.rec!;
    return this.block(lv.loc.blocks, x, y, 42, 42) === this.seg && this.regionOf(x, y) === n >> 3 && lv.walkable(x, y)
      && !rec.exits.some(e => e.x === x && e.y === y) && !rec.doors.some(d => d.x === x && d.y === y)
      && !this.guards().some(g => g.x === x && g.y === y) && this.patrolAt(x, y) < 0;
  }

  /** ovl_17c0: one step straight toward the party; if that square is not free, the direction's two side steps
   *  (P01 tables 0x17A0 / 0x17B0) count only when they end next to the party. False = it gave up (`_ptrleng` cleared). */
  private chase(lv: Level, n: number, px: number, py: number): boolean {
    const [x, y] = this.ptrl[n];
    if (x === px && y === py) return true;
    const dx = Math.sign(px - x), dy = Math.sign(py - y);
    if (this.free(lv, n, x + dx, y + dy)) { this.ptrl[n] = [x + dx, y + dy]; return true; }
    const { dirs, side1, side2 } = this.p01.steps, i = dirs.findIndex(([a, b]) => a === dx && b === dy);
    for (const [sx, sy] of [side1[i], side2[i]]) {
      const tx = x + sx, ty = y + sy;
      if (this.free(lv, n, tx, ty) && Math.abs(tx - px) <= 1 && Math.abs(ty - py) <= 1) { this.ptrl[n] = [tx, ty]; return true; }
    }
    this.engaged.delete(n);
    return false;
  }

  /** ovl_18c1: from a random start in the wander order, the first of three directions that is free. */
  private wander(lv: Level, n: number) {
    const [x, y] = this.ptrl[n], { dirs, order } = this.p01.steps, r = rnd(8);
    for (let k = 0; k < 3; k++) {
      const [dx, dy] = dirs[order[r + k]];
      if (this.free(lv, n, x + dx, y + dy)) { this.ptrl[n] = [x + dx, y + dy]; return; }
    }
  }

  /** P01 ovl_0be8: the live patrol on (x, y), or -1. */
  patrolAt(x: number, y: number): number {
    return this.ptrl.findIndex(([a, b], n) => a === x && b === y && a && !this.dead.has(n));
  }

  /** P01 ovl_0a94: a live patrol on one of the 8 squares around the party is seen and starts chasing it. */
  engage(px: number, py: number) {
    for (let dy = -1; dy <= 1; dy++) for (let dx = -1; dx <= 1; dx++) {
      const n = (dx || dy) ? this.patrolAt(px + dx, py + dy) : -1;
      if (n >= 0) this.engaged.add(n);
    }
  }

  /** The patrols drawn (E00 icon 0x0F, like a guard): those next to the party (ovl_0a94), or every live one while event
   *  105 is set (ovl_076c; also while a Locate spell lasts, not built). */
  patrols(px: number, py: number, all: boolean): { x: number; y: number }[] {
    return this.ptrl.filter(([x, y], n) => x && !this.dead.has(n) && (all || (Math.abs(x - px) <= 1 && Math.abs(y - py) <= 1)))
      .map(([x, y]) => ({ x, y }));
  }

  /** P01 ovl_0846: the group of patrol n, from the region record's `newsr` table. */
  patrolGroup(n: number): number { return hex(this.rec!.tables.newsr)[n & 7]; }

  /** P01 table 0x33A: the difficulty of fights in this region (`_diff`). */
  diff(table: number[]): number { return table[this.region]; }

  /** P01 ovl_09bf: a mushroom patch's tileset by the terrain class under the party. */
  patchTileset(ter: number): number { return this.p01.patchtiles[ter]; }

  /** P01 ovl_10f7: five-minute ticks for one step on terrain class `ter` (+1 at night, +1 if anyone has a condition). */
  stepTicks(ter: number, clock: Clock, party: Party): number {
    let n = (this.p01.terraintime[ter] + 4 + this.p01.weathertime[clock.weather]) & 0xff;
    if (!clock.daylight()) n++;
    if (party.members.some(m => (m.hero.rec.h_cond1 as number) | (m.hero.rec.h_cond2 as number))) n++;
    return n;
  }

  /** Energy per member and step: terrain energy + clothing penalty in this weather (minus `_tailorcharm`, 0 here). The
   *  clothing row is the first worn item in 0x2B-0x30, else "none" (ovl_1a47). */
  fatigue(ter: number, clock: Clock, party: Party) {
    for (const { hero } of party.members) {
      const r = hero.rec, worn = r.h_wears.map(s => s === 0xff ? 0 : r.h_invitem[s]).find(c => c >= 0x2b && c <= 0x30);
      const row = worn ? worn - 0x2b : 6;
      hero.lose('h_energy', Math.max(0, this.p01.clothing[row][clock.weather]) + this.p01.terrainenergy[ter]);
      hero.isHeTr();
    }
  }
}
