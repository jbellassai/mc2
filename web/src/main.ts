// Milestone 1 (decision 2): walk around Telermain from a fresh start.
import { Level, type Figure } from './level';
import { Clock } from './clock';
import { View } from './view';
import { resolveRoom, BASE_X, BASE_Y } from './room';
import { json, two, type Door, type Exit } from './pack';
import { Talk, format, wmatch } from './talk';
import { Hero, PICK, STATS, SKILLS } from './hero';
import { panel, type Button } from './panel';
import { loadTrade, lot, single, prices, incObj, sellable } from './shop';
import { ServiceRoom, noon, rent, INN } from './service';
import { camp } from './camp';
import { Party, type Member } from './party';
import { World } from './world';
import { Patches, type Patch } from './patch';
import { Fight, type Rec } from './combat';
import { aim as spellAim, BUILT, cost as spellCost, effect } from './spells';
import type { Icon } from './view';

const status = document.getElementById('status')!;
const START = { level: 'D02', x: 97, y: 17 };   // new_game.md: window (93,14) + (4,3), formation cell 0; mutable for ?at=
const NEW_GAME_EVENTS = [10, 88, 117];
const rnd = (n: number) => Math.floor(Math.random() * n);   // RndCo(n): 0 … n−1

async function main() {
  const view = await View.create(document.getElementById('view') as HTMLCanvasElement);
  const [cmd, p02, comtxt, npctypes, items, p93, conds] = await Promise.all(['commands', 'p02text', 'comtxt', 'npctypes',
    'items', 'p93text', 'conds'].map(n => json<string[]>(`${n}.json`)));
  const p97 = await json<{ texts: string[]; events: Record<string, number> }>('p97.json');
  const tables = await json<{ hungerhours: number[]; nousetext: number[]; useall: number[]; lootvalues: number[]; weathers: string[] }>('exetables.json');
  const world = await World.create();
  const p92 = await json<string[]>('p92text.json');
  const patches = await Patches.create();
  const cdata = await Fight.data();
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
  let patch: Patch | null = null;                                        // the mushroom patch the party is in
  let fight: Fight | null = null;                                        // the fight in progress
  let roomStart = { x: 0, y: 0 };                                       // its formation origin (base square)
  let figures: Figure[] = level.figures(clock, events, party.away);
  let message = `${hero.name} has landed in Telermain.`;
  const say = (s: string, other = '') => format(s, hero, other);

  let phase = 0;   // animation step; 300 ms is a guess (the original's timer unit is not traced)
  setInterval(() => { phase++; render(); }, 300);
  const render = () => {
    const room = level.loc.kind === 'room', wild = level.loc.kind === 'world';
    const icons: Icon[] = fight ? fight.recs.filter(r => r.side && fight!.alive(r)).map(r => ({ x: r.x, y: r.y, frame: r.tile, sheet: 'E01' }))
      : wild ? world.guards().map(g => ({ ...g, frame: 0x0f })) : patch?.icons() ?? [];
    const people = fight ? fight.recs.filter(r => !r.side && fight!.alive(r)) : wild ? [lead] : party.members;   // world: the leader alone
    view.draw(level, room ? 5 : lead.x, room ? 4 : lead.y, figures, people, phase, icons);
    const where = wild || patch || fight ? `${world.rec?.name.replace(/\s*[MX]$/, '') ?? ''}, ${tables.weathers[clock.weather]}` : place();
    status.textContent = `${clock}  —  ${where}${message ? '  —  ' + message : ''}`;
  };
  /** School and job D-files have no location name: show the town's. */
  const place = () => (level.loc.name.trim() || outside?.level.loc.name || '').replace(/\s*[MX]$/, '');
  /** To a level with the formation origin at (x, y). */
  const go = (lv: Level, x: number, y: number) => {
    level = lv; party.place(x, y);
    figures = level.figures(clock, events, party.away);
  };
  const close = (msg = '') => { panel.hide(); message = msg; render(); };
  /** The hour tick: who is about, and the inns' noon checkout (P92). */
  const hourly = () => {
    figures = level.figures(clock, events, party.away);
    if (clock.hour === 0 && !(clock.juldate & 7)) patches.regrow();
    party.hunger(tables.hungerhours);
    world.hour(clock);
    // Hirelings' payday (P92 ovl_09ff): 17:00 warning when the week earns under 6, 18:00 settlement; then departures.
    const speak = (m: Member, s: string) => { const t = `${m.hero.name}: ${format(s, m.hero, hero.name)}`; if (panel.open) panel.line(t); else message = t; };
    if (clock.minute === 0 && (clock.hour === 17 || clock.hour === 18))
      for (const [m, att] of party.payday(clock.date, clock.hour === 18)) {
        if (clock.hour === 17 && att < 6) speak(m, p92[0]);
        if (clock.hour === 18 && att < 4) speak(m, p92[1]);
      }
    for (const m of party.members.filter(p => p.hero.rec.h_attitude === 0xff)) party.partyEvents(events, p97.events, m.num, false);
    if (party.departures().length) figures = level.figures(clock, events, party.away);
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
      const rec = await party.record(who.num);
      const join = () => {
        party.add(rec, items, cell, who.x, who.y);
        party.partyEvents(events, p97.events, who.num, true);
        if (!room) party.place(lead.x, lead.y);                       // _NewPXY: town programs only
        figures = level.figures(clock, events, party.away);
        close(`${who.name}: ${comtxt[0x21]}`);                        // "I am honored."
      };
      if (rec.h_relatn === 3 && !events.has(65)) return speak(say(p97.texts[0]));   // the King: `_events+8 & 2`
      if (rec.h_relatn !== 2) return join();
      speak(say(p97.texts[1], who.name));                                   // "…for a fair share… Will %h hire %o?"
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
  /** A town exit with a world-map PGM (program 1): the window goes to (tx, ty), the leader to window + (5,4) (FFSAVB/D). */
  const toWorld = async (exit: Exit) => {
    const pgm = level.loc.pgms[exit.pgm];
    if (pgm?.program !== 1) { message = 'This way leads somewhere not built yet.'; return; }
    go(await Level.load('D01'), exit.tx + 5, exit.ty + 4);
    await world.at(lead.x, lead.y, clock);
    outside = null; service = null; message = '';
  };
  /** A world-map step (P01): a town entrance of the current region (`exitptr`) loads that town with the window at
   *  (tx, ty); features and spots are later milestones; otherwise walkable tiles only. A step costs ticks and energy. */
  const worldStep = async (dx: number, dy: number) => {
    const x = lead.x + dx, y = lead.y + dy, rec = world.rec!;
    const entrance = rec.exits.find(e => e.x === x && e.y === y);
    if (entrance) {
      const pgm = rec.pgms[entrance.pgm];
      if (pgm.program === 2) { go(await Level.load(`D${two(pgm.datafile)}`), entrance.tx + 4, entrance.ty + 3); message = ''; return; }
      message = `${level.tileName(x, y)}: not built yet.`; return;
    }
    const feature = rec.doors.find(d => d.x === x && d.y === y);
    if (feature && rec.pgms[feature.pgm].program === 4) return enterPatch(feature.id, x, y);
    if (feature) { message = `${level.tileName(x, y)}: not built yet.`; return; }
    if (!level.walkable(x, y)) { message = `Blocked by ${level.tileName(x, y)}.`; return; }
    party.shift(dx, dy);
    message = '';
    const ter = level.data.nameindex[level.tile(x, y)];
    for (let n = world.stepTicks(ter, clock, party); n > 0; n--) tick();
    world.fatigue(ter, clock, party);
    await world.at(x, y, clock);
    const guard = world.guards().find(g => g.x === x && g.y === y);
    if (guard) await startFight(guard.group, world.diff(cdata.guarddiff), ter, () => world.cleared.add(guard.bit));
  };

  // ---- combat (rules/combat.md; combat.ts) ----
  /** `%a`/`%b`/`%h`/`%l` filled from `v` (the combat texts name records, not the acting hero). */
  const ctext = (n: number, v: Record<string, string | number> = {}) => comtxt[n].replace(/%([a-z])/g, (_, c: string) => String(v[c] ?? ''));
  let actor: Rec | null = null;
  /** P01 ovl_0846 → _DoACmbt: a wilderness fight on G00 chunk `ter`; `won` runs on victory (e.g. the guard is cleared).
   *  "COMBAT!" (comtxt 0x44), then rounds: the party phase, hero by hero, then the monster phase (P94 ovl_02e8). */
  const startFight = async (group: number, diff: number, ter: number, won: () => void) => {
    outside = { level, x: lead.x, y: lead.y };
    level = await Level.wild(world.patchTileset(ter), ter);
    figures = [];
    fight = Fight.wild(cdata, level, party.members, group, diff);
    if (import.meta.env.DEV) Object.assign(window, { dbg: { fight } });   // for scripts/shot.mjs eval:
    panel.show();
    panel.line(comtxt[0x44]);
    fight.newRound();
    onWin = won; fightDiff = diff;
    partyTurn();
  };
  let onWin = () => {}, fightDiff = 0;
  /** The next hero with actions left acts; when none is left, the monsters' phase. */
  const partyTurn = () => {
    if (finished()) return;
    actor = fight!.recs.find(r => !r.side && fight!.alive(r) && r.moves > 0) ?? null;
    if (!actor) return void monsterPhase();
    message = `${actor.name}: ${actor.moves}`;
    panel.set([{ label: cmd[7], act: aim }, { label: cmd[27], act: magic }, { label: cmd[35], act: recall }, { label: cmd[43], act: fightUse },
      { label: cmd[14], act: drawWeapon }, { label: cmd[30], act: () => { actor!.moves = 0; partyTurn(); } }]);
    render();
  };
  const report = (lines: string[]) => { for (const l of lines) panel.line(l); };
  /** Attack: the enemies in range (adjacent, or in a bow's clear line); choosing one strikes it. */
  const aim = () => {
    const a = actor!, foes = fight!.enemies(a).filter(t => fight!.inRange(a, t));
    if (!foes.length) { panel.line(ctext(0x0d)); return; }                 // "Mark the target."
    panel.set([...foes.map(t => ({ label: `${t.name} (${t.x},${t.y})`, act: () => strike(t) })), { label: cmd[0], act: partyTurn }]);
  };
  const strike = (t: Rec) => { report(fight!.attack(actor!, t, ctext)); partyTurn(); };
  /** Use in combat (P94 `_mnusel` 0x2B → _UseItem for the acting member): the consumables' handlers, synced onto the
   *  combat record (Potion also stands a downed member up; Gonshi gives 4 actions now; Nift 3 charges now); the
   *  instruments play their songs (INT61_1d) and are never used up. One action (assumed). The Horn and Fireglobe
   *  (globe traps, INT61_1f) are not built. */
  const fightUse = () => {
    const a = actor!, h = a.hero!, r = h.rec;
    const codes = [...new Set(r.h_invitem.filter(c => c > 0x30 && c < 0x51 || c === 0x5b))];
    const fmt = (s: string, item: number) => format(s.replace(/%l/g, items[item]), h, h.name);
    const done = () => { a.moves--; partyTurn(); };
    panel.line(comtxt[0x2b]);                                                     // "Select."
    panel.set([...codes.map(item => ({ label: items[item], act: () => {
      if (cdata.songs.instruments.includes(item)) { report(fight!.song(a, item, ctext)); return done(); }
      const down = (r.h_cond1 as number) & 1;
      if (!h.use(item, tables.hungerhours[r.h_race as number])) { panel.line(fmt(comtxt[tables.nousetext[item]], item)); return partyTurn(); }
      h.dec(h.slot(item));
      a.hp = r.h_hitpts;
      if (item === 0x32 && down && !((r.h_cond1 as number) & 8)) {
        r.h_cond1 = (r.h_cond1 as number) & ~1; a.health &= ~1; a.agi = r.h_agility as number; a.dex = r.h_dextrty;
      }
      if (item === 0x35) a.nift = 3;
      if (item === 0x34) a.moves = 4;                                              // then this Use spends one of them
      panel.line(fmt(comtxt[0x38], item));                                        // "%o uses a %l."
      done();
    } })), { label: cmd[0], act: partyTurn }]);
  };
  /** Recall (_RecSpl): ready one of the spells the hero has memorised (`h_spells`, `h_rdyspl`). Takes no action. */
  const recall = () => {
    const r = actor!.hero!.rec, known = r.h_spells.flat().map((n, i) => [n, i]).filter(([n]) => n > 0);
    panel.set([...known.map(([n, i]) => ({ label: `${cdata.spells.names[i]} (${n})`, act: () => {
      r.h_rdyspl = i; partyTurn();
    } })), { label: cmd[0], act: partyTurn }]);
  };
  /** Magic (_Magic in combat, spells.md): the readied spell, if it may be cast in combat (`_splocs` & 16), was not
   *  already cast this encounter (30-35, `_magbits`) and the hero has the energy (`_EneUsg`); then its target, the
   *  effect, the energy, one memorised copy, and a magic skill roll for the SKLSPLS spells. Uses one action. */
  const magic = () => {
    const a = actor!, r = a.hero!.rec, sp = r.h_rdyspl, f = fight!;
    if (sp === 0xff) return void panel.line(ctext(0x40, { h: a.name }));                  // "%h must recall a spell first."
    if (!(cdata.spells.where[sp] & 0x10)) return void panel.line(ctext(0x56, { h: a.name }));   // "%h can't do that here!"
    if (sp >= 30 && sp <= 35 && f.magbits.has(sp)) return void panel.line(comtxt[0x42]);
    const need = spellCost(f, sp, r.h_magic);
    if (r.h_energy < need) return void panel.line(comtxt[0x41]);                          // "Not enough energy!"
    const go = (t: Rec | null) => {
      panel.line(`${a.name}: ${cdata.spells.names[sp]}`);
      report(BUILT.has(sp) ? effect(f, a, sp, t, ctext) : [comtxt[0x119]]);
      r.h_energy -= need; a.hero!.isHeTr();
      const row = Math.floor(sp / 7), col = sp % 7;
      if (--r.h_spells[row][col] <= 0) { r.h_spells[row][col] = 0; r.h_rdyspl = 0xff; }
      if (cdata.spells.skill.includes(sp)) report(f.skillUp(a, 3, ctext));
      if (sp >= 30 && sp <= 35) f.magbits.add(sp);
      a.moves--;
      partyTurn();
    };
    const side = spellAim(f, sp);
    if (!side) return go(null);
    const pool = sp === 40 ? f.recs.filter(t => t.side && (t.state & 0x82) === 0x82 && !(t.state & 8))
      : f.recs.filter(t => (side === 'own' ? t.side === a.side : t.side !== a.side) && f.visible(t));
    panel.set([...pool.map(t => ({ label: `${t.name} (${t.x},${t.y})`, act: () => go(t) })), { label: cmd[0], act: partyTurn }]);
  };
  /** Draw (_DrawWeap): a weapon 9-0x1E from the pack; refused for another race (comtxt 0x103), broken (0x39) or too
   *  heavy (0x69). Takes no action. */
  const drawWeapon = () => {
    const a = actor!, h = a.hero!, r = h.rec;
    const slots = r.h_invitem.map((c, i) => i).filter(i => r.h_invitem[i] >= 9 && r.h_invitem[i] <= 0x1e && i !== r.h_inhand);
    panel.set([...slots.map(i => ({ label: items[r.h_invitem[i]], act: () => {
      const w = cdata.weapons[r.h_invitem[i] - 9];
      if (w.race !== 0xff && w.race !== r.h_race) panel.line(ctext(0x103, { a: items[r.h_invitem[i]] }));
      else if (r.h_invamt[i] >= 0xe4) panel.line(ctext(0x39));
      else if (r.h_strngth < w.minst) panel.line(ctext(0x69, { h: a.name }));
      else { r.h_inhand = i; a.weapon = r.h_invitem[i]; a.wskl = Fight.wpnSkl(h); panel.line(`${a.name}: ${items[a.weapon]}`); }
      partyTurn();
    } })), { label: cmd[0], act: partyTurn }]);
  };
  /** A hero's step (P94 ovl_01ad → _RMove): walking into an enemy attacks it; a step off the arena asks to flee
   *  ("%h is fleeing from combat." "Do you want to leave?", comtxt 0x6C/0x6D — the ids are assumed from their
   *  wording) and Yes takes the hero off the board. (The leader's flight is refused while a companion holds a quest
   *  item, ovl_09a8 → comtxt 0x114 — not modelled.) */
  const fightStep = (dx: number, dy: number) => {
    const a = actor;
    if (!a) return;
    const x = a.x + dx, y = a.y + dy;
    if (x < 0 || y < 0 || x >= fight!.level.w || y >= fight!.level.h) {
      panel.line(ctext(0x6c, { h: a.name }));
      panel.line(comtxt[0x6d]);
      return void panel.set([{ label: cmd[3], act: () => { fight!.remove(a); partyTurn(); } }, { label: cmd[4], act: partyTurn }]);
    }
    const t = fight!.at(a.x + dx, a.y + dy);
    if (t && t.side) return strike(t);
    if (fight!.move(a, dx, dy)) return partyTurn();
    message = `Blocked by ${t?.name ?? level.tileName(a.x + dx, a.y + dy)}.`;
    render();
  };
  const sleep = (ms: number) => new Promise(r => setTimeout(r, ms));
  /** P94 ovl_0b4b: monsters 6-23 in order, each using its actions; then a new round. */
  const monsterPhase = async () => {
    actor = null;
    panel.set([]);
    fight!.endSide(0);
    for (const m of fight!.timestop ? [] : fight!.recs.filter(r => r.side)) {
      while (fight && m.moves > 0 && fight.alive(m) && !fight.outcome()) {
        report(fight.monsterAct(m, ctext));
        render();
        await sleep(200);
      }
    }
    if (finished()) return;
    fight!.endSide(1);
    fight!.newRound();
    partyTurn();
  };
  /** INT61_08: "VICTORY!" (0x4E), or every hero dead: "Alas, your quest has failed." (0x50). Loot (P95) is not built. */
  const finished = (): boolean => {
    const o = fight!.outcome();
    if (!o) return false;
    actor = null; message = '';
    if (o === 2) { panel.line(comtxt[0x50]); panel.set([{ label: cmd[1], act: () => location.reload() }]); return true; }
    if (o === 3) { panel.set([{ label: cmd[0], act: endFight }]); render(); return true; }   // fled: the guard stays
    panel.line(comtxt[0x4e]);
    onWin();
    for (const { hero: h } of party.members) h.rec.h_inuse = (h.rec.h_inuse as number) & ~0xc0;   // P95: Gonshi and Nift end
    // P95 ovl_072d: loot for every slain monster, its value to each hireling's partybucks (ovl_164e, cap 30000).
    const value = fight!.rollLoot(fightDiff, events, tables.lootvalues);
    for (const { hero: h } of party.members)
      if (h.rec.h_relatn === 2) h.rec.h_partybucks = Math.min(30000, (h.rec.h_partybucks as number) + value);
    searchAsk();
    render();
    return true;
  };
  const endFight = () => { level = outside!.level; party.place(outside!.x, outside!.y); outside = null; fight = null; close(); };
  /** P95 ovl_0a06: while a corpse is unsearched, "Would you like to search for valuables?" (comtxt 0xC8); Yes → "Who is
   *  going to search?" (0x10F, a living member) → ovl_0a78. No ends the fight's aftermath. */
  const searchAsk = () => {
    if (!fight!.recs.some(r => r.loot)) return void panel.set([{ label: cmd[0], act: endFight }]);
    panel.line(comtxt[0xc8]);
    const living = fight!.recs.filter(r => !r.side && fight!.alive(r));
    panel.set([{ label: cmd[3], act: () => {
      if (living.length === 1) return search(living[0].hero!);
      panel.line(comtxt[0x10f]);
      panel.set(living.map(r => ({ label: r.name, act: () => search(r.hero!) })));
    } }, { label: cmd[4], act: endFight }]);
  };
  /** P95 ovl_0a78: corpse by corpse, "%h searches a(n) %l" (0xA7, 0xA8/0xA9 for the races at P95 0xCDB) + " and finds
   *  nothing." (0xAA) or " and finds: " (0xAB) and the treasure (_PrtTreasure: "n Item" with "s" for more than one is
   *  assumed); _IncObj gives it (Coins to h_gold, cap 9999). When it refuses (0x32 / 0x33) the search stops there and
   *  the question comes again. */
  const search = (h: Hero) => {
    for (const r of fight!.recs.filter(m => m.loot)) {
      const { item, amount } = r.loot!, worn = amount & 0x80;
      const who = ctext(0xa7, { h: h.name }) + ctext(cdata.loot.an.includes(r.race) ? 0xa9 : 0xa8, { l: r.name });
      if (!amount) { panel.line(who + comtxt[0xaa]); r.loot = undefined; continue; }
      const n = worn ? 1 : amount;
      panel.line(who + comtxt[0xab] + `${n} ${items[item]}${n > 1 ? comtxt[0x51] : ''}`);
      const rec = h.rec, free = rec.h_invitem.indexOf(0xff);
      let ok: boolean;
      if (item === 0) { ok = rec.h_gold + n <= 9999; if (ok) rec.h_gold += n; }
      else { ok = incObj(h, item, n); if (ok && worn) rec.h_invamt[free] = amount; }
      if (!ok) { panel.line(ctext(item === 0 || h.slot(item) >= 0 ? 0x32 : 0x33, { o: h.name })); return searchAsk(); }
      r.loot = undefined;
    }
    panel.set([{ label: cmd[0], act: endFight }]);
  };
  /** P01 ovl_0d01 onto a mushroom-patch feature: the step's time is spent and the window stays where it was, so leaving
   *  the patch returns the party to the square it stepped from. P04 ovl_050f: the formation from (4,3), each member by
   *  _PlacePerson; then the mushrooms (patch.ts). */
  const enterPatch = async (id: number, x: number, y: number) => {
    const ter = level.data.nameindex[level.tile(x, y)];
    for (let n = world.stepTicks(ter, clock, party); n > 0; n--) tick();
    outside = { level, x: lead.x, y: lead.y };
    const lv = await Level.wild(world.patchTileset(ter), ter);
    go(lv, 4, 3);
    const placed: Member[] = [];
    for (const m of party.members) { Object.assign(m, lv.place(m.x, m.y, (a, b) => placed.some(p => p.x === a && p.y === b))); placed.push(m); }
    patch = patches.open(id, lv, party.members);
    message = patch.count ? '' : patches.texts[1];                      // "No more mushrooms are growing here. …"
  };
  /** P04: stepping off the map (_RMove returns 2) asks "Do you want to leave now?" (comtxt 0x23). */
  const leavePatch = () => {
    panel.show();
    panel.line(comtxt[0x23]);
    panel.set([{ label: cmd[3], act: () => { go(outside!.level, outside!.x, outside!.y); outside = null; patch = null; close(); } },
               { label: cmd[4], act: () => close() }]);
  };
  /** P04: stepping onto a mushroom asks "%h may pick %b %as." (D04 text 0); Yes gives `amount` of the patch's kind to
   *  the acting member (_IncObj), and a refusal (comtxt 0x32 / 0x33) leaves it growing. Text 2 after picking is assumed
   *  (P04 ovl_04dd, which prints both, is not decompiled). */
  const pickAt = (x: number, y: number) => {
    const p = patch!, i = p.find(x, y), h = lead.hero;
    if (i < 0) return;
    const vars = { a: items[p.item], b: p.amount };
    panel.show();
    panel.line(format(patches.texts[0], h, h.name, vars));
    panel.set([{ label: cmd[3], act: () => {
      if (!incObj(h, p.item, p.amount)) return close(format(comtxt[h.slot(p.item) >= 0 ? 0x32 : 0x33], h, h.name));
      p.pick(i);
      close(format(patches.texts[2], h, h.name, vars));
    } }, { label: cmd[4], act: () => close() }]);
  };
  const step = async (dx: number, dy: number) => {
    if (level.loc.kind === 'world') { await worldStep(dx, dy); return render(); }
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
      if (patch && (x < 0 || y < 0 || x >= level.w || y >= level.h)) { leavePatch(); return render(); }
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
      if (exit && !mate) { await toWorld(exit); return render(); }
      message = `Blocked by ${mate ? mate.hero.name : level.tileName(x, y)}.`;
      return render();
    }
    for (const m of movers) { m.x += dx; m.y += dy; }
    message = '';
    if (patch) pickAt(lead.x, lead.y);
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
    const member = party.members.find(m => m.hero === who)!;
    panel.set([...(party.members.length > 1 ? party.members.map(m => ({ label: m.hero.name, act: () => sheet(m.hero) })) : []),
               ...(party.members.length > 1 ? [{ label: cmd[42], act: () => transfer(member) }] : []),   // Transfr
               ...(member !== lead ? [{ label: cmd[12], act: () => dismiss(member) }] : []),   // Dismiss
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
  /** Transfr: an item or coins to another member. Assumption: like giving (economy.md), not what is in hand or worn.
   *  Whatever a hireling receives adds lootvalue × count to h_mybucks (FFFAR ovl_2402, cap 30000). */
  const transfer = (from: Member) => {
    const r = from.hero.rec, back = () => sheet(from.hero);
    const give = (to: Member, item: number, slot: number, n: number) => {
      const t = to.hero.rec;
      if (item === 0) { r.h_gold -= n; t.h_gold += n; }
      else if (r.h_invamt[slot] & 0x80) {                                         // equipment keeps its wear byte
        const e = t.h_invitem.indexOf(0xff);
        if (e < 0) { panel.line(say(comtxt[0x20])); return; }
        t.h_invitem[e] = item; t.h_invamt[e] = r.h_invamt[slot]; r.h_invitem[slot] = 0xff; r.h_invamt[slot] = 0;
      } else {
        if (!incObj(to.hero, item, n)) { panel.line(say(comtxt[0x20])); return; }
        for (let k = 0; k < n; k++) from.hero.dec(slot);
      }
      if (t.h_relatn === 2) t.h_mybucks = Math.min(30000, (t.h_mybucks as number) + tables.lootvalues[item] * n);
      back();
      panel.line(`${from.hero.name} → ${to.hero.name}: ${n > 1 || item === 0 ? n + ' ' : ''}${item === 0 ? comtxt[0xb1] : items[item]}`);
    };
    const amount = (to: Member, item: number, slot: number, max: number) => {
      if (max <= 1) return give(to, item, slot, 1);
      panel.set([{ label: cmd[0], act: back }], w => { const n = Number(w); if (Number.isInteger(n) && n > 0 && n <= max) give(to, item, slot, n); }, `1–${max}`);
    };
    const target = (item: number, slot: number, max: number) =>
      panel.set([...party.members.filter(m => m !== from).map(m => ({ label: m.hero.name, act: () => amount(m, item, slot, max) })), { label: cmd[0], act: back }]);
    const slots = r.h_invitem.map((c, i) => i).filter(i => r.h_invitem[i] !== 0xff && r.h_invitem[i] !== 0 && i !== r.h_inhand && !r.h_wears.includes(i));
    panel.set([...(r.h_gold > 0 ? [{ label: `${r.h_gold} ${comtxt[0xb1]}`, act: () => target(0, -1, r.h_gold) }] : []),
               ...slots.map(i => ({ label: items[r.h_invitem[i]], act: () => target(r.h_invitem[i], i, r.h_invamt[i] & 0x80 ? 1 : r.h_invamt[i]) })),
               { label: cmd[0], act: back }]);
  };
  /** Dismiss (P97 ovl_01fd, ovl_02e8). Buzbazgut pleads (text 3); Lady Subia without event 4 says text 4, with it in
   *  `_locspec` 3, 20 or 21 thanks the party with three Emeralds for the leader and sets event 5, elsewhere asks for an
   *  escort (text 5); a plea adds " Dismiss %d anyway?" and Yes dismisses silently. Otherwise the companion leaves with
   *  "Good luck, %h, I'll be seeing you." (comtxt 6). */
  const dismiss = (m: Member) => {
    const name = m.hero.name, num = m.num, locspec = (level.loc.kind === 'room' ? outside?.level.loc : level.loc)?.locnum;
    const fmt = (s: string) => format(s, hero, name).replace(/%d/g, m.hero.female ? 'her' : 'him');
    let thanks = '';
    const go = (farewell: boolean) => {
      party.partyEvents(events, p97.events, num, false);
      party.remove(m);
      figures = level.figures(clock, events, party.away);
      close(farewell ? `${name}: ${thanks}${say(comtxt[6])}` : '');
    };
    panel.show();
    let plea = -1;
    if (num === 0x15) plea = 3;
    else if (num === 0x1d && !events.has(5)) {
      if (!events.has(4)) plea = 4;
      else if ([3, 0x14, 0x15].includes(locspec ?? -1)) {
        thanks = fmt(p97.texts[6]) + ' ';
        incObj(hero, 7, 3); events.add(5);                                     // three Emeralds (item 7) for the leader
      } else plea = 5;
    }
    if (plea < 0) return go(true);
    panel.line(`${name}: ${fmt(p97.texts[plea] + p97.texts[2])}`);
    panel.set([{ label: cmd[3], act: () => go(false) }, { label: cmd[4], act: () => close() }]);
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
    if (fight) { const k = KEYS[e.key]; if (k) { e.preventDefault(); fightStep(...k); } return; }
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
  const [wx, wy] = (q.get('world') ?? '').split(',').map(n => parseInt(n));
  if (import.meta.env.DEV && wx >= 0 && wy >= 0) {             // dev aid: ?world=x,y starts on the world map
    const [x, y] = [wx, wy];
    go(await Level.load('D01'), x, y);
    await world.at(x, y, clock);
    message = '';
  }
  render();
}

main().catch(e => { status.textContent = String(e); console.error(e); });
