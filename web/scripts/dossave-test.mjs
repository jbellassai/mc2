// Round-trip test of web/src/dossave.ts on every real DOS save: node web/scripts/dossave-test.mjs [ORIGDIR] [PACKDIR]
// (defaults original/ and out/pack/, the pack from tools/export_json.py). Exit 1 when a check fails.
//  (a) toDos(fromDos(S), S) == S, except the documented derived caches (SCRATCH) and saves made inside a room;
//  (b) toDos(fromDos(S), T) for every other save T: the globals that still differ from S' = toDos(fromDos(S), S), i.e.
//      the bytes the port does not model and takes from T (derived globals are already in S');
//  (c) fromDos(toDos(fromDos(S), T)) == fromDos(S): the port's state survives any template;
//  (d) port-made state (Pierce log, room/chest/gate bits, ships, a partial roster …) survives toDos → fromDos.
import { registerHooks } from 'node:module';
import { readFileSync, readdirSync, existsSync } from 'node:fs';
import { join } from 'node:path';

// src/*.ts import each other without an extension (Vite style); let Node find the .ts files.
registerHooks({ resolve(s, c, next) {
  try { return next(s, c); } catch (e) { if (/^\.\.?\//.test(s) && !/\.\w+$/.test(s)) return next(s + '.ts', c); throw e; }
} });
const { fromDos, toDos, globalAt } = await import('../src/dossave.ts');

const [orig = 'original', pack = 'out/pack'] = process.argv.slice(2);
const load = async p => JSON.parse(readFileSync(join(pack, p), 'utf8'));
const files = [...readdirSync(orig).filter(f => /^FFSAV.*\.MCS$/i.test(f)).map(f => join(orig, f)),
  ...(existsSync(join(orig, 'saves')) ? readdirSync(join(orig, 'saves')).filter(f => /\.MCS$/i.test(f)).map(f => join(orig, 'saves', f)) : [])];
const name = f => f.slice(orig.length + 1);

/** Caches recomputed by the game when P01/P02 starts (dossave.ts header): a template may hold stale values. */
const SCRATCH = new Set(['_psize', '_p1x', '_p1y', '_curseg', '_curmap', '_tailorcharm']);
/** Differing bytes grouped by global: {global: [offsets]}. */
const diff = (a, b) => {
  const g = {};
  for (let i = 0; i < a.length; i++) if (a[i] !== b[i]) (g[globalAt(i)] ??= []).push(i);
  return g;
};
const strip = sv => JSON.stringify({ ...sv, when: '' });
const ranges = offs => offs.reduce((r, o) => (r.length && r.at(-1)[1] === o - 1 ? r.at(-1)[1] = o : r.push([o, o]), r), [])
  .map(([s, e]) => s === e ? s.toString(16) : `${s.toString(16)}-${e.toString(16)}`).join(',');

let fail = 0, cfail = 0;
const saves = [];
for (const f of files) {
  const b = new Uint8Array(readFileSync(f));
  try { saves.push({ f, b, sv: await fromDos(b, load) }); }
  catch (e) { console.log(`skip ${name(f)}: ${e.message}`); }
}

console.log('(a) toDos(fromDos(S), S) vs S');
for (const { f, b, sv } of saves) {
  const room = b[0x4e] !== 1 && b[0x4e] !== 2;   // _curmpg: saved inside a room, moved out to its door by fromDos
  const g = diff(await toDos(JSON.parse(JSON.stringify(sv)), b, load), b), bad = Object.keys(g).filter(k => !SCRATCH.has(k));
  if (bad.length && !room) fail++;
  console.log(`  ${room ? `room P0${b[0x4e]}` : bad.length ? 'FAIL' : 'ok  '} ${name(f)} ${sv.level.id} (${sv.at.x},${sv.at.y}) party ${sv.party.members.length}`
    + Object.entries(g).map(([k, o]) => ` ${SCRATCH.has(k) ? '' : '!'}${k}[${ranges(o)}]`).join(''));
}

console.log("(b) toDos(fromDos(S), T) vs toDos(fromDos(S), S) = S', T ≠ S: the globals left as T has them");
const left = {};
for (const s of saves) s.own = await toDos(JSON.parse(JSON.stringify(s.sv)), s.b, load);
for (const s of saves) for (const t of saves) {
  if (s === t) continue;
  const out = await toDos(JSON.parse(JSON.stringify(s.sv)), t.b, load);
  // free party slots (_party 0xFF in S) keep T's bytes: unused, reported apart
  const used = [0, 1, 2, 3, 4, 5].filter(k => s.b[0x21 + 2 * k] !== 0xff || s.b[0x22 + 2 * k]);
  const slot = i => i >= 0x78 && i < 0x5a0 ? Math.floor((i - 0x78) / 220) : i >= 0x38 && i < 0x44 ? (i - 0x38) % 6 : -1;
  const g = {};
  for (const [k, o] of Object.entries(diff(out, s.own))) for (const i of o) (g[slot(i) >= 0 && !used.includes(slot(i)) ? `${k} (free slots)` : k] ??= []).push(i);
  for (const [k, o] of Object.entries(g)) {
    const e = left[k] ??= { pairs: 0, offs: new Set() };
    e.pairs++; o.forEach(i => e.offs.add(i));
  }
  const back = await fromDos(out, load);
  if (strip(back) !== strip(s.sv)) {
    cfail++;
    const a = JSON.parse(strip(back)), b = JSON.parse(strip(s.sv));
    console.log(`  (c) FAIL ${name(s.f)} on ${name(t.f)}: ${Object.keys(b).filter(k => JSON.stringify(a[k]) !== JSON.stringify(b[k])).join(' ')}`);
  }
}
const n = saves.length * (saves.length - 1);
for (const [k, e] of Object.entries(left).sort((a, b) => b[1].pairs - a[1].pairs))
  console.log(`  ${k.padEnd(14)} ${String(e.pairs).padStart(4)}/${n} pairs  bytes ${ranges([...e.offs].sort((a, b) => a - b))}`);
console.log(`(c) fromDos(toDos(fromDos(S), T)) == fromDos(S): ${cfail ? `${cfail} failures above` : `ok for all ${n} pairs`}`);

// (d) state only the port makes, written into the new-game save and read back
const base = saves.find(x => x.f.endsWith('FFSAVA.MCS')) ?? saves[0], snake = saves.flatMap(x => x.sv.snakes)[0];
const lvl = id => JSON.parse(readFileSync(join(pack, 'locations', `${id}.json`), 'utf8'));
const ids = readdirSync(join(pack, 'locations')).filter(f => /^D\d\d\.json$/.test(f)).map(f => f.slice(0, 3));
const hr = ids.map(id => [id, lvl(id)]).find(([, l]) => l.kind === 'level' && l.hrooms?.length && l.hrooms[0].id !== 251);
const ch = ids.map(id => [id, lvl(id)]).find(([, l]) => l.kind === 'level' && l.spots?.some(p => p.type === 3));
const sv = structuredClone(base.sv), r90 = await load('companions.json');
Object.assign(sv, { dunrms: [`${hr[0]}:${hr[1].hrooms[0].id}`], duntre: [`${hr[0]}:${hr[1].hrooms[0].id}`],
  chests: [`${ch[0]}:${ch[1].spots.find(p => p.type === 3).d2}`], gates: [0, 5], ambushed: [12, 101], detect: 7, disguise: 1,
  disasterday: 40, scroll: 0x4f, been: 0x8000 | 0x10, rent: [0, 3, 0, 0, 0, 0, 0, 2], casino: [1000, 800, 1000, 1000, 1000, 1000, 1000, 50],
  patches: sv.patches.map((n, i) => i % 7 ? n : 3), snakes: snake ? [snake] : [], events: [...sv.events, 7, 200] });
sv.world.ships = { ...sv.world.ships, cur: 2, sta: [3, 3, 6, 3, 3, 1], days: [0, 0, 4, 0, 0, 9] };
sv.world.cleared = [9, 100]; sv.world.dead = [3]; sv.world.engaged = [127]; sv.world.lastgen[4] = 7; sv.world.ptrl[5] = [44, 55];
sv.party.away = [56, 60, 61]; sv.party.roster = [[2, { ...r90[1], h_gold: 1234 }]];
sv.assigns = sv.assigns.map((r, i) => i === 10 ? { ...sv.assigns.find(Boolean), as_npc: 11 } : r);
const got = await fromDos(await toDos(structuredClone(sv), base.b, load), load);
const want = { ...sv, events: [...sv.events].sort((a, b) => a - b), party: { ...sv.party, roster: r90.map((r, i) => [i + 1, i === 1 ? { ...r, h_gold: 1234 } : r]) } };
const bad = Object.keys(want).filter(k => k !== 'when' && JSON.stringify(got[k]) !== JSON.stringify(want[k]));
console.log(`(d) port-made state through toDos → fromDos: ${bad.length ? `FAIL ${bad.join(' ')}` : 'ok'}`);
if (bad.length) cfail++;
process.exit(fail || cfail ? 1 : 0);
