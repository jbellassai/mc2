// Sound effects and music (decision 5). `_GameSound(n)` plays the digitised effect n (FFFAR's VOC name table,
// converted to sounds/n.wav by tools/export_json.py); `_song(n)` plays MC2nnA.CMF through the OPL2 model (opl.ts),
// and `_finishsong` waits for it to end. The original's sound and music switches (`_e_soundon`, the install-time
// music board) become two toggles kept in the browser.
import { renderCmf, RATE } from './opl';

const BASE = './pack/';
const KEY = 'mc2.audio';

let ctx: AudioContext | null = null;
const effects = new Map<number, Promise<AudioBuffer | null>>();
const songs = new Map<number, AudioBuffer>();

function load(): { sound: boolean; music: boolean } {
  try { return { sound: true, music: true, ...JSON.parse(localStorage.getItem(KEY) ?? '{}') }; } catch { return { sound: true, music: true }; }
}
export const audio = load();
export function saveAudio() { try { localStorage.setItem(KEY, JSON.stringify(audio)); } catch { /* not kept */ } }

/** Browsers start audio only after a gesture: until the first key or click the context stays suspended, effects are
 *  dropped and a song waits to start. */
function unlock() {
  ctx ??= new AudioContext();
  if (ctx.state === 'suspended') void ctx.resume();
}
addEventListener('pointerdown', unlock);
addEventListener('keydown', unlock);

const play = (b: AudioBuffer) => {
  const src = ctx!.createBufferSource();
  src.buffer = b; src.connect(ctx!.destination); src.start();
  return src;
};

/** The last effects (n) and songs (100 + n) started, for checking a run (dbg.played). */
export const played: number[] = [];
const note = (n: number) => { played.push(n); if (played.length > 20) played.shift(); };
if (import.meta.env.DEV) Object.assign(window, { played, audioTime: () => [ctx?.state, ctx?.currentTime] });   // for scripts/shot.mjs eval: (before dbg exists)

let voice: AudioBufferSourceNode | null = null;
/** _GameSound(n): fire and forget; like the Sound Blaster's single DMA voice, a new effect cuts the one playing. A
 *  missing file (thunder, 29) is silent. */
export function sfx(n: number) {
  if (!audio.sound || !ctx || ctx.state !== 'running') return;
  if (!effects.has(n)) effects.set(n, fetch(`${BASE}sounds/${n}.wav`).then(r => r.ok ? r.arrayBuffer() : null)
    .then(a => a ? ctx!.decodeAudioData(a) : null).catch(() => null));
  void effects.get(n)!.then(b => { if (!b) return; voice?.stop(); voice = play(b); note(n); });
}

let queue: Promise<void> = Promise.resolve();
/** _song(n) + _finishsong: plays the song after any still playing and resolves when it has ended (at once with music
 *  off). */
export function song(n: number): Promise<void> { return queue = queue.then(() => playSong(n)); }
async function playSong(n: number): Promise<void> {
  if (!audio.music) return;
  ctx ??= new AudioContext();
  let b = songs.get(n);
  if (!b) {
    const r = await fetch(`${BASE}music/${n}.cmf`);
    if (!r.ok) return;
    const s = renderCmf(new Uint8Array(await r.arrayBuffer()));
    b = ctx.createBuffer(1, s.length, RATE);
    b.copyToChannel(s, 0);
    songs.set(n, b);
  }
  const src = play(b);
  note(100 + n);
  await new Promise(ok => { src.onended = ok; });
}
