// The songs' Roland MT-32 arrangements (MC2nnT.MID, standard MIDI files, type 1, 192 ticks per quarter): the same
// melodies as the CMF files plus a drum track, scored for the MT-32's preset instruments. Parsed to timed notes and
// channel controls for the modern renderers (modern.ts).

export interface Note { t: number; dur: number; ch: number; key: number; vel: number; prog: number }
export interface Ctl { t: number; ch: number; kind: 'vol' | 'pan' | 'bend'; v: number }   // vol, pan 0-127; bend −1..1
export interface Song { notes: Note[]; ctls: Ctl[]; length: number }

/** MT-32 preset (capital tone) → General MIDI program, for the presets the songs use (MT-32 owner's manual list). */
export const MT32_GM: Record<number, number> = {
  24: 62, 25: 63,      // Syn Brass 1, 2
  32: 88,              // Fantasy → New Age pad
  48: 48, 51: 45,      // Str Sect 1, Pizzicato
  57: 46, 58: 46,      // Harp 1, 2
  61: 27,              // Elec Gtr 1 → clean electric guitar
  75: 72, 77: 75,      // Piccolo 2, Pan Pipes
  84: 68,              // Oboe
  92: 60, 93: 60, 94: 58,   // Fr Horn 1, 2, Tuba
  112: 47, 122: 55,    // Timpani, Orche Hit
};

export function parseMidi(d: Uint8Array): Song {
  const u16 = (o: number) => d[o] << 8 | d[o + 1], u32 = (o: number) => (u16(o) << 16 | u16(o + 2)) >>> 0;
  const ntr = u16(10), div = u16(12);
  type Ev = { tick: number; s: number; a: number; b: number; tempo?: number };
  const evs: Ev[] = [];
  let p = 14;
  for (let k = 0; k < ntr; k++) {
    const end = p + 8 + u32(p + 4);
    let q = p + 8, tick = 0, st = 0;
    const vl = () => { let v = 0, b; do { b = d[q++]; v = v << 7 | b & 0x7f; } while (b & 0x80); return v; };
    while (q < end) {
      tick += vl();
      if (d[q] & 0x80) st = d[q++];
      if (st === 0xff) {
        const type = d[q++], len = vl();
        if (type === 0x51) evs.push({ tick, s: 0xff, a: 0, b: 0, tempo: d[q] << 16 | d[q + 1] << 8 | d[q + 2] });
        q += len;
      } else if (st === 0xf0 || st === 0xf7) q += vl();
      else if ((st & 0xf0) === 0xc0 || (st & 0xf0) === 0xd0) evs.push({ tick, s: st, a: d[q++], b: 0 });
      else { evs.push({ tick, s: st, a: d[q], b: d[q + 1] }); q += 2; }
    }
    p = end;
  }
  evs.sort((x, y) => x.tick - y.tick || (x.s === 0xff ? -1 : 0) - (y.s === 0xff ? -1 : 0));
  // ticks → seconds through the tempo map
  let tempo = 500000, lastTick = 0, lastSec = 0;
  const sec = (tick: number) => lastSec + (tick - lastTick) * tempo / 1e6 / div;
  const notes: Note[] = [], ctls: Ctl[] = [], on = new Map<number, Note>(), prog = new Array(16).fill(0);
  for (const e of evs) {
    const t = sec(e.tick);
    if (e.tempo) { lastSec = t; lastTick = e.tick; tempo = e.tempo; continue; }
    const ch = e.s & 15, kind = e.s & 0xf0, id = ch << 8 | e.a;
    if (kind === 0xc0) prog[ch] = e.a;
    else if (kind === 0x90 && e.b) {
      const n = { t, dur: 0, ch, key: e.a, vel: e.b, prog: prog[ch] };
      const old = on.get(id); if (old) old.dur = t - old.t;
      on.set(id, n); notes.push(n);
    } else if (kind === 0x80 || kind === 0x90) {
      const n = on.get(id); if (n) { n.dur = t - n.t; on.delete(id); }
    } else if (kind === 0xb0 && (e.a === 7 || e.a === 10)) ctls.push({ t, ch, kind: e.a === 7 ? 'vol' : 'pan', v: e.b });
    else if (kind === 0xe0) ctls.push({ t, ch, kind: 'bend', v: ((e.b << 7 | e.a) - 8192) / 8192 });
  }
  const length = Math.max(0, ...notes.map(n => n.t + n.dur));
  for (const n of on.values()) n.dur = length - n.t;
  return { notes, ctls, length };
}
