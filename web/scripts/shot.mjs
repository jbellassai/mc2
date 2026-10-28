// Drive the dev build in headless Chrome: press keys, then save a screenshot and print the status line.
// usage: node scripts/shot.mjs URL OUT.png [key ...]   keys: any key name (ArrowUp, Enter …); "xN" repeats the previous key;
// "type:TEXT" types text into the focused field; "click:LABEL" clicks a button; "wait:MS" pauses
import { spawn } from 'node:child_process';
import { writeFileSync, mkdtempSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join } from 'node:path';

const [url, out, ...script] = process.argv.slice(2);
const CHROME = process.env.CHROME ?? '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
const port = 9300 + Math.floor(Math.random() * 500);
const chrome = spawn(CHROME, ['--headless=new', '--disable-gpu', `--remote-debugging-port=${port}`, '--window-size=1100,800',
  `--user-data-dir=${mkdtempSync(join(tmpdir(), 'mc2shot-'))}`, 'about:blank'], { stdio: 'ignore' });
const sleep = ms => new Promise(r => setTimeout(r, ms));

try {
  let target;
  for (let i = 0; i < 50 && !target; i++) {
    await sleep(100);
    try { target = (await (await fetch(`http://127.0.0.1:${port}/json/list`)).json()).find(t => t.type === 'page'); } catch {}
  }
  const ws = new WebSocket(target.webSocketDebuggerUrl);
  await new Promise(r => ws.addEventListener('open', r, { once: true }));
  let id = 0; const pending = new Map();
  ws.addEventListener('message', e => { const m = JSON.parse(e.data); pending.get(m.id)?.(m); });
  const send = (method, params = {}) => new Promise(r => { pending.set(++id, r); ws.send(JSON.stringify({ id, method, params })); });
  const evaluate = async expr => (await send('Runtime.evaluate', { expression: expr, returnByValue: true })).result?.result?.value;

  await send('Page.enable');
  await send('Page.navigate', { url });
  for (let i = 0; i < 100 && (await evaluate('document.getElementById("status")?.textContent')) === 'Loading…'; i++) await sleep(100);
  const keys = [];
  for (const k of script) {
    const rep = /^x(\d+)$/.exec(k);
    if (rep) for (let i = 1; i < +rep[1]; i++) keys.push(keys.at(-1)); else keys.push(k);
  }
  for (const key of keys) {
    if (key.startsWith('type:')) { await sleep(300); await send('Input.insertText', { text: key.slice(5) }); continue; }
    if (key.startsWith('wait:')) { await sleep(+key.slice(5)); continue; }
    if (key.startsWith('click:')) {
      await sleep(300);
      await evaluate(`[...document.querySelectorAll('button')].find(b => b.textContent === ${JSON.stringify(key.slice(6))})?.click()`);
      continue;
    }
    const extra = key === 'Enter' ? { windowsVirtualKeyCode: 13, text: '\r' } : {};
    await send('Input.dispatchKeyEvent', { type: 'keyDown', key, code: key, ...extra });
    await send('Input.dispatchKeyEvent', { type: 'keyUp', key, code: key });
  }
  await sleep(500);
  console.log(await evaluate('document.getElementById("status").textContent'));
  writeFileSync(out, Buffer.from((await send('Page.captureScreenshot', { format: 'png' })).result.data, 'base64'));
  ws.close();
} finally {
  chrome.kill();
}
