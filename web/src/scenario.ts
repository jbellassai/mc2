// Dev-only scenario editor (F2, or Scenario in the Game panel): edits a save snapshot (decision 4) and applies it with
// the game's own restore, so a scenario is just a save file. Place (location + square, picked on a map), time, the
// party (companions, stats, skills, pack, spells, conditions), the event bits (labelled from docs/events.md) and files.
import { Level } from './level';
import { json } from './pack';
import { STATS, SKILLS, type HeroRecord } from './hero';

export interface Snapshot {
  when: string; place: string;
  clock: { minute: number; hour: number; date: number; month: number; weather: number; juldate: number };
  events: number[];
  party: { members: { rec: HeroRecord; cell: number; num: number }[]; away: number[]; roster: [number, HeroRecord][] };
  level: { id: string; ts?: number }; at: { x: number; y: number };
  [more: string]: unknown;
}
export interface ScenarioCtx {
  snapshot(): Snapshot;
  apply(sv: Snapshot): Promise<void>;
  items: string[]; spells: string[]; conds: string[]; weathers: string[]; companions: HeroRecord[];
  slots: { get(n: number): Snapshot | null; set(n: number, sv: Snapshot): boolean };
}

const MONTHS = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'];
const COND1 = [[0x01, 'Wounded'], [0x02, 'Poisoned'], [0x04, 'Paralyzed'], [0x08, 'Ill'], [0x10, 'Exhausted'], [0x20, 'Hungry'],
  [0x40, 'Starving'], [0x80, 'Dead']] as const;   // h_cond1 bits (hero.ts condition, items.md)

/** `el('div.cls', {props}, ...children)` */
function el<K extends keyof HTMLElementTagNameMap>(spec: K | `${K}.${string}`, props: Partial<HTMLElementTagNameMap[K]> & Record<string, unknown> = {},
  ...kids: (Node | string)[]): HTMLElementTagNameMap[K] {
  const [tag, ...cls] = spec.split('.');
  const e = document.createElement(tag) as HTMLElementTagNameMap[K];
  if (cls.length) e.className = cls.join(' ');
  Object.assign(e, props);
  e.append(...kids);
  return e;
}
const num = (value: number, set: (v: number) => void, min = 0, max = 255) => {
  const i = el('input', { type: 'number', value: String(value), min: String(min), max: String(max) });
  i.onchange = () => set(Math.max(min, Math.min(max, Number(i.value) || 0)));
  return i;
};
const pick = (options: [string | number, string][], value: string | number, set: (v: string) => void) => {
  const s = el('select', {}, ...options.map(([v, t]) => el('option', { value: String(v), textContent: t, selected: String(v) === String(value) })));
  s.onchange = () => set(s.value);
  return s;
};
const field = (label: string, input: Node) => el('label.sc-field', {}, el('span', { textContent: label }), input);

let open = false;
/** The editor is showing (the game ignores keys meanwhile). */
export const editing = () => open;

export async function openScenario(ctx: ScenarioCtx) {
  if (open) return;
  open = true;
  const sv = structuredClone(ctx.snapshot());
  const index = (await json<{ id: string; name: string; kind: string }[]>('locations/index.json')).filter(l => l.kind !== 'region');
  const events = parseEvents(await fetch('./docs/events.md').then(r => r.ok ? r.text() : '').catch(() => ''));
  const style = el('style', { textContent: CSS });
  const body = el('div.sc-body');
  const tabs: [string, () => Promise<Node> | Node][] = [['Place', place], ['Time', time], ['Party', partyTab], ['Events', eventsTab], ['Files', files]];
  const bar = el('div.sc-tabs', {}, ...tabs.map(([name, make], i) => {
    const b = el('button', { type: 'button', textContent: name });
    b.onclick = async () => { bar.querySelectorAll('button').forEach(x => x.classList.remove('on')); b.classList.add('on'); body.replaceChildren(await make()); };
    if (!i) queueMicrotask(() => b.click());
    return b;
  }));
  const status = el('span.sc-status');
  const close = () => { root.remove(); style.remove(); open = false; };
  const applyBtn = el('button.sc-primary', { type: 'button', textContent: 'Apply and play' });
  applyBtn.onclick = async () => {
    try { await ctx.apply(structuredClone(sv)); close(); } catch (e) { status.textContent = String(e); }
  };
  const cancel = el('button', { type: 'button', textContent: 'Cancel' });
  cancel.onclick = close;
  const root = el('div.sc-root', {}, el('div.sc-box', {},
    el('header', {}, el('h2', { textContent: 'Scenario' }), bar), body, el('footer', {}, status, cancel, applyBtn)));
  root.tabIndex = -1;
  root.onkeydown = e => { e.stopPropagation(); if (e.key === 'Escape') close(); };   // keys stay in the editor
  document.head.append(style); document.body.append(root); root.focus();

  // ---- Place: the location and the leader's square, picked on a small map of it ----
  async function place(): Promise<Node> {
    const wrap = el('div');
    const coords = el('span.sc-note');
    const canvas = el('canvas.sc-map');
    const draw = async () => {
      const lv = await Level.load(sv.level.id);
      const s = Math.max(2, Math.min(8, Math.floor(720 / lv.w)));
      canvas.width = lv.w * s; canvas.height = lv.h * s;
      const c = canvas.getContext('2d')!;
      c.imageSmoothingEnabled = false;
      for (let y = 0; y < lv.h; y++) for (let x = 0; x < lv.w; x++) {
        const t = lv.tile(x, y);
        if (t !== 0xff) c.drawImage(lv.tiles, (t % 16) * 16, (t >> 4) * 16, 16, 16, x * s, y * s, s, s);
      }
      c.strokeStyle = '#ff0'; c.lineWidth = 2; c.strokeRect(sv.at.x * s - 2, sv.at.y * s - 2, s + 4, s + 4);
      const ok = lv.walkable(sv.at.x, sv.at.y);
      coords.textContent = `Leader at (${sv.at.x}, ${sv.at.y}): ${lv.tileName(sv.at.x, sv.at.y)}${ok ? '' : ' (not walkable)'}`;
      canvas.onclick = e => {
        const r = canvas.getBoundingClientRect();
        sv.at = { x: Math.floor((e.clientX - r.left) / r.width * lv.w), y: Math.floor((e.clientY - r.top) / r.height * lv.h) };
        void draw();
      };
    };
    const loc = pick(index.map(l => [l.id, `${l.id}  ${l.name.replace(/\s+[MX]$/, '')}`]), sv.level.id, v => {
      sv.level = { id: v }; void draw();
    });
    wrap.append(el('div.sc-row', {}, field('Location', loc), coords),
      el('p.sc-note', { textContent: 'Click the map to place the party (the leader; companions follow in formation). Rooms are entered by walking in.' }),
      el('div.sc-scroll', {}, canvas));
    await draw();
    return wrap;
  }

  // ---- Time ----
  function time(): Node {
    const c = sv.clock;
    return el('div.sc-grid', {},
      field('Hour', num(c.hour, v => c.hour = v, 0, 23)), field('Minute', num(c.minute, v => c.minute = v - v % 5, 0, 55)),
      field('Day', num(c.date, v => c.date = v, 1, 30)),
      field('Month', pick(MONTHS.map((m, i) => [i, m]), c.month, v => c.month = Number(v))),
      field('Weather', pick(ctx.weathers.map((w, i) => [i, w]), c.weather, v => c.weather = Number(v))));
  }

  // ---- Party ----
  function partyTab(): Node {
    const p = sv.party, wrap = el('div');
    let sel = 0;
    const render = () => {
      const list = el('div.sc-members', {}, ...p.members.map((m, i) => {
        const b = el('button', { type: 'button', textContent: m.rec.h_name || `#${m.num}`, className: i === sel ? 'on' : '' });
        b.onclick = () => { sel = i; render(); };
        return b;
      }));
      const free = ctx.companions.filter(r => !p.members.some(m => m.num === r.h_orinum));
      const add = pick([['', 'Add a companion…'], ...free.map(r => [r.h_orinum as number, r.h_name] as [number, string])], '', v => {
        const n = Number(v), cell = [...Array(9).keys()].find(c => !p.members.some(m => m.cell === c));
        if (!v || cell === undefined || p.members.length >= 6) return;
        const rec = structuredClone(p.roster.find(([k]) => k === n)?.[1] ?? ctx.companions[n - 1]);
        p.members.push({ rec, cell, num: n });
        if (!p.away.includes(n)) p.away.push(n);
        sel = p.members.length - 1; render();
      });
      const remove = el('button', { type: 'button', textContent: 'Remove', disabled: sel === 0 });
      remove.onclick = () => {
        const [m] = p.members.splice(sel, 1);
        p.away = p.away.filter(n => n !== m.num);
        p.roster = [...p.roster.filter(([k]) => k !== m.num), [m.num, m.rec]];
        sel = 0; render();
      };
      wrap.replaceChildren(el('div.sc-row', {}, list, add, remove), member(p.members[sel].rec));
    };
    render();
    return wrap;
  }

  function member(r: HeroRecord): Node {
    const R = r as Record<string, unknown> & HeroRecord, n = (k: string, max = 99) => num(R[k] as number, v => R[k] = v, 0, max);
    const conds = el('div.sc-checks', {}, ...COND1.map(([bit, name]) => {
      const c = el('input', { type: 'checkbox', checked: !!((R.h_cond1 as number) & bit) });
      c.onchange = () => R.h_cond1 = c.checked ? (R.h_cond1 as number) | bit : (R.h_cond1 as number) & ~bit;
      return el('label', {}, c, name);
    }));
    return el('div.sc-cols', {},
      el('section', {}, el('h3', { textContent: 'Vitals' }), el('div.sc-grid', {},
        field('HP', n('h_hitpts')), field('Max HP', n('h_hpmax')), field('Energy', n('h_energy')),
        field('Gold', num(r.h_gold, v => r.h_gold = v, 0, 65535)), field('Shield', n('h_shield'))), conds,
        el('h3', { textContent: 'Attributes' }), el('div.sc-grid', {}, ...STATS.map(([k, label]) => field(label, n(k))))),
      el('section', {}, el('h3', { textContent: 'Skills' }), el('div.sc-grid', {}, ...SKILLS.map(([k, label]) => field(label, n(k))))),
      el('section', {}, el('h3', { textContent: 'Pack' }), pack(r)),
      el('section', {}, el('h3', { textContent: 'Spells memorised' }), spells(r)));
  }

  /** `h_invitem`/`h_invamt` (40 slots, 0xFF empty; equipment amounts are 0x80 | wear), `h_inhand` and `h_wears` slots. */
  function pack(r: HeroRecord): Node {
    const wrap = el('div');
    const render = () => {
      const rows = r.h_invitem.map((it, s) => [it, s] as const).filter(([it]) => it !== 0xff).map(([it, s]) => {
        const hand = el('input', { type: 'radio', name: 'sc-hand', checked: r.h_inhand === s, title: 'In hand' });
        hand.onchange = () => { r.h_inhand = s; };
        const worn = el('input', { type: 'checkbox', checked: r.h_wears.includes(s), title: 'Worn' });
        worn.onchange = () => {
          const w = r.h_wears.filter(x => x !== s && x !== 0xff);
          if (worn.checked) w.push(s);
          r.h_wears = [...w, ...Array(6).fill(0xff)].slice(0, 6);
        };
        const del = el('button', { type: 'button', textContent: '×', title: 'Remove' });
        del.onclick = () => {
          r.h_invitem[s] = 0xff; r.h_invamt[s] = 0;
          if (r.h_inhand === s) r.h_inhand = 0xff;
          r.h_wears = r.h_wears.map(x => x === s ? 0xff : x);
          render();
        };
        return el('tr', {}, el('td', { textContent: ctx.items[it] ?? `#${it}` }),
          el('td', {}, num(r.h_invamt[s], v => r.h_invamt[s] = v, 0, 255)), el('td', {}, hand), el('td', {}, worn), el('td', {}, del));
      });
      const add = pick([['', 'Add an item…'], ...ctx.items.map((t, i) => [i, t] as [number, string])], '', v => {
        const s = r.h_invitem.indexOf(0xff);
        if (v === '' || s < 0) return;
        const i = Number(v), have = r.h_invitem.indexOf(i);
        if (have >= 0 && i < 9 || i >= 0x31 && have >= 0) r.h_invamt[have] = Math.min(255, r.h_invamt[have] + 1);
        else { r.h_invitem[s] = i; r.h_invamt[s] = i >= 9 && i <= 0x30 ? 0x80 : 1; }
        render();
      });
      wrap.replaceChildren(el('table.sc-table', {}, el('tr', {}, ...['Item', 'Amount', 'Hand', 'Worn', ''].map(t => el('th', { textContent: t }))), ...rows), add,
        el('p.sc-note', { textContent: 'Equipment amounts are 128 + wear (128 = new). Coins are the Gold field.' }));
    };
    render();
    return wrap;
  }

  function spells(r: HeroRecord): Node {
    return el('div.sc-grid.sc-spells', {}, ...ctx.spells.map((name, i) =>
      field(name, num(r.h_spells[Math.floor(i / 7)][i % 7], v => r.h_spells[Math.floor(i / 7)][i % 7] = v, 0, 99))));
  }

  // ---- Events ----
  function eventsTab(): Node {
    const set = new Set(sv.events), search = el('input', { type: 'search', placeholder: 'Filter by number or text…' });
    const only = el('input', { type: 'checkbox' });
    const list = el('div.sc-events');
    const render = () => {
      const q = search.value.toLowerCase();
      list.replaceChildren(...[...Array(256).keys()].filter(n => {
        const text = (events.get(n) ?? []).join(' ').toLowerCase();
        return (!only.checked || set.has(n)) && (!q || String(n) === q || text.includes(q));
      }).map(n => {
        const c = el('input', { type: 'checkbox', checked: set.has(n) });
        c.onchange = () => { if (c.checked) set.add(n); else set.delete(n); sv.events = [...set].sort((a, b) => a - b); };
        const lines = events.get(n) ?? ['(no references found)'];
        return el('label.sc-event', { title: lines.join('\n') }, c, el('b', { textContent: String(n) }), el('span', { textContent: lines[0] }));
      }));
    };
    search.oninput = render; only.onchange = render;
    render();
    return el('div', {}, el('div.sc-row', {}, search, el('label', {}, only, ' only set')), list);
  }

  // ---- Files: a scenario is a save ----
  function files(): Node {
    const out = el('div.sc-files');
    const download = el('button', { type: 'button', textContent: 'Download scenario…' });
    download.onclick = () => saveFile(sv, 'scenario');
    const upload = el('input', { type: 'file', accept: '.json,application/json' });
    upload.onchange = async () => {
      const f = upload.files?.[0];
      if (!f) return;
      try { Object.assign(sv, JSON.parse(await f.text())); status.textContent = `Loaded ${f.name}; Apply to play it.`; }
      catch (e) { status.textContent = String(e); }
    };
    out.append(el('h3', { textContent: 'File' }), el('div.sc-row', {}, download, field('Load a scenario or save', upload)), el('h3', { textContent: 'Save slots' }));
    for (const n of [1, 2, 3]) {
      const has = ctx.slots.get(n);
      const save = el('button', { type: 'button', textContent: `Store in slot ${n}` });
      save.onclick = () => { status.textContent = ctx.slots.set(n, { ...sv, when: new Date().toISOString() }) ? `Stored in slot ${n}.` : 'This browser refused.'; };
      const load = el('button', { type: 'button', textContent: `Edit slot ${n}`, disabled: !has });
      load.onclick = () => { Object.assign(sv, structuredClone(has)); status.textContent = `Editing slot ${n}; Apply to play it.`; };
      out.append(el('div.sc-row', {}, el('span', { textContent: has ? `${n}: ${has.place}, ${new Date(has.when).toLocaleString()}` : `${n}: empty` }), save, load));
    }
    return out;
  }
}

/** Plain names for the quest milestones (rules/quest_scenes.md), shown before the references. */
const MILESTONES: Record<number, string> = { 34: 'Marked One 1 (Orb)', 35: 'Marked One 2 (Orb)', 36: 'Marked One 3 (Orb)',
  120: 'Jemil found (the egg cracked)', 121: 'Zakhad has appeared', 122: 'Zakhad banished (epilogue next)', 123: 'Orb given to Jemil',
  166: 'The epilogue is over' };

/** docs/events.md: `## n` headings, then `- reference` lines. */
function parseEvents(md: string): Map<number, string[]> {
  const out = new Map<number, string[]>();
  let cur = -1;
  for (const line of md.split('\n')) {
    const h = /^## (\d+)/.exec(line);
    if (h) { cur = Number(h[1]); out.set(cur, MILESTONES[cur] ? [MILESTONES[cur]] : []); }
    else if (cur >= 0 && line.startsWith('- ')) out.get(cur)!.push(line.slice(2));
  }
  return out;
}

/** A save or scenario as a downloaded JSON file. */
export function saveFile(sv: { place?: string }, kind: string) {
  const name = `mc2-${kind}-${(sv.place || 'game').replace(/[^\w]+/g, '-').toLowerCase()}.json`;
  const a = el('a', { href: URL.createObjectURL(new Blob([JSON.stringify(sv)], { type: 'application/json' })), download: name });
  a.click();
  setTimeout(() => URL.revokeObjectURL(a.href), 1000);
}

const CSS = `
.sc-root { position: fixed; inset: 0; background: rgb(0 0 0 / .6); display: grid; place-items: center; z-index: 10; }
.sc-box { width: min(1100px, 96vw); height: min(820px, 94vh); display: flex; flex-direction: column; background: var(--panel, #1d1a16);
  border: 1px solid var(--gold, #a8853c); border-radius: 8px; box-shadow: 0 10px 40px rgb(0 0 0 / .6); }
.sc-box header { display: flex; align-items: center; gap: 16px; padding: 10px 16px; border-bottom: 1px solid #3a3226; }
.sc-box h2 { margin: 0; font: 600 18px var(--title, Georgia, serif); color: var(--gold-hi, #e8c873); }
.sc-box h3 { margin: 12px 0 6px; font: 600 13px system-ui; color: var(--gold-hi, #e8c873); text-transform: uppercase; letter-spacing: .06em; }
.sc-tabs { display: flex; gap: 4px; }
.sc-box button, .sc-box select, .sc-box input { background: #2a251e; color: #eee; border: 1px solid #4a4030; border-radius: 4px; padding: 4px 8px; font: inherit; }
.sc-box button { cursor: pointer; } .sc-box button:hover:not(:disabled) { border-color: var(--gold, #a8853c); }
.sc-box button.on { background: #4a3c22; border-color: var(--gold, #a8853c); }
.sc-box button:disabled { opacity: .4; cursor: default; }
.sc-box .sc-primary { background: #6b5320; border-color: #c9a24d; }
.sc-body { flex: 1; overflow: auto; padding: 12px 16px; }
.sc-box footer { display: flex; gap: 8px; align-items: center; padding: 10px 16px; border-top: 1px solid #3a3226; }
.sc-status { flex: 1; color: #bfb; }
.sc-row { display: flex; gap: 10px; align-items: center; flex-wrap: wrap; margin-bottom: 8px; }
.sc-field { display: flex; flex-direction: column; gap: 2px; font-size: 12px; color: #bbb; }
.sc-field input[type=number] { width: 64px; }
.sc-grid { display: grid; grid-template-columns: repeat(auto-fill, minmax(96px, 1fr)); gap: 6px 10px; }
.sc-spells { grid-template-columns: repeat(auto-fill, minmax(110px, 1fr)); }
.sc-cols { display: grid; grid-template-columns: 1fr 1fr minmax(340px, 1.4fr) 1fr; gap: 16px; }
@media (max-width: 1000px) { .sc-cols { grid-template-columns: 1fr 1fr; } }
.sc-checks { display: flex; flex-wrap: wrap; gap: 4px 12px; margin-top: 8px; font-size: 13px; }
.sc-members { display: flex; gap: 4px; flex-wrap: wrap; }
.sc-table { border-collapse: collapse; margin-bottom: 6px; } .sc-table td, .sc-table th { padding: 2px 6px; text-align: left; font-size: 13px; }
.sc-table input[type=number] { width: 52px; } .sc-table td:first-child { white-space: nowrap; }
.sc-scroll { overflow: auto; max-height: 560px; border: 1px solid #3a3226; }
.sc-map { image-rendering: pixelated; cursor: crosshair; display: block; max-width: none; max-height: none; }
.sc-note { color: #999; font-size: 12px; }
.sc-events { display: grid; grid-template-columns: repeat(auto-fill, minmax(320px, 1fr)); gap: 2px 12px; }
.sc-event { display: flex; gap: 6px; align-items: baseline; font-size: 12px; white-space: nowrap; overflow: hidden; }
.sc-event b { min-width: 2.2em; text-align: right; color: var(--gold-hi, #e8c873); } .sc-event span { overflow: hidden; text-overflow: ellipsis; color: #ccc; }
.sc-files .sc-row span { min-width: 280px; }
`;
