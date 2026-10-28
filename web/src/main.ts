// Milestone 1 (decision 2): walk around Telermain from a fresh start.
import { Level, type Figure } from './level';
import { Clock } from './clock';
import { View } from './view';
import { resolveRoom } from './room';
import { json, type Door, type Exit } from './pack';
import { Talk, format, wmatch } from './talk';
import { Hero, PICK, STATS, SKILLS } from './hero';
import { panel, type Button } from './panel';
import { loadTrade, lot, single, prices, incObj, sellable } from './shop';

const status = document.getElementById('status')!;
const START = { level: 'D02', x: 98, y: 18 };   // mutable for the ?at= dev aid     // new_game.md: window (93,14), leader at window cell (5,4)
const NEW_GAME_EVENTS = [10, 88, 117];
const rnd = (n: number) => Math.floor(Math.random() * n);   // RndCo(n): 0 … n−1

async function main() {
  const view = await View.create(document.getElementById('view') as HTMLCanvasElement);
  const [cmd, p02, comtxt, npctypes] = await Promise.all([json<string[]>('commands.json'), json<string[]>('p02text.json'),
    json<string[]>('comtxt.json'), json<string[]>('npctypes.json')]);
  const hero = await Hero.profile(0);                        // profile A until character creation exists
  const clock = Clock.newGame();
  // Dev aids: ?hour=20 starts in the evening, ?at=74,25 starts on another square.
  const q = new URLSearchParams(location.search);
  if (import.meta.env.DEV && q.has('hour')) clock.hour = Math.min(23, Math.max(0, Number(q.get('hour')) || 0));
  if (import.meta.env.DEV && q.has('at')) [START.x, START.y] = q.get('at')!.split(',').map(Number);
  const events = new Set(NEW_GAME_EVENTS);
  const pos = { x: START.x, y: START.y, sprite: 0x3b };      // hero 0 = E00 tile 0x3B (_MCCPTile)
  let level = await Level.load(START.level);
  let outside: { level: Level; x: number; y: number } | null = null;   // where to return from a room
  let figures: Figure[] = level.figures(clock, events);
  let message = `${hero.name} has landed in Telermain.`;
  const say = (s: string, other = '') => format(s, hero, other);

  let phase = 0;   // animation step; 300 ms is a guess (the original's timer unit is not traced)
  setInterval(() => { phase++; render(); }, 300);
  const render = () => {
    const room = level.loc.kind === 'room';
    view.draw(level, room ? 5 : pos.x, room ? 4 : pos.y, figures, [pos], phase);
    status.textContent = `${clock}  —  ${level.loc.name.replace(/\s+[MX]$/, '')}${message ? '  —  ' + message : ''}`;
  };
  const go = (lv: Level, x: number, y: number) => {
    level = lv; pos.x = x; pos.y = y;
    figures = level.figures(clock, events);
  };
  const close = (msg = '') => { panel.hide(); message = msg; render(); };

  // ---- talking (dialogue.md) ----
  const talkTo = async (who: Figure) => {
    const t = await Talk.open(level.loc, who, hero, events);
    const speak = (s: string) => panel.line(`${who.name ? who.name + ': ' : ''}${s}`);
    const end = () => { const bye = t.farewell(); close(bye ? `${who.name}: ${bye}` : ''); };
    const items = await json<string[]>('items.json');
    await loadTrade();
    const coins = (n: number) => `${n} ${comtxt[0xb1]}`;
    const pouch = (item: number) => lot(item) > 1 ? comtxt[0xb2].replace('%b', String(lot(item))) : '';
    const fill = (s: string, n: number) => say(s.replace('%i', String(n)), who.name);
    const yesNo = (yes: () => void, no: () => void) => panel.set([{ label: cmd[3], act: yes }, { label: cmd[4], act: no }]);
    // The order the original assembles these common texts in is not traced; this follows the economy.md flow.
    const ask = (q: string, max: number, then: (n: number) => void) => {
      speak(say(q, who.name));
      panel.set([{ label: cmd[0], act: menu }], w => {
        const n = Number(w);
        panel.line(`> ${w}`, 'you');
        if (!Number.isInteger(n) || n < 0 || n > max) return ask(q, max, then);
        if (n === 0) return menu();
        then(n);
      }, `0–${max}`);
    };
    const buy = () => {
      speak(say(comtxt[0xac].trim(), who.name));
      panel.set([...t.shop.map(s => ({ label: `${items[s.item]} — ${coins(prices(s, hero.rec.h_trade as number, t.skill).charges)}${pouch(s.item)}`,
        act: () => buyOne(s) })), { label: cmd[0], act: menu }]);
    };
    const buyOne = (s: { item: number; pays: number; charges: number }) => {
      const each = prices(s, hero.rec.h_trade as number, t.skill).charges, n = lot(s.item);
      panel.line(`> ${items[s.item]}`, 'you');
      speak(comtxt[0xb0] + coins(each) + pouch(s.item) + '.');
      const deal = (count: number) => {
        if (n * count >= 100) { speak(comtxt[0xbf]); return menu(); }
        const total = each * count;
        speak(fill(comtxt[0xc0], total) + comtxt[0xc4]);
        yesNo(() => {
          if (hero.rec.h_gold < total) speak(say(comtxt[0x25]));                   // "%h doesn't have that much!"
          else if (incObj(hero, s.item, n * count)) { hero.rec.h_gold -= total; speak(say(comtxt[0xc1])); }
          menu();
        }, () => { speak(comtxt[0xc2]); menu(); });
      };
      if (single(s.item)) { speak(comtxt[0xb3].trim() + ' ' + comtxt[0xb4] + comtxt[0xb7]); yesNo(() => deal(1), () => { speak(comtxt[0xc2]); menu(); }); }
      else ask(comtxt[0xb6].trim() + ' ' + comtxt[0xb4] + comtxt[0xbe], 99, deal);
    };
    const sell = () => {
      if (t.nobuy) { speak(comtxt[0xc7].trim()); return menu(); }
      const wanted = t.shop.filter(s => sellable(hero, s.item).length);
      if (!wanted.length) { speak(say(comtxt[0xb8], who.name)); return menu(); }
      speak(comtxt[0xbd].trim());
      panel.set([...wanted.map(s => ({ label: `${items[s.item]} — ${coins(prices(s, hero.rec.h_trade as number, t.skill).pays)}${pouch(s.item)}`,
        act: () => sellOne(s) })), { label: cmd[0], act: menu }]);
    };
    const sellOne = (s: { item: number; pays: number; charges: number }) => {
      const each = prices(s, hero.rec.h_trade as number, t.skill).pays, n = lot(s.item), slots = sellable(hero, s.item);
      const have = single(s.item) && s.item <= 0x30 ? slots.length : hero.rec.h_invamt[slots[0]];
      const max = Math.floor(have / n);
      panel.line(`> ${items[s.item]}`, 'you');
      if (!max) { speak(say(comtxt[0xb8], who.name)); return menu(); }
      const deal = (count: number) => {
        const total = each * count;
        speak(comtxt[0xc3] + coins(total) + '.' + comtxt[0xc5]);
        yesNo(() => {
          hero.rec.h_gold += total;
          for (let k = 0; k < n * count; k++) hero.dec(sellable(hero, s.item)[0]);
          speak(say(comtxt[0xc1])); menu();
        }, () => { speak(comtxt[0xc2]); menu(); });
      };
      speak(comtxt[0xc3] + coins(each) + pouch(s.item) + '.');
      if (max === 1) deal(1); else ask(comtxt[0xb6].trim() + ' ' + comtxt[0xb5] + comtxt[0xbe], max, deal);
    };
    const talkButtons = (): Button[] => [
      { label: 'News', act: () => { panel.line('> News', 'you'); speak(t.news() ?? t.ask('').text); } },
      { label: 'Weather', act: () => { panel.line('> Weather', 'you'); speak(t.weather(clock.weather) ?? t.ask('').text); } },
      ...(t.shop.length ? [{ label: cmd[9], act: buy }, { label: comtxt[0x17b], act: sell }] : []),   // Buy, Sell
      { label: cmd[0], act: end }];
    function menu() {
      panel.set(talkButtons(), word => {
        panel.line(`> ${word}`, 'you');
        const r = t.ask(word);
        if (r.end) end(); else speak(r.text);
      }, 'Ask about… (type a word, Enter)');
    }
    panel.show();
    speak(t.greeting());
    menu();
  };

  // ---- doors (rules/locations.md, Towns; P02 ovl_196b) ----
  const enterRoom = async (door: Door) => {
    const ref = await resolveRoom(door, level.loc.pgms[door.pgm]);
    if (!ref) return void (message = 'This door leads somewhere not built yet.');
    outside = { level, x: pos.x, y: pos.y };
    go(await Level.loadRoom(ref), ref.start.x, ref.start.y);
    message = `${hero.name} enters ${level.loc.name}.`;
  };

  const lockedDoor = (door: Door) => {
    const r = level.loc.residents[door.id];
    const doorstn = level.loc.doorstn;
    panel.show();
    panel.line(p02[0]);                                               // "The door is locked."
    const done = (text: string) => { panel.line(say(text)); menu(); };
    const goIn = async (...texts: string[]) => { close(); message = texts.map(t => say(t)).join(''); await enterRoom(door); render(); };
    const yesNo = (text: string) => {
      panel.line(say(text));
      panel.set([{ label: cmd[3], act: () => void goIn() }, { label: cmd[4], act: menu }]);   // Yes / No
    };
    const knock = () => {
      // Sound 0x11. Home = resident's hours (_TimCalc), not removed (_npcsta), RESID event conditions.
      const home = r && r.num !== 0xfe && clock.within(r.appear, r.disappear) &&
                   (!r.ifevent || events.has(r.ifevent)) && (!r.ifnevent || !events.has(r.ifnevent));
      if (!home) return done(p02[1]);                                 // "There is no response."
      panel.line(say(p02[2]));                                        // "Whom do you seek?"
      panel.set([{ label: cmd[0], act: menu }], word => {
        panel.line(`> ${word}`, 'you');
        if (wmatch(word, level.loc.words) === r.name) yesNo(p02[4]);  // "That's me! Would you like to come in?"
        else done(p02[3]);                                            // "There is no one here by that name."
      }, 'Whom do you seek?');
    };
    const pick = () => {
      if (doorstn === 0xff) return done(p02[6]);                      // "%h resists the urge …"
      const s = hero.slot(PICK);
      if (s < 0) return done(p02[11]);                                // "%h needs a lockpick to do that."
      if (Math.min(99, (hero.rec.h_dextrty >> 1) + hero.rec.h_lockpck) < rnd(100)) {
        hero.dec(s); return done(comtxt[0x90]);                       // the pick breaks (text inferred: ovl_100b)
      }
      void goIn(p02[7], p02[9]);                                      // "The lock clicks open!" " The party goes inside."
    };
    const breakIn = () => {
      if (doorstn === 0xff || doorstn >= hero.rec.h_strngth) return done(doorstn === 0xff ? p02[6] : p02[10]);
      void goIn(p02[8], p02[9]);                                      // "%h breaks open the door!"
    };
    function menu() {
      panel.set([{ label: cmd[26], act: knock }, { label: cmd[31], act: pick }, { label: cmd[8], act: breakIn },
                 { label: cmd[0], act: () => close() }]);             // Knock, Pick, Break, End
    }
    menu();
  };

  const door = async (d: Door) => {
    if (d.type & 0x80) return void (message = 'The door is magically locked.');   // key doors: rules/locations.md, Keys
    if (d.type === 0 || d.type === 3) return enterRoom(d);
    lockedDoor(d);
  };

  /** Room exits {x,y,pgm,tx,ty,datafile}: back to town `datafile` with the window at (tx,ty), leader at cell (5,4). */
  const leave = async (exit: Exit) => {
    const id = `D${String(exit.datafile).padStart(2, '0')}`;
    if (exit.datafile !== undefined && exit.datafile !== 255)
      go(outside?.level.id === id ? outside.level : await Level.load(id), exit.tx + 5, exit.ty + 4);
    else if (outside) go(outside.level, outside.x, outside.y);
    outside = null;
    message = '';
  };

  const step = async (dx: number, dy: number) => {
    const x = pos.x + dx, y = pos.y + dy;
    const who = figures.find(f => f.x === x && f.y === y);
    const d = level.loc.doors.find(e => e.x === x && e.y === y);
    const exit = level.loc.exits.find(e => e.x === x && e.y === y);
    const room = level.loc.kind === 'room';
    if (who) { message = ''; await talkTo(who); }   // walking into someone talks to them (the original uses a Talk command)
    else if (level.walkable(x, y) && !(room && exit)) {
      pos.x = x; pos.y = y;
      message = '';
      if (clock.step()) figures = level.figures(clock, events);
    } else if (exit && room) await leave(exit);
    else if (d) await door(d);
    else if (exit) message = 'The way out of town. The world map comes later.';
    else message = `Blocked by ${level.tileName(x, y)}.`;
    render();
  };

  /** _Look (rules/locations.md, Look). Line of sight is not modelled yet: every square counts as visible. */
  const look = (x: number, y: number) => {
    let what: string;
    const who = figures.find(f => f.x === x && f.y === y);
    if (who && who.num < 0x20 && who.name) what = who.name;
    else if (who) {
      const t = npctypes[who.type] ?? '';
      what = comtxt[/^[aeiou]/i.test(t) ? 0x0f : 0x0e] + t;
    } else what = level.tileName(x, y);
    let text = say(comtxt[0x08]) + what + comtxt[0x10];
    const spot = (level.loc.look ?? []).find(l => l.x === x && l.y === y);
    if (spot && (!(spot.text & 0x80) || (who && who.num >= 0x20))) text += say(level.loc.texts[spot.text & 0x7f] ?? '');
    message = text;
    render();
  };
  const chunks = <T,>(a: T[], n: number) => Array.from({ length: Math.ceil(a.length / n) }, (_, i) => a.slice(i * n, i * n + n));
  /** Character sheet (the original's Inven): attributes, skills, coins, pack. */
  const sheet = () => {
    const r = hero.rec;
    const table = (title: string, rows: [string, string][]) => {
      const t = document.createElement('table'); t.className = 'sheet';
      t.createCaption().textContent = title || '\u00a0';
      for (const [k, v] of rows) { const tr = t.insertRow(); tr.insertCell().textContent = k; tr.insertCell().textContent = v; }
      return t;
    };
    const wrap = document.createElement('div'); wrap.className = 'sheets';
    wrap.append(
      table(`${r.h_fullnm}`, [['Hit points', `${r.h_hitpts} / ${r.h_hpmax}`], ['Energy', String(r.h_energy)], ['Coins', String(r.h_gold)],
                              ...STATS.map(([f, l]) => [l, String(r[f])] as [string, string])]),
      table('Skills', SKILLS.map(([f, l]) => [l, String(r[f])] as [string, string])),
      ...chunks(hero.pack().map(p => [p.name + (p.worn ? ' (worn)' : p.hand ? ' (in hand)' : ''), p.count] as [string, string]), 12)
        .map((rows, i) => table(i ? '' : 'Pack', rows)));
    panel.show(); panel.add(wrap);
    panel.set([{ label: cmd[0], act: () => close(message) }]);   // End
  };
  let looking = false;
  view.canvas.addEventListener('click', e => {
    if (panel.open) return;
    const t = view.cellAt(e, level.loc.kind === 'room' ? 5 : pos.x, level.loc.kind === 'room' ? 4 : pos.y);
    look(t.x, t.y);
  });

  const KEYS: Record<string, [number, number]> = {
    ArrowUp: [0, -1], ArrowDown: [0, 1], ArrowLeft: [-1, 0], ArrowRight: [1, 0],
    w: [0, -1], s: [0, 1], a: [-1, 0], d: [1, 0],
  };
  let queue = Promise.resolve();   // steps run in order; keys pressed while a room loads are not lost
  addEventListener('keydown', e => {
    if (panel.open) return;
    if (e.key === 'i' || e.key === 'I') { sheet(); return; }
    if (e.key === 'l' || e.key === 'L') { looking = true; message = say(comtxt[0x0d]); render(); return; }   // "Mark the target."
    const k = KEYS[e.key];
    if (!k) return;
    e.preventDefault();
    if (looking) { looking = false; look(pos.x + k[0], pos.y + k[1]); return; }
    queue = queue.then(() => step(...k)).catch(err => { status.textContent = String(err); console.error(err); });
  });
  render();
}

main().catch(e => { status.textContent = String(e); console.error(e); });
