// Data pack access (docs/data_schema.md). The pack is built by tools/export_json.py and served at ./pack/.

export interface Door { x: number; y: number; pgm: number; id: number; type: number }
export interface Pgm { program: number; tileset: number; datafile: number; disk: number }
export interface Exit { x: number; y: number; pgm: number; tx: number; ty: number }
export interface Townsfolk { x: number; y: number; type: number; tile: number; num: number }
export interface Npc extends Townsfolk { name: number; appear: number; disappear: number; ifevent: number; ifnevent: number }
export interface Block { block: number; tileset: number; x: number; y: number }

export interface Location {
  kind: 'level' | 'room' | 'region' | 'world';
  name: string;
  mapsize: [number, number];
  blocks: Block[];
  words: string[];
  texts: string[];
  doors: Door[];
  pgms: Pgm[];
  exits: Exit[];
  townsfolk: Townsfolk[];
  npcs: Npc[];
  roommap?: { g: number; chunks: number[] } | null;
}

export interface TileData { names: string[]; nameindex: number[]; walkable: number[]; walkable_los: number[] }
export interface Sprites { columns: number; npc: { start: number; frames: number }[] }

const BASE = './pack/';
const cache = new Map<string, Promise<unknown>>();

function once<T>(key: string, load: () => Promise<T>): Promise<T> {
  if (!cache.has(key)) cache.set(key, load());
  return cache.get(key) as Promise<T>;
}

export function json<T>(path: string): Promise<T> {
  return once(path, async () => {
    const r = await fetch(BASE + path);
    if (!r.ok) throw new Error(`data pack: ${path} (${r.status}) — build it with tools/export_json.py`);
    return r.json() as Promise<T>;
  });
}

export function image(path: string): Promise<HTMLImageElement> {
  return once(path, () => new Promise((ok, fail) => {
    const im = new Image();
    im.onload = () => ok(im);
    im.onerror = () => fail(new Error(`data pack: ${path}`));
    im.src = BASE + path;
  }));
}

export function hex(s: string): Uint8Array {
  const out = new Uint8Array(s.length / 2);
  for (let i = 0; i < out.length; i++) out[i] = parseInt(s.substr(i * 2, 2), 16);
  return out;
}

export const two = (n: number) => String(n).padStart(2, '0');
