// Mushroom patches (P04, rules/locations.md Mushroom patches): world features with program 4, ids 0–29. `_mushsta`
// keeps the mushrooms still growing at each patch (15 in a new game, +1 every 8th day up to 15). Inside, the map is
// G00 chunk `_curter` (terrain class under the party) drawn with the tileset P01 picks for that class (ovl_09bf).
import { json, hex, type Location } from './pack';
import type { Level } from './level';

interface P04 { amount: number[]; icon: number[]; x: number[]; y: number[] }

export class Patches {
  /** `_mushsta`: one count per patch (the original packs two per byte, the even id in the high nibble). */
  readonly left: number[] = new Array(30).fill(15);
  private constructor(private p04: P04, private kinds: number[], readonly texts: string[]) {}

  static async create(): Promise<Patches> {
    const d04 = await json<Location>('locations/D04.json');
    return new Patches(await json<P04>('p04.json'), [...hex(d04.tables.gwrds)], d04.texts);
  }

  /** P92 ovl_02cb, on a new day with `_juldate & 7 == 0`. */
  regrow() { this.left.forEach((n, i) => { if (n < 15) this.left[i]++; }); }

  /** P04 ovl_0441: on the patch map (Level.wild), `count` mushrooms placed from the last growing place to the first,
   *  each by _PlacePerson around the party (mushrooms do not block each other). */
  open(id: number, lv: Level, party: { x: number; y: number }[]): Patch {
    const item = this.kinds[id], k = item - 0x33;
    const at: ({ x: number; y: number } | null)[] = new Array(15).fill(null);
    for (let i = this.left[id]; i > 0; i--)
      at[i - 1] = lv.place(this.p04.x[i - 1], this.p04.y[i - 1], (x, y) => party.some(p => p.x === x && p.y === y));
    return new Patch(this, id, lv, item, this.p04.amount[k], this.p04.icon[k], at);
  }
}

export class Patch {
  constructor(private all: Patches, readonly id: number, readonly level: Level, readonly item: number,
              readonly amount: number, private frame: number, private at: ({ x: number; y: number } | null)[]) {}

  get count(): number { return this.all.left[this.id]; }

  /** The mushroom on (x, y), or −1. */
  find(x: number, y: number): number { return this.at.findIndex(p => p?.x === x && p?.y === y); }

  /** Picked: the last placed mushroom takes the picked one's place (P04 ovl_0146 after _IncObj), the count is saved. */
  pick(i: number) {
    const n = --this.all.left[this.id];
    this.at[i] = this.at[n];
    this.at[n] = null;
  }

  /** E00 icons to draw (ovl_055a). */
  icons(): { x: number; y: number; frame: number }[] {
    return this.at.flatMap(p => p ? [{ ...p, frame: this.frame }] : []);
  }
}
