// Data pack access (docs/data_schema.md). In development the pack is built by tools/export_json.py and served at
// ./pack/; anywhere else (the public site) it is converted in the browser from the player's own game files, which are
// kept in IndexedDB (decision 1, convert.ts, importer.ts).
import type { Files, Pack } from './convert';

export interface Door { x: number; y: number; pgm: number; id: number; type: number }
export interface Pgm { program: number; tileset: number; datafile: number; disk: number }
export interface Exit { x: number; y: number; pgm: number; tx: number; ty: number; datafile?: number }
export interface Townsfolk { x: number; y: number; type: number; tile: number; num: number }
export interface Npc extends Townsfolk { name: number; appear: number; disappear: number; ifevent: number; ifnevent: number }
/** A dungeon room (`HROOM`, rules/locations.md): guards, chest/fountain reward, map chunk, the four doors' windows. */
export interface HRoom { id: number; group: number; reward: number; amount: number; map: number; xy: number[] }
export interface Block { block: number; tileset: number; x: number; y: number }

export interface Location {
  locnum: number;      // the location number, used as `_locspec` (assumption: equal for towns)
  tables: Record<string, string>;   // each LOCTYPE sub-table's raw bytes as hex (data_schema.md)
  kind: 'level' | 'room' | 'region' | 'world';
  name: string;
  mapsize: [number, number];
  doorstn: number;
  blocks: Block[];
  words: string[];
  texts: string[];
  doors: Door[];
  pgms: Pgm[];
  exits: Exit[];
  townsfolk: Townsfolk[];
  npcs: Npc[];
  script: { word: number; resp: number; cmds: { op: 'E' | 'C' | 'S'; arg?: number; alt?: number; song?: number }[] }[];
  news: { npctype: number; event: number; text: number }[];
  look?: { x: number; y: number; text: number }[];
  residents: { name: number; num: number; appear: number; disappear: number; ifevent: number; ifnevent: number }[];
  roommap?: { g: number; chunks: number[] } | null;
  hrooms?: HRoom[];
  keydoor?: { x: number; y: number; newtile: number; text: number }[];
  spots?: { x: number; y: number; type: number; d1: number; d2: number; d3: number }[];
  locdiff: number;
  lcharm: number;                       // charm a generic townsperson asks for (FFFAR 0x3245)
}

/** A room record as exported: exits, townsfolk and NPCs are one list per room index (formats.md, Room maps). */
export interface RoomRecord extends Omit<Location, 'exits' | 'townsfolk' | 'npcs'> {
  exits: Exit[][];
  townsfolk: Townsfolk[][];
  npcs: Npc[][];
}

export interface TileData { names: string[]; nameindex: number[]; walkable: number[]; walkable_los: number[]; anim: string; doors: string }
export interface Sprites { columns: number; npc: { start: number; frames: number }[] }

const BASE = './pack/';
const cache = new Map<string, Promise<unknown>>();
let local: Pack | null = null;           // converted in this browser
const urls = new Map<string, string>();

/** Opens the pack: the server's ./pack/ when it has one, else the game files kept in this browser, converted now.
 *  False when there are neither (the import screen asks for the files). */
export async function openPack(): Promise<boolean> {
  try {
    const r = await fetch(BASE + 'comtxt.json');
    if (r.ok && r.headers.get('content-type')?.includes('json')) return true;
  } catch { /* no server pack */ }
  const files = await stored();
  if (!files) return false;
  local = await (await import('./convert')).convert(files);
  return true;
}

/** A pack file as a fetch response (404 when it is missing). */
export function packFetch(path: string): Promise<Response> {
  if (!local) return fetch(BASE + path);
  const d = local.get(path);
  return Promise.resolve(d ? new Response(d as BodyInit) : new Response(null, { status: 404 }));
}

/** A URL for a pack file (images): the server's, or an object URL for a converted one. */
export function packUrl(path: string): string {
  if (!local) return BASE + path;
  if (!urls.has(path)) urls.set(path, URL.createObjectURL(new Blob([local.get(path) as BlobPart], { type: 'image/png' })));
  return urls.get(path)!;
}

// The player's game files in IndexedDB (database mc2, store `files`, one record per file name).
function db(): Promise<IDBDatabase> {
  return new Promise((ok, fail) => {
    const r = indexedDB.open('mc2', 1);
    r.onupgradeneeded = () => r.result.createObjectStore('files');
    r.onsuccess = () => ok(r.result);
    r.onerror = () => fail(r.error);
  });
}
const done = (t: IDBTransaction) => new Promise<void>((ok, fail) => { t.oncomplete = () => ok(); t.onerror = () => fail(t.error); });

async function stored(): Promise<Files | null> {
  try {
    const t = (await db()).transaction('files'), s = t.objectStore('files'), files: Files = new Map();
    const [keys, vals] = await Promise.all([s.getAllKeys(), s.getAll()].map(q => new Promise<unknown[]>(ok => { q.onsuccess = () => ok(q.result); })));
    keys.forEach((k, i) => files.set(k as string, vals[i] as Uint8Array));
    return files.size ? files : null;
  } catch { return null; }
}

/** Keeps the game files in this browser (replacing any kept before). */
export async function keepFiles(files: Files) {
  const t = (await db()).transaction('files', 'readwrite'), s = t.objectStore('files');
  s.clear();
  for (const [k, v] of files) s.put(v, k);
  await done(t);
}

/** Forgets the kept game files. */
export async function forgetFiles() {
  const t = (await db()).transaction('files', 'readwrite');
  t.objectStore('files').clear();
  await done(t);
}

/** True when the pack was converted in this browser (the Game panel can then forget the files). */
export const isLocal = () => !!local;

function once<T>(key: string, load: () => Promise<T>): Promise<T> {
  if (!cache.has(key)) cache.set(key, load());
  return cache.get(key) as Promise<T>;
}

export function json<T>(path: string): Promise<T> {
  return once(path, async () => {
    const r = await packFetch(path);
    if (!r.ok) throw new Error(`data pack: ${path} (${r.status})`);
    return r.json() as Promise<T>;
  });
}

export function image(path: string): Promise<HTMLImageElement> {
  return once(path, () => new Promise((ok, fail) => {
    const im = new Image();
    im.onload = () => ok(im);
    im.onerror = () => fail(new Error(`data pack: ${path}`));
    im.src = packUrl(path);
  }));
}

export function hex(s: string): Uint8Array {
  const out = new Uint8Array(s.length / 2);
  for (let i = 0; i < out.length; i++) out[i] = parseInt(s.substr(i * 2, 2), 16);
  return out;
}

export const two = (n: number) => String(n).padStart(2, '0');
