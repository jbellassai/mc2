// Modernised music (decision 6): the songs' own MT-32 arrangements (midi.ts) played by synthesisers built here, so
// the melodies, harmonies and drum parts are the original composer's. Stereo placement from the songs' pan controls,
// their volume changes and pitch bends, reverb, a stereo echo and synthesised drums. Rendered offline, then played as
// one buffer at the original FM music's loudness.
import { MT32_GM, type Song } from './midi';

const RATE = 44100;
const freq = (key: number) => 440 * 2 ** ((key - 69) / 12);

/** Renders a song. */
export async function renderModern(song: Song): Promise<AudioBuffer> {
  const ctx = new OfflineAudioContext(2, Math.ceil((song.length + 3) * RATE), RATE);
  const noise = ctx.createBuffer(1, RATE, RATE);
  noise.getChannelData(0).forEach((_, i, a) => { a[i] = Math.random() * 2 - 1; });

  // the mix: dry + reverb + a stereo delay into a gentle compressor
  const comp = ctx.createDynamicsCompressor();
  comp.threshold.value = -14; comp.ratio.value = 3; comp.connect(ctx.destination);
  const verb = ctx.createConvolver(), verbIn = ctx.createGain();
  verb.buffer = impulse(ctx, 2.0);
  verbIn.gain.value = 0.25;
  verbIn.connect(verb).connect(comp);
  const delayIn = ctx.createGain();
  const l = ctx.createDelay(1), r = ctx.createDelay(1), fb = ctx.createGain(), merge = ctx.createChannelMerger(2);
  l.delayTime.value = 0.28; r.delayTime.value = 0.42; fb.gain.value = 0.3; delayIn.gain.value = 0.18;
  delayIn.connect(l); delayIn.connect(r); l.connect(merge, 0, 0); r.connect(merge, 0, 1);
  r.connect(fb).connect(l); merge.connect(comp);

  // one strip per MIDI channel: volume (CC7, squared) → pan (CC10) → mix
  const strips = Array.from({ length: 16 }, () => {
    const g = ctx.createGain(), pan = ctx.createStereoPanner();
    g.gain.value = (100 / 127) ** 2;
    g.connect(pan); pan.connect(comp); pan.connect(verbIn); pan.connect(delayIn);
    return { g, pan, bend: 0 };
  });
  for (const c of song.ctls) {
    if (c.kind === 'vol') strips[c.ch].g.gain.setValueAtTime((c.v / 127) ** 2, c.t);
    if (c.kind === 'pan') strips[c.ch].pan.pan.setValueAtTime((c.v - 64) / 64 * 0.8, c.t);
  }

  const sources: { ch: number; t: number; end: number; detune: AudioParam }[] = [];
  const bends = song.ctls.filter(c => c.kind === 'bend');
  const bendAt = (ch: number, t: number) => bends.filter(b => b.ch === ch && b.t <= t).at(-1)?.v ?? 0;
  for (const n of song.notes) {
    const out = strips[n.ch].g, vel = n.vel / 127;
    if (n.ch === 9) { drum(ctx, noise, n.key, n.t, vel, out); continue; }
    const v = synth(ctx, noise, MT32_GM[n.prog] ?? 0, n.key, n.t, n.dur, vel, out);
    for (const p of v.detune) { p.setValueAtTime(bendAt(n.ch, n.t) * 200, n.t); sources.push({ ch: n.ch, t: n.t, end: v.end, detune: p }); }
  }
  for (const b of bends) for (const s of sources) if (s.ch === b.ch && s.t < b.t && b.t < s.end) s.detune.setValueAtTime(b.v * 200, b.t);
  return normalize(await ctx.startRendering());
}

/** Brings a render to the loudness of the original FM music (RMS 0.13, the intro's): the gain that reaches it, then a
 *  soft limiter that rounds off only what passes 0.6 so that sharp attacks (plucks, hits, drums) cannot clip. */
function normalize(b: AudioBuffer): AudioBuffer {
  const chans = Array.from({ length: b.numberOfChannels }, (_, c) => b.getChannelData(c));
  let sum = 0;
  for (const d of chans) for (const x of d) sum += x * x;
  const rms = Math.sqrt(sum / (chans.length * b.length));
  if (!rms) return b;
  const k = 0.13 / rms, knee = 0.6, room = 0.38;
  for (const d of chans) for (let i = 0; i < d.length; i++) {
    const x = d[i] * k, a = Math.abs(x);
    d[i] = a <= knee ? x : Math.sign(x) * (knee + room * Math.tanh((a - knee) / room));
  }
  return b;
}

/** A stereo reverb impulse: decaying noise, slightly different per side. */
function impulse(ctx: BaseAudioContext, secs: number): AudioBuffer {
  const b = ctx.createBuffer(2, Math.floor(secs * RATE), RATE);
  for (let c = 0; c < 2; c++) b.getChannelData(c).forEach((_, i, a) => { a[i] = (Math.random() * 2 - 1) * (1 - i / a.length) ** 3; });
  return b;
}

/** Synth instruments by General MIDI family. */
function synth(ctx: BaseAudioContext, noise: AudioBuffer, gm: number, key: number, t: number, dur: number, vel: number, out: AudioNode) {
  const f = freq(key), end = t + Math.max(dur, 0.05), env = ctx.createGain(), filt = ctx.createBiquadFilter();
  filt.type = 'lowpass'; filt.connect(env).connect(out);
  const oscs: OscillatorNode[] = [];
  const osc = (type: OscillatorType, mult = 1, cents = 0, gain = 1) => {
    const o = ctx.createOscillator(), g = ctx.createGain();
    o.type = type; o.frequency.value = f * mult; o.detune.value = cents; g.gain.value = gain;
    o.connect(g).connect(filt); oscs.push(o); return o;
  };
  const adsr = (a: number, peak: number, sus: number, rel: number) => {
    env.gain.setValueAtTime(0, t); env.gain.linearRampToValueAtTime(peak, t + a);
    env.gain.setTargetAtTime(peak * sus, t + a, 0.15);
    env.gain.setValueAtTime(peak * sus, end); env.gain.setTargetAtTime(0, end, rel / 4);
    return end + rel;
  };
  const pluck = (decay: number, peak: number) => {
    env.gain.setValueAtTime(0, t); env.gain.linearRampToValueAtTime(peak, t + 0.004);
    env.gain.setTargetAtTime(0, t + 0.004, decay / 4);
    return t + decay;
  };
  let stop: number;
  const v = 0.22 * vel;
  if (gm === 48 || gm === 88) {                                   // strings, pad: detuned saws, soft attack
    osc('sawtooth', 1, -8, 0.5); osc('sawtooth', 1, 8, 0.5); osc('sawtooth', 0.5, 0, gm === 88 ? 0.4 : 0.2);
    filt.frequency.value = gm === 88 ? 1800 : 2600; filt.Q.value = 0.5;
    stop = adsr(gm === 88 ? 0.35 : 0.12, v * 0.9, 0.85, 0.8);
  } else if (gm === 60 || gm === 58 || gm === 62 || gm === 63) {  // brass: saw + square, opening filter
    osc('sawtooth', 1, 0, 0.7); osc('square', 1, 5, 0.3);
    const top = gm === 58 ? 900 : gm === 60 ? 1800 : 3200;
    filt.frequency.setValueAtTime(top / 4, t); filt.frequency.linearRampToValueAtTime(top, t + 0.06);
    filt.frequency.setTargetAtTime(top * 0.6, t + 0.06, 0.2); filt.Q.value = 2;
    stop = adsr(0.03, v, 0.8, 0.25);
  } else if (gm === 72 || gm === 75 || gm === 68) {               // flutes, pipes, oboe: soft tone with vibrato
    const o = osc(gm === 68 ? 'square' : 'triangle', 1, 0, 1);
    if (gm !== 68) osc('sine', 2, 0, 0.15);
    const lfo = ctx.createOscillator(), depth = ctx.createGain();
    lfo.frequency.value = 5.2; depth.gain.setValueAtTime(0, t); depth.gain.linearRampToValueAtTime(f * 0.006, t + 0.35);
    lfo.connect(depth).connect(o.frequency); lfo.start(t); lfo.stop(end + 0.5);
    filt.frequency.value = gm === 68 ? 1600 : 5000; filt.Q.value = gm === 68 ? 4 : 0.5;
    stop = adsr(0.04, v * (gm === 68 ? 0.6 : 1), 0.9, 0.2);
  } else if (gm === 47) {                                         // timpani: a falling sine and a thud
    const o = osc('sine', 1, 0, 1); o.frequency.setValueAtTime(f * 1.05, t); o.frequency.exponentialRampToValueAtTime(f, t + 0.2);
    filt.frequency.value = 2000; stop = pluck(1.6, v * 2);
    hit(ctx, noise, t, 0.12, 400, 'lowpass', v, out);
  } else if (gm === 55) {                                         // orchestra hit: a chord stab
    osc('sawtooth', 1); osc('sawtooth', 1.5, 0, 0.6); osc('sawtooth', 2, 0, 0.5); osc('square', 0.5, 0, 0.5);
    filt.frequency.setValueAtTime(5000, t); filt.frequency.exponentialRampToValueAtTime(600, t + 0.4);
    stop = pluck(0.6, v * 1.3);
    hit(ctx, noise, t, 0.15, 2000, 'bandpass', v, out);
  } else {                                                        // harp, pizzicato, guitars: plucks
    osc('triangle', 1, 0, 1); osc('sawtooth', 1, 3, 0.25);
    filt.frequency.setValueAtTime(f * 8, t); filt.frequency.exponentialRampToValueAtTime(f * 2, t + 0.3);
    stop = pluck(gm === 45 ? 0.35 : gm === 46 ? 1.8 : 1.2, v * 1.2);
  }
  for (const o of oscs) { o.start(t); o.stop(stop + 0.05); }
  return { detune: oscs.map(o => o.detune), end: stop };
}

/** A burst of filtered noise. */
function hit(ctx: BaseAudioContext, noise: AudioBuffer, t: number, decay: number, f: number, type: BiquadFilterType, peak: number, out: AudioNode) {
  const src = ctx.createBufferSource(), filt = ctx.createBiquadFilter(), g = ctx.createGain();
  src.buffer = noise; filt.type = type; filt.frequency.value = f;
  g.gain.setValueAtTime(peak, t); g.gain.setTargetAtTime(0, t, decay / 4);
  src.connect(filt).connect(g).connect(out);
  src.start(t, Math.random() * 0.5); src.stop(t + decay + 0.05);
}

/** A falling sine (kick, toms). */
function thump(ctx: BaseAudioContext, t: number, f0: number, f1: number, decay: number, peak: number, out: AudioNode) {
  const o = ctx.createOscillator(), g = ctx.createGain();
  o.frequency.setValueAtTime(f0, t); o.frequency.exponentialRampToValueAtTime(f1, t + decay * 0.5);
  g.gain.setValueAtTime(peak, t); g.gain.setTargetAtTime(0, t, decay / 4);
  o.connect(g).connect(out); o.start(t); o.stop(t + decay + 0.05);
}

/** The drum notes the songs use (General MIDI / MT-32 rhythm keys). */
function drum(ctx: BaseAudioContext, noise: AudioBuffer, key: number, t: number, vel: number, out: AudioNode) {
  const v = 0.5 * vel;
  switch (key) {
    case 35: case 36: thump(ctx, t, 150, 45, 0.45, v * 1.6, out); break;                        // kick
    case 37: hit(ctx, noise, t, 0.04, 3000, 'bandpass', v, out); break;                          // rim shot
    case 38: case 40: hit(ctx, noise, t, 0.2, 1500, 'highpass', v * 0.9, out); thump(ctx, t, 220, 160, 0.12, v * 0.6, out); break;   // snare
    case 41: case 43: thump(ctx, t, 110, 70, 0.45, v * 1.2, out); break;                          // low toms
    case 45: case 47: thump(ctx, t, 150, 95, 0.4, v * 1.2, out); break;                           // mid tom
    case 48: case 50: thump(ctx, t, 190, 120, 0.35, v * 1.2, out); break;                         // high toms
    case 42: case 44: hit(ctx, noise, t, 0.05, 7000, 'highpass', v * 0.5, out); break;           // closed / pedal hi-hat
    case 46: hit(ctx, noise, t, 0.35, 7000, 'highpass', v * 0.5, out); break;                     // open hi-hat
    case 49: case 57: hit(ctx, noise, t, 1.6, 5000, 'highpass', v * 0.6, out); break;            // crash
    case 51: case 59: hit(ctx, noise, t, 0.8, 6500, 'bandpass', v * 0.5, out); break;            // ride
    case 54: hit(ctx, noise, t, 0.14, 8500, 'highpass', v * 0.5, out); break;                     // tambourine
    case 69: hit(ctx, noise, t, 0.07, 6000, 'highpass', v * 0.4, out); break;                     // cabasa
    default: hit(ctx, noise, t, 0.1, 2500, 'bandpass', v * 0.5, out);
  }
}
