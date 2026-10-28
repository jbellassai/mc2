// The world map (P01, rules/locations.md World map, rules/time_weather.md): the leader alone stands at window + (5,4);
// the region (`_curreg`) is the first of 16 rectangles containing the party and selects the region record R(32+n),
// whose town entrances, features and spots live on its own tables. Weather is regional and hourly (P92 ovl_04c7).
import { json, hex, type Location } from './pack';
import type { Party } from './party';
import type { Clock } from './clock';

interface P01 { terraintime: number[]; weathertime: number[]; terrainenergy: number[]; clothing: number[][]; regions: number[][] }
const SEASON = [0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 0];   // P92 file 0x24D, by month
const rnd = (n: number) => Math.floor(Math.random() * n);

export class World {
  region = 0;                                          // new game `_curreg` 0 (Oshcrun Isle, Telermain's region)
  rec: Location | null = null;
  /** `_curwthrs`: {weather, hours left} per region; all {Clear, 0} in a new game (FFSAVA). */
  private readonly wthrs = Array.from({ length: 16 }, () => ({ weather: 0, hours: 0 }));
  /** `_ssnwthrs`: the current region's 4 {threshold, weather, duration} triples; new game [100, Clear, 0x8F]. */
  private ssn = [100, 0, 0x8f, 0, 0, 0, 0, 0, 0, 0, 0, 0];

  private constructor(private p01: P01) {}
  static async create(): Promise<World> { return new World(await json<P01>('p01.json')); }

  /** P01 ovl_14d6 / ovl_14fd: entering another region loads its record and its season's weather table. */
  async at(x: number, y: number, clock: Clock) {
    const r = this.p01.regions.findIndex(([x0, y0, x1, y1]) => x >= x0 && x <= x1 && y >= y0 && y <= y1);
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
