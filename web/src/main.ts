// Milestone 1 (decision 2): walk around Telermain from a fresh start.
import { Level, type Figure } from './level';
import { Clock } from './clock';
import { View } from './view';
import { resolveRoom, BASE_X, BASE_Y } from './room';
import { json, type Door, type Exit } from './pack';
import { Talk, format, wmatch } from './talk';
import { Hero, PICK, STATS, SKILLS } from './hero';
import { panel, type Button } from './panel';
import { loadTrade, lot, single, prices, incObj, sellable } from './shop';
import { ServiceRoom, noon, rent, INN } from './service';
import { camp } from './camp';
import { Party } from './party';

const status = document.getElementById('status')!;
const START = { level: 'D02', x: 97, y: 17 };   // new_game.md: window (93,14) + (4,3), formation cell 0; mutable for ?at=
const NEW_GAME_EVENTS = [10, 88, 117];
const rnd = (n: number) => Math.floor(Math.random() * n);   // RndCo(n): 0 … n−1

async function main() {
  const view = await View.create(document.getElementById('view') as HTMLCanvasElement);
  const [cmd, p02, comtxt, npctypes, items, p97, p93, conds] = await Promise.all(['commands', 'p02text', 'comtxt', 'npctypes',
    'items', 'p97text', 'p93text', 'conds'].map(n => json<string[]>(`${n}.json`)));
  const tables = await json<{ hungerhours: number[]; nousetext: number[]; useall: number[] }>('exetables.json');
  const hero = await Hero.profile(0);                        // profile A until character creation exists
  const clock = Clock.newGame();
  // Dev aids: ?hour=20 starts in the evening, ?at=74,25 starts on another square.
  const q = new URLSearchParams(location.search);
  if (import.meta.env.DEV && q.has('hour')) clock.hour = Math.min(23, Math.max(0, Number(q.get('hour')) || 0));
  if (import.meta.env.DEV && q.has('at')) [START.x, START.y] = q.get('at')!.split(',').map(Number);
  const events = new Set(NEW_GAME_EVENTS);
  const party = new Party(hero, START.x, START.y);
  const lead = party.leader;                                 // the acting member (_curpla) is always the leader for now
  let level = await Level.load(START.level);
  let outside: { level: Level; x: number; y: number } | null = null;   // where to return from a room
  let service: ServiceRoom | null = null;                               // the P05 room the party is in
  let roomStart = { x: 0, y: 0 };                                       // its formation origin (base square)
  let figures: Figure[] = level.figures(clock, events, party.away);
  let message = `${hero.name} has landed in Telermain.`;
  const say = (s: string, other = '') => format(s, hero, other);

  let phase = 0;   // animation step; 300 ms is a guess (the original's timer unit is not traced)
  setInterval(() => { phase++; render(); }, 300);
  const render = () => {
    const room = level.loc.kind === 'room';
    view.draw(level, room ? 5 : lead.x, room ? 4 : lead.y, figures, party.members, phase);
    status.textContent = `${clock}  —  ${place()}${message ? '  —  ' + message : ''}`;
  };
  /** School and job D-files have no location name: show the town's. */
  const place = () => (level.loc.name.trim() || outside?.level.loc.name || '').replace(/\s+[MX]$/, '');
  /** To a level with the formation origin at (x, y). */
  const go = (lv: Level, x: number, y: number) => {
    level = lv; party.place(x, y);
    figures = level.figures(clock, events, party.away);
  };
  const close = (msg = '') => { panel.hide(); message = msg; render(); };
  /** The hour tick: who is about, and the inns' noon checkout (P92). */
  const hourly = () => {
    figures = level.figures(clock, events, party.away);
    party.hunger(tables.hungerhours);
    if (clock.hour !== 12 || clock.minute !== 0) return;
    if (!noon().includes(service?.kind === INN ? service.room : -1)) return;
    if (panel.open) panel.line(level.loc.texts[9]); else message = level.loc.texts[9];   // "It's time to check out."
  };
  /** _CalUpd: five minutes; _DecEnergy at minute 0 and 30; the hour tick. */
  const tick = () => {
    const hour = clock.tick();
    if (clock.minute % 30 === 0) party.decEnergy();
    if (hour) hourly();
    render();
  };
  let walkSteps = 0, walkTicks = 0;   // P02: 12 steps = one tick, and every second tick costs 1 energy (ovl_0fca)
  const walked = () => {
    if (++walkSteps < 12) return;
    walkSteps = 0;
    if (++walkTicks & 1) party.walkTired();
    tick();
  };
  const ctx = { hero, clock, cmd, comtxt, items, close, tick };

  // ---- talking (dialogue.md) ----
  const talkTo = async (who: Figure) => {
    const t = await Talk.open(level.loc, who, hero, events);
    const speak = (s: string) => panel.line(`${who.name ? who.name + ': ' : ''}${s}`);
    const end = () => { const bye = t.farewell(); close(bye ? `${who.name}: ${bye}` : ''); };
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
    /** _Invite (EXE 2166:01D6) → P97 ovl_03f7 (rules/npcs.md, Companions). */
    const invite = async () => {
      panel.line(`> ${cmd[23]}`, 'you');
      if (who.num >= 0x20) return speak(comtxt[0x1f]);              // ICANT: "I can't do that." (text read from its name, not traced)
      const room = level.loc.kind === 'room';
      const cell = party.members.length < 6 ? party.freeCell((x, y) => room || level.walkable(x, y) && !figureAt(x, y)) : -1;
      if (cell < 0) return panel.line(comtxt[0x20]);                 // "No room!"
      const rec = await Party.companion(who.num);
      const join = () => {
        party.add(rec, items, cell, who.x, who.y);
        if (!room) party.place(lead.x, lead.y);                       // _NewPXY: town programs only
        figures = level.figures(clock, events, party.away);
        close(`${who.name}: ${comtxt[0x21]}`);                        // "I am honored."
      };
      if (rec.h_relatn === 3 && !events.has(65)) return speak(say(p97[0]));   // the King: `_events+8 & 2`
      if (rec.h_relatn !== 2) return join();
      speak(say(p97[1], who.name));                                   // "…for a fair share… Will %h hire %o?"
      yesNo(() => {                                                   // ovl_0612: settlement every 7 days from hire day −1
        rec.h_partybucks = rec.h_mybucks = 0;
        const pay = rec.h_paydays as number[];
        for (let i = 0, d = clock.date + 29; i < 4; i++, d += 7) pay[i] = d > 30 ? (d -= 30) : d;
        join();
      }, menu);
    };
    const talkButtons = (): Button[] => [
      { label: 'News', act: () => { panel.line('> News', 'you'); speak(t.news() ?? t.ask('').text); } },
      { label: 'Weather', act: () => { panel.line('> Weather', 'you'); speak(t.weather(clock.weather) ?? t.ask('').text); } },
      { label: cmd[23], act: () => void invite() },                     // Invite
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
    outside = { level, x: lead.x, y: lead.y };
    roomStart = ref.start;
    go(await Level.loadRoom(ref), ref.start.x, ref.start.y);
    message = level.loc.name.trim() ? `${hero.name} enters ${level.loc.name}.` : '';   // which of D08/D09's room names applies is not traced
    service = ref.pgm.program === 5 ? await ServiceRoom.open(ctx, ref.room, ref.kind, level.loc.texts, level.loc.words) : null;
    service?.greet();
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

  /** Room exits {x,y,pgm,tx,ty,datafile}: back to town `datafile` with the window at (tx,ty), formation at window + (4,3). */
  const leave = async (exit: Exit) => {
    const id = `D${String(exit.datafile).padStart(2, '0')}`;
    if (exit.datafile !== undefined && exit.datafile !== 255)
      go(outside?.level.id === id ? outside.level : await Level.load(id), exit.tx + 4, exit.ty + 3);
    else if (outside) go(outside.level, outside.x, outside.y);
    outside = null; service = null;
    message = '';
  };

  /** P05 ovl_16a5, bumping the inn's archway at (8,4): from the guest side back to the keeper's base, with rent paid
   *  through to the guest side (base entry 8), otherwise "…only to paying guests" (room text 6). */
  const innArch = () => {
    const k = lead.y < 5 ? 1 : rent[service!.room - 0x40] ? 8 : -1;
    if (k < 0) { message = level.loc.texts[6]; return; }
    party.place(BASE_X[k], BASE_Y[k]);
    message = '';
  };
  const figureAt = (x: number, y: number) => figures.find(f => f.x === x && f.y === y);
  /** A step (rules/locations.md, A step). Town: the whole formation moves, members tested in slot order 5…0, and
   *  one blocked member holds everyone. Rooms: only the acting member moves (_RMove moves `_p1x/_p1y[_curpla]`). */
  const step = async (dx: number, dy: number) => {
    const room = level.loc.kind === 'room';
    const who = figureAt(lead.x + dx, lead.y + dy);
    if (who) {   // walking into someone talks to them (the original uses a Talk command)
      message = '';
      if (!service?.talk()) await talkTo(who);
      return render();
    }
    const movers = room ? [lead] : [...party.members].reverse();
    const unable = movers.find(m => (m.hero.rec.h_cond1 as number) & 0xfc);   // Dead, Paralyzed, Exhausted, Poisoned, Starving
    if (unable) { message = `${unable.hero.name}: ${unable.hero.condition(conds)}.`; return render(); }
    for (const m of movers) {
      const x = m.x + dx, y = m.y + dy;
      const exit = level.loc.exits.find(e => e.x === x && e.y === y);
      const other = figureAt(x, y);
      if (room && exit) {
        if (service) service.leave(() => void leave(exit).then(render)); else await leave(exit);
        return render();
      }
      if (other) { message = `Blocked by ${other.name ?? npctypes[other.type] ?? 'someone'}.`; return render(); }
      const mate = party.at(x, y);                       // in town a mate's square is vacated by the same step
      if (mate ? !room : level.walkable(x, y)) continue;
      const d = level.loc.doors.find(e => e.x === x && e.y === y);
      if (d && !mate) { await door(d); return render(); }
      if (room && service?.kind === INN && x === 8 && y === 4) { innArch(); return render(); }
      message = exit ? 'The way out of town. The world map comes later.' : `Blocked by ${mate ? mate.hero.name : level.tileName(x, y)}.`;
      return render();
    }
    for (const m of movers) { m.x += dx; m.y += dy; }
    message = '';
    walked();
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
  const sheet = (who: Hero = hero) => {
    const r = who.rec;
    const table = (title: string, rows: [string, string][]) => {
      const t = document.createElement('table'); t.className = 'sheet';
      t.createCaption().textContent = title || '\u00a0';
      for (const [k, v] of rows) { const tr = t.insertRow(); tr.insertCell().textContent = k; tr.insertCell().textContent = v; }
      return t;
    };
    const wrap = document.createElement('div'); wrap.className = 'sheets';
    wrap.append(
      table(`${r.h_fullnm}`, [['Condition', who.condition(conds)], ['Hit points', `${r.h_hitpts} / ${r.h_hpmax}`],
                              ['Energy', String(r.h_energy)], ['Coins', String(r.h_gold)],
                              ...STATS.map(([f, l]) => [l, String(r[f])] as [string, string])]),
      table('Skills', SKILLS.map(([f, l]) => [l, String(r[f])] as [string, string])),
      ...chunks(who.pack().map(p => [p.name + (p.worn ? ' (worn)' : p.hand ? ' (in hand)' : ''), p.count] as [string, string]), 12)
        .map((rows, i) => table(i ? '' : 'Pack', rows)));
    panel.show(); panel.add(wrap);
    panel.set([...(party.members.length > 1 ? party.members.map(m => ({ label: m.hero.name, act: () => sheet(m.hero) })) : []),
               { label: cmd[0], act: () => close(message) }]);   // End
  };
  /** Talk + direction: the person there, or "%h talks to" the square (comtxt 0x11). In a service room the keeper
   *  answers whatever square is marked (assumption: how the original routes Talk to `_swgreet = −3` is not traced). */
  const talkAt = async (x: number, y: number) => {
    const who = figures.find(f => f.x === x && f.y === y);
    message = '';
    if (service?.talk()) return;
    if (who) return talkTo(who);
    message = say(comtxt[0x11]) + level.tileName(x, y) + comtxt[0x10];
  };
  /** Camp (C). In a P05 inn room P05 first refuses the keeper's side (acting member at x ≥ 4 and y ≥ 5: comtxt 0x24);
   *  when camp ends with the rent used up, the party goes back to the base square and the keeper speaks (ovl_19b0/167f). */
  const campCmd = () => {
    const inn = service?.kind === INN && service.room < 0x5c ? service.room - 0x40 : -1;
    if (inn >= 0 && lead.x >= 4 && lead.y >= 5) { message = say(comtxt[0x24]); return render(); }
    camp({ party, clock, cmd, p93, items, use: () => useCmd(), tick, rent: () => inn >= 0 ? rent[inn] : null, done: () => {
      close();
      if (inn < 0 || rent[inn]) return;
      party.place(roomStart.x, roomStart.y);
      message = level.loc.texts[9];   // "It's time to check out." (assumption: ovl_167f's text number is not traced)
      render();
    } });
  };
  /** Use (U), _UseItem: the member's items 0x31-0x50 and 0x5B ("Select."). For the consumables (DS:8AE) a party of
   *  2+ is asked "Is this order for everyone?": then each member holding one uses it ("%o uses a %l.") or "%o has no %ls.".
   *  Alone: success "%o uses a %l.", nothing to do → the item's _NoUse text. The original acts as `_curpla`; the port
   *  asks whose pack first. */
  const useCmd = () => {
    const fmt = (s: string, who: Hero, item: number) => format(s.replace(/%l/g, items[item]), who, who.name);
    const usable = (who: Hero) => [...new Set(who.rec.h_invitem.filter(c => c > 0x30 && c < 0x51 || c === 0x5b))];
    const done = (text: string) => { panel.line(text.trim()); panel.set([{ label: cmd[0], act: () => close() }]); };
    const once = (who: Hero, item: number) => {
      const slot = who.slot(item);
      if (!who.use(item, tables.hungerhours[who.rec.h_race as number])) return fmt(comtxt[tables.nousetext[item]], who, item);
      who.dec(slot);
      return fmt(comtxt[0x38], who, item);
    };
    const everyone = (item: number) => party.members.map(({ hero: who }) => {
      const slot = who.slot(item);
      if (slot < 0) return fmt(comtxt[0x3e], who, item);
      who.use(item, tables.hungerhours[who.rec.h_race as number]); who.dec(slot);
      return fmt(comtxt[0x38], who, item);
    }).join(' ');
    const pick = (who: Hero, item: number) => {
      panel.line(`> ${items[item]}`, 'you');
      if (!tables.useall.includes(item) || party.members.length < 2) return done(once(who, item));
      panel.line(say(comtxt[0x3c]));
      panel.set([{ label: cmd[3], act: () => done(everyone(item)) }, { label: cmd[4], act: () => done(once(who, item)) }]);
    };
    const list = (who: Hero) => {
      const codes = usable(who);
      if (!codes.length) return close();                                           // nothing usable: the original just returns
      panel.show();
      panel.line(comtxt[0x2b]);                                                   // "Select."
      panel.set([...codes.map(c => ({ label: items[c], act: () => pick(who, c) })), { label: cmd[0], act: () => close() }]);
    };
    if (party.members.length < 2) return list(hero);
    panel.show();
    panel.set([...party.members.map(m => ({ label: m.hero.name, act: () => list(m.hero) })), { label: cmd[0], act: () => close() }]);
  };
  let looking = false, talking = false;
  view.canvas.addEventListener('click', e => {
    if (panel.open) return;
    const t = view.cellAt(e, level.loc.kind === 'room' ? 5 : lead.x, level.loc.kind === 'room' ? 4 : lead.y);
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
    if (e.key === 'c' || e.key === 'C') { campCmd(); return; }
    if (e.key === 'u' || e.key === 'U') { useCmd(); return; }
    if (e.key === 't' || e.key === 'T') { talking = true; message = say(comtxt[0x0d]); render(); return; }
    const k = KEYS[e.key];
    if (!k) return;
    e.preventDefault();
    if (looking) { looking = false; look(lead.x + k[0], lead.y + k[1]); return; }
    if (talking) { talking = false; void talkAt(lead.x + k[0], lead.y + k[1]).then(render); return; }
    queue = queue.then(() => step(...k)).catch(err => { status.textContent = String(err); console.error(err); });
  });
  render();
}

main().catch(e => { status.textContent = String(e); console.error(e); });
