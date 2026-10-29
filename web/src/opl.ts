// The game's music: Creative Music Files (MC2nnA.CMF) as Creative's SBFMDRV played them on the Sound Blaster's OPL2
// (YM3812) FM chip (decision 5). A small OPL2 model renders a whole song to samples: nine two-operator voices, the
// four waveforms, feedback, FM or additive connection, ADSR with key scaling, tremolo and vibrato. Rates and levels
// follow the YM3812 data sheet (attack 2826 ms and decay 39280 ms at rate 1, halving every rate step; levels in
// 0.1875 dB units); the operator and feedback scaling follow Nuked-OPL3's. Not modelled: rhythm mode and the CSM and
// note-select bits (no song uses them).

export const RATE = 49716;                                   // the OPL2's sample rate: 3.579545 MHz / 72

const MULT = [0.5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 12, 12, 15, 15];
const KSL = [0, 32, 40, 45, 48, 51, 53, 56, 56, 58, 59, 60, 61, 62, 63, 64], KSLSHIFT = [8, 1, 2, 0];
const SINE = Float32Array.from({ length: 1024 }, (_, i) => Math.sin(2 * Math.PI * i / 1024));
const VOICE = [0, 1, 2, 8, 9, 10, 16, 17, 18];               // the modulator's register offset per voice; carrier +3
const Stage = { Attack: 0, Decay: 1, Sustain: 2, Release: 3, Off: 4 } as const;

class Operator {
  // register fields
  am = false; vib = false; hold = false; ksr = false; mult = 1; ksl = 0; tl = 0; ar = 0; dr = 0; sl = 0; rr = 0; wave = 0;
  // state
  phase = 0; env = 511; stage: number = Stage.Off; out = 0; prev = 0;

  set(reg: number, v: number) {
    switch (reg & 0xe0) {
      case 0x20: this.am = !!(v & 0x80); this.vib = !!(v & 0x40); this.hold = !!(v & 0x20); this.ksr = !!(v & 0x10); this.mult = MULT[v & 15]; break;
      case 0x40: this.ksl = v >> 6; this.tl = v & 63; break;
      case 0x60: this.ar = v >> 4; this.dr = v & 15; break;
      case 0x80: this.sl = (v >> 4) === 15 ? 31 : v >> 4; this.rr = v & 15; break;
      case 0xe0: this.wave = v & 3; break;
    }
  }
  on() { this.stage = Stage.Attack; this.phase = 0; }
  off() { if (this.stage !== Stage.Off) this.stage = Stage.Release; }

  /** One sample: `inc` the phase step in cycles, `mod` the phase offset in cycles, `kslAtt`/`rof` from the voice's
   *  frequency, `trem` the tremolo attenuation and `vib` the vibrato factor. */
  step(inc: number, mod: number, rof: number, kslAtt: number, trem: number, vib: number): number {
    const rate = (r: number) => r ? Math.min(63, 4 * r + (this.ksr ? rof : rof >> 2)) : 0;
    switch (this.stage) {
      case Stage.Attack: {
        const re = rate(this.ar);
        if (re >= 60) this.env = 0;
        else if (re) this.env -= (this.env + 1) * 6.2 / (2.82624 * 2 ** (-(re - 4) / 4) * RATE);
        if (this.env <= 0) { this.env = 0; this.stage = Stage.Decay; }
        break;
      }
      case Stage.Decay: {
        const re = rate(this.dr);
        if (re) this.env += 512 / (39.28064 * 2 ** (-(re - 4) / 4) * RATE);
        if (this.env >= this.sl << 4) { this.env = this.sl << 4; this.stage = Stage.Sustain; }
        break;
      }
      case Stage.Sustain:
        if (this.hold) break;
      // fall through: without the sustain bit the sound keeps fading at the release rate
      case Stage.Release: {
        const re = rate(this.rr);
        if (re) this.env += 512 / (39.28064 * 2 ** (-(re - 4) / 4) * RATE);
        if (this.env >= 511) { this.env = 511; this.stage = Stage.Off; }
        break;
      }
    }
    this.phase = (this.phase + inc * this.mult * (this.vib ? vib : 1)) % 1;
    if (this.stage === Stage.Off) return this.out = 0;
    const att = this.env + (this.tl << 2) + (kslAtt >> KSLSHIFT[this.ksl]) + (this.am ? trem : 0);
    if (att >= 511) { this.prev = this.out; return this.out = 0; }
    let p = (this.phase + mod) % 1; if (p < 0) p += 1;
    const i = (p * 1024) | 0;
    let s = SINE[i];
    if (this.wave === 1 && i >= 512) s = 0;
    else if (this.wave === 2) s = Math.abs(s);
    else if (this.wave === 3) s = (i & 511) < 256 ? Math.abs(s) : 0;
    this.prev = this.out;
    return this.out = s * 10 ** (-att * 0.1875 / 20);
  }
}

class Voice {
  mod = new Operator(); car = new Operator(); fnum = 0; block = 0; key = false; fb = 0; additive = false;
  sample(trem: number, vib: number): number {
    if (this.mod.stage === Stage.Off && this.car.stage === Stage.Off) return 0;
    const inc = this.fnum * 2 ** (this.block - 20), rof = this.block << 1 | this.fnum >> 9;
    const ksl = Math.max(0, (KSL[this.fnum >> 6] << 2) - ((8 - this.block) << 5));
    const fb = this.fb ? (this.mod.out + this.mod.prev) * 4 / 2 ** (9 - this.fb) : 0;
    const m = this.mod.step(inc, fb, rof, ksl, trem, vib);
    const c = this.car.step(inc, this.additive ? 0 : m * 4, rof, ksl, trem, vib);
    return this.additive ? m + c : c;
  }
}

/** The chip, driven by register writes. */
export class OPL2 {
  private voices = Array.from({ length: 9 }, () => new Voice());
  private t = 0;                                              // samples since reset, for the LFOs
  private deepAm = false; private deepVib = false;

  write(reg: number, v: number) {
    if (reg === 0xbd) { this.deepAm = !!(v & 0x80); this.deepVib = !!(v & 0x40); return; }
    const hi = reg & 0xf0, ch = reg & 15;
    if (hi === 0xa0 && ch < 9) { this.voices[ch].fnum = this.voices[ch].fnum & 0x300 | v; return; }
    if (hi === 0xb0 && ch < 9) {
      const vc = this.voices[ch], key = !!(v & 0x20);
      vc.fnum = vc.fnum & 0xff | (v & 3) << 8; vc.block = v >> 2 & 7;
      if (key && !vc.key) { vc.mod.on(); vc.car.on(); }
      if (!key && vc.key) { vc.mod.off(); vc.car.off(); }
      vc.key = key;
      return;
    }
    if (hi === 0xc0 && ch < 9) { this.voices[ch].fb = v >> 1 & 7; this.voices[ch].additive = !!(v & 1); return; }
    const off = reg & 0x1f, k = VOICE.findIndex(o => o === off || o + 3 === off);
    if (k >= 0 && reg >= 0x20) (VOICE[k] === off ? this.voices[k].mod : this.voices[k].car).set(reg, v);
  }

  /** Renders `n` samples into `out` from `at`. */
  render(out: Float32Array, at: number, n: number) {
    for (let i = 0; i < n; i++, this.t++) {
      const sec = this.t / RATE;
      const trem = (1 - Math.abs((sec * 3.7) % 2 - 1)) * (this.deepAm ? 25.6 : 5.33);   // 4.8 dB / 1 dB, triangle
      const vib = 1 + Math.sin(2 * Math.PI * 6.1 * sec) * (this.deepVib ? 0.0081 : 0.0041);   // 14 / 7 cents
      let s = 0;
      for (const v of this.voices) s += v.sample(trem, vib);
      out[at + i] = s * 0.3;
    }
  }
}

/** A CMF file (Creative's format: "CTMF", offsets to the 16-byte instruments and to a MIDI-like stream timed in
 *  clock ticks, `ticks per second` at +0x0C) rendered as SBFMDRV plays it: a program change picks the channel's
 *  instrument; a note takes a free voice (else the one sounding longest), loads the instrument into it and keys it;
 *  velocity, volume (controller 7), pan and pitch bend are ignored, as the driver does; controller 0x67 (rhythm mode)
 *  stays off in every song. */
export function renderCmf(d: Uint8Array): Float32Array<ArrayBuffer> {
  const w = (o: number) => d[o] | d[o + 1] << 8;
  const insAt = w(6), musAt = w(8), tps = w(0x0c), nins = w(0x24);
  const ins = Array.from({ length: nins }, (_, k) => d.subarray(insAt + 16 * k, insAt + 16 * k + 16));
  type Ev = { at: number; s: number; a: number; b: number };
  const evs: Ev[] = [];
  let p = musAt, t = 0, st = 0;
  const vl = () => { let v = 0, b; do { b = d[p++]; v = v << 7 | b & 0x7f; } while (b & 0x80); return v; };
  while (p < d.length) {
    t += vl();
    if (d[p] & 0x80) st = d[p++];
    const kind = st & 0xf0;
    if (kind === 0xc0 || kind === 0xd0) evs.push({ at: t, s: st, a: d[p++], b: 0 });
    else if (kind >= 0x80 && kind <= 0xe0) { evs.push({ at: t, s: st, a: d[p], b: d[p + 1] }); p += 2; }
    else if (st === 0xff) { const type = d[p], len = d[p + 1]; p += 2 + len; if (type === 0x2f) break; }
    else if (st === 0xf0 || st === 0xf7) p += vl();
    else break;
  }
  const end = Math.ceil(((evs.at(-1)?.at ?? 0) / tps + 1.5) * RATE);
  const out = new Float32Array(end), chip = new OPL2();
  chip.write(0xbd, 0);
  const program = new Array(16).fill(0), voices: { ch: number; note: number; since: number }[] = VOICE.map(() => ({ ch: -1, note: -1, since: 0 }));
  const keyOff = (v: number) => { chip.write(0xb0 + v, 0); voices[v].note = -1; };
  const keyOn = (v: number, ch: number, note: number, at: number) => {
    const i = ins[program[ch]] ?? ins[0], m = VOICE[v];
    [0x20, 0x23, 0x40, 0x43, 0x60, 0x63, 0x80, 0x83, 0xe0, 0xe3].forEach((r, k) => chip.write(r + m, i[k]));
    chip.write(0xc0 + v, i[10]);
    const f = 440 * 2 ** ((note - 69) / 12);
    let block = 0, fnum = Math.round(f * 2 ** (20 - block) / RATE);
    while (fnum > 1023 && block < 7) fnum = Math.round(f * 2 ** (20 - ++block) / RATE);
    chip.write(0xa0 + v, fnum & 0xff);
    chip.write(0xb0 + v, 0x20 | block << 2 | fnum >> 8 & 3);
    voices[v] = { ch, note, since: at };
  };
  let done = 0;
  for (const e of evs) {
    const at = Math.min(end, Math.round(e.at / tps * RATE));
    chip.render(out, done, at - done); done = at;
    const ch = e.s & 15, kind = e.s & 0xf0;
    if (kind === 0xc0) program[ch] = e.a;
    else if (kind === 0x80 || kind === 0x90 && e.b === 0) {
      const v = voices.findIndex(x => x.ch === ch && x.note === e.a);
      if (v >= 0) keyOff(v);
    } else if (kind === 0x90) {
      let v = voices.findIndex(x => x.ch === ch && x.note === e.a);
      if (v < 0) v = voices.findIndex(x => x.note < 0);
      if (v < 0) v = voices.reduce((a, x, k) => x.since < voices[a].since ? k : a, 0);
      keyOff(v); keyOn(v, ch, e.a, at);
    }
  }
  chip.render(out, done, end - done);
  return out;
}
