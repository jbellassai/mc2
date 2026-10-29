// The in-browser data converter (decision 1): the player's own game files → the data pack, exactly as
// tools/export_json.py builds it. That exporter is the reference: `node web/scripts/convert.mjs original out/pack-ts`
// then `tools/packdiff.py out/pack out/pack-ts` must report no difference. The pack's JSON is compact here and every
// image is an RGBA PNG; the engine reads only the values and pixels. No imports, so Node runs this file as it is.

/** Game files by upper-case name. */
export type Files = Map<string, Uint8Array>;
/** Pack files by path (`locations/D02.json`, `tilesets/V01.png` …). */
export type Pack = Map<string, Uint8Array>;

type Bytes = Uint8Array;
type Obj = Record<string, unknown>;

const PTRS = ['roomptr', 'genptr', 'knpcptr', 'resids', 'maps', 'loctext', 'lkdata', 'pgmptr', 'exitptr', 'gwrds', 'newsr',
  'weathr', 'peopr', 'hroomptr', 'spetbl', 'treasptr', 'spdoors', 'locptr', 'locevptr', 'notyet0'];
const DS = 0x1800 + 0x15B50;   // MC2.EXE's data segment in the file

// ---- Python's bytes operations ----
const latin1 = (b: Bytes) => { let s = ''; for (const c of b) s += String.fromCharCode(c); return s; };
const list = (b: Bytes) => Array.from(b);
const hexs = (b: Bytes) => Array.from(b, c => c.toString(16).padStart(2, '0')).join('');
const u16 = (d: Bytes, o: number) => d[o] | d[o + 1] << 8;
const u16s = (d: Bytes, o: number, n: number) => Array.from({ length: n }, (_, i) => u16(d, o + 2 * i));
const sb = (b: number) => b > 127 ? b - 256 : b;
/** bytes.split(bytes([sep])): every part, the last one too. */
function split(b: Bytes, sep: number): Bytes[] {
  const out: Bytes[] = [];
  let s = 0;
  for (let i = 0; i < b.length; i++) if (b[i] === sep) { out.push(b.subarray(s, i)); s = i + 1; }
  out.push(b.subarray(s));
  return out;
}
/** bytes.index(sub, start) for one or two bytes. */
function index(d: Bytes, sub: number[], start: number): number {
  for (let i = start; i + sub.length <= d.length; i++) if (sub.every((c, k) => d[i + k] === c)) return i;
  throw new Error(`converter: ${sub} not found from ${start}`);
}
/** [x.decode('latin1') for x in b.split(b'\0')[:n]] */
const texts = (b: Bytes, n?: number) => split(b, 0).slice(0, n).map(latin1);
/** dict(zip(keys, r)) */
const zip = (keys: string[], r: number[]) => Object.fromEntries(r.slice(0, keys.length).map((v, i) => [keys[i], v]));
const strings = (b: Bytes) => b.length ? split(b, 0).slice(0, -1).map(latin1) : [];
/** Python's round(): halves to even. */
const round = (x: number) => { const f = Math.floor(x); return x - f === 0.5 ? f + (f & 1) : Math.round(x); };
/** str.rstrip() / str.strip() of a latin1 string. */
const rstrip = (s: string) => s.replace(/[\s\x1c-\x1f\x85]+$/, '');
const strip = (s: string) => rstrip(s).replace(/^[\s\x1c-\x1f\x85]+/, '');

/** Fixed-size records; `stop` ends the list (the terminator is not included). */
function recs(b: Bytes, size: number, stop?: (r: Bytes) => boolean): number[][] {
  const out: number[][] = [];
  for (let i = 0; i + size <= b.length; i += size) {
    const r = b.subarray(i, i + size);
    if (stop?.(r)) break;
    out.push(list(r));
  }
  return out;
}
/** Per-room-index lists (P05 ovl_16fa): records of `size` bytes, each list ended by 0xFF. */
function lists(b: Bytes, size: number): number[][][] {
  const out: number[][][] = [];
  let cur: number[][] = [], i = 0;
  while (i < b.length) {
    if (b[i] === 0xff) { out.push(cur); cur = []; i++; }
    else { cur.push(list(b.subarray(i, i + size))); i += size; }
  }
  return out;
}

/** Conversation script (P91 ovl_05e2): entries `word resp cmd* 0`, 0xFF ends; cmd = 'E' ev alt | 'C' need alt | 'S' song. */
function script(b: Bytes): Obj[] {
  const out: Obj[] = [];
  let i = 0;
  while (i + 1 < b.length && b[i] !== 0xff) {
    const cmds: Obj[] = [], e = { word: b[i], resp: b[i + 1], cmds };
    i += 2;
    if (e.resp !== 0xff) {
      while (i < b.length && b[i] !== 0 && b[i] !== 0xff) {
        const c = String.fromCharCode(b[i]);
        if (c === 'S') { cmds.push({ op: 'S', song: b[i + 1] }); i += 2; }
        else if ((c === 'E' || c === 'C') && i + 2 < b.length) { cmds.push({ op: c, arg: b[i + 1], alt: b[i + 2] }); i += 3; }
        else throw new Error(`script byte ${b[i]} at ${i}`);
      }
      i++;
    }
    out.push(e);
  }
  return out;
}

/** Cnn.MCV: text block, word list, and per-slot script, gifts, shop, greet/bye, trade skill, no-buy, unknown-word reply. */
function conversation(d: Bytes): Obj {
  const p = u16s(d, 0, 42), seg = (i: number) => d.subarray(p[i], p[i + 1]);
  const slots = Array.from({ length: 8 }, (_, k) => {
    const gb = [...split(d.subarray(p[34 + k]), 0xff)[0], 0xff, 0xff];
    return {
      script: script(d.subarray(p[2 + k], k < 7 ? p[3 + k] : p[10])),
      gifts: recs(seg(18 + k), 5, r => r[0] === 0xff).map(r => zip(['item', 'min', 'fewer', 'enough', 'event'], r)),
      shop: recs(seg(26 + k), 5, r => r[0] === 0xff).map(r => ({ item: r[0], pays: r[1] * 100 + r[2], charges: r[3] * 100 + r[4] })),
      greet: gb[0], bye: gb[1], skill: d[0x54 + k], nobuy: d[0x5c + k], unknown: d[0x64 + k],
    };
  });
  const words = latin1(split(d.subarray(p[1], p[2]), 0xff)[0]).split('\0').slice(0, -1);
  return { texts: strings(seg(0)), words, slots };
}

// HERO and ASSIGNMENT as tools/export_json.py struct_fields reads them from docs/structs.h: [field, offset, kind, dims].
type Field = [string, number, 'str' | 'u8' | 'u16', number[]];
const HERO: Field[] = [['h_name', 0, 'str', [6]], ['h_race', 6, 'u8', []], ['h_sex', 7, 'u8', []], ['h_orinum', 8, 'u8', []],
  ['h_songs', 9, 'u8', [4]], ['h_bravery', 13, 'u8', []], ['h_strngth', 14, 'u8', []], ['h_dextrty', 15, 'u8', []],
  ['h_endur', 16, 'u8', []], ['h_agility', 17, 'u8', []], ['h_loyalty', 18, 'u8', []], ['h_charm', 19, 'u8', []],
  ['h_intellg', 20, 'u8', []], ['h_resist', 21, 'u8', []], ['h_helped', 22, 'u8', []], ['h_sword', 23, 'u8', []],
  ['h_axe', 24, 'u8', []], ['h_archry', 25, 'u8', []], ['h_magic', 26, 'u8', []], ['h_fist', 27, 'u8', []],
  ['h_swim', 28, 'u8', []], ['h_trade', 29, 'u8', []], ['h_stealth', 30, 'u8', []], ['h_research', 31, 'u8', []],
  ['h_soulrd', 32, 'u8', []], ['h_lockpck', 33, 'u8', []], ['h_track', 34, 'u8', []], ['h_music', 35, 'u8', []],
  ['h_carpent', 36, 'u8', []], ['h_smith', 37, 'u8', []], ['h_gemcut', 38, 'u8', []], ['h_tailor', 39, 'u8', []],
  ['h_hunt', 40, 'u8', []], ['h_ldrshp', 41, 'u8', []], ['h_glamcnt', 42, 'u8', []], ['h_invitem', 43, 'u8', [40]],
  ['h_invamt', 83, 'u8', [40]], ['h_spells', 123, 'u8', [6, 7]], ['h_inuse', 165, 'u8', []], ['h_hpmax', 166, 'u8', []],
  ['h_lrncnt', 167, 'u8', []], ['h_inevent', 168, 'u8', []], ['h_noinmsg', 169, 'u8', []], ['h_godseen', 170, 'u8', []],
  ['h_fullnm', 171, 'str', [13]], ['h_relatn', 184, 'u8', []], ['h_actvty', 185, 'u8', []], ['h_energy', 186, 'u8', []],
  ['h_shield', 187, 'u8', []], ['h_lastmeal', 188, 'u8', []], ['h_cond1', 189, 'u8', []], ['h_cond2', 190, 'u8', []],
  ['h_inhand', 191, 'u8', []], ['h_wears', 192, 'u8', [6]], ['h_favrts', 198, 'u8', [3]], ['h_defprob', 201, 'u8', []],
  ['h_hitpts', 202, 'u8', []], ['h_rdyspl', 203, 'u8', []], ['h_gold', 204, 'u16', []], ['h_partybucks', 206, 'u16', []],
  ['h_mybucks', 208, 'u16', []], ['h_attitude', 210, 'u8', []], ['h_paydays', 211, 'u8', [4]], ['h_actmisc', 215, 'u8', []],
  ['h_actdate', 216, 'u8', []], ['h_acthour', 217, 'u8', []], ['h_actroom', 218, 'u8', []], ['h_actdays', 219, 'u8', []]];
const ASSIGNMENT: Field[] = [['as_npc', 0, 'u8', []], ['as_loc', 1, 'u8', []], ['as_room', 2, 'u8', []], ['as_x', 3, 'u8', []],
  ['as_y', 4, 'u8', []], ['as_task', 5, 'u8', []], ['as_done', 6, 'u8', []], ['as_gowildx', 7, 'u8', []], ['as_misc', 8, 'u8', []],
  ['as_race', 9, 'u8', []], ['as_tile', 10, 'u8', []], ['as_hroom', 11, 'u8', []], ['as_region', 12, 'u8', []],
  ['as_wildx', 13, 'u8', []], ['as_wildy', 14, 'u8', []], ['as_goreg', 15, 'u8', []], ['as_gowildy', 16, 'u8', []],
  ['as_gold', 17, 'u16', []], ['as_date', 19, 'u8', []], ['as_daysleft', 20, 'u8', []], ['as_hour', 21, 'u8', []],
  ['as_goloc', 22, 'u8', []], ['as_goroom', 23, 'u8', []], ['as_godays', 24, 'u8', []]];

function decode(d: Bytes, fields: Field[]): Obj {
  const obj: Obj = {};
  for (const [field, off, kind, dims] of fields) {
    if (kind === 'str') { obj[field] = latin1(split(d.subarray(off, off + dims[0]), 0)[0]); continue; }
    const n = dims.reduce((a, b) => a * b, 1);
    const vals = kind === 'u16' ? u16s(d, off, n) : list(d.subarray(off, off + n));
    obj[field] = !dims.length ? vals[0] : dims.length === 1 ? vals
      : Array.from({ length: n / dims[1] }, (_, i) => vals.slice(i * dims[1], (i + 1) * dims[1]));
  }
  return obj;
}

/** The 20 header pointers and each sub-table's bytes, bounded by the next larger pointer. A pointer equal to roomptr
 *  (other than roomptr itself) marks an unused table (locations.md). */
function tables(d: Bytes): [Record<string, number>, Record<string, Bytes>] {
  const p = Object.fromEntries(PTRS.map((k, i) => [k, u16(d, 2 * i)]));
  const ends = [...new Set(Object.values(p).filter(v => v))].sort((a, b) => a - b).concat(d.length);
  const t: Record<string, Bytes> = {};
  for (const k of PTRS) {
    const v = p[k];
    t[k] = !v || v >= d.length || (k !== 'roomptr' && v === p.roomptr) ? new Uint8Array(0) : d.subarray(v, ends.find(e => e > v));
  }
  return [p, t];
}

const FOLK = ['x', 'y', 'type', 'tile', 'num'], NPC = ['x', 'y', 'type', 'tile', 'num', 'name', 'appear', 'disappear', 'ifevent', 'ifnevent'];

function location(d: Bytes, kind: string): Obj {
  const [p, t] = tables(d);
  let n = p.maps ? d[p.maps - 1] : 0xff;
  if (n === 0xff) n = 0;
  const m = p.maps;
  const L: Obj = { kind, locnum: d[40], roomno: d[41], name: rstrip(latin1(split(d.subarray(42, 53), 0)[0])),
    lcharm: d[53], mapsize: [d[54], d[55]], doorstn: d[56], locdiff: d[57], pearlsw: d[58], greet: list(d.subarray(59, 62)),
    pointers: PTRS.map(k => p[k]), tables: Object.fromEntries(PTRS.map(k => [k, hexs(t[k])])),
    blocks: Array.from({ length: n }, (_, i) => ({ block: d[m + i], tileset: d[m + n + i], x: d[m + 2 * n + i], y: d[m + 3 * n + i] })),
    words: strings(t.gwrds), texts: strings(t.loctext) };
  if (kind === 'room') L.roommap = t.maps.length ? { g: t.maps[0], chunks: list(t.maps.subarray(1)) } : null;
  L.doors = recs(t.roomptr, 5, r => r[0] === 0).map(r => zip(['x', 'y', 'pgm', 'id', 'type'], r));
  L.pgms = recs(t.pgmptr, 4).map(r => zip(['program', 'tileset', 'datafile', 'disk'], r));
  if (kind === 'room') {
    L.exits = lists(t.exitptr, 6).map(l => l.map(r => zip(['x', 'y', 'pgm', 'tx', 'ty', 'datafile'], r)));
    L.townsfolk = lists(t.genptr, 5).map(l => l.map(r => zip(FOLK, r)));
    L.npcs = lists(t.knpcptr, 10).map(l => l.map(r => zip(NPC, r)));
  } else L.exits = recs(t.exitptr, 5, r => r[0] === 0 || r[0] === 0xff).map(r => zip(['x', 'y', 'pgm', 'tx', 'ty'], r));
  if (kind === 'region') return L;
  if (kind !== 'room') {
    L.townsfolk = recs(t.genptr, 5, r => r[0] === 0xff).map(r => zip(FOLK, r));
    L.npcs = recs(t.knpcptr, 10, r => r[0] === 0xff).map(r => zip(NPC, r));
  }
  L.residents = recs(t.resids, 6).map(r => zip(['name', 'num', 'appear', 'disappear', 'ifevent', 'ifnevent'], r));
  L.script = script(t.peopr);
  L.news = recs(t.newsr, 3, r => r[0] === 0xff).map(r => zip(['npctype', 'event', 'text'], r));
  if (kind === 'level') {
    L.look = recs(t.lkdata, 3, r => r[0] === 0).map(r => zip(['x', 'y', 'text'], r));
    L.spots = recs(t.spetbl, 6, r => r[0] === 0).map(r => zip(['x', 'y', 'type', 'd1', 'd2', 'd3'], r));
    L.keydoor = recs(t.spdoors, 5, r => r[0] === 0xff).map(r => zip(['unused', 'x', 'y', 'newtile', 'text'], r));
    L.hrooms = recs(t.hroomptr, 13, r => r[0] === 0xff).map(r => ({ id: r[0], group: r[1], reward: r[2], amount: r[3], map: r[4],
      xy: u16s(Uint8Array.from(r), 5, 4) }));
  }
  return L;
}

/** [name, bytes, kind] for every location record: plain Dnn files, bank entries Dnn_r, regions Rnn. */
function* entries(files: Files): Generator<[string, Bytes, string]> {
  for (const f of [...files.keys()].sort()) {
    if (!f.endsWith('.MCV') || !'DR'.includes(f[0]) || f === 'D06.MCV') continue;
    const d = files.get(f)!, k = u16(d, 0);
    if (f[0] === 'R') { if (f !== 'R90.MCV') yield [f.slice(0, 3), d, 'region']; continue; }
    if (k < 0x1f) {
      const offs = u16s(d, 2, k);
      for (let r = 0; r < k; r++) yield [`${f.slice(0, 3)}_${String(r).padStart(2, '0')}`, d.subarray(offs[r], r + 1 < k ? offs[r + 1] : d.length), 'room'];
      continue;
    }
    yield [f.slice(0, 3), d, d[54] === 11 && d[55] === 9 ? 'room' : f === 'D01.MCV' ? 'world' : 'level'];
  }
}

function tiledata(d: Bytes): Obj {
  const p = u16s(d, 0, 6), seg = (i: number) => d.subarray(p[i], i < 5 ? p[i + 1] : d.length);
  const walk = [...split(seg(2), 0xff), new Uint8Array(0)];   // list 2 is absent in B04, B05, B61
  return { names: strings(seg(0)), nameindex: list(seg(1)), walkable: list(walk[0]), walkable_los: list(walk[1]),
    anim: hexs(seg(3)), doors: hexs(seg(4)), colors: list(seg(5)) };
}

// ---- images: RGBA PNGs ----
const CRC = Array.from({ length: 256 }, (_, n) => { let c = n; for (let k = 0; k < 8; k++) c = c & 1 ? 0xedb88320 ^ c >>> 1 : c >>> 1; return c >>> 0; });
const crc32 = (b: Bytes) => { let c = 0xffffffff; for (const x of b) c = CRC[(c ^ x) & 0xff] ^ c >>> 8; return (c ^ 0xffffffff) >>> 0; };
async function zlib(b: Bytes): Promise<Bytes> {
  return new Uint8Array(await new Response(new Blob([b as BlobPart]).stream().pipeThrough(new CompressionStream('deflate'))).arrayBuffer());
}
class Rgba {
  readonly w: number; readonly h: number; readonly px: Bytes;
  constructor(w: number, h: number) { this.w = w; this.h = h; this.px = new Uint8Array(w * h * 4); }
  set(x: number, y: number, c: number[]) { this.px.set(c, (y * this.w + x) * 4); }
  async png(): Promise<Bytes> {
    const row = this.w * 4 + 1, raw = new Uint8Array(row * this.h);
    for (let y = 0; y < this.h; y++) raw.set(this.px.subarray(y * this.w * 4, (y + 1) * this.w * 4), y * row + 1);
    const chunk = (type: string, data: Bytes) => {
      const out = new Uint8Array(12 + data.length), v = new DataView(out.buffer);
      v.setUint32(0, data.length);
      for (let i = 0; i < 4; i++) out[4 + i] = type.charCodeAt(i);
      out.set(data, 8);
      v.setUint32(8 + data.length, crc32(out.subarray(4, 8 + data.length)));
      return out;
    };
    const ihdr = new Uint8Array(13), v = new DataView(ihdr.buffer);
    v.setUint32(0, this.w); v.setUint32(4, this.h); ihdr.set([8, 6, 0, 0, 0], 8);
    return concat([Uint8Array.from([0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a]), chunk('IHDR', ihdr),
      chunk('IDAT', await zlib(raw)), chunk('IEND', new Uint8Array(0))]);
  }
}
const concat = (parts: Bytes[]) => {
  const out = new Uint8Array(parts.reduce((n, p) => n + p.length, 0));
  let o = 0;
  for (const p of parts) { out.set(p, o); o += p.length; }
  return out;
};

/** VnnMCT (formats.md): 256 × RGB palette, {0x108, count, 16, 16}, then count 16×16 tiles of palette indexes. */
function vgaTiles(d: Bytes) {
  const palette = Array.from({ length: 256 }, (_, i) => list(d.subarray(3 * i, 3 * i + 3)));
  const count = u16(d, 770);
  if (u16(d, 768) !== 0x108 || d[772] !== 16 || d[773] !== 16 || 774 + count * 256 !== d.length) throw new Error('converter: not a VGA tileset');
  return { palette, tiles: Array.from({ length: count }, (_, i) => d.subarray(774 + i * 256, 774 + (i + 1) * 256)) };
}
/** render.py render_tileset: 16 tiles a row, opaque. */
function tileset(d: Bytes): Rgba {
  const ts = vgaTiles(d), im = new Rgba(16 * 16, Math.ceil(ts.tiles.length / 16) * 16);
  for (let y = 0; y < im.h; y++) for (let x = 0; x < im.w; x++) im.set(x, y, [0, 0, 0, 255]);
  ts.tiles.forEach((t, i) => { for (let p = 0; p < 256; p++) im.set(i % 16 * 16 + p % 16, (i >> 4) * 16 + (p >> 4), [...ts.palette[t[p]], 255]); });
  return im;
}
/** Creature tile RLE (_UnpackTile): c ≥ 0x80 → the next byte c − 0x7F times, else c + 1 literal bytes; 128 bytes out. */
function unpackCtile(b: Bytes): number[] {
  const out: number[] = [];
  let i = 0;
  while (out.length < 128) {
    const c = b[i++];
    if (c >= 0x80) { for (let k = 0; k < c - 0x7f; k++) out.push(b[i]); i++; }
    else { out.push(...b.subarray(i, i + c + 1)); i += c + 1; }
  }
  return out.slice(0, 128);
}

// ---- sounds ----
const ADPCM4 = [[0, 1, 2, 3, 4, 5, 6, 7, 0, -1, -2, -3, -4, -5, -6, -7, 1, 3, 5, 7, 9, 11, 13, 15, -1, -3, -5, -7, -9, -11, -13, -15,
  2, 6, 10, 14, 18, 22, 26, 30, -2, -6, -10, -14, -18, -22, -26, -30, 4, 12, 20, 28, 36, 44, 52, 60, -4, -12, -20, -28, -36, -44, -52, -60],
[...rep([0, 0, 0, 0, 0, 16, 16, 16], 2), ...rep([-16, 0, 0, 0, 0, 16, 16, 16], 4), ...rep([-16, 0, 0, 0, 0, 0, 0, 0], 2)]];
const ADPCM3 = [[0, 1, 2, 3, 0, -1, -2, -3, 1, 3, 5, 7, -1, -3, -5, -7, 2, 6, 10, 14, -2, -6, -10, -14, 4, 12, 20, 28, -4, -12, -20, -28,
  5, 15, 25, 35, -5, -15, -25, -35], [...rep([0, 0, 0, 8], 2), ...rep([-8, 0, 0, 8], 6), ...rep([-8, 0, 0, 0], 2)]];
function rep(a: number[], n: number) { return Array.from({ length: n }, () => a).flat(); }

/** Creative Voice File → 8-bit mono WAV (export_json.py voc_to_wav; the ADPCM decoders as DOSBox's sblaster.cpp). */
function vocToWav(v: Bytes): Bytes {
  if (latin1(v.subarray(0, 19)) !== 'Creative Voice File') throw new Error('converter: not a VOC file');
  let p = u16(v, 0x14), rate = 11025, codec = 0;
  const pcm: number[] = [], st = [128, 0];
  const adpcm = (data: Bytes, table: number[][], codes: (b: number) => number[]) => {
    st[0] = data[0]; pcm.push(data[0]);
    for (const b of data.subarray(1)) for (const c of codes(b)) {
      const n = Math.max(0, Math.min(table[0].length - 1, c + st[1]));
      st[0] = Math.max(0, Math.min(255, st[0] + table[0][n])); st[1] += table[1][n];
      pcm.push(st[0]);
    }
  };
  const data = (d: Bytes) => {
    if (codec === 0) pcm.push(...d);
    else if (codec === 1) adpcm(d, ADPCM4, b => [b >> 4, b & 15]);
    else adpcm(d, ADPCM3, b => [b >> 5, b >> 2 & 7, (b & 3) << 1]);
  };
  while (p < v.length && v[p] !== 0) {
    const t = v[p], ln = v[p + 1] | v[p + 2] << 8 | v[p + 3] << 16;
    if (t === 1) { rate = round(1e6 / (256 - v[p + 4])); codec = v[p + 5]; st[1] = 0; data(v.subarray(p + 6, p + 4 + ln)); }
    else if (t === 2) data(v.subarray(p + 4, p + 4 + ln));
    else if (t === 3) for (let k = 0; k <= u16(v, p + 4); k++) pcm.push(0x80);
    p += 4 + ln;
  }
  const out = new Uint8Array(44 + pcm.length), w = new DataView(out.buffer);
  const tag = (o: number, s: string) => { for (let i = 0; i < 4; i++) out[o + i] = s.charCodeAt(i); };
  tag(0, 'RIFF'); w.setUint32(4, 36 + pcm.length, true); tag(8, 'WAVE'); tag(12, 'fmt ');
  w.setUint32(16, 16, true); w.setUint16(20, 1, true); w.setUint16(22, 1, true); w.setUint32(24, rate, true);
  w.setUint32(28, rate, true); w.setUint16(32, 1, true); w.setUint16(34, 8, true); tag(36, 'data'); w.setUint32(40, pcm.length, true);
  out.set(pcm, 44);
  return out;
}

/** MCE full screens (tools/mce.py): run-length coded, n & 0x7F literal bytes after a count with bit 7, else one byte n times. */
function unrle(d: Bytes, size: number): Bytes {
  const out = new Uint8Array(size);
  let o = 0, p = 0;
  while (o < size && p < d.length) {
    const n = d[p] & 0x7f;
    if (d[p] & 0x80) { out.set(d.subarray(p + 1, p + 1 + n).subarray(0, size - o), o); o += n; p += 1 + n; }
    else { out.fill(d[p + 1], o, Math.min(size, o + n)); o += n; p += 2; }
  }
  return out;
}

/** The whole pack. `step(done, of)` reports progress. */
export async function convert(files: Files, step: (done: number, of: number) => void = () => {}): Promise<Pack> {
  const pack: Pack = new Map(), enc = new TextEncoder();
  const need = (f: string) => { const d = files.get(f); if (!d) throw new Error(`${f} is missing`); return d; };
  const dump = (path: string, obj: unknown) => pack.set(path, enc.encode(JSON.stringify(obj)));
  const names = [...files.keys()].sort();
  const exe = need('MC2.EXE');
  const ex = (a: number, b: number) => exe.subarray(DS + a, DS + b);

  const places: Obj[] = [];
  for (const [name, d, kind] of entries(files)) {
    const L = location(d, kind);
    dump(`locations/${name}.json`, L);
    if (kind !== 'room') places.push({ id: name, name: strip(L.name as string), kind });
  }
  dump('locations/index.json', places);
  step(1, 6);
  for (const f of names) {
    if (f[0] === 'B' && f.endsWith('.MCV')) dump(`tiledata/${f.slice(0, 3)}.json`, tiledata(files.get(f)!));
    if (f[0] === 'V' && f.endsWith('.MCT')) pack.set(`tilesets/${f.slice(0, 3)}.png`, await tileset(files.get(f)!).png());
  }
  step(2, 6);
  const blocks: Obj = {}, rooms: Obj = {};
  for (const f of names) {
    const d = files.get(f)!;
    if (f[0] === 'M' && f.endsWith('.MCM') && d[0] === 0x2a && d[1] === 0x2a && d.length >= 2 + 42 * 42) blocks[f.slice(0, 6)] = hexs(d.subarray(2, 2 + 42 * 42));
    if (f[0] === 'G' && f.endsWith('.MCM')) {
      const chunks: string[] = [];
      for (let i = 0; i < d.length - 100; i += 101) if (d[i] === 0x0b && d[i + 1] === 0x09) chunks.push(hexs(d.subarray(i + 2, i + 101)));
      rooms[f.slice(0, 3)] = chunks;
    }
  }
  dump('blocks.json', blocks);
  dump('rooms.json', rooms);

  // sprites (E0n.MCI offsets into E0n.MCC, 0xFFFF = none): tile k at cell k of 32 a row, colour 2 clear
  const palette = vgaTiles(need('V01.MCT')).palette.slice(0, 16), counts: Obj = {};
  for (let n = 0; n < 4; n++) {
    const idx = need(`E0${n}.MCI`), dat = need(`E0${n}.MCC`), offs = u16s(idx, 0, idx.length >> 1);
    const im = new Rgba(32 * 16, Math.ceil(offs.length / 32) * 16);
    offs.forEach((o, k) => {
      if (o >= dat.length) return;
      unpackCtile(dat.subarray(o, o + 129)).flatMap(b => [b >> 4, b & 15]).forEach((c, p) =>
        im.set(k % 32 * 16 + p % 16, (k >> 5) * 16 + (p >> 4), c === 2 ? [0, 0, 0, 0] : [...palette[c], 255]));
    });
    pack.set(`sprites/E0${n}.png`, await im.png());
    counts[`E0${n}`] = offs.length;
  }
  const atc = ex(0x373a, 0x3744), npc: Obj[] = [];   // _animtilecount, _npcanimtype
  let k0 = 0;
  for (const t of ex(0x3744, 0x37c4)) { npc.push({ start: k0, frames: atc[t] }); k0 += atc[t]; }
  dump('sprites.json', { columns: 32, counts, npc });
  for (const f of names) if (f[0] === 'C' && /^\d\d$/.test(f.slice(1, 3)) && f.endsWith('.MCV')) dump(`conversations/${f.slice(0, 3)}.json`, conversation(files.get(f)!));
  step(3, 6);

  dump('items.json', texts(ex(0x3bb7, 0x4000), 0x5d));
  const p81 = need('P81.MCO'), r90 = need('R90.MCV');
  dump('heroes.json', Array.from({ length: 5 }, (_, i) => decode(p81.subarray(0x82d + 220 * i), HERO)));
  dump('companions.json', Array.from({ length: Math.floor(r90.length / 220) }, (_, i) => decode(r90.subarray(220 * i), HERO)));
  dump('npctypes.json', texts(ex(0x2296, 0x2471), 60));
  dump('commands.json', texts(ex(0x2471, 0x2800), 51));
  const p90 = need('P90.MCO'), lots = p90.subarray(0xf2, index(p90, [0xff], 0xf2));
  const lot: Obj = {};
  for (let i = 0; i < lots.length - 1; i += 2) lot[String(lots[i])] = lots[i + 1];
  dump('p90.json', { haggle: Array.from({ length: 0x5d }, (_, i) => [p90[0x38 + 2 * i], p90[0x39 + 2 * i]]), lots: lot,
    orb: { texts: texts(p90.subarray(0x113, 0x113 + 1200), 19), marked: list(p90.subarray(0x10b, 0x10e)), bits: list(p90.subarray(0x10e, 0x111)) },
    keep: list(need('FFFAR.MCO').subarray(0x2235, 0x223d)) });
  const p02 = need('P02.MCO');
  dump('p02text.json', texts(p02.subarray(0x67, 0x28a), 17));
  const p08 = need('P08.MCO'), gifts = p08.subarray(0x1092, index(p08, [0xff], 0x1092));
  dump('p08.json', { texts: texts(p08.subarray(0x123, 0x500), 18),
    gifts: Array.from({ length: Math.ceil(gifts.length / 2) }, (_, i) => [gifts[2 * i], gifts[2 * i + 1]]),
    ghosts: { npcs: list(p08.subarray(0xba, 0xbd)), scrolls: list(p08.subarray(0xb7, 0xba)),
      paras: [0, 1, 2].map(i => latin1(p08.subarray(0xbd + 2 * i, 0xbf + 2 * i))),
      spoken: list(p08.subarray(0xb1, 0xb4)), rested: list(p08.subarray(0xb4, 0xb7)) },
    base: u16s(p08, 0x83, 16).map(w => [w & 0xff, w >> 8]),
    side: { odd: list(p08.subarray(0xa3, 0xac)), even: list(p08.subarray(0xac, 0xb1)) },
    junk: list(p08.subarray(0xe49, index(p08, [0, 0], 0xe49))), banquet: list(p08.subarray(0x97c, 0x97c + 33)) });
  const v02 = need('V02.MCO');
  dump('v02.json', { disguise: { towns: list(v02.subarray(0xcba, 0xcbd)), texts: texts(v02.subarray(0x07, 0x60), 2) },
    hroomtype: { ids: list(v02.subarray(0xe19, 0xe27)), types: list(v02.subarray(0xe27, 0xe35)) },
    vision: { ids: list(v02.subarray(0x8c, 0x9c)), texts: list(v02.subarray(0x9c, 0xac)) }, sense: u16s(v02, 0x7fe, 16) });
  const p89 = need('P89.MCO');
  dump('p89.json', { tiers: list(p89.subarray(0x09, 0x0e)), x0: list(p89.subarray(0x10, 0x15)), y0: list(p89.subarray(0x15, 0x1a)),
    x1: list(p89.subarray(0x1a, 0x1f)), y1: list(p89.subarray(0x1f, 0x24)),
    rects: Array.from({ length: p89[0x10a] }, (_, i) => [p89[0x10c + i], p89[0x10f + i], p89[0x112 + i], p89[0x115 + i]]) });
  const p93 = need('P93.MCO');
  dump('p93text.json', texts(p93.subarray(0x3d, 0x254)));
  dump('p93.json', { hunt: { terrain: list(p93.subarray(0x03, 0x0d)).map(sb), weather: list(p93.subarray(0x0d, 0x19)).map(sb) },
    formation: Array.from({ length: 6 }, (_, i) => list(p93.subarray(0x19 + 2 * i, 0x1b + 2 * i))) });
  dump('conds.json', texts(ex(0x4204, 0x4300), 12));
  const p97 = need('P97.MCO'), p92 = need('P92.MCO');
  dump('p92text.json', texts(p92.subarray(0x39, 0xc4), 2));
  dump('p97.json', { texts: texts(p97.subarray(0x17, 0x1ba), 7),
    events: Object.fromEntries(list(p97.subarray(0x68e, 0x69d)).map((c, i) => [String(c), p97[0x69d + i]])) });
  const p91 = need('P91.MCO'), end = index(p91, [0xff], 0x48), pairs = p91.subarray(0x48, end);
  dump('p91text.json', { lines: texts(p91.subarray(end + 1, 0x2e0), 16),
    weather: Array.from({ length: pairs.length >> 1 }, (_, i) => [pairs[2 * i], pairs[2 * i + 1]]) });
  const p01 = need('P01.MCO'), s8 = (o: number, n: number) => list(p01.subarray(o, o + n)).map(sb);
  dump('p01.json', { terraintime: list(p01.subarray(0x276, 0x284)), weathertime: s8(0x280, 12), terrainenergy: list(p01.subarray(0x298, 0x2a6)),
    swimweather: list(p01.subarray(0x2f6, 0x302)),
    clothing: Array.from({ length: 7 }, (_, k) => list(p01.subarray(0x2a2 + 12 * k, 0x2ae + 12 * k))),
    regions: Array.from({ length: 16 }, (_, k) => list(p01.subarray(0x236 + 4 * k, 0x23a + 4 * k))),
    patchtiles: list(p01.subarray(0x36a, 0x374)),
    patrols: Array.from({ length: 128 }, (_, k) => list(p01.subarray(0x136 + 2 * k, 0x138 + 2 * k))),
    respawn: list(p01.subarray(0x32a, 0x33a)),
    steps: { ...Object.fromEntries([['dirs', 0x1790], ['side1', 0x17a0], ['side2', 0x17b0]].map(([k, o]) =>
      [k, Array.from({ length: 8 }, (_, i) => s8(o as number + 2 * i, 2))])), order: list(p01.subarray(0x18b7, 0x18c1)).map(b => b >> 1) },
    ships: { weather: s8(0x28c, 12), rate: list(p01.subarray(0x34a, 0x350)), homex: list(p01.subarray(0x350, 0x356)), homey: list(p01.subarray(0x356, 0x35c)) } });
  const p09 = need('P09.MCO');
  dump('p09.json', { pieces: list(p09.subarray(0x4b, 0x50)), piecetiles: list(p09.subarray(0x50, 0x55)), altars: list(p09.subarray(0x3a, 0x3d)),
    icons: list(p09.subarray(0x3d, 0x45)), wake: list(p09.subarray(0xc86, 0xc8e)), offer: texts(p09.subarray(0x92, 0xa1), 2),
    texts: texts(p09.subarray(0xfb, 0x1fb), 6) });
  const parts = split(p81.subarray(0x15, 0x7b1), 0);
  dump('p81.json', { texts: parts.slice(0, 40).map(latin1), scenes: split(parts[40], 0xff).slice(0, 5).map(list) });
  const p88 = need('P88.MCO'), words = (d: Bytes, a: number, n: number) => texts(d.subarray(a), n);
  const start: Obj[] = [];
  for (let o = 0x167f; p81[o] !== 0xff; o += 25) start.push(decode(p81.subarray(o), ASSIGNMENT));
  dump('assign.json', { start, menu: words(p88, 6, 4), texts: words(p88, 0x2d9, 58), dests: words(p88, 0x24, 16),
    destxy: Array.from({ length: 16 }, (_, i) => list(p88.subarray(0xab + 3 * i, 0xae + 3 * i))),
    places: words(p88, 0xdb, 25), locplace: list(p88.subarray(0x1ee, 0x24b)), homes: list(p88.subarray(0x24b, 0x26b)),
    jail: list(p88.subarray(0xdbd, 0xdc5)),
    rects: Array.from({ length: 16 }, (_, i) => list(p92.subarray(0xc2 + 4 * i, 0xc6 + 4 * i))),
    cands: Array.from({ length: 16 }, (_, i) => list(p92.subarray(0x64e + 4 * i, 0x652 + 4 * i))),
    prisons: Object.fromEntries(['id', 'loc', 'x', 'y'].map((k, i) => [k, list(p92.subarray(0x68e + 9 * i, 0x697 + 9 * i))])),
    rescue: latin1(split(need('P07.MCO').subarray(0x539), 0)[0]) });
  dump('spots.json', { ambush: { ids: list(p02.subarray(0x1743, 0x1749)), events: list(p02.subarray(0x1749, 0x174f)) },
    remarks: { ids: list(v02.subarray(0xbdb, 0xbf6)), events: list(v02.subarray(0xbf6, 0xc11)), locspecs: list(v02.subarray(0xc11, 0xc2c)) } });
  const p07 = need('P07.MCO');
  dump('p07.json', { texts: texts(p07.subarray(0x806, 0x980), 15), trap: list(p07.subarray(0x804, 0x806)),
    doorx: list(p07.subarray(3, 11)), doory: list(p07.subarray(11, 19)) });
  const p04 = need('P04.MCO');
  dump('p04.json', { amount: list(p04.subarray(0x72, 0x7c)), icon: list(p04.subarray(0x7c, 0x86)), x: list(p04.subarray(0x88, 0x97)), y: list(p04.subarray(0x97, 0xa6)) });
  const p05 = need('P05.MCO'), u8 = (o: number, n: number) => list(p05.subarray(o, o + n));
  dump('p05.json', { leave: u8(0xcd, 9), inn: { price: u8(0x283, 8) },
    school: { skill: u8(0x149, 19), cost: Array.from({ length: 0x5b - 0x48 }, (_, i) => u16(p05, 0x4d + 2 * (0x48 + i))),
      days: u8(0x125, 19), gain: u8(0x16d, 19), cap: Array.from({ length: 19 }, (_, k) => u8(0x17f + 6 * k, 6)) },
    job: { trade: u8(0x273, 16) },
    library: { subjects: [0, 1, 2].map(k => u8(0x1f7 + 5 * k, 5)), research: u8(0x20b, 15), days: u8(0x21f, 15), task: u8(0x233, 15),
      lists: split(p05.subarray(0x28b, 0x2b9), 0).map(list), texts: texts(need('V05.MCO').subarray(7), 48) },
    lodge: { mask: u8(0x247, 3), cost: 200 } });
  dump('exetables.json', { hungerhours: list(ex(0x3aa8, 0x3aae)), nousetext: list(ex(0x2d9a, 0x2d9a + 0x5c)),
    weathers: texts(ex(0x424e, 0x4300), 12), lootvalues: u16s(exe, DS + 0x2e72, 93),
    useall: Array.from({ length: 32 }, (_, i) => i).filter(i => u16(exe, DS + 0x8ae + 2 * i)).map(i => i + 0x31),
    attribs: texts(ex(0x3aae, 0x3c00), 29), speltim: list(ex(0x2b8f, 0x2bb9)),
    tod: { words: texts(ex(0x41e0, 0x4204), 5), hour: list(ex(0x38f2, 0x390a)) } });
  step(4, 6);

  // combat (rules/combat.md, encounters.md): monsters by code − 5, groups by number − 60, weapons by item − 9
  const p96 = need('P96.MCO'), p95 = need('P95.MCO'), v06 = need('V06.MCO'), d06 = need('D06.MCV'), ptr = u16s(d06, 0, 14);
  const mnames = texts(ex(0x40a4, 0x4204), 37);
  const monster = (k: number) => {
    const r = exe.subarray(DS + 0x308e + 23 * k, DS + 0x308e + 23 * k + 23);
    return { name: mnames[k], hp: u16(r, 0), shield: r[2], weapon: r[3], armor: r[4], bravery: r[5], str: r[6], dex: r[7], agi: r[8],
      res: r[9], int: r[10], wskl: r[11], mskl: r[12], spells: list(r.subarray(13, 16)), tile: u16(r, 20), anim: r[22],
      leader: p96[0x39 + 5 + k], undead: p96[0x62 + 5 + k] };
  };
  const weapon = (k: number) => {
    const r = exe.subarray(DS + 0x2cf6 + 9 * k, DS + 0x2cf6 + 9 * k + 9), hl = u16(r, 7);
    return { minst: r[0], basedam: r[1], type: r[2], unbreakable: r[3], stbonus: r[4], sklbonus: r[5], race: r[6],
      hitlist: hl ? list(exe.subarray(DS + hl, index(exe, [0xff], DS + hl))) : [] };
  };
  const sl = (d: Bytes, a: number, b: number) => list(d.subarray(a, b));
  dump('combat.json', {
    monsters: Array.from({ length: 37 }, (_, k) => monster(k)),
    groups: Array.from({ length: 163 }, (_, k) => list(ex(0x340b + 5 * k, 0x3410 + 5 * k))),
    weapons: Array.from({ length: 22 }, (_, k) => weapon(k)),
    setupxy: sl(p81, 0x162f, 0x165f),
    ranges: { x: Array.from({ length: 8 }, (_, k) => sl(p96, 0x19 + 2 * k, 0x1b + 2 * k)), y: Array.from({ length: 8 }, (_, k) => sl(p96, 0x29 + 2 * k, 0x2b + 2 * k)) },
    loot: { thresholds: sl(p95, 0x21e, 0x21e + 168), items: sl(p95, 0x17a, 0x17a + 168),
      amounts: Array.from({ length: (index(p95, [0xff], 0x13a) - 0x13a + 2) / 3 | 0 }, (_, i) => sl(p95, 0x13a + 3 * i, 0x13d + 3 * i)),
      an: sl(p95, 0xcdb, 0xce0) },
    resurrect: texts(p95.subarray(0x27, 0x13a), 7),
    spells: { names: texts(ex(0x3edc, 0x4100), 42), energy: list(ex(0x2bc6, 0x2bc6 + 42)), where: list(ex(0x2bf0, 0x2bf0 + 42)),
      side: sl(need('P94.MCO'), 0x1529, 0x1529 + 42), skill: list(ex(0x390c, 0x390c + 20)), here: list(ex(0x2c1a, 0x2c1a + 10)),
      summon: sl(v06, 0x14ae, 0x14ae + 37), destroy: sl(v06, 0x2466, 0x2466 + 37) },
    songs: { instruments: sl(v06, 0x28ff, index(v06, [0], 0x28ff)), races: Array.from({ length: 4 }, (_, k) => sl(v06, 0x4ec + 8 * k, 0x4ee + 8 * k)),
      names: Array.from({ length: 4 }, (_, k) => split(ex(0x4014, 0x4200), 0).slice(8 * k, 8 * k + 2).map(latin1)) },
    parley: { texts: texts(v06.subarray(u16(v06, 5), 0x45a), 40), kins: texts(ex(0x4084, 0x42ae), 40), attitudes: texts(ex(0x42ae, 0x4320), 8),
      worth: u16s(p96, 0xb3f, 6), rolls: sl(p96, 0xb4b, 0xb5c) },
    maxtbl: list(ex(0x2c7e, 0x2c7e + 120)),
    guarddiff: sl(p01, 0x33a, 0x34a),
    d06: { cast: sl(d06, ptr[0], ptr[1]), crit: sl(d06, ptr[1], ptr[2]), crit2: sl(d06, ptr[2], ptr[3]), prey: sl(d06, ptr[3], ptr[3] + 42),
      gonshi: sl(d06, ptr[4], ptr[5]), sermin: sl(d06, ptr[5], ptr[6]), potion: sl(d06, ptr[6], ptr[7]), counts: sl(d06, ptr[8], ptr[8] + 56),
      armor: sl(d06, ptr[9], ptr[10]), dodge: sl(d06, ptr[10], ptr[11]), prefs: sl(d06, ptr[12], ptr[12] + 132) } });
  step(5, 6);

  // sound (decision 5): _GameSound(n) plays FFFAR's name table entry n − 1 (file 0x3FB0, 13-byte names); _song(n) plays
  // _cmffile[n] (DS:3070), and the MT-32 arrangement's name follows 14 names later
  const fff = need('FFFAR.MCO');
  for (let n = 1; n < 30; n++) {
    const raw = latin1(split(fff.subarray(0x3fb0 + 13 * (n - 1), 0x3fb0 + 13 * n), 0)[0]);
    const voc = files.get(raw.split('.voc')[0].toUpperCase() + '.VOC');
    if (voc) pack.set(`sounds/${n}.wav`, vocToWav(voc));
  }
  const cstr = (o: number) => latin1(exe.subarray(o, index(exe, [0], o))).toUpperCase();
  for (let n = 1; n < 15; n++) {
    const p = u16(exe, DS + 0x3070 + 2 * n);
    pack.set(`music/${n}.cmf`, need(cstr(DS + p)));
    pack.set(`music/${n}.mid`, need(cstr(DS + p + 14 * 11)));
  }
  // the game font (E26.MCT): 128 glyphs of 8×8 4bpp, ink 0 → opaque white, the rest clear, 16 a row
  const f26 = need('E26.MCT'), font = new Rgba(128, 64);
  u16s(f26, 0, 128).forEach((o, g) => {
    o += 256;
    if (f26[o] !== 4 || f26[o + 1] !== 8) throw new Error('converter: E26.MCT glyph header');
    f26.subarray(o + 2, o + 34).forEach((b, i) => [b >> 4, b & 15].forEach((v, k) => {
      if (v === 0) font.set((g % 16) * 8 + (i % 4) * 2 + k, (g >> 4) * 8 + (i >> 2), [255, 255, 255, 255]);
    }));
  });
  pack.set('font.png', await font.png());
  // VGA full screens (P81 ovl_1469): 5 the Mindcraft logo, 1 the title, E/I/M the intro's pictures
  for (const x of '51EIM') {
    const raw = unrle(need(`VSCR${x}.MCE`), 0xfd00), pal = list(raw.subarray(0, 768)).map(v => Math.min(255, Math.floor(v * 255 / 63)));
    const im = new Rgba(320, 200);
    for (let i = 0; i < 64000; i++) { const c = raw[768 + i]; im.set(i % 320, Math.floor(i / 320), [pal[3 * c], pal[3 * c + 1], pal[3 * c + 2], 255]); }
    pack.set(`screens/${x}.png`, await im.png());
  }
  dump('comtxt.json', texts(exe.subarray(DS + 0x9f8, DS + 0x9f8 + 0x4000), 400));
  step(6, 6);
  return pack;
}
