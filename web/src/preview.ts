// Dev page (preview.html): each song as the original FM music and as the modern synth version (decision 6).
import { renderCmf, RATE } from './opl';
import { parseMidi } from './midi';
import { renderModern } from './modern';

const NAMES = ['Title', 'Intro', "Flute: 'Lullaby of Gu'", "Flute: \"Urg's Dream\"", "Lyre: \"Mage's Joy\"", "Lyre: 'Rondo Miz'",
  "Lute: 'Morning Mist'", "Lute: 'Wind Song'", "Bandore: 'Sambali'", "Bandore: 'Firedance'", 'Epilogue',
  "'The Happy Traveller'", 'The Horn (combat)', "The Conch's call"];
const status = document.getElementById('status')!, table = document.getElementById('songs') as HTMLTableElement;
let ctx: AudioContext | null = null, playing: AudioBufferSourceNode | null = null;
const cache = new Map<string, AudioBuffer>();
Object.assign(window, { previewCache: cache });   // for scripts/shot.mjs eval:
const bytes = async (path: string) => new Uint8Array(await (await fetch(`./pack/${path}`)).arrayBuffer());

async function play(n: number, style: 'fm' | 'synth') {
  ctx ??= new AudioContext();
  playing?.stop();
  const key = `${n}:${style}`;
  let b = cache.get(key);
  if (!b) {
    status.textContent = `Rendering ${NAMES[n - 1]}…`;
    const t0 = performance.now();
    if (style === 'fm') {
      const s = renderCmf(await bytes(`music/${n}.cmf`));
      b = ctx.createBuffer(1, s.length, RATE); b.copyToChannel(s, 0);
    } else b = await renderModern(parseMidi(await bytes(`music/${n}.mid`)));
    cache.set(key, b);
    status.textContent = `Rendered in ${Math.round(performance.now() - t0)} ms.`;
  }
  const src = ctx.createBufferSource();
  src.buffer = b; src.connect(ctx.destination); src.start();
  playing = src;
  status.textContent = `Playing ${NAMES[n - 1]} (${style === 'fm' ? 'original FM' : style}), ${b.duration.toFixed(0)} s.`;
  src.onended = () => { if (playing === src) status.textContent = ''; };
}

for (let n = 1; n <= 14; n++) {
  const row = table.insertRow();
  row.insertCell().textContent = `${n}. ${NAMES[n - 1]}`;
  for (const [label, style] of [['Original FM', 'fm'], ['Synth', 'synth']] as const) {
    const b = document.createElement('button');
    b.textContent = label;
    b.onclick = () => void play(n, style).catch(e => { status.textContent = String(e); });
    row.insertCell().append(b);
  }
}
document.getElementById('stop')!.onclick = () => { playing?.stop(); status.textContent = ''; };
