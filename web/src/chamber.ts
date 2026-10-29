// A dungeon room (P07, rules/locations.md Dungeon rooms): G05 chunk `hrmmap & 0xF` with the door PGM's tileset, a chest
// (tile 0x1F at (1,1)) or a fountain (0x1C at (9,0) over 0x0E at (9,1)) when `hrmreward` is set, and a door on each side
// n (W, N, E, S) whose `hrmxy[n]` is non-zero: P07 file 0x03/0x0B give its two squares, the tileset's `doorptr` its two
// tiles (ovl_049a). Leaving by door n puts the dungeon window at `hrmxy[n]` (low byte x, high byte y).
import { hex, json, type HRoom, type Location } from './pack';
import { Level, type Figure } from './level';

export interface P07 { texts: string[]; trap: number[]; doorx: number[]; doory: number[] }
/** A Dark Candle room's own data (D98): texts, the elden's names (`gwrds`), KNPC records of 11 bytes. */
interface Candle { texts: string[]; words: string[]; knpc: Uint8Array }

export class Chamber {
  opened = false;   // OV_0x8FC: the chest was opened this visit
  /** `_hroomtype` (V02 INT60_12, by room id): 1 prison cell, 2-5 Dark Candle rooms, 6 Vankruh's chamber, else 0. */
  type = 0;
  /** D98 for the candle rooms. */
  candle: Candle | null = null;
  /** The elden freed this visit (the KNPC pointer advanced by `(type − 1)·11`). */
  freed: Figure | null = null;

  private constructor(readonly hr: HRoom, readonly level: Level, readonly key: string, private p07: P07) {}

  static async build(hr: HRoom, ts: number, key: string, events: Set<number>): Promise<Chamber> {
    const p07 = await json<P07>('p07.json'), types = (await json<{ hroomtype: { ids: number[]; types: number[] } }>('v02.json')).hroomtype;
    const lv = await Level.chunk(5, ts, hr.map & 15);
    if (hr.reward && !(hr.reward & 0x80)) lv.set(1, 1, 0x1f);
    else if (hr.reward & 0x80) { lv.set(9, 0, 0x1c); lv.set(9, 1, 0x0e); }
    const tiles = hex(lv.data.doors);
    const c = new Chamber(hr, lv, key, p07);
    for (const d of c.doors()) lv.set(d.x, d.y, tiles[d.k]);
    c.type = types.types[types.ids.indexOf(hr.id)] ?? 0;
    if (c.type >= 2 && c.type <= 5) {                        // P07 ovl_069e: lkdata row type − 1 = the inscription at (4,1)
      const d98 = await json<Location>('locations/D98.json');
      c.candle = { texts: d98.texts, words: d98.words, knpc: hex(d98.tables.knpcptr) };
      lv.loc.texts = d98.texts;
      lv.loc.look = [{ x: 4, y: 1, text: c.type - 2 }];
      if (events.has(0x3c + c.type)) c.snuff();              // freed before: the flame is out
    }
    if (c.type === 6) {                                      // Vankruh's chamber: its record is D98's KNPC 5 (meet)
      const d98 = await json<Location>('locations/D98.json');
      c.candle = { texts: d98.texts, words: d98.words, knpc: hex(d98.tables.knpcptr) };
    }
    return c;
  }

  /** P07 ovl_069e on entry: once Vankruh has been greeted (event 66) it stands where it was (`_VANKRUHXY`, the KNPC
   *  pointer advanced 0x37 to record 5) and speaks like a freed elden (`_swgreet` 2). */
  meet(events: Set<number>, at: [number, number]) {
    if (this.type === 6 && events.has(66)) this.freed = { ...this.elden(), x: at[0], y: at[1] };
  }

  /** ovl_07c1: the candle square (`_mapyl+6`, cell 5) becomes 0x5D. */
  snuff() { this.level.set(5, 0, 0x5d); }

  /** The elden of this room, from KNPC record `type − 1` {x, y, tile, type, num, text, …}. */
  elden(): Figure {
    const k = this.candle!.knpc, o = 11 * (this.type - 1);
    return { x: k[o], y: k[o + 1], tile: k[o + 2], type: k[o + 3], num: k[o + 4], name: this.candle!.words[this.type - 2] };
  }
  /** What a freed elden, or a greeted Vankruh, says (`_swgreet` 2 → P07 ovl_04ef): D98 text 9 + the record's text byte. */
  says(f: Figure): string | null {
    if (!this.freed || f.num !== this.freed.num) return null;
    return this.candle!.texts[9 + this.candle!.knpc[11 * (this.type - 1) + 5]];
  }

  get texts(): string[] { return this.p07.texts; }
  get trap(): number[] { return this.p07.trap; }

  /** The door squares: side n, part k = 2n + (0|1). */
  doors(): { x: number; y: number; n: number; k: number }[] {
    const out: { x: number; y: number; n: number; k: number }[] = [];
    for (let n = 0; n < 4; n++) if (this.hr.xy[n])
      for (const k of [2 * n, 2 * n + 1]) out.push({ x: this.p07.doorx[k], y: this.p07.doory[k], n, k });
    return out;
  }

  /** The door side a step to (x, y) leaves by: a door square (`_ChkDoor`), or off the map on a side that has a door
   *  (assumed: `_RMove` returns 2 there and P07 uses the member's `_exitdir`). −1 = neither. */
  exitAt(x: number, y: number): number {
    const d = this.doors().find(o => o.x === x && o.y === y);
    if (d) return d.n;
    const n = x < 0 ? 0 : y < 0 ? 1 : x > 10 ? 2 : y > 8 ? 3 : -1;
    return n >= 0 && this.hr.xy[n] ? n : -1;
  }

  /** Where door n leads: the dungeon window. */
  window(n: number): { x: number; y: number } { return { x: this.hr.xy[n] & 0xff, y: this.hr.xy[n] >> 8 }; }
}
