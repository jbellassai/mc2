// Visual effects (FFFAR 0x37A2-0x3F68, P06 ovl_1144; docs/rules/effects.md): E00 icon sequences drawn on squares,
// colour flashes of a figure (the EGA XOR recolouring of _movectileFX, drawn as a difference blend), and the inverted
// window. Each routine is a list of frames played on one queue; a frame may start a sound, as the routines do.
import type { Icon } from './view';

export interface Tint { x: number; y: number; color: number }   // an EGA colour index blended over a square
/** A person's sprite (as `View.draw` picks it: companions by number, anyone else by E02 sprite `tile`) part drawn by
 *  `_MultiFX`: the first `shown` pixels in ORDER (`out`: all but those), in their colours or a rainbow (flag 7);
 *  `under` keeps the whole figure in rainbow colours beneath, as an earlier pass left it. */
export interface Ghost { x: number; y: number; num: number; tile: number; shown: number; out?: boolean; rainbow?: boolean; under?: boolean }
export interface Overlay { icons: Icon[]; tints: Tint[]; invert: boolean; ghosts?: Ghost[] }
export interface Frame extends Partial<Overlay> { ms: number; sound?: number }
type At = { x: number; y: number };

const TICK = 64;                       // ovl_3bdf(n) = _delay(n << 6)

/** ovl_3b52: the icons of `list` on one square, `n` ticks each, `reps` times. */
const seq = (p: At, list: number[], n: number, reps: number, sound?: number): Frame[] =>
  Array.from({ length: reps }, () => list).flat().map((frame, i) => ({ icons: [{ x: p.x, y: p.y, frame }], ms: n * TICK, sound: i ? undefined : sound }));

/** ovl_3caa: every marked square steps through `list` from its own stage, one pass every `n` ticks, until all are done. */
function multi(marks: (At & { stage: number })[], list: number[], n: number, sound?: number): Frame[] {
  const out: Frame[] = [];
  for (let pass = 0; marks.some(m => m.stage + pass < list.length); pass++)
    out.push({ icons: marks.filter(m => m.stage + pass < list.length).map(m => ({ x: m.x, y: m.y, frame: list[m.stage + pass] })),
      ms: n * TICK, sound: pass ? undefined : sound });
  return out;
}

const tint = (p: At, colors: (number | null)[], ms: number, sound?: number): Frame[] =>
  colors.map((c, i) => ({ tints: c === null ? [] : [{ x: p.x, y: p.y, color: c }], ms, sound: i ? undefined : sound }));

/** _MultiFX (EXE): FFAWRK visits the 16×16 pixels (y = n >> 4, x = n & 15) from 0 by n → ((n + 1)·37 mod 257) − 1. */
export const ORDER: number[] = (() => { const o = [0]; for (let v = 36; v; v = (v + 1) * 37 % 257 - 1) o.push(v); return o; })();

/** One `_MultiFX` pass over a person, `ms` long. */
function dissolve(f: Omit<Ghost, 'shown'>, ms: number): Frame[] {
  const n = 16;
  return Array.from({ length: n }, (_, i) => ({ ghosts: [{ ...f, shown: (i + 1) * 256 / n }], ms: ms / n }));
}

const BURST = [6, 7, 8], RINGS = [0x27, 0x28, 0x29, 0x2a], ACID = [0x2a, 0x29, 0x28, 0x27];

export const FX = {
  spef1: (p: At) => seq(p, [0xd, 0xe], 2, 4, 10),                       // 0x3F2F: frames paced by sound 10
  spef2: (p: At) => tint(p, [...Array(3).fill([7, 0xc, 8, 0xf]).flat(), null], 80),   // a Barg's blow
  spef3: (p: At) => tint(p, [0xc, null, 9, null, 0xd, null, 0xf, null], TICK),        // Fear
  spef3single: (p: At, color: number) => tint(p, [color], 400),        // Freeze 9, Zofir 0xC
  spef4: (p: At, color: number) => tint(p, Array(4).fill([color, null]).flat(), 3 * TICK, 10),   // Heal, Energy, Shield… (callers play 10 first)
  spef5: (p: At) => seq(p, RINGS, 1, 3, 15),                            // Forget
  spef5a: (p: At) => seq(p, RINGS, 3, 2, 10),                           // Pierce, Repel
  spef6: (p: At) => seq(p, [0x22, 0x23, 0x24, 0x25, 0x26], 2, 2, 11),   // Courage, the Orb
  spef7: (p: At) => tint(p, Array(5).fill([7, null]).flat(), 66, 16),   // Betray (_MultiFX, 10 frames)
  bang: (p: At, from = 0) => seq(p, [0x1d, 0x1e, 0x1f, 0x20, 0x21].slice(from), 3, 1, 3),
  acidBang: (p: At) => seq(p, ACID, 4, 1, 3),
  /** 0x3D91: the 3×3 around the square, the centre a frame ahead, then MultiBang(3). */
  bigBang: (p: At, sound = 3) => multi([-1, 0, 1].flatMap(dy => [-1, 0, 1].map(dx => ({ x: p.x + dx, y: p.y + dy, stage: dx || dy ? 0 : 1 }))), BURST, 1, sound),
  multiBang: (marks: (At & { stage?: number })[], sound?: number) => multi(marks.map(m => ({ x: m.x, y: m.y, stage: m.stage ?? 0 })), BURST, 1, sound),
  multiThing: (marks: At[], sound: number) => multi(marks.map(m => ({ x: m.x, y: m.y, stage: 0 })), ACID, 5, sound),
  invert: (ms: number, sound?: number): Frame[] => [{ invert: true, ms, sound }],
  /** P08 0x1890 (ovl_191b): a person appears - four rainbow passes (flag 7, timer 4000), then the colours (flag 3). */
  appear: (p: At & { num: number; tile: number }): Frame[] => {
    const f = { x: p.x, y: p.y, num: p.num, tile: p.tile };
    return [...[0, 1, 2, 3].flatMap(k => dissolve({ ...f, rainbow: true, under: k > 0 }, 300)), ...dissolve({ ...f, under: true }, 600)];
  },
  /** P08 0x18B4 (ovl_18cd): a person fades out (flag 3, timer 60000, the slowest). */
  vanish: (p: At & { num: number; tile: number }): Frame[] => dissolve({ x: p.x, y: p.y, num: p.num, tile: p.tile, out: true }, 2500),
  /** P06 ovl_1144 / ovl_138c: the missile's tile square by square along `path`; types 1-4 cycle three tiles. */
  missile: (path: At[], tile: number, sheet?: 'E01', cycle = false): Frame[] =>
    path.map((p, i) => ({ icons: [{ x: p.x, y: p.y, frame: cycle ? tile + i % 3 : tile, sheet }], ms: 40 })),
};
/** P06 0x1479 (OV_0x1579): the flying tile of missile types 1-8 (1 fire, 2 acid, 6 shatter); types 1-4 cycle. */
export const MISSILE = [0, 3, 0x30, 0x33, 0x37, 0x36, 0x2f, 0x0b, 0x0a];

export class Fx {
  overlay: Overlay = { icons: [], tints: [], invert: false };
  private queue = Promise.resolve();
  constructor(private redraw: () => void, private sound: (n: number) => void) {}

  play(frames: Frame[]) {
    this.queue = this.queue.then(async () => {
      for (const f of frames) {
        if (f.sound) this.sound(f.sound);
        this.overlay = { icons: f.icons ?? [], tints: f.tints ?? [], invert: f.invert ?? false, ghosts: f.ghosts };
        this.redraw();
        await new Promise(ok => setTimeout(ok, f.ms));
      }
      this.overlay = { icons: [], tints: [], invert: false };
      this.redraw();
    });
  }

  /** Resolves when every queued effect has played. */
  idle(): Promise<void> { return this.queue; }
}
