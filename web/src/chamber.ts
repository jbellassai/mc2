// A dungeon room (P07, rules/locations.md Dungeon rooms): G05 chunk `hrmmap & 0xF` with the door PGM's tileset, a chest
// (tile 0x1F at (1,1)) or a fountain (0x1C at (9,0) over 0x0E at (9,1)) when `hrmreward` is set, and a door on each side
// n (W, N, E, S) whose `hrmxy[n]` is non-zero: P07 file 0x03/0x0B give its two squares, the tileset's `doorptr` its two
// tiles (ovl_049a). Leaving by door n puts the dungeon window at `hrmxy[n]` (low byte x, high byte y).
import { hex, json, type HRoom } from './pack';
import { Level } from './level';

export interface P07 { texts: string[]; trap: number[]; doorx: number[]; doory: number[] }

export class Chamber {
  opened = false;   // OV_0x8FC: the chest was opened this visit

  private constructor(readonly hr: HRoom, readonly level: Level, readonly key: string, private p07: P07) {}

  static async build(hr: HRoom, ts: number, key: string): Promise<Chamber> {
    const p07 = await json<P07>('p07.json');
    const lv = await Level.chunk(5, ts, hr.map & 15);
    if (hr.reward && !(hr.reward & 0x80)) lv.set(1, 1, 0x1f);
    else if (hr.reward & 0x80) { lv.set(9, 0, 0x1c); lv.set(9, 1, 0x0e); }
    const tiles = hex(lv.data.doors);
    const c = new Chamber(hr, lv, key, p07);
    for (const d of c.doors()) lv.set(d.x, d.y, tiles[d.k]);
    return c;
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
