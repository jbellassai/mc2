// A program-2 location (town or dungeon level): its composed map and who is on it (docs/rules/locations.md, npcs.md).
import { hex, json, image, two, type Location, type TileData } from './pack';
import type { Clock } from './clock';

export interface Figure { x: number; y: number; tile: number; num: number; name?: string }

export class Level {
  readonly w: number;
  readonly h: number;
  readonly cells: Uint8Array;
  private readonly walk: Set<number>;

  private constructor(readonly id: string, readonly loc: Location, readonly tileset: number,
                      readonly tiles: HTMLImageElement, readonly data: TileData) {
    [this.w, this.h] = loc.mapsize;
    this.cells = new Uint8Array(this.w * this.h).fill(0xff);
    this.walk = new Set(data.walkable);
  }

  static async load(id: string): Promise<Level> {
    const loc = await json<Location>(`locations/${id}.json`);
    const blocks = await json<Record<string, string>>('blocks.json');
    // Blocks of one location share a tileset (formats.md, Locations are mosaics); use the most common one.
    const counts = new Map<number, number>();
    for (const b of loc.blocks) counts.set(b.tileset, (counts.get(b.tileset) ?? 0) + 1);
    const ts = [...counts].sort((a, b) => b[1] - a[1])[0][0];
    const lv = new Level(id, loc, ts, await image(`tilesets/V${two(ts)}.png`), await json<TileData>(`tiledata/B${two(ts)}.json`));
    for (const b of loc.blocks) {
      if (b.block === 0) continue;
      const m = hex(blocks[`M${two(b.block)}E${two(b.tileset)}`]);   // later blocks win on overlap
      for (let y = 0; y < 42; y++)
        for (let x = 0; x < 42; x++) lv.cells[(b.y + y) * lv.w + b.x + x] = m[y * 42 + x];
    }
    return lv;
  }

  tile(x: number, y: number): number {
    return x < 0 || y < 0 || x >= this.w || y >= this.h ? 0xff : this.cells[y * this.w + x];
  }

  /** _ChkWlk: the tile is in the tileset's walkable list (list 2 only applies during P02's flood-fill). */
  walkable(x: number, y: number): boolean {
    return this.walk.has(this.tile(x, y));
  }

  tileName(x: number, y: number): string {
    return this.data.names[this.data.nameindex[this.tile(x, y)]] ?? '?';
  }

  /** _SetNPCs: townsfolk by day/night, named NPCs by hours and event conditions (npcs.md). */
  figures(clock: Clock, events: Set<number>): Figure[] {
    const out: Figure[] = [];
    const light = clock.daylight();
    for (const g of this.loc.townsfolk)
      if (g.num >= 0xfc || (g.num === 0xfa && light) || (g.num === 0xfb && !light)) out.push(g);
    for (const n of this.loc.npcs) {
      if (!clock.within(n.appear, n.disappear)) continue;
      if (n.ifevent && !events.has(n.ifevent)) continue;
      if (n.ifnevent && events.has(n.ifnevent)) continue;
      out.push({ ...n, name: this.loc.words[n.name] });
    }
    return out;
  }
}
