// A program-2 location (town or dungeon level): its composed map and who is on it (docs/rules/locations.md, npcs.md).
import { hex, json, image, two, type Location, type RoomRecord, type TileData } from './pack';
import type { Clock } from './clock';
import type { RoomRef } from './room';

export interface Figure { x: number; y: number; type: number; tile: number; num: number; name?: string }

export class Level {
  readonly w: number;
  readonly h: number;
  readonly cells: Uint8Array;
  private readonly walk: Set<number>;
  /** Tileset `aniptr` records {tile, barrier class, kind, cycle…, FF}, list ends FF FF: tile → its animation cycle. */
  readonly anim = new Map<number, number[]>();

  private constructor(readonly id: string, readonly loc: Location, readonly tileset: number,
                      readonly tiles: HTMLImageElement, readonly data: TileData) {
    // The world map (D01) is larger than its header's mapsize: size by the block extent when that is bigger.
    const ext = (k: 'x' | 'y') => Math.max(0, ...loc.blocks.map(b => b[k] + 42));
    [this.w, this.h] = loc.kind === 'room' ? loc.mapsize : [Math.max(loc.mapsize[0], ext('x')), Math.max(loc.mapsize[1], ext('y'))];
    this.cells = new Uint8Array(this.w * this.h).fill(0xff);
    this.walk = new Set(data.walkable);
    const a = hex(data.anim);
    for (let i = 0; i + 3 < a.length && a[i] !== 0xff;) {
      let j = i + 3;
      while (j < a.length && a[j] !== 0xff) j++;
      this.anim.set(a[i], [...a.slice(i + 3, j)]);
      i = j + 2;                                     // FF ends the cycle, a second FF separates records
    }
  }

  private static async make(id: string, loc: Location, ts: number): Promise<Level> {
    return new Level(id, loc, ts, await image(`tilesets/V${two(ts)}.png`), await json<TileData>(`tiledata/B${two(ts)}.json`));
  }

  /** A town or dungeon level composed from its map blocks, drawn with tileset `ts` (the PGM record's), else the one its
   *  blocks share (formats.md, Locations are mosaics; the most common one). */
  static async load(id: string, ts?: number): Promise<Level> {
    const loc = await json<Location>(`locations/${id}.json`);
    const blocks = await json<Record<string, string>>('blocks.json');
    const counts = new Map<number, number>();
    for (const b of loc.blocks) counts.set(b.tileset, (counts.get(b.tileset) ?? 0) + 1);
    ts ??= [...counts].sort((a, b) => b[1] - a[1])[0][0];
    const lv = await Level.make(id, loc, ts);
    for (const b of loc.blocks) {
      if (b.block === 0) continue;
      const m = hex(blocks[`M${two(b.block)}E${two(b.tileset)}`]);   // later blocks win on overlap
      for (let y = 0; y < 42; y++)
        for (let x = 0; x < 42; x++) lv.cells[(b.y + y) * lv.w + b.x + x] = m[y * 42 + x];
    }
    return lv;
  }

  /** An 11×9 room: one G-file chunk drawn with the tileset of the door's PGM record (formats.md, Room maps). */
  static async loadRoom(ref: RoomRef): Promise<Level> {
    const rec = await json<RoomRecord>(`locations/${ref.id}.json`);
    const rooms = await json<Record<string, string[]>>('rooms.json');
    const i = ref.index;   // P05 ovl_16fa: this room's own exit / townsfolk / NPC lists
    const loc: Location = { ...rec, mapsize: [11, 9], exits: rec.exits[i] ?? [], townsfolk: rec.townsfolk[i] ?? [], npcs: rec.npcs[i] ?? [] };
    const lv = await Level.make(ref.id, loc, ref.pgm.tileset);
    lv.cells.set(hex(rooms[`G${two(ref.map.g)}`][ref.map.chunk]));
    return lv;
  }

  /** A mushroom patch (P04) or wilderness arena (P96 `_cmbtyp` 1): G00 chunk `chunk` drawn with tileset `ts`
   *  (formats.md, Room maps). */
  static async wild(ts: number, chunk: number): Promise<Level> { return Level.chunk(0, ts, chunk); }

  /** Chunk `chunk` of G-file `g` as an 11×9 map with tileset `ts` (G05: dungeon rooms and their arenas, P07/P96). */
  static async chunk(g: number, ts: number, chunk: number): Promise<Level> {
    const rec = await json<Location>('locations/D04.json');
    const rooms = await json<Record<string, string[]>>('rooms.json');
    const lv = await Level.make(`G${two(g)}`, { ...rec, name: '', exits: [], townsfolk: [], npcs: [] }, ts);
    lv.cells.set(hex(rooms[`G${two(g)}`][chunk]));
    return lv;
  }

  /** Overwrite one map square (room features: chest, fountain, doors). */
  set(x: number, y: number, tile: number) { this.cells[y * this.w + x] = tile; }

  /** _PlacePerson: (x, y) if free (walkable, on the map, not `taken`), else the first free square on diamonds of
   *  growing radius, each walked clockwise from its west corner (direction tables DS:0995/0999). */
  place(x: number, y: number, taken: (x: number, y: number) => boolean): { x: number; y: number } {
    const free = (a: number, b: number) => a >= 0 && b >= 0 && a < this.w && b < this.h && this.walkable(a, b) && !taken(a, b);
    if (free(x, y)) return { x, y };
    for (let r = 1; r < this.w + this.h; r++) {
      let a = x - r, b = y;
      for (const [dx, dy] of [[1, -1], [1, 1], [-1, 1], [-1, -1]])
        for (let s = 0; s < r; s++, a += dx, b += dy) if (free(a, b)) return { x: a, y: b };
    }
    return { x, y };   // the original searches forever
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
  figures(clock: Clock, events: Set<number>, away: Set<number> = new Set()): Figure[] {
    const out: Figure[] = [];
    if (!this.loc.townsfolk) return out;                 // world map and regions: nobody standing about
    const light = clock.daylight();
    for (const g of this.loc.townsfolk)
      if (g.num >= 0xfc || (g.num === 0xfa && light) || (g.num === 0xfb && !light)) out.push(g);
    for (const n of this.loc.npcs) {
      if (away.has(n.num) || !clock.within(n.appear, n.disappear)) continue;   // _npcsta: in the party
      if (n.ifevent && !events.has(n.ifevent)) continue;
      if (n.ifnevent && events.has(n.ifnevent)) continue;
      out.push({ ...n, name: this.loc.words[n.name] });
    }
    return out;
  }
}
