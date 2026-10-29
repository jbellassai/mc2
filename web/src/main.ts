// Milestone 1 (decision 2): walk around Telermain from a fresh start.
import { Level, type Figure } from './level';
import { Clock } from './clock';
import { View } from './view';
import { resolveRoom, BASE_X, BASE_Y } from './room';
import { json, hex, two, type Door, type Exit } from './pack';
import { Talk, format, wmatch } from './talk';
import { Hero, PICK, STATS, SKILLS, type HeroRecord } from './hero';
import { Assignments, JAILED } from './assign';
import { panel, type Button } from './panel';
import { loadTrade, lot, single, prices, incObj, sellable } from './shop';
import { ServiceRoom, noon, rent, INN, SCHOOL, JOB, LODGE } from './service';
import { Special, casino, refill, gates } from './special';
import { Scene, sceneBase } from './scene';
import { camp, OPEN, SHIP, DUNGEON, INNROOM, GUEST } from './camp';
import { Party, type Member } from './party';
import { World } from './world';
import { Patches, type Patch } from './patch';
import { Fight, type Rec } from './combat';
import { Chamber } from './chamber';
import { newGame, landed } from './newgame';
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
  const tables = await json<{ hungerhours: number[]; nousetext: number[]; useall: number[]; lootvalues: number[]; weathers: string[]; attribs: string[];
    tod: { words: string[]; hour: number[] }; speltim: number[] }>('exetables.json');
  const p93tables = await json<{ hunt: { terrain: number[]; weather: number[] } }>('p93.json');
  const v02 = await json<{ vision: { ids: number[]; texts: number[] }; sense: number[] }>('v02.json');
  const p89 = await json<{ tiers: number[]; x0: number[]; y0: number[]; x1: number[]; y1: number[]; rects: number[][] }>('p89.json');
  const world = await World.create();
  const p92 = await json<string[]>('p92text.json');
  const patches = await Patches.create();
  const cdata = await Fight.data();
  const assigns = await Assignments.create();
  const r90 = await json<HeroRecord[]>('companions.json');   // the companions' starting records (names, Recall)
  // Dev aids: ?hour=20 starts in the evening, ?at=74,25 starts on another square; any of them skips the new-game
  // screens (?profile=0-4 picks the hero).
  const q = new URLSearchParams(location.search);
  const dev = import.meta.env.DEV && ['at', 'world', 'level', 'hour', 'profile'].some(k => q.has(k));
  const savedSlots = Array.from({ length: 3 }, (_, i) => i + 1).flatMap(n => {
    try { const sv = JSON.parse(localStorage.getItem(`mc2.save.${n}`) ?? 'null'); return sv ? [{ slot: n, label: `${sv.place}, ${new Date(sv.when).toLocaleString()}` }] : []; }
    catch { return []; }
  });
  const start = dev ? { hero: await Hero.profile(Math.min(4, Math.max(0, Number(q.get('profile')) || 0))) }
    : await newGame(savedSlots, await json<string[]>('commands.json'));
  const hero = 'hero' in start ? start.hero : await Hero.profile(0);   // a continued game replaces it on restore
  panel.hide();
  const clock = Clock.newGame();
  if (import.meta.env.DEV && q.has('hour')) clock.hour = Math.min(23, Math.max(0, Number(q.get('hour')) || 0));
  if (import.meta.env.DEV && q.has('at')) [START.x, START.y] = q.get('at')!.split(',').map(Number);
  if (import.meta.env.DEV && /^D\d\d$/.test(q.get('level') ?? '')) START.level = q.get('level')!;   // ?level=D23
  const events = new Set(NEW_GAME_EVENTS);
  const party = new Party(hero, START.x, START.y);
  const lead = party.leader;                                 // the acting member (_curpla) is always the leader for now
  if (import.meta.env.DEV) Object.assign(window, { dbg: { party, world } });   // for scripts/shot.mjs eval:
  let level = await Level.load(START.level);
  let outside: { level: Level; x: number; y: number } | null = null;   // where to return from a room
  let service: ServiceRoom | null = null;                               // the P05 room the party is in
  let special: Special | null = null;                                   // the P09 room the party is in
  let scene: Scene | null = null;                                       // the P08 room the party is in
  const scroll = { item: 0 };                                           // `_scrollonfloor` (P08, saved)
  let disasterday = 0;                                                  // `_disasterday` (White Scroll; 0 = none)
  let speaker: Member | null = null;                                    // who talks next (P08 rooms ask)
  let lastStep = { dx: 0, dy: -1 };                                     // `_lastdir`: the last step, for P08 placement
  let patch: Patch | null = null;                                        // the mushroom patch the party is in
  let fight: Fight | null = null;                                        // the fight in progress
  let roomStart = { x: 0, y: 0 };                                       // its formation origin (base square)
  let roomAt = { loc: 0, room: 0xff };                                  // `_locspec`/`_currm` while in a room
  let wildAt = { x: 29, y: 56 };                                        // `_wildxy` while off the world map (new game)
  let been = 0x8000;                                                    // `_beenflg`: strongholds entered, bit 15 = entry 0
  let figures: Figure[] = level.figures(clock, events, party.away);
  let message = await landed(hero);
  const say = (s: string, other = '') => format(s, hero, other);

  let phase = 0;   // animation step; 300 ms is a guess (the original's timer unit is not traced)
  setInterval(() => { phase++; render(); }, 300);
  /** P01 ovl_076c: guard posts and patrols are drawn only while event 105 is set or a Locate spell lasts (patrols next
   *  to the party are seen anyway, ovl_0a94). */
  let detect = 0, walkwater = 0;   // `_detectsw` (5-minute ticks left, saved), `_wlkwcount` (steps left; P02 zeroes it)
  let sensed = '';                  // P02 cs:0x133: the ambush spot the last Sense pointed at ("x,y")
  const snakes: [string, number, number, number][] = [];   // `_snakes`/`_snakelocs`: barriers Pierce/Repel removed
  let locate = 0;   // P01 OV_0x1bb: world-map draws left in which a Locate spell shows every patrol and guard post
  const seeAll = () => events.has(105) || locate > 0;
  const render = () => {
    const room = level.loc.kind === 'room', wild = level.loc.kind === 'world';
    const icons: Icon[] = fight ? fight.recs.filter(r => r.side && fight!.alive(r)).map(r => ({ x: r.x, y: r.y, frame: r.tile, sheet: 'E01' }))
      : wild ? [...(seeAll() ? world.guards() : []), ...world.patrols(lead.x, lead.y, seeAll())].map(g => ({ x: g.x, y: g.y, frame: 0x0f }))
          .concat(world.ships.boats().map(b => ({ ...b, frame: 0x12 })))
      : patch?.icons() ?? (detect && level.loc.kind === 'level'   // V02 INT60_0d: Detect shows the teleportal spots
        ? (level.loc.spots ?? []).filter(p => p.type === 1).map(p => ({ x: p.x, y: p.y, frame: 10 + (phase & 1) })) : []);
    const people = fight ? fight.recs.filter(r => !r.side && fight!.alive(r)) : wild ? [lead] : party.members;   // world: the leader alone
    view.draw(level, room ? 5 : lead.x, room ? 4 : lead.y, figures, people, phase, icons);
    const where = wild || patch || (fight && outside?.level.loc.kind === 'world') ? `${world.rec?.name.replace(/\s*[MX]$/, '') ?? ''}, ${tables.weathers[clock.weather]}` : place();
    status.textContent = `${clock}  —  ${where}${message ? '  —  ' + message : ''}`;
  };
  /** School and job D-files have no location name: show the town's (the region's, from the world map). */
  const place = () => (level.loc.name.trim() || (outside?.level.loc.kind === 'world' ? world.rec?.name : outside?.level.loc.name)
    || chamberBack?.level.loc.name || '').replace(/\s*[MX]$/, '').trim();
  /** To a level with the formation origin at (x, y). */
  const go = (lv: Level, x: number, y: number) => {
    if (level.loc.kind === 'world' && lv.loc.kind !== 'world') wildAt = { x: lead.x, y: lead.y };
    level = lv; party.place(x, y);
    if (lv.loc.kind === 'level') { walkwater = 0; sensed = ''; }        // P02 start; INT60_14 puts the removed barriers back
    for (const [id, x1, y1, t] of snakes) if (id === lv.id) lv.set(x1, y1, t);
    figures = people();
  };
  const close = (msg = '') => { panel.hide(); message = msg; render(); };
  const wildxy = () => level.loc.kind === 'world' ? { x: lead.x, y: lead.y } : wildAt;
  /** `_locspec`, `_currm` and `_hroomrec` as _AssignedHere reads them. */
  const spot = () => chamber ? { loc: chamberBack!.level.loc.locnum, room: 0xff, hroom: chamber.hr.id }
    : level.loc.kind === 'room' ? { ...roomAt, hroom: 0xff } : { loc: level.loc.locnum, room: 0xff, hroom: 0xff };
  /** Who stands about: the location's people and the companions on assignment here (not drawn on the world map). */
  const people = (): Figure[] => {
    if (level.loc.kind === 'world') return level.figures(clock, events, party.away);
    const at = spot();
    return [...level.figures(clock, events, party.away), ...(chamber?.freed ? [chamber.freed] : []), ...assigns.here(at.loc, at.room, at.hroom)
      .map(a => ({ x: a.as_x, y: a.as_y, type: 0, tile: a.as_tile, num: a.as_npc, name: r90[a.as_npc - 1].h_name }))];
  };
  /** The hour tick: who is about, and the inns' noon checkout (P92). */
  const hourly = () => {
    figures = people();
    if (clock.hour === 0 && !(clock.juldate & 7)) patches.regrow();
    if (clock.hour === 0 && clock.date === 1) refill();                 // new month: the casino banks (P92 ovl_02ac)
    if (clock.hour === 0) {                                             // P92 ovl_01cd, the new day's events
      if (disasterday && clock.juldate - disasterday === 7) events.add(1);   // the White Scroll's disaster
      if (clock.juldate === 20) events.add(114);
      if (clock.date === 1 && clock.month === 9) events.add(27);       // month 9 begins (Ziyx's Book of Emenad)
    }
    if (clock.hour === 0 && world.ships.daily()) for (const m of party.members) m.hero.rec.h_gold = 0;   // Amos (P92 ovl_0447)
    party.hunger(tables.hungerhours);
    world.hour(clock);
    const lrnTim = (sp: number, h: HeroRecord) => Math.max(2, tables.speltim[sp] - (h.h_intellg as number));   // _LrnTim
    for (const n of assigns.daily(clock, n => party.kept(n, r90[n - 1]), lrnTim)) party.away.delete(n);   // quit: home
    // Hirelings' payday (P92 ovl_09ff): 17:00 warning when the week earns under 6, 18:00 settlement; then departures.
    const speak = (m: Member, s: string) => { const t = `${m.hero.name}: ${format(s, m.hero, hero.name)}`; if (panel.open) panel.line(t); else message = t; };
    if (clock.minute === 0 && (clock.hour === 17 || clock.hour === 18))
      for (const [m, att] of party.payday(clock.date, clock.hour === 18)) {
        if (clock.hour === 17 && att < 6) speak(m, p92[0]);
        if (clock.hour === 18 && att < 4) speak(m, p92[1]);
      }
    for (const m of party.members.filter(p => p.hero.rec.h_attitude === 0xff)) party.partyEvents(events, p97.events, m.num, false);
    if (party.departures().length) figures = people();
    if (clock.hour !== 12 || clock.minute !== 0) return;
    if (!noon().includes(service?.kind === INN ? service.room : -1)) return;
    if (panel.open) panel.line(level.loc.texts[9]); else message = level.loc.texts[9];   // "It's time to check out."
  };
  /** _CalUpd: five minutes; _DecEnergy at minute 0 and 30; the hour tick. */
  const tick = () => {
    const hour = clock.tick();
    if (detect) detect--;                                                // _DecSpells: Detect runs out
    for (const { hero: h } of party.members)                            // _DecSpells: Glamour wears off with charm
      if ((h.rec.h_glamcnt as number) > 0) { h.rec.h_glamcnt = (h.rec.h_glamcnt as number) - 1; h.rec.h_charm = (h.rec.h_charm as number) - 1; }
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
  const ctx = { hero, clock, cmd, comtxt, items, close, tick, members: () => party.members.map(m => m.hero),
    assigned: (room: number) => assigns.here(spot().loc, room, 0xff).length > 0 };
  /** Talk in a service room reaches the keeper; with company the port asks who speaks (the acting member, `_curpla`,
   *  who pays and is taught). */
  const keeper = (): boolean => {
    if (!service?.talks) return false;
    if (party.members.length < 2) return service.talk();
    panel.show(); panel.line('Who speaks?');
    panel.set([...party.members.map(m => ({ label: m.hero.name, act: () => void service!.talk(false, m.hero) })), { label: cmd[0], act: () => close() }]);
    return true;
  };

  // ---- talking (dialogue.md) ----
  const talkTo = async (who: Figure) => {
    const elden = chamber?.says(who);
    if (elden) { panel.show(); panel.line(`${who.name}: ${elden}`); return void panel.set([{ label: cmd[0], act: () => close() }]); }
    if (scene && party.members.length > 1 && !speaker) {                // P08 scenes care who speaks (`_curpla`)
      panel.show(); panel.line(say(comtxt[0x11]).trim());
      return void panel.set([...party.members.map(m => ({ label: m.hero.name, act: () => { speaker = m; void talkTo(who); } })),
        { label: cmd[0], act: () => close() }]);
    }
    const by = speaker ?? party.members[0];
    speaker = null;
    const opening = scene?.greet(who, by);
    if (opening?.leave) { await leave(level.loc.exits[0]); message = opening.text; return render(); }   // the priest sends the party out
    const t = await Talk.open(level.loc, who, by.hero, events);
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
        const a = assigns.take(who.num), t = a?.as_task ?? 0xff;          // P97: the record folds back in (ovl_0511)
        if (a) Object.assign(rec, { h_gold: (rec.h_gold as number) + a.as_gold }, t >= 10 && t < 0x28
          ? { h_actvty: t, h_actmisc: a.as_misc, h_actdate: a.as_date, h_acthour: a.as_hour, h_actroom: spot().room, h_actdays: a.as_daysleft }
          : { h_actvty: 0xff });
        party.partyEvents(events, p97.events, who.num, true);
        if (!room) party.place(lead.x, lead.y);                       // _NewPXY: town programs only
        figures = people();
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
    if (opening) panel.line(opening.text); else speak(t.greeting());
    menu();
  };

  // ---- doors (rules/locations.md, Towns; P02 ovl_196b) ----
  const enterRoom = async (door: Door, pgms = level.loc.pgms, locspec = level.loc.locnum) => {
    const ref = await resolveRoom(door, pgms[door.pgm]);
    if (!ref) return void (message = 'This door leads somewhere not built yet.');
    outside = { level, x: lead.x, y: lead.y };
    const lv = await Level.loadRoom(ref);
    roomStart = ref.pgm.program === 8 ? await sceneBase(lv.loc.exits, lastStep.dx, lastStep.dy) : ref.start;
    roomAt = { loc: locspec, room: ref.room };
    if (ref.pgm.program === 5 && ref.room >= 0x5c && ref.room < 0x6c) been |= 0x8000 >> ref.room - 0x5c;   // a stronghold
    go(lv, roomStart.x, roomStart.y);
    message = level.loc.name.trim() ? `${hero.name} enters ${level.loc.name}.` : '';   // which of D08/D09's room names applies is not traced
    scene = ref.pgm.program === 8 ? await Scene.open({ party, events, items, comtxt, figures: () => figures, scroll,
      disaster: () => { disasterday = clock.juldate; } }, locspec, ref.room, level) : null;
    if (scene) message = scene.enter() || message;
    service = ref.pgm.program === 5 ? await ServiceRoom.open(ctx, ref.room, ref.kind, level.loc.texts, level.loc.words) : null;
    service?.greet();
    special = ref.pgm.program === 9 ? await Special.open({ hero, clock, cmd, comtxt, party, tod: tables.tod, attribs: tables.attribs,
      kins: cdata.parley.kins, serve, close }, ref.kind, ref.kind === 13 ? ref.index - 8 : ref.index, level) : null;
  };

  /** A member leaves into a god's service (P09 ovl_1290): the leaving events, the Mindstone (0x40) stays behind, and
   *  the companion is kept out of the location tables (assignment task 100); Somona sets event 96. */
  const serve = (m: Member) => {
    party.partyEvents(events, p97.events, m.num, false);
    if (m.hero.slot(0x40) >= 0) m.hero.dec(m.hero.slot(0x40));
    party.remove(m);
    party.away.add(m.num);
    if (m.num === 31) events.add(96);
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
    if (d.type & 0x80) return keyDoor(d);
    if (d.type === 2 && (d.pgm === 0x78 || d.pgm === 0x79)) return passThrough(d);
    if (d.type >= 6 && d.type <= 9) return guardedRoom(d);
    if (d.type === 0 || d.type === 3) return enterRoom(d);
    lockedDoor(d);
  };

  /** P02 pass-through door (type 2, `pgm` 'x'/'y', `id` '+'/'−'): the whole party jumps its formation's extent along
   *  that axis + 1 squares (`_PartyWH`) and the step is tested again from there; blocked → it stays. */
  const passThrough = (d: Door) => {
    const horiz = d.pgm === 0x78, sign = d.id === 0x2b ? 1 : -1;
    const cells = party.members.map(m => horiz ? m.cell % 3 : Math.floor(m.cell / 3));
    const n = (Math.max(...cells) - Math.min(...cells) + 2) * sign, dx = horiz ? n : 0, dy = horiz ? 0 : n;
    if (party.members.every(m => level.walkable(m.x + dx, m.y + dy) && !figureAt(m.x + dx, m.y + dy))) { party.shift(dx, dy); message = ''; }
    else message = `Blocked by ${level.tileName(d.x, d.y)}.`;
  };

  /** Room exits {x,y,pgm,tx,ty,datafile}: back to town `datafile` with the window at (tx,ty), formation at window + (4,3). */
  const leave = async (exit: Exit) => {
    const id = `D${String(exit.datafile).padStart(2, '0')}`, pgm = level.loc.pgms[exit.pgm];
    special = null;
    if (scene?.transport) {                                              // P08 ovl_0f20: the White Scroll's council
      const said = format(level.loc.texts[3] ?? '', hero, hero.name).trim();
      scene = null; outside = null;
      await enterRoom(level.loc.doors[0], level.loc.pgms, 3);
      message = said;
      return;
    }
    scene = null;
    if (pgm?.program === 1) return toWorld(exit);                      // a P09 room on the world map
    if (exit.datafile !== undefined && exit.datafile !== 255)
      go(outside?.level.id === id ? outside.level : await Level.load(id, pgm?.tileset), exit.tx + 4, exit.ty + 3);
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
    if (pgm?.program === 2) {                                   // another level (stairs): window (tx, ty), formation at +(4,3)
      go(await Level.load(`D${two(pgm.datafile)}`, pgm.tileset), exit.tx + 4, exit.ty + 3);
      message = level.loc.name.replace(/\s*[MX]$/, '').trim(); return;
    }
    if (pgm?.program !== 1) { message = 'This way leads somewhere not built yet.'; return; }
    await toWorldAt(exit.tx, exit.ty);
  };
  /** Onto the world map with the window at (tx, ty) (exits, teleportals). */
  const toWorldAt = async (tx: number, ty: number) => {
    go(await Level.load('D01'), tx + 5, ty + 4);
    await world.at(lead.x, lead.y, clock);
    world.movePatrols(level, lead.x, lead.y, clock.month);              // P01 start: ovl_169e, then ovl_0a94
    world.engage(lead.x, lead.y);
    outside = null; service = null; special = null; scene = null; message = '';
  };
  /** A world-map step (P01): a town entrance of the current region (`exitptr`) loads that town with the window at
   *  (tx, ty); a mushroom patch opens; a boat is boarded or, aboard, water is sailed and land disembarks (ships.md);
   *  otherwise walkable tiles only. */
  const worldStep = async (dx: number, dy: number) => {
    const x = lead.x + dx, y = lead.y + dy, rec = world.rec!, ships = world.ships;
    if (level.tile(x, y) === 0xff) { message = rec.texts[0x14]; return; }   // ovl_147c: "…unsafe to sail in that direction!"
    const entrance = rec.exits.find(e => e.x === x && e.y === y);
    if ((entrance || rec.doors.some(d => d.x === x && d.y === y)) && ships.sailing) return;   // a ship can't enter either
    if (entrance) {
      const pgm = rec.pgms[entrance.pgm];
      if (pgm.program === 2) { go(await Level.load(`D${two(pgm.datafile)}`), entrance.tx + 4, entrance.ty + 3); message = ''; return; }
      // Ziyx's (R36 47,38) is both an entrance and a feature of program 8; the feature's record names the room
      // (assumption: P01's entrance path for a room program is not traced)
      if (!rec.doors.some(d => d.x === x && d.y === y)) { message = `${level.tileName(x, y)}: not built yet.`; return; }
    }
    const spot = ships.sailing ? null : world.spot(x, y, events);
    if (spot && rec.pgms[spot.pgm].program === 2) {                   // an event-gated town (Demonspine, Shumaran)
      go(await Level.load(`D${two(rec.pgms[spot.pgm].datafile)}`), spot.tx + 4, spot.ty + 3); message = ''; return;
    }
    const feature = rec.doors.find(d => d.x === x && d.y === y)
      ?? (spot && [5, 8, 9].includes(rec.pgms[spot.pgm].program) ? { x, y, pgm: spot.pgm, id: spot.id, type: 0 } : undefined);
    if (feature && rec.pgms[feature.pgm].program === 4) return enterPatch(feature.id, x, y);
    if (feature && [5, 8, 9].includes(rec.pgms[feature.pgm].program)) {   // ovl_0d01: the step's time, then the room
      for (let n = world.stepTicks(level.data.nameindex[level.tile(x, y)], clock, party); n > 0; n--) tick();
      return enterRoom(feature, rec.pgms);
    }
    if (feature) { message = `${level.tileName(x, y)}: not built yet.`; return; }
    const ter = level.data.nameindex[level.tile(x, y)];
    if (ships.sailing && level.walkable(x, y)) return disembark(dx, dy);
    if (ships.sailing && ter !== 13) return;                             // @0xEA1: only water, silently
    if (ships.sailing && y === 101 && !events.has(102)) { message = shipText(ships.cur, 0x29); return; }   // ovl_0f3b
    if (!ships.sailing && !level.walkable(x, y)) {
      const i = ships.boatAt(x, y);                                      // ovl_1070
      if (i >= 0) return board(i, dx, dy);
      const no = world.swim(ter, clock.weather, party);
      if (no) { message = no[0] < 0 ? `Blocked by ${level.tileName(x, y)}.` : comtxt[no[0]].replace('%a', no[1]); return; }
    } else world.swimming = false;
    return worldMove(dx, dy);
  };
  /** The step itself (P01 ovl_147c / ovl_10f7), then the per-step states, patrols and guards. */
  const worldMove = async (dx: number, dy: number) => {
    const x = lead.x + dx, y = lead.y + dy, ships = world.ships, ter = level.data.nameindex[level.tile(x, y)];
    party.shift(dx, dy);
    message = '';
    if (ships.sailing) {                                                 // ovl_10f7 @0x114D: the boat moves, no energy
      ships.x[ships.cur] = x; ships.y[ships.cur] = y;
      if (shipCamp) shipCamp();                                          // camping aboard: one camp pass, not the step's time
      else for (let n = 4 + ships.d.weather[clock.weather]; n > 0; n--) tick();
    } else {
      for (let n = world.stepTicks(ter, clock, party); n > 0; n--) tick();
      world.fatigue(ter, clock, party);
    }
    await world.at(x, y, clock);
    if (locate) locate--;                                                // ovl_076c counts the Locate draws down
    shipEvents();
    world.movePatrols(level, x, y, clock.month);
    // ovl_0846: a live guard spot under the party, else a live patrol (which may just have walked onto it)
    const guard = world.guards().find(g => g.x === x && g.y === y), n = guard ? -1 : world.patrolAt(x, y);
    if (guard || n >= 0) return wildFight(guard, n);
    world.engage(x, y);
  };
  /** A world-map fight with a guard spot or patrol n on the party's square (ovl_0846). */
  const wildFight = async (guard: ReturnType<World['guards']>[number] | undefined, n: number, ambush = false) => {
    const ter = level.data.nameindex[level.tile(lead.x, lead.y)];
    const lv = await Level.wild(world.patchTileset(ter), ter), diff = world.diff(cdata.guarddiff);
    const group = guard ? guard.group : world.patrolGroup(n);
    startFight(lv, Fight.wild(cdata, lv, party.members, group, diff), diff,
      () => guard ? world.cleared.add(guard.bit) : world.dead.add(n), null, ambush);
  };

  // ---- ships (rules/ships.md; ships.ts) ----
  /** Region text n with "Captain <name>" in front for the captain's lines (ovl_126a), `%f` = the ship (ovl_1098). */
  const shipText = (i: number, n: number, v: Record<string, string | number> = {}) => {
    const t = world.rec!.texts, s = [0x0f, 0x15, 0x16, 0x23, 0x24, 0x25, 0x27].includes(n) ? t[8] + t[9 + i] + t[n] : t[n];
    return format(s, lead.hero, lead.hero.name, { f: t[2 + i], ...v });
  };
  const shipYesNo = (yes: () => void, no: () => void) => panel.set([{ label: cmd[3], act: yes }, { label: cmd[4], act: no }]);
  /** ovl_0fcc: "…%b coins a day. How many days?" (GetNum 0-99, 0 cancels), at most 99 with the credit left (0x15),
   *  "That will be %i coins. Do you accept?" (No asks again), then the acting member pays or `cancel` runs. */
  const buyDays = (i: number, ok: (n: number) => void, cancel: () => void) => {
    const rate = world.ships.d.rate[i];
    panel.line(shipText(i, 0x12, { b: rate }));
    panel.set([{ label: cmd[0], act: cancel }], w => {
      const n = Number(w);
      panel.line(`> ${w}`, 'you');
      if (!Number.isInteger(n) || n < 0 || n > 99) return buyDays(i, ok, cancel);
      if (n === 0) return cancel();
      if (n + world.ships.days[i] > 99) { panel.line(shipText(i, 0x15)); return buyDays(i, ok, cancel); }
      panel.line(shipText(i, 0x13, { i: n * rate }));
      shipYesNo(() => {
        if (lead.hero.rec.h_gold < n * rate) { panel.line(format(comtxt[0x25], lead.hero, lead.hero.name)); return cancel(); }
        lead.hero.rec.h_gold -= n * rate;
        ok(n);
      }, () => buyDays(i, ok, cancel));
    }, '0–99');
  };
  /** Boarding (ovl_0cb2 @0xEDB): the party's anchored boat (state 1) at once, "…welcomes %h on board" (0x0F); any other
   *  "…available for hire. Will %h hire her?" (0x23, ovl_0f5c) and days bought, "…ready to sail" (0x24). Then the step. */
  const board = (i: number, dx: number, dy: number) => {
    const sail = (text: number) => { world.ships.board(i); panel.hide(); void worldMove(dx, dy).then(() => { message = shipText(i, text); render(); }); };
    if (world.ships.sta[i] === 1) return sail(0x0f);
    panel.show();
    panel.line(shipText(i, 0x23));
    shipYesNo(() => buyDays(i, n => { world.ships.days[i] = n; sail(0x24); }, () => close()), () => close());
  };
  /** Landing (@0xD7D): "Do you want to disembark?" (0x10); with credit "…your credit is %b days. Do you want him to wait
   *  longer?" (0x16), else "…drop anchor here and wait?" (0x11); Yes buys days (cancel = No). Then the step ashore. */
  const disembark = (dx: number, dy: number) => {
    const s = world.ships, i = s.cur;
    if (shipCamp) { message = shipText(i, 0x19); return; }              // "End camp activities first."
    const ashore = (n: number) => { s.land(n); panel.hide(); void worldStep(dx, dy).then(render); };
    panel.show();
    panel.line(shipText(i, 0x10));
    shipYesNo(() => {
      panel.line(s.days[i] ? shipText(i, 0x16, { b: s.days[i] }) : shipText(i, 0x11));
      shipYesNo(() => buyDays(i, ashore, () => ashore(0)), () => ashore(0));
    }, () => close());
  };
  /** ovl_15e4 after a step: "Your time is up" (0x25, ovl_0f95) or Amos' theft (0x2C). */
  const shipEvents = () => {
    const s = world.ships, e = s.step();
    if (e === 'stolen') message = shipText(s.cur, 0x2c);
    if (e !== 'timeup') return;
    const i = s.cur, paid = (n: number) => { s.days[i] = n; s.sta[i] = 5; close(); };
    const work = () => {                                                // 0x26: No → back to buying days
      panel.line(shipText(i, 0x26));
      shipYesNo(() => { s.passage = 1; close(); }, () => buyDays(i, paid, work));
    };
    panel.show();
    panel.line(shipText(i, 0x25));
    shipYesNo(() => buyDays(i, paid, work), work);
  };

  // ---- combat (rules/combat.md; combat.ts) ----
  /** `%a`/`%b`/`%h`/`%l` filled from `v` (the combat texts name records, not the acting hero). */
  const ctext = (n: number, v: Record<string, string | number> = {}) => comtxt[n].replace(/%([a-z])/g, (_, c: string) => String(v[c] ?? ''));
  let actor: Rec | null = null;
  /** P01 ovl_0846 → _DoACmbt: a wilderness fight on G00 chunk `ter`; `won` runs on victory (e.g. the guard is cleared).
   *  "COMBAT!" (comtxt 0x44), then rounds: the party phase, hero by hero, then the monster phase (P94 ovl_02e8). */
  const startFight = (lv: Level, f: Fight, diff: number, won: () => void, after: (() => void) | null = null, ambush = false) => {
    outside = { level, x: lead.x, y: lead.y };
    level = lv;
    figures = [];
    fight = f;
    afterWin = after;
    autoHeroes.clear(); heading = false;
    panel.show();
    panel.line(comtxt[ambush ? 0x7c : 0x44]);                         // "AMBUSH!" / "COMBAT!"
    fight.newRound();
    onWin = won; fightDiff = diff; f.mood = f.attitude();
    if (!f.street && f.recs.find(r => r.side)?.race !== 28) advice();
    if (ambush) void monsterPhase();                                  // `_ambflg`: the monsters move first
    else if (f.street) partyTurn();                                   // no pre-fight menu in a street fight
    else prefight();
  };
  let onWin = () => {}, fightDiff = 0, afterWin: (() => void) | null = null;

  // ---- before the fight (P96 menu 10 and ovl_06e7; rules/combat.md, Talk before a fight) ----
  /** V06's texts with `%x` from `v`. */
  const vtext = (n: number, v: Record<string, string | number> = {}) =>
    cdata.parley.texts[n].replace(/%([a-z])/g, (_, c: string) => String(v[c] ?? ''));
  /** `_Advice` (P96 ovl_0b5c): RndCo(100) ≤ the party's best soul reading → the attitude, as "The monsters appear to be
   *  %l." (30) when the best reader is the acting member, else "%o thinks the monsters seem %l." (29). */
  const advice = () => {
    const best = party.members.reduce((a, m) => (m.hero.rec.h_soulrd as number) > (a.hero.rec.h_soulrd as number) ? m : a);
    if (rnd(100) > (best.hero.rec.h_soulrd as number)) return;
    const l = cdata.parley.attitudes[fight!.mood].toLowerCase();
    panel.line(best === lead ? vtext(30, { l }) : vtext(29, { o: best.hero.name, l }));
  };
  /** Menu 10: Draw, Recall, Talk, Look, Begin, Sheathe, and moving. Built: Draw, Recall, Talk, Begin, Sheathe; Draw and
   *  Recall ask which member acts. */
  const prefight = () => {
    const who = (then: (a: Rec) => void) => {
      const heroes = fight!.recs.filter(r => !r.side && fight!.alive(r));
      if (heroes.length === 1) return then(heroes[0]);
      panel.set([...heroes.map(r => ({ label: r.name, act: () => then(r) })), { label: cmd[0], act: prefight }]);
    };
    panel.set([{ label: cmd[14], act: () => who(a => drawWeapon(a, prefight)) }, { label: cmd[35], act: () => who(a => recall(a, prefight)) },
      { label: cmd[41], act: () => panel.set([{ label: cmd[34], act: rally }, { label: cmd[18], act: greet },
      { label: cmd[0], act: prefight }]) }, { label: cmd[5], act: () => begin(false) }, { label: cmd[38], act: sheathe }]);
    render();
  };
  /** Sheathe (_Sheathe): with 2+ members "Is this order for everyone?" (_AllDoit, comtxt 0x3C) - Yes every member, No
   *  the acting member (asked); fists in hand (`h_inhand` 0xFF, `c_rdywpn` 0xFF), then "Done." (0x37). */
  const sheathe = () => {
    const heroes = fight!.recs.filter(r => !r.side && r.hero && fight!.alive(r));
    const off = (rs: Rec[]) => {
      for (const a of rs) { a.hero!.rec.h_inhand = 0xff; a.weapon = 0xff; a.wskl = Fight.wpnSkl(a.hero!); }
      panel.line(comtxt[0x37]); prefight();
    };
    if (heroes.length < 2) return off(heroes);
    panel.line(comtxt[0x3c]);
    panel.set([{ label: cmd[3], act: () => off(heroes) }, { label: cmd[4], act: () =>
      panel.set([...heroes.map(r => ({ label: r.name, act: () => off([r]) })), { label: cmd[0], act: prefight }]) }]);
  };
  const begin = (ambush: boolean) => { if (ambush) void monsterPhase(); else partyTurn(); };
  /** Rally (ovl_06e7 menu 14 item 0): alone → "There is no one to rally!" (0) and back; a coin flip → "The enemy
   *  attacks!!" (4) and the monsters move first; else the speech (1) and RndCo(100) < the leader's leadership gives every
   *  other member bravery + RndCo(3)+1 and agility + 4, each capped at 12 (2; P95 restores both after the fight),
   *  or "Unfortunately, they are not impressed!" (3). The fight begins either way. */
  const rally = () => {
    const f = fight!;
    if (party.members.length < 2) { panel.line(vtext(0)); return prefight(); }
    if (!rnd(2)) { panel.line(vtext(4)); return begin(true); }
    panel.line(vtext(1, { h: lead.hero.name }));
    if (rnd(100) < (lead.hero.rec.h_ldrshp as number)) {
      const b = rnd(3) + 1;
      for (const r of f.recs.filter(r => !r.side && r.hero !== lead.hero)) { r.bravery = Math.min(12, r.bravery + b); r.agi = Math.min(12, r.agi + 4); }
      panel.line(vtext(2, { b, i: 4 }));
    } else panel.line(vtext(3));
    begin(false);
  };
  /** Greet = hail the leader (menu 14 item 1). Attitude 6/7: "The monsters do not understand %h." / "The %a leader
   *  will not discuss a truce!", then "The enemy attacks!!". Otherwise "%h hails the %a leader." and "The %l glowers at
   *  the party.", then by attitude (handlers P96 0x94B / 0x957): 0 panic (31, every monster routed, they move first);
   *  1 surrender (33, a won fight with loot); 2 ransom of 3 coins per monster to the acting member (34); 3 truce (35);
   *  4 bribe of 100 coins per party member, at most the party's coins, paid member by member (36); 5 attack (32, they
   *  move first). 2-4 ask Yes/No: Yes → "The monsters leave." (37) and the fight ends, No → the fight begins.
   *  Vankruh (the first monster's race 28) instead: no hero holds a weapon → its rhyme (comtxt 0x108), events 66 and 150,
   *  and it leaves; else "Vankruh's eyes widen in affront and it attacks!" (0x107) and it moves first. */
  const greet = () => {
    const f = fight!, mood = f.mood, kin = cdata.parley.kins[f.speaker], v = { h: lead.hero.name, a: kin, l: kin };
    if (f.recs.find(r => r.side)?.race === 28) {
      if (f.recs.some(r => !r.side && r.weapon !== 0xff)) { panel.line(comtxt[0x107]); return begin(true); }
      panel.line(comtxt[0x108]); events.add(66); events.add(150);
      f.leave(); return void finished();
    }
    if (mood >= 6) { panel.line(vtext(mood - 1, v)); panel.line(vtext(4)); return begin(true); }
    panel.line(vtext(7, v)); panel.line(vtext(8, v));
    if (mood === 0) { panel.line(vtext(31, v)); for (const r of f.recs.filter(r => r.side)) r.state |= 0x40; return begin(true); }
    if (mood === 1) { panel.line(vtext(33, v)); f.ended = 1; return void finished(); }
    if (mood === 5) { panel.line(vtext(32, v)); return begin(true); }
    const here = f.recs.filter(r => !(r.state & 8)), coins = party.members.reduce((t, m) => t + m.hero.rec.h_gold, 0);
    const amount = mood === 2 ? 3 * here.filter(r => r.side).length : mood === 4 ? Math.min(100 * here.filter(r => !r.side).length, coins) : 0;
    panel.line(vtext(mood + 32, { ...v, i: amount }));
    panel.set([{ label: cmd[3], act: () => {
      if (mood === 2) lead.hero.rec.h_gold = Math.min(9999, lead.hero.rec.h_gold + amount);
      if (mood === 4) for (let left = amount, k = 0; left > 0 && k < party.members.length; k++) {
        const h = party.members[k].hero.rec, pay = Math.min(h.h_gold, left);
        h.h_gold -= pay; left -= pay;
      }
      panel.line(vtext(37)); f.leave(); finished();
    } }, { label: cmd[4], act: () => begin(false) }]);
  };
  /** The next hero with actions left acts; when none is left, the monsters' phase. */
  const partyTurn = () => {
    if (finished()) return;
    actor = fight!.recs.find(r => !r.side && fight!.alive(r) && r.moves > 0) ?? null;
    if (!actor) return void monsterPhase();
    message = `${actor.name}: ${actor.moves}`;
    if (heading || autoHeroes.has(actor.recno)) return void autoTurn(actor);
    panel.set([{ label: cmd[7], act: aim }, { label: cmd[27], act: magic }, { label: cmd[35], act: () => recall(actor!, partyTurn) }, { label: cmd[43], act: fightUse },
      { label: cmd[19], act: () => { heading = true; partyTurn(); } }, { label: cmd[46], act: () => { autoHeroes.add(actor!.recno); partyTurn(); } },
      { label: cmd[14], act: () => drawWeapon(actor!, partyTurn) }, { label: cmd[30], act: () => { actor!.moves = 0; partyTurn(); } }]);
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
    const a = actor!, r = a.hero!.rec;
    const codes = [...new Set(r.h_invitem.filter(c => c > 0x30 && c < 0x51 || c === 0x5b))];
    panel.line(comtxt[0x2b]);                                                     // "Select."
    panel.set([...codes.map(item => ({ label: items[item], act: () => {
      const lines = useInFight(a, item);
      report(lines.map(l => l.replace(/^!/, '')));
      if (lines.length && a.moves > 0 && !lines[0].startsWith('!')) a.moves--;
      partyTurn();
    } })), { label: cmd[0], act: partyTurn }]);
  };
  /** One item used by `a` in a fight; a refused item's _NoUse text comes back marked '!' (no action spent). */
  const useInFight = (a: Rec, item: number): string[] => {
    const h = a.hero!, r = h.rec, fmt = (s: string) => format(s.replace(/%l/g, items[item]), h, h.name);
    if (cdata.songs.instruments.includes(item)) return fight!.song(a, item, ctext);
    const down = (r.h_cond1 as number) & 1;
    if (!h.use(item, tables.hungerhours[r.h_race as number])) return ['!' + fmt(comtxt[tables.nousetext[item]])];
    h.dec(h.slot(item));
    a.hp = r.h_hitpts;
    if (item === 0x32 && down && !((r.h_cond1 as number) & 8)) {
      r.h_cond1 = (r.h_cond1 as number) & ~1; a.health &= ~1; a.agi = r.h_agility as number; a.dex = r.h_dextrty;
    }
    if (item === 0x35) a.nift = 3;
    if (item === 0x34) a.moves = 4;                                              // then this Use spends one of them
    return [fmt(comtxt[0x38])];                                                   // "%o uses a %l."
  };
  /** Head (`_mnusel` 0x13: the whole party on auto until a key is pressed) and Will (0x2E: this member for the rest of
   *  the fight) run P94 ovl_0a98 (Fight.autoHero) for the hero's actions. Head's speed digit is not asked. */
  const autoHeroes = new Set<number>();
  let heading = false;
  const autoTurn = async (a: Rec) => {
    panel.set(heading ? [{ label: cmd[40], act: () => { heading = false; } }] : []);   // Stop
    while (fight && a.moves > 0 && fight.alive(a) && !fight.outcome()) {
      report(fight.autoHero(a, (r, item) => { const l = useInFight(r, item); r.moves--; return l.map(x => x.replace(/^!/, '')); }, ctext));
      render();
      await sleep(200);
    }
    partyTurn();
  };
  /** Recall (_RecSpl): ready one of the spells the hero has memorised (`h_spells`, `h_rdyspl`). Takes no action. */
  const recall = (a: Rec, back: () => void) => {
    const r = a.hero!.rec, known = r.h_spells.flat().map((n, i) => [n, i]).filter(([n]) => n > 0);
    panel.set([...known.map(([n, i]) => ({ label: `${cdata.spells.names[i]} (${n})`, act: () => {
      r.h_rdyspl = i; back();
    } })), { label: cmd[0], act: back }]);
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
  const drawWeapon = (a: Rec, back: () => void) => {
    const h = a.hero!, r = h.rec;
    const slots = r.h_invitem.map((c, i) => i).filter(i => r.h_invitem[i] >= 9 && r.h_invitem[i] <= 0x1e && i !== r.h_inhand);
    panel.set([...slots.map(i => ({ label: items[r.h_invitem[i]], act: () => {
      const w = cdata.weapons[r.h_invitem[i] - 9];
      if (w.race !== 0xff && w.race !== r.h_race) panel.line(ctext(0x103, { a: items[r.h_invitem[i]] }));
      else if (r.h_invamt[i] >= 0xe4) panel.line(ctext(0x39));
      else if (r.h_strngth < w.minst) panel.line(ctext(0x69, { h: a.name }));
      else { r.h_inhand = i; a.weapon = r.h_invitem[i]; a.wskl = Fight.wpnSkl(h); panel.line(`${a.name}: ${items[a.weapon]}`); }
      back();
    } })), { label: cmd[0], act: back }]);
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
    if (fight!.ended === 4) { onWin(); panel.set([{ label: cmd[0], act: endFight }]); render(); return true; }   // they left: no loot
    panel.line(comtxt[0x4e]);
    onWin();
    for (const { hero: h } of party.members) h.rec.h_inuse = (h.rec.h_inuse as number) & ~0xc0;   // P95: Gonshi and Nift end
    // P95 ovl_072d: loot for every slain monster, its value to each hireling's partybucks (ovl_164e, cap 30000).
    const value = fight!.rollLoot(fightDiff, events, tables.lootvalues);
    for (const { hero: h } of party.members)
      if (h.rec.h_relatn === 2) h.rec.h_partybucks = Math.min(30000, (h.rec.h_partybucks as number) + value);
    if (fight!.recs.some(r => !r.side && (r.state & 0x98) === 0x80)) { panel.line(comtxt[0x110]); raise(); }
    else searchAsk();
    render();
    return true;
  };
  /** P95 ovl_072d: while a party member lies dead, menu 0x15 - Use, Recall, Magic, Done ("Combat is over: this is your
   *  only opportunity to resurrect your dead.", comtxt 0x110, once). Magic casts the acting member's readied spell where
   *  `_spellshere` is 0x20 (Resurrect only). Done while someone is still dead asks "Are you sure you've resurrected
   *  everyone that you want to?" (P95 text 0); Yes (or nobody dead) goes on to the search. Use, and the dead companion
   *  who will not be left behind with a quest item (ovl_0c87, comtxt 0x114), are not built. */
  const raise = () => {
    const f = fight!, dead = () => f.recs.some(r => !r.side && (r.state & 0x98) === 0x80);
    if (!dead()) return searchAsk();
    const living = f.recs.filter(r => !r.side && f.alive(r));
    const who = (then: (a: Rec) => void) => living.length === 1 ? then(living[0])
      : panel.set([...living.map(r => ({ label: r.name, act: () => then(r) })), { label: cmd[0], act: raise }]);
    panel.set([{ label: cmd[35], act: () => who(a => recall(a, raise)) }, { label: cmd[27], act: () => who(resurrect) },
      { label: cmd[0], act: () => {
        panel.line(cdata.resurrect[0]);
        panel.set([{ label: cmd[3], act: searchAsk }, { label: cmd[4], act: raise }]);
      } }]);
  };
  /** Magic on the aftermath screen (_Magic with `_spellshere` 0x20). Resurrect (P95 slot 3, spells.md): "Mark the
   *  target." (text 1) among the records on the board; alive → "%a does not need resurrection." (2); else it always
   *  works: HP and energy 1, not dead (a hero: `h_hitpts = h_energy = 1`, `cond1 &= ~Dead`, "Done."); a monster thanks
   *  the caster (4) and gives its loot (", giving %d " (5) and the treasure, _IncObj to the caster; a full pack keeps
   *  only the thanks), then leaves the board. One copy, the energy and a magic skill roll as elsewhere (assumed). The
   *  "decides not to resurrect" refusal (3, a record byte +9 not traced) and the looting refusal (6, the search comes
   *  after this screen in the port) are not built. */
  const resurrect = (a: Rec) => {
    const h = a.hero!, r = h.rec, sp = r.h_rdyspl, need = Math.max(1, cdata.spells.energy[sp] - (r.h_magic >> 2));
    if (sp === 0xff) { panel.line(ctext(0x40, { h: a.name })); return raise(); }        // "%h must recall a spell first."
    if (!(cdata.spells.where[sp] & 0x20)) { panel.line(ctext(0x56, { h: a.name })); return raise(); }
    if (r.h_energy < need) { panel.line(comtxt[0x41]); return raise(); }                 // "Not enough energy!"
    const f = fight!, rt = cdata.resurrect, say = (s: string, v: Record<string, string> = {}) =>
      format(s.replace(/%d/g, h.female ? 'her' : 'him').replace(/%[al]/g, m => v[m[1]] ?? ''), h, h.name);
    panel.line(rt[1]);
    panel.set([...f.recs.filter(t => !(t.state & 0x10)).map(t => ({ label: `${t.name} (${t.x},${t.y})`, act: () => {
      if (!(t.state & 0x80)) { panel.line(say(rt[2], { a: t.name })); return raise(); }
      t.state &= 0x7f; t.health &= 0x7f; t.hp = 1;
      if (t.hero) {
        const tr = t.hero.rec;
        tr.h_hitpts = tr.h_energy = 1; tr.h_cond1 = (tr.h_cond1 as number) & 0x7f;
        panel.line(comtxt[0x37]);
      } else {
        const l = t.loot, gift = l && l.amount && (l.item === 0 ? r.h_gold + l.amount <= 9999 : incObj(h, l.item, l.amount & 0x80 ? 1 : l.amount));
        if (gift && l.item === 0) r.h_gold += l.amount;
        if (gift && l.amount & 0x80) r.h_invamt[r.h_invitem.lastIndexOf(l.item)] = l.amount;
        const n = l ? (l.amount & 0x80 ? 1 : l.amount) : 0;
        panel.line(say(rt[4], { l: t.name }).replace(/\.$/, gift ? say(rt[5]) + `${n} ${items[l!.item]}${n > 1 ? comtxt[0x51] : ''}.` : '.'));
        t.loot = undefined; f.remove(t);
      }
      const row = Math.floor(sp / 7), col = sp % 7;
      if (--r.h_spells[row][col] <= 0) { r.h_spells[row][col] = 0; r.h_rdyspl = 0xff; }
      r.h_energy -= need; h.isHeTr();
      if (cdata.spells.skill.includes(sp)) report(f.skillUp(a, 3, ctext));
      render(); raise();
    } })), { label: cmd[0], act: raise }]);
  };
  /** After the fight: a won room fight goes on into the room (P95 → P07, `_p07flg`), anything else back to where the
   *  fight started. */
  const endFight = () => {
    const won = fight!.outcome() === 1, next = afterWin;
    afterWin = null;
    if (won && next) { next(); fight = null; close(); return; }
    level = outside!.level; party.place(outside!.x, outside!.y); outside = null; fight = null; close();
  };

  // ---- dungeon rooms (rules/locations.md, Doors into dungeon rooms; P07) ----
  const dunrms = new Set<string>(), duntre = new Set<string>();   // _dunrms (guards beaten), _duntre (reward taken)
  let chamber: Chamber | null = null;
  /** A door of type 6-9: the room's HROOM record; its guards fight first (`_cmbtyp` 5, `_diff` = locdiff − 1) unless
   *  beaten before, then the room (P07). Group 0xCA's swap for 0xDE before event 31/32 is not modelled. */
  const guardedRoom = async (d: Door) => {
    const hr = level.loc.hrooms?.find(h => h.id === d.id), pgm = level.loc.pgms[d.pgm];
    if (!hr || !pgm) return void (message = 'This door leads somewhere not built yet.');
    const key = `${level.id}:${hr.id}`, ch = await Chamber.build(hr, pgm.tileset, key, events), diff = Math.max(0, level.loc.locdiff - 1);
    const back = { level, x: lead.x, y: lead.y };
    if (dunrms.has(key)) return enterChamber(ch, d.type, back, false);
    startFight(ch.level, Fight.room(cdata, ch.level, party.members, hr.group, diff, d.type, ch.doors()), diff,
      () => dunrms.add(key), () => enterChamber(ch, d.type, back, true));
  };
  /** P07 entry: from the fight the members keep their squares (`_p07flg`), else formation `side − 6` of `_setupxy`. */
  let chamberBack: { level: Level; x: number; y: number } | null = null;
  const enterChamber = (ch: Chamber, side: number, back: { level: Level; x: number; y: number }, fromFight: boolean) => {
    const recs = fight?.recs;
    level = ch.level; chamber = ch; chamberBack = back; outside = null;
    const taken: Member[] = [];
    party.members.forEach((m, i) => {
      const r = recs?.[i];
      const at = fromFight && r && r.x >= 0 ? { x: r.x, y: r.y }
        : level.place(cdata.setupxy[6 * (side - 6) + i], cdata.setupxy[24 + 6 * (side - 6) + i], (x, y) => taken.some(t => t.x === x && t.y === y));
      m.x = at.x; m.y = at.y; taken.push(m);
    });
    message = '';
    const freed = assigns.rescue(back.level.loc.locnum, ch.hr.id, (x, y) => level.place(x, y, (a, b) => taken.some(t => t.x === a && t.y === b)), events);
    if (freed.length) message = assigns.rescueText;                    // P07 ovl_05ad: a prison cell
    figures = people();
  };
  /** P07 ovl_06c2, using the room's scroll (item 0x4A + type) in a Dark Candle room: an undeciphered scroll is blank
   *  (D98 text 4), a member without magic cannot read it (5); otherwise the incantation (6, 7), the scroll burns, the
   *  flame goes out, "%o has been set free!" (8, the elden's name from `gwrds`), the elden stands in the room and
   *  event 0x3C + type is set. The original also plays sound 5 and a Bang at the reader. */
  const candle = (h: Hero, item: number): string => {
    const ch = chamber!, t = (n: number, o = '') => format(ch.candle!.texts[n].replace(/%a/g, items[item]), h, o || h.name);
    if (!(h.rec.h_invamt[h.slot(item)] & 0x80)) return t(4);
    if (!h.rec.h_magic) return t(5);
    h.dec(h.slot(item));
    ch.snuff(); ch.freed = ch.elden(); events.add(0x3c + ch.type);
    figures = people();
    return [t(6), t(7), t(8, ch.freed.name)].join(' ');
  };
  /** The chest and fountain need the acting member next to them (`_ChkRng` 1); otherwise " %w considers moving closer
   *  to it." (text 8; text 7 when another member makes the suggestion — `_Advice` chooses). */
  const near = (x: number, y: number) => Math.max(Math.abs(lead.x - x), Math.abs(lead.y - y)) <= 1;
  const ptext = (n: number, h: Hero, v: Record<string, string | number> = {}) => format(chamber!.texts[n], h, h.name, v).trim();
  /** P07 ovl_0969, using a Pick on the chest: already emptied → texts 0 + 1; the first opening this visit rolls
   *  min(99, dex/2 + lockpick) against RndCo(100) (a miss breaks the Pick, comtxt 0x90, the chest still opens); then
   *  1 in 4 and RndCo(120) > skill springs the trap ("The chest is trapped! %h is poisoned!/ill!", Poisoned for an even
   *  `hrmid`, Ill for an odd one, energy and HP halved, " But the chest is open."), else a lockpick skill roll and
   *  "%h opens the chest."; then its contents (chestLook). */
  const openChest = (h: Hero) => {
    const ch = chamber!, r = h.rec as Record<string, number> & Hero['rec'];
    panel.show();
    if (!near(1, 1)) { panel.line(ptext(8, h)); return void panel.set([{ label: cmd[0], act: () => close() }]); }
    if (duntre.has(ch.key)) { panel.line(ptext(0, h) + ch.texts[1]); return void panel.set([{ label: cmd[0], act: () => close() }]); }
    if (!ch.opened) {
      const skill = Math.min(99, (r.h_dextrty >> 1) + r.h_lockpck);
      if (skill <= rnd(100)) { panel.line(comtxt[0x90]); h.dec(h.slot(0x50)); }
      ch.opened = true;
      if (rnd(4) === 0 && rnd(120) > skill) {
        const odd = ch.hr.id & 1;
        r.h_cond1 |= ch.trap[odd]; r.h_energy >>= 1; r.h_hitpts >>= 1; h.isHeTr();
        panel.line(ptext(2, h) + ' ' + ch.texts[3 + odd]);
        panel.line(ptext(5, h));
      } else {
        const up = skillUp0(h, 10);                                     // lockpick
        if (up) panel.line(up);
        panel.line(ptext(9, h));
      }
    }
    chestLook(h);
  };
  /** The opened chest's contents: " It contains %b %as. Will %h take them?" (6; 14 for one) → _IncObj; taken: the
   *  `_duntre` bit, hirelings' partybucks += value × amount, and Darkfinder (0x1E) sets event 93 (`_events+11 & 0x20`). */
  const chestLook = (h: Hero) => {
    const ch = chamber!, item = ch.hr.reward, n = ch.hr.amount;
    panel.show();
    if (!near(1, 1)) { panel.line(ptext(8, h)); return void panel.set([{ label: cmd[0], act: () => close() }]); }
    if (duntre.has(ch.key)) { panel.line(ch.texts[1].trim()); return void panel.set([{ label: cmd[0], act: () => close() }]); }
    panel.line(ptext(n === 1 ? 14 : 6, h, { a: items[item], b: n }));
    panel.set([{ label: cmd[3], act: () => {
      const ok = item === 0 ? h.rec.h_gold + n <= 9999 && (h.rec.h_gold += n, true) : incObj(h, item, n);
      if (!ok) return close(ctext(h.slot(item) >= 0 ? 0x32 : 0x33, { o: h.name }));
      duntre.add(ch.key);
      if (item === 0x1e) events.add(93);
      for (const { hero: m } of party.members)
        if (m.rec.h_relatn === 2) m.rec.h_partybucks = Math.min(30000, (m.rec.h_partybucks as number) + tables.lootvalues[item] * n);
      close();
    } }, { label: cmd[4], act: () => close() }]);
  };
  /** P07 ovl_0d54, Look at the fountain: the first drink of a spell fountain by a member with magic (spell ≠ 0x2A)
   *  adds its charges (" of %a spells.", "Will %h drink from it?", "%h gains %b %a spells.", cap 99); every other drink
   *  sets energy to 99 ("How refreshing!"). */
  const fountain = (h: Hero) => {
    const ch = chamber!, spell = ch.hr.reward - 0x80, r = h.rec;
    panel.show();
    if (!near(9, 1) && !near(9, 0)) { panel.line(ptext(8, h)); return void panel.set([{ label: cmd[0], act: () => close() }]); }
    const charges = !duntre.has(ch.key) && r.h_magic && spell !== 0x2a;
    if (charges) panel.line(level.tileName(9, 1) + ptext(10, h, { a: cdata.spells.names[spell] }));
    panel.line(ptext(11, h));
    panel.set([{ label: cmd[3], act: () => {
      if (charges) {
        const row = Math.floor(spell / 7), col = spell % 7, before = r.h_spells[row][col];
        r.h_spells[row][col] = Math.min(99, before + ch.hr.amount);
        duntre.add(ch.key);
        return close(ptext(12, h, { b: r.h_spells[row][col] - before, a: cdata.spells.names[spell] }));
      }
      r.h_energy = 99; h.isHeTr();
      close(ptext(13, h));
    } }, { label: cmd[4], act: () => close() }]);
  };
  /** Leaving by door n (P07: "Do you want to leave now?", comtxt 0x23): the level with the window at `hrmxy[n]`. */
  const leaveChamber = (n: number) => {
    panel.show();
    panel.line(comtxt[0x23]);
    panel.set([{ label: cmd[3], act: () => {
      const w = chamber!.window(n);
      go(chamberBack!.level, w.x + 4, w.y + 3);
      chamber = null; chamberBack = null; close();
    } }, { label: cmd[4], act: () => close() }]);
  };
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
    lastStep = { dx, dy };
    if (level.loc.kind === 'world') { await worldStep(dx, dy); return render(); }
    const room = level.loc.kind === 'room';
    const who = figureAt(lead.x + dx, lead.y + dy);
    if (who) {   // walking into someone talks to them (the original uses a Talk command)
      message = '';
      if (!keeper()) await talkTo(who);
      return render();
    }
    const movers = room ? [lead] : [...party.members].reverse();
    const scared = scene?.step(dy, lead.hero);
    if (scared) { message = scared; return render(); }
    const unable = movers.find(m => (m.hero.rec.h_cond1 as number) & 0xfc);   // Dead, Paralyzed, Exhausted, Poisoned, Starving
    if (unable) { message = `${unable.hero.name}: ${unable.hero.condition(conds)}.`; return render(); }
    for (const m of movers) {
      const x = m.x + dx, y = m.y + dy;
      if (patch && (x < 0 || y < 0 || x >= level.w || y >= level.h)) { leavePatch(); return render(); }
      if (chamber && chamber.exitAt(x, y) >= 0) { leaveChamber(chamber.exitAt(x, y)); return render(); }
      const exit = level.loc.exits.find(e => e.x === x && e.y === y);
      const other = figureAt(x, y);
      if (room && exit) {
        const no = scene?.refuseLeave();
        if (no) { message = no; return render(); }
        if (scene) {                                                     // P08 L_06fa: "Do you want to leave?"
          panel.show(); panel.line(comtxt[0x23]);
          panel.set([{ label: cmd[3], act: () => { close(); void leave(exit).then(render); } }, { label: cmd[4], act: () => close() }]);
          return render();
        }
        if (service) service.leave(() => void leave(exit).then(render));
        else if (special) special.exit(exit, () => void leave(exit).then(render));
        else await leave(exit);
        return render();
      }
      if (other) { message = `Blocked by ${other.name ?? npctypes[other.type] ?? 'someone'}.`; return render(); }
      const mate = party.at(x, y);                       // in town a mate's square is vacated by the same step
      if (mate ? !room : level.walkable(x, y)) continue;
      if (walkwater && !room && water(x, y)) continue;                  // V02 INT60_02: Walkwater crosses the listed tiles
      const d = level.loc.doors.find(e => e.x === x && e.y === y);
      if (d && !mate) { await door(d); return render(); }
      if (room && service?.kind === INN && x === 8 && y === 4) { innArch(); return render(); }
      if (exit && !mate) { await toWorld(exit); return render(); }
      message = `Blocked by ${mate ? mate.hero.name : level.tileName(x, y)}.`;
      if (!room) bump(movers, dx, dy);
      return render();
    }
    for (const m of movers) { m.x += dx; m.y += dy; }
    if (walkwater && !room) walkwater--;
    message = '';
    if (patch) pickAt(lead.x, lead.y);
    walked();
    if (level.loc.kind === 'level') await spotsAround();
    render();
  };

  /** V02 INT60_02: the tileset's segment-4 list (door tiles in room tilesets; water and rocks in B60) up to its 0xFF. */
  const water = (x: number, y: number) => {
    const t = hex(level.data.doors), i = t.indexOf(0xff);
    return [...(i < 0 ? t : t.subarray(0, i + 1))].includes(level.tile(x, y));
  };
  /** V02 INT60_08/09, a step refused: each member whose square ahead is a barrier tile pays - class 'C' (Pierce)
   *  10 + RndCo(10) energy, class 'B' (Repel) 1 HP, never below 1 HP. (The port tests the squares ahead after the first
   *  refusal; the original marks the members as it tests them.) */
  const bump = (movers: Member[], dx: number, dy: number) => {
    for (const m of movers) {
      const r = barrierRec(level.tile(m.x + dx, m.y + dy)), h = m.hero.rec;
      if (!r || party.at(m.x + dx, m.y + dy)) continue;
      if (r[2] === 0x43) h.h_energy = Math.max(0, (h.h_energy as number) - 10 - rnd(10));
      else h.h_hitpts = Math.max(1, (h.h_hitpts as number) - 1);
      m.hero.isHeTr();
    }
  };
  /** P02 ovl_0d70, a key door (type bit 0x80): the key is item `type & 0x7F` anywhere in the party (not used up). With
   *  it every `spdoors` record's square gets its `newtile` and the carrier says `loctext[text]`; without it
   *  `loctext[text + 1]`. With the key the party then goes through: the door's PGM record (P02 L_198c). */
  const keyDoor = async (d: Door) => {
    const key = d.type & 0x7f, recs = level.loc.keydoor ?? [];
    const carrier = party.members.find(m => m.hero.rec.h_invitem.includes(key));
    if (!recs.length) return void (message = level.tileName(d.x, d.y));
    const t = level.loc.texts[recs[0].text + (carrier ? 0 : 1)] ?? '';
    if (carrier) for (const r of recs) level.set(r.x, r.y, r.newtile);
    const line = format(t.replace(/%a/g, items[key]), carrier?.hero ?? hero, hero.name);
    message = carrier ? `${carrier.hero.name}: ${line}` : line;
    if (!carrier) return;
    const pgm = level.loc.pgms[d.pgm];
    if (pgm?.program === 2) { go(await Level.load(`D${two(pgm.datafile)}`, pgm.tileset), lead.x, lead.y); return; }
    if (pgm?.program === 5) { const said = message; await enterRoom(d); message = said; return; }
    message += ` (P0${pgm?.program} D${two(pgm?.datafile ?? 0)}: not built yet.)`;
  };

  // ---- digging and lockpicking (P02 ovl_1131 Shovel, ovl_1044 Pick; rules/locations.md, Towns) ----
  const chests = new Set<string>();                                  // `_chests`, by level and treasure group
  const mark = (prompt: string, then: (x: number, y: number) => void) => { message = prompt; marking = then; render(); };
  const adjacent = (x: number, y: number) => Math.max(Math.abs(lead.x - x), Math.abs(lead.y - y)) <= 1;
  const spotAt = (x: number, y: number, type: number) => (level.loc.spots ?? []).find(p => p.x === x && p.y === y && p.type === type);
  /** Shovel: "Where shall %h dig?" (0x7F); an unwalkable square without a Look text → "%h is unable to dig there."
   *  (0x80); a type-3 spot whose treasure is still there → its treasure, else "%h finds nothing." (0x81). */
  const dig = (h: Hero) => mark(format(comtxt[0x7f], h, h.name), (x, y) => {
    if (!adjacent(x, y)) return;
    if (!level.walkable(x, y) && !(level.loc.look ?? []).some(l => l.x === x && l.y === y)) return void (message = format(comtxt[0x80], h, h.name));
    const p = spotAt(x, y, 3);
    if (!p) return void (message = format(comtxt[0x81], h, h.name));
    treasure(h, p.d2);
  });
  /** Pick: "Mark the target."; not a type-2 spot → "%h can not use a lockpick on that!" (0x8F). The pick roll
   *  min(99, dex/2 + lockpick) against RndCo(100) (a miss breaks the Pick, 0x90, the lock opens anyway); a trapped spot
   *  (d3: 1 Poisoned, 2 Ill) springs when RndCo(120) > skill (V02 service 0x15: energy and HP halved), else a lockpick
   *  skill roll; then the treasure. */
  const lockpick = (h: Hero) => mark(say(comtxt[0x0d]), (x, y) => {
    if (!adjacent(x, y)) return;
    const p = spotAt(x, y, 2), r = h.rec as Record<string, number> & Hero['rec'];
    if (!p) return void (message = format(comtxt[0x8f], h, h.name));
    panel.show();
    const skill = Math.min(99, (r.h_dextrty >> 1) + r.h_lockpck);
    if (skill <= rnd(100)) { panel.line(comtxt[0x90]); h.dec(h.slot(0x50)); }
    if (p.d3 && skill < rnd(120)) {
      r.h_cond1 |= p.d3 === 1 ? 0x08 : 0x02; r.h_energy >>= 1; r.h_hitpts >>= 1; h.isHeTr();
      const t = (n: number) => format(chamberTexts[n], h, h.name);
      panel.line(`${t(2)} ${chamberTexts[2 + p.d3]}`); panel.line(t(5));
    } else {
      const chance = r.h_lockpck < 50 ? (50 - r.h_lockpck) >> 2 : 1;
      if (r.h_lockpck < cdata.maxtbl[10 * 6 + r.h_race] && rnd(100) < chance) { r.h_lockpck++; panel.line(ctext(0x60, { h: h.name, l: 'Lockpick' })); }
    }
    treasure(h, p.d2);
  });
  const chamberTexts = (await json<{ texts: string[] }>('p07.json')).texts;   // the same trap texts as V02's
  /** The treasure of group `g` (`treasptr`: id, {item, amount}…, 0xFF): taken already → "%h finds nothing."; else
   *  "%h unearths treasure!" (0x82), each item listed (a pair with item 0x80 prints loctext[amount] instead), "Who will
   *  take the treasure?" (0x85) and the chosen member gets all of it (_IncObj; weapons and armour as one, unworn); a
   *  refusal stops there and the question comes back for the rest. */
  const treasure = (h: Hero, g: number) => {
    const key = `${level.id}:${g}`;
    panel.show();
    if (chests.has(key)) { panel.line(format(comtxt[0x81], h, h.name)); return void panel.set([{ label: cmd[0], act: () => close() }]); }
    const t = hex(level.loc.tables.treasptr ?? '');
    let i = 0;
    while (i < t.length && t[i] !== g) { while (i < t.length && t[i] !== 0xff) i++; i++; }
    const loot: [number, number][] = [];
    for (i++; i + 1 < t.length && t[i] !== 0xff; i += 2) loot.push([t[i], t[i + 1]]);
    panel.line(format(comtxt[0x82], h, h.name));
    for (const [item, n] of loot)
      panel.line(item === 0x80 ? format(level.loc.texts[n] ?? '', h, h.name)
        : item >= 9 && item <= 0x30 || n === 1 ? `1 ${items[item]}` : `${n} ${items[item]}${comtxt[0x51]}`);   // _PrtTreasure (assumed form)
    let left = loot.filter(([item]) => item !== 0x80);
    if (!left.length) { chests.add(key); return void panel.set([{ label: cmd[0], act: () => close() }]); }
    const ask = () => {
      panel.line(comtxt[0x85]);
      panel.set(party.members.map(m => ({ label: m.hero.name, act: () => {
        chests.add(key);
        while (left.length) {
          const [item, n] = left[0], w = m.hero, worn = item >= 9 && item <= 0x30;
          const ok = item === 0 ? w.rec.h_gold + n <= 9999 && (w.rec.h_gold += n, true) : incObj(w, item, worn ? 1 : n);
          if (!ok) { panel.line(ctext(w.slot(item) >= 0 ? 0x32 : 0x33, { o: w.name })); return ask(); }
          left = left.slice(1);
        }
        close();
      } })));
    };
    ask();
  };

  // ---- special spots (rules/locations.md, Special spots; P02 ovl_189d/ovl_151a) ----
  const spotTables = await json<{ ambush: { ids: number[]; events: number[] }; remarks: { ids: number[]; events: number[]; locspecs: number[] } }>('spots.json');
  const ambushed = new Set<number>();                                 // `_ambush` bits by ambush id
  let spotsDone = new Set<number>(), spotsLevel = '';                 // `_spetbldone`, kept while on the same level
  /** After a step: the 3×3 squares around the leader, the first record per square (row by row from the top left;
   *  the original's scan order was not traced). */
  const spotsAround = async () => {
    if (spotsLevel !== level.id) { spotsDone = new Set(); spotsLevel = level.id; }
    const list = level.loc.spots ?? [];
    for (let y = lead.y - 1; y <= lead.y + 1; y++) for (let x = lead.x - 1; x <= lead.x + 1; x++) {
      const i = list.findIndex((p, k) => p.x === x && p.y === y && !spotsDone.has(k) && p.type !== 2 && p.type !== 3);
      if (i < 0) continue;
      const p = list[i], on = party.members.some(m => m.x === x && m.y === y);
      if (p.type === 0 && !ambushed.has(p.d2)) return ambushAt(p);
      if ((p.type === 1 || p.type === 5) && on) return jump(p.d1, p.d2, p.d3, comtxt[p.type === 1 ? 0x7b : 0x7e]);
      if (p.type === 6 && remark(p)) spotsDone.add(i);
    }
  };
  /** Type 0, an ambush: group d1, ambush id d2 (its `_ambush` bit set once won; ids 12, 101, 97, 108, 155, 110 also set
   *  events 49, 70, 71, 72, 90, 107 when they trigger). A street fight on the view around the party, `_diff` = locdiff − 1;
   *  the monsters move first unless `RndCo(200)` is below the party's best tracking ("%o detects an ambush!", 0xBB).
   *  (The Sense spell's detection is not modelled.) */
  const ambushAt = (p: { x: number; y: number; d1: number; d2: number }) => {
    const k = spotTables.ambush.ids.indexOf(p.d2);
    if (k >= 0) events.add(spotTables.ambush.events[k]);
    const best = party.members.reduce((a, m) => (m.hero.rec.h_track as number) > (a.hero.rec.h_track as number) ? m : a);
    const seen = sensed === `${p.x},${p.y}` || rnd(200) < (best.hero.rec.h_track as number);
    if (seen) message = format(comtxt[0xbb], hero, best.hero.name);
    const wx = lead.x - 4, wy = lead.y - 3, lv = Level.view(level, wx, wy), diff = Math.max(0, level.loc.locdiff - 1);
    const f = Fight.street(cdata, lv, party.members, p.d1, diff, party.members.map(m => ({ x: m.x - wx, y: m.y - wy })));
    startFight(lv, f, diff, () => ambushed.add(p.d2), null, !seen);
  };
  /** Types 1 (teleportal: "The party is swept into a teleportal!" first) and 5 (hidden chute: "The party slides through
   *  a hidden chute!" after): another level, PGM record `pgm`, with the window at (x, y) (assumed, as for exits). */
  const jump = async (pgm: number, x: number, y: number, text: string) => {
    const g = level.loc.pgms[pgm];
    if (!g || g.program !== 2) { message = text; return; }
    go(await Level.load(`D${two(g.datafile)}`, g.tileset), x + 4, y + 3);
    message = text;
  };
  /** Type 6, a companion's remark: the first of members 1-5 whose race is d1 & 0x7F (d1 ≥ 0x80) or who is companion d1
   *  (0xFE: no speaker needed); none, or event d2 already set (d2 ≠ 0xFF) → nothing, the spot stays armed. Else the
   *  remark-event table (V02 0xBDB) may set an event for this `_locspec`, and `loctext[d3]` is spoken. */
  const remark = (p: { d1: number; d2: number; d3: number }): boolean => {
    const who = p.d1 === 0xfe ? null : party.members.slice(1).find(m => p.d1 >= 0x80 ? m.hero.rec.h_race === (p.d1 & 0x7f) : m.num === p.d1);
    if ((p.d1 !== 0xfe && !who) || (p.d2 !== 0xff && events.has(p.d2))) return false;
    const t = spotTables.remarks;
    for (let k = 0; k < t.ids.length; k++) if (t.ids[k] === p.d3 && t.locspecs[k] === level.loc.locnum) events.add(t.events[k]);
    const text = format(level.loc.texts[p.d3] ?? '', who?.hero ?? hero, hero.name);
    message = who ? `${who.hero.name}: ${text}` : text;
    return true;
  };

  /** _Look (rules/locations.md, Look). Line of sight is not modelled yet: every square counts as visible. */
  const look = (x: number, y: number) => {
    if (chamber && x === 1 && y === 1 && chamber.opened && !(chamber.hr.reward & 0x80)) return chestLook(lead.hero);
    if (chamber && x === 9 && (y === 0 || y === 1) && chamber.hr.reward & 0x80) return fountain(lead.hero);
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
    if (special) text += special.look(x, y, lead);
    if (scene?.scrollAt(x, y)) {                                         // P08 ovl_16e9: the scroll on the floor
      const near = adjacent(x, y);
      panel.show(); panel.line(scene.lookScroll(lead.hero, near));
      if (!near) return void panel.set([{ label: cmd[0], act: () => close() }]);
      return void panel.set([{ label: cmd[3], act: () => close(scene!.pickScroll(lead.hero) ?? '') }, { label: cmd[4], act: () => close() }]);
    }
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
               ...(member !== lead ? [{ label: cmd[6], act: () => assign(member) }, { label: cmd[12], act: () => dismiss(member) }] : []),   // Assign, Dismiss
               { label: cmd[0], act: () => close(message) }]);   // End
  };
  /** Talk + direction: the person there, or "%h talks to" the square (comtxt 0x11). In a service room the keeper
   *  answers whatever square is marked (assumption: how the original routes Talk to `_swgreet = −3` is not traced). */
  const talkAt = async (x: number, y: number) => {
    const who = figures.find(f => f.x === x && f.y === y);
    message = '';
    if (keeper()) return;
    if (!who && special?.talk()) return;                               // the casino: Talk to anyone but the gamblers
    if (who) return talkTo(who);
    message = say(comtxt[0x11]) + level.tileName(x, y) + comtxt[0x10];
  };
  /** Whisper (H; the original's Whisper command): "What magic word will %h whisper?" (comtxt 0xCD), matched against
   *  the location's `gwrds`. A word nothing answers gets "Nothing happens." (0x83; assumed, P09 prints `_comtxtptr`). */
  const whisper = (by: Member = lead) => {
    panel.show();
    if (scene && party.members.length > 1 && by === lead && !speaker) return pick(h => { speaker = party.members.find(m => m.hero === h)!; whisper(speaker); });
    speaker = null;
    panel.line(format(comtxt[0xcd], by.hero, by.hero.name));
    panel.set([{ label: cmd[0], act: () => close() }], w => {
      panel.line(`> ${w}`, 'you');
      if (special?.whisper(w)) return;
      const s = scene?.whisper(wmatch(w, level.loc.words), by);
      close(s ?? comtxt[0x83]);
    }, 'Word');
  };
  // ---- magic outside combat (spells.md, _Magic; P01 slots 13-15, FFFAR) ----
  /** The location program (`__curmpg`) for `_spellshere`: 1 world map, 2 town or dungeon level, 4 patch, 5 service
   *  room, 7 dungeon room, 9 special room. */
  const program = () => special ? 9 : scene ? 8 : chamber ? 7 : service ? 5 : patch ? 4 : level.loc.kind === 'world' ? 1 : 2;
  /** Magic (M): the caster and one of their memorised spells (the original readies it with Recall, `h_rdyspl`, then
   *  casts with Magic). Refused, at no cost, without the energy (`_EneUsg`, comtxt 0x41) or where `_splocs[spell] &
   *  _spellshere[program]` is 0 (0x56). Cast: the effect; a spell that did not go off (carry set) costs nothing;
   *  else a magic skill roll for SKLSPLS, one memorised copy and the energy. */
  const magicCmd = () => {
    panel.show();
    const cast = (h: Hero) => {
      const r = h.rec, known = r.h_spells.flat().map((n, i) => [n, i]).filter(([n]) => n > 0);
      if (!known.length) return close(ctext(0x40, { h: h.name }));                          // "%h must recall a spell first."
      panel.set([...known.map(([n, sp]) => ({ label: `${cdata.spells.names[sp]} (${n})`, act: () => {
        r.h_rdyspl = sp;
        const need = Math.max(1, cdata.spells.energy[sp] - (r.h_magic >> 2));
        if (r.h_energy < need) return close(comtxt[0x41]);                                  // "Not enough energy!"
        const here = cdata.spells.here[program()] | (program() === 2 && level.loc.locdiff ? 4 : 0);   // + _InDungeon
        if (!(cdata.spells.where[sp] & here)) return close(ctext(0x56, { h: h.name }));
        spell(h, sp, (text: string) => {
          const rr = h.rec as Record<string, number>, up = cdata.spells.skill.includes(sp) ? magicUp(h) : '';
          const row = Math.floor(sp / 7), col = sp % 7;
          if (--r.h_spells[row][col] <= 0) { r.h_spells[row][col] = 0; r.h_rdyspl = 0xff; }
          rr.h_energy = Math.max(0, rr.h_energy - need); h.isHeTr();
          close([text, up].filter(Boolean).join(' '));
        });
      } })), { label: cmd[0], act: () => close() }]);
    };
    pick(cast);
  };
  /** The acting member: asked when the party has more than one. */
  const pick = (then: (h: Hero) => void) => {
    if (party.members.length < 2) return then(lead.hero);
    panel.set([...party.members.map(m => ({ label: m.hero.name, act: () => then(m.hero) })), { label: cmd[0], act: () => close() }]);
  };
  /** _SkillUp for magic (skill 3) outside a fight: chance 20 + (50 − skill)/4 % below 50, else 20 − (skill − 50)/2
   *  (at least 1 off), up to _MaxSkill (combat.md, Skill advancement). */
  const magicUp = (h: Hero) => {
    const r = h.rec as Record<string, number>, v = r.h_magic;
    if (v >= cdata.maxtbl[3 * 6 + r.h_race] || rnd(100) >= 20 + (v < 50 ? (50 - v) >> 2 : -Math.max(1, (v - 50) >> 1))) return '';
    r.h_magic = v + 1;
    return ctext(0x60, { h: h.name, l: SKILLS[3][1] });
  };
  /** The spell's effect (SPLVECS); `done(text)` when it went off. Spells not built yet answer "The spell fails." */
  const spell = (h: Hero, sp: number, done: (text: string) => void) => {
    const m = h.rec.h_magic, member = (then: (t: Hero) => void) => panel.set([...party.members.map(p => ({ label: p.hero.name,
      act: () => then(p.hero) })), { label: cmd[0], act: () => close() }]);
    const heal = (t: Hero) => { t.rec.h_hitpts = t.rec.h_hpmax; return ctext(0x5c, { a: t.name }); };
    const shield = (t: Hero, n: number) => { t.rec.h_shield = n; return ctext(0x5e, { a: t.name, b: n }); };
    const dead = (t: Hero) => (t.rec.h_cond1 as number) & 0x80;
    switch (sp) {
      case 8: return member(t => done(dead(t) ? comtxt[0x95] : heal(t)));                  // Heal: HP to the maximum
      case 20: return done(party.members.filter(p => !dead(p.hero)).map(p => heal(p.hero)).join(' '));   // Zengrl
      case 12: return member(t => done(dead(t) ? comtxt[0x95] : (t.use(0x33, 0), ctext(0x5d, { a: t.name }))));   // Energy = a Sermin
      case 16: return member(t => done(dead(t) ? comtxt[0x95] : shield(t, m)));             // Shield = magic skill
      case 21: return done(party.members.filter(p => !dead(p.hero)).map(p => shield(p.hero, m >> 1)).join(' '));   // Zishoxe
      case 26: return member(t => {                                                         // Glamour (FFFAR ovl_3440)
        const c = t.rec.h_charm as number, g = Math.min(c, 12 - c);
        if (c > 11 || dead(t)) return close(comtxt[0x119]);
        t.rec.h_charm = c + g; t.rec.h_glamcnt = (t.rec.h_glamcnt as number) + g;
        done(`${t.name}: ${STATS[6][1]} ${c + g}`);
      });
      case 1:                                                                               // Confuse (P01 ovl_1ae3)
        for (let n = 8 * world.region; n < 8 * world.region + 8; n++) world.engaged.delete(n);
        return done(comtxt[0x43]);
      case 4: locate = m >> 2; return done('');                                             // Locate (P01 ovl_1ac2)
      case 7: return teleport(m, done);
      case 10: return target(h, (x, y) => done(format(comtxt[0xdb], h, h.name) + comtxt[vision(x, y)]));   // Vision
      case 15:                                                                              // Walkwater: dungeons only
        if (!level.loc.locdiff) return done(comtxt[0x95]);
        walkwater = Math.floor(m / 20) + 2;
        return done(ctext(0xc9, { b: walkwater }));
      case 25: detect += m >> 4; return done(ctext(0xf6, { u: detect * 5 }));             // Detect
      case 13: case 3: return target(h, (x, y) => {                                         // Pierce 'C', Repel 'B'
        const r = barrierRec(level.tile(x, y), sp === 13 ? 0x43 : 0x42);
        if (!r) return done(comtxt[0x95]);
        snakes.push([level.id, x, y, r[1]]); level.set(x, y, r[1]);
        done(comtxt[sp === 13 ? 0xe7 : 0xe8]);
      });
      case 39: return done(sense(h, m));                                                    // Sense
      case 40: case 41: {                                                                   // Restsoul, Soulspeak (P08)
        const s = scene?.spell(sp, h);
        return s === null || s === undefined ? close(ctext(0x56, { h: h.name })) : done(s);
      }
    }
    close(comtxt[0x119]);
  };
  /** _Target: mark any square ("Mark the target.", comtxt 0x0D); cancelling (Escape) casts nothing. */
  const target = (h: Hero, then: (x: number, y: number) => void) => { close(); mark(format(comtxt[0x0d], h, h.name), then); };
  /** V02 INT60_00 (Vision): a door there names what is behind it - rooms of types 6-9 by their HROOM record and whether
   *  their guards were beaten (`_dunrms`): 0xE1-0xE3 / 0xE4-0xE6 for no reward, a chest, a fountain; other doors by the
   *  band of their id (V02 0x8C → comtxt 220-223). No door: "nothing. Try a door." (0xE0). */
  const vision = (x: number, y: number) => {
    const d = level.loc.doors.find(e => e.x === x && e.y === y);
    if (!d) return 0xe0;
    if (d.type < 6 || d.type > 9) return v02.vision.texts[v02.vision.ids.findIndex(t => t > d.id)];
    const hr = level.loc.hrooms?.find(r => r.id === d.id);
    const k = !hr || !(hr.reward || hr.amount) ? 0 : hr.reward < 0x80 ? 1 : 2;
    return (dunrms.has(`${level.id}:${d.id}`) ? 0xe4 : 0xe1) + k;
  };
  /** The tileset's `aniptr` record (7 bytes: tile, new tile, class, cycle…) of `tile` with barrier class `cls`
   *  ('C' 0x43 Pierce, 'B' 0x42 Repel), scanned as V02 does in steps of 7. */
  const barrierRec = (tile: number, cls?: number) => {
    const a = hex(level.data.anim);
    for (let i = 0; i < a.length && a[i] !== 0xff; i += 7)
      if (a[i] === tile && (cls === undefined ? a[i + 2] === 0x43 || a[i + 2] === 0x42 : a[i + 2] === cls)) return a.slice(i, i + 7);
    return null;
  };
  /** V02 INT60_13 (Sense): the nearest ambush spot not yet fought (`_ambush`), squared distance from the leader below
   *  255 and at most (magic/4)²: "%h senses an ambush to the " (0x9D) + a direction (0x9E + V02 0x7FE table), and
   *  that spot is then always detected (P02 cs:0x133); else "%h senses nothing." (0x9C). */
  const sense = (h: Hero, m: number) => {
    let best = 0xff, at: { x: number; y: number } | null = null;
    for (const p of level.loc.spots ?? []) {
      if (p.type !== 0 || ambushed.has(p.d2)) continue;
      const d = (p.x - lead.x) ** 2 + (p.y - lead.y) ** 2;
      if (d < best) { best = d; at = p; }
    }
    if (!at || (m >> 2) ** 2 < best) return format(comtxt[0x9c], h, h.name);
    sensed = `${at.x},${at.y}`;
    let a = at.x - lead.x, b = lead.y - at.y, f = 0;                                   // ovl_082e: b > 0 = north
    if (a < 0) { f |= 8; a = -a; }
    if (b < 0) { f |= 4; b = -b; }
    if (b + 2 <= a * 3) f |= 2;
    if (b * 3 <= a + 1) f |= 1;
    return format(comtxt[0x9d], h, h.name) + comtxt[0x9e + v02.sense[f]];
  };
  /** Teleport (P01 ovl_1b02 → P89): not aboard (region text 0x1A) or while camping (0x19). The magic skill picks a
   *  tier ([10, 30, 50, 70, 90], below 10 nothing) and the window rectangle the target must lie in; the target is not
   *  the party's square, a live guard post or patrol, a town entrance or feature, or in P89's three no-teleport
   *  rectangles, and is walkable. A bad target or cancelling casts nothing (assumed: P89's carry is not traced). */
  const teleport = (m: number, done: (text: string) => void) => {
    const rec = world.rec!;
    if (world.ships.sailing) return close(rec.texts[0x1a]);
    if (shipCamp) return close(rec.texts[0x19]);
    const t = p89.tiers.filter(v => v <= m).length - 1, wx = lead.x - 5, wy = lead.y - 4;
    close();
    mark(say(comtxt[0x0d]), (x, y) => {
      const sx = x - wx, sy = y - wy;
      const ok = t >= 0 && sx >= p89.x0[t] && sx < p89.x1[t] && sy >= p89.y0[t] && sy < p89.y1[t] && !(sx === 5 && sy === 4)
        && !world.guards().some(g => g.x === x && g.y === y) && world.patrolAt(x, y) < 0
        && !rec.exits.some(e => e.x === x && e.y === y) && !rec.doors.some(d => d.x === x && d.y === y)
        && !p89.rects.some(([x0, y0, x1, y1]) => x >= x0 && x <= x1 && y >= y0 && y <= y1) && level.walkable(x, y);
      if (!ok) { message = comtxt[0x119]; return; }
      party.shift(x - lead.x, y - lead.y);
      void world.at(x, y, clock).then(() => { world.engage(x, y); done(''); render(); });
    });
  };
  /** _SkillUp0 (combat.md): skill `idx` (SKILLS order) +1 with chance (50 − skill)/4 % below 50, else 1 %, up to
   *  _MaxSkill; returns comtxt 0x60 or ''. */
  const skillUp0 = (h: Hero, idx: number) => {
    const r = h.rec as Record<string, number>, [f, l] = SKILLS[idx], v = r[f];
    if (v >= cdata.maxtbl[idx * 6 + r.h_race] || rnd(100) >= (v < 50 ? (50 - v) >> 2 : 1)) return '';
    r[f] = v + 1;
    return ctext(0x60, { h: h.name, l });
  };
  let shipCamp: (() => void) | null = null;   // camping aboard: one camp pass per sailing step (P93 SUB_04d4)
  /** `_CAMPSITE` (P93 ovl_1099): world map 2 (aboard 4), a P07 dungeon room 8, inn rooms 0x40-0x47 0x20, the camp
   *  rooms 0x5C-0x6B 0x10, else 1. Not built: `_locspec` 0x14 room 9 (also a guest room). */
  const campsite = () => level.loc.kind === 'world' && !patch ? world.ships.sailing ? SHIP : OPEN : chamber ? DUNGEON
    : service && service.room >= 0x40 && service.room < 0x48 ? INNROOM : service && service.room >= 0x5c && service.room < 0x6c ? GUEST : 1;
  /** Camp (C). In a P05 inn room P05 first refuses the keeper's side (acting member at x ≥ 4 and y ≥ 5: comtxt 0x24);
   *  when camp ends with the rent used up, the party goes back to the base square and the keeper speaks (ovl_19b0/167f). */
  const campCmd = () => {
    if (world.ships.passage === 1 && world.ships.sailing) { message = shipText(world.ships.cur, 0x27); return render(); }   // working for passage
    const inn = service?.kind === INN && service.room < 0x5c ? service.room - 0x40 : -1;
    if (inn >= 0 && lead.x >= 4 && lead.y >= 5) { message = say(comtxt[0x24]); return render(); }
    camp({ party, clock, cmd, p93, items, comtxt, site: campsite(), terrain: level.data.nameindex[level.tile(lead.x, lead.y)],
      hunt: p93tables.hunt, speltim: tables.speltim, spells: cdata.spells.names, skillUp: skillUp0,
      use: () => useCmd(), tick, rent: () => inn >= 0 ? rent[inn] : null, sail: p => { shipCamp = p; },
      wild: watch => {                                                   // P01 ovl_169e and the fight check (ovl_0846)
        world.movePatrols(level, lead.x, lead.y, clock.month);
        const n = world.patrolAt(lead.x, lead.y);
        if (n < 0) { world.engage(lead.x, lead.y); return false; }
        void wildFight(undefined, n, !watch);
        return true;
      }, done: () => {
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
      // The Conch (ovl_1349, the original's K command): aboard on row 100 it calms the rough sea (event 102)
      const sc = scene?.use(item, party.members.find(m => m.hero === who)!);
      if (sc) return done(sc);
      if (item === 0x4b) return done(world.ships.sailing && lead.y === 100
        ? (events.add(102), format(world.rec!.texts[0x2a], who, who.name)) : comtxt[0x83]);
      if (special?.piece(item)) {                                      // a teleportal piece on a pedestal (P09)
        close();
        return mark(say(comtxt[0x0d]), (x, y) => {
          const to = adjacent(x, y) ? special!.place(item, x, y, who) : null;
          if (to) void toWorldAt(to.x, to.y).then(render);
        });
      }
      if (item === 0x40) return who === hero ? recallAway() : done(format(comtxt[0x1d], hero, hero.name));   // "Only %h can do that."
      if (chamber?.candle && item === 0x4a + chamber.type && !chamber.freed && !events.has(0x3c + chamber.type)) return done(candle(who, item));
      if (chamber && item === 0x50 && chamber.hr.reward && !(chamber.hr.reward & 0x80)) return openChest(who);
      if (level.loc.kind === 'level' && (item === 0x50 || item === 0x46)) { close(); return item === 0x50 ? lockpick(who) : dig(who); }
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
  /** Assign (P88 entry 0): a volunteer leaves the party to wait here and then go to a stronghold, to go to one now, or
   *  — in a school, library or lodge — to finish the task they started there (a job has no afterwards). The record
   *  takes their task and purse; they stand where they were (_AssignedHere) and rejoin when invited. */
  const assign = (m: Member) => {
    const r = m.hero.rec as HeroRecord & Record<string, number>, name = m.hero.name, fmt = (s: string) => format(s, hero, name);
    panel.show();
    if (r.h_relatn !== 1) return close(comtxt[0x6f]);                   // "Only companions can be assigned tasks."
    const at = { ...spot(), x: m.x, y: m.y }, w = wildxy(), make = (go: number | null) => assigns.make(m.num, r, clock, at, w, world.region, go);
    const part = () => {                                                // P97 with `_swass` 1: out of the party, kept off the tables
      party.partyEvents(events, p97.events, m.num, false);
      party.remove(m); party.away.add(m.num);
      figures = people(); close(`${name} leaves the party.`);
    };
    const pick = (q: string, then: (n: number) => void) => {
      panel.line(`${name}: ${fmt(q)}`);
      panel.set([...assigns.dests(been).map(n => ({ label: assigns.destName(n), act: () => then(n) })), { label: cmd[0], act: () => close() }]);
    };
    const kind = service?.kind ?? 0;
    if (kind >= SCHOOL && kind <= LODGE) {                              // `_curvar` 8-11: the task started here
      if (r.h_actvty === 0xff) return close(fmt(comtxt[0x70] + comtxt[0x11a + kind + 0x12] + comtxt[0x71]));   // "%o must talk to the instructor first."
      const keep = (go: number | null) => {
        Object.assign(make(go), { as_task: r.h_actvty, as_misc: r.h_actmisc, as_date: r.h_actdate, as_hour: r.h_acthour, as_daysleft: r.h_actdays });
        r.h_helped |= 0x80; part();
      };
      return kind === JOB ? keep(null) : pick(comtxt[0x73], keep);
    }
    panel.line(name);
    panel.set([
      { label: assigns.menu[0], act: () => pick(comtxt[0x74], n => {   // Go to: "Should %o get going now?"
        panel.line(fmt(comtxt[0x75]));
        panel.set([{ label: cmd[3], act: () => { assigns.travel(make(null), n, w); part(); } }, { label: cmd[4], act: () => close() }]);
      }) },
      { label: assigns.menu[1], act: () => {                            // Stay: 1-30 days, then a stronghold
        panel.line(`${name}: ${comtxt[0x72]}`);
        panel.set([{ label: cmd[0], act: () => close() }], word => {
          const days = Number(word);
          if (!Number.isInteger(days) || days < 1 || days > 30) return close();
          pick(comtxt[0x73], go => { Object.assign(make(go), { as_task: 7, as_daysleft: days }); part(); });
        }, '1–30');
      } },
      { label: cmd[0], act: () => close() }]);
  };
  /** Recall (P88 entry 1, Use the Mindstone): the companions away from the party who carry a Mindstone, then one's
   *  Assignment Report; anyone but a prisoner can be sent to another stronghold from where they are now (Go to). */
  const recallAway = () => {
    const away = r90.map((_, i) => i + 1).filter(n => !party.members.some(m => m.num === n) && (party.stored(n) ?? r90[n - 1]).h_invitem.includes(0x40));
    if (!away.length) return close();                                   // the original just returns
    const report = (n: number) => {
      const name = r90[n - 1].h_name, a = assigns.get(n);
      panel.show();
      for (const l of assigns.report(n, name, items, hero.name, tables.tod.words[tables.tod.hour[clock.hour]])) panel.line(l);
      if (!a) return panel.set([{ label: cmd[0], act: () => close() }]);
      panel.set([...(a.as_task === JAILED ? [] : [{ label: assigns.menu[0], act: () => {
        panel.line(format(assigns.text(57), hero, name));                   // "Where will %o go?"
        panel.set([...assigns.dests(been).map(d => ({ label: assigns.destName(d), act: () => { assigns.redirect(a, d, clock); figures = people(); close(); } })),
          { label: cmd[0], act: () => close() }]);
      } }]), { label: assigns.menu[2], act: () => close() }]);           // Continue
    };
    panel.show();
    panel.set([...away.map(n => ({ label: r90[n - 1].h_name, act: () => report(n) })), { label: cmd[0], act: () => close() }]);
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
      figures = people();
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
  // ---- saving (decision 4): the port's own JSON snapshot in localStorage, three slots, only between activities ----
  const SLOTS = 3, slotKey = (n: number) => `mc2.save.${n}`;
  const store = {   // localStorage may be missing or refuse (private windows); a failed save says so
    get: (k: string) => { try { return localStorage.getItem(k); } catch { return null; } },
    set: (k: string, v: string) => { try { localStorage.setItem(k, v); return true; } catch { return false; } },
  };
  const snapshot = () => ({
    v: 1, when: new Date().toISOString(), place: place() || world.rec?.name || '',
    clock: { minute: clock.minute, hour: clock.hour, date: clock.date, month: clock.month, weather: clock.weather, juldate: clock.juldate },
    events: [...events], party: party.snapshot(), level: { id: level.id, ts: level.tileset }, at: { x: lead.x, y: lead.y },
    world: world.snapshot(), patches: [...patches.left], dunrms: [...dunrms], duntre: [...duntre], chests: [...chests],
    ambushed: [...ambushed], rent: [...rent], walk: [walkSteps, walkTicks], casino: [...casino], gates: [...gates],
    detect, snakes: snakes.map(r => [...r] as [string, number, number, number]), scroll: scroll.item, disasterday,
    assigns: assigns.snapshot(), wild: wildAt, been,
  });
  type Save = ReturnType<typeof snapshot>;
  const canSave = () => !fight && !patch && !chamber && level.loc.kind !== 'room';
  const restore = async (sv: Save) => {
    Object.assign(clock, sv.clock);
    events.clear(); for (const e of sv.events) events.add(e);
    party.restore(sv.party, items);
    await world.restore(sv.world);
    patches.left.splice(0, patches.left.length, ...sv.patches);
    for (const [set, vals] of [[dunrms, sv.dunrms], [duntre, sv.duntre], [chests, sv.chests]] as [Set<string>, string[]][]) { set.clear(); vals.forEach(v => set.add(v)); }
    ambushed.clear(); sv.ambushed.forEach(v => ambushed.add(v));
    rent.splice(0, rent.length, ...sv.rent);
    casino.splice(0, 8, ...(sv.casino ?? casino.map(() => 1000)));
    gates.clear(); (sv.gates ?? []).forEach(g => gates.add(g));
    detect = sv.detect ?? 0; snakes.splice(0, snakes.length, ...(sv.snakes ?? []));
    scroll.item = sv.scroll ?? 0; disasterday = sv.disasterday ?? 0;
    if (sv.assigns) assigns.restore(sv.assigns); else assigns.reset();
    wildAt = sv.wild ?? { x: 29, y: 56 }; been = sv.been ?? 0x8000;
    [walkSteps, walkTicks] = sv.walk;
    outside = null; service = null; special = null; scene = null; patch = null; fight = null; chamber = null; chamberBack = null; shipCamp = null;
    go(await Level.load(sv.level.id, sv.level.id === 'D01' ? undefined : sv.level.ts), sv.at.x, sv.at.y);
    message = '';
  };
  /** G: the game panel — save to or load from a slot, or start over. */
  const gameMenu = () => {
    const saved = (n: number) => { try { return JSON.parse(store.get(slotKey(n)) ?? 'null') as Save | null; } catch { return null; } };
    const label = (n: number) => { const sv = saved(n); return sv ? `${n}: ${sv.place}, ${new Date(sv.when).toLocaleString()}` : `${n}: empty`; };
    panel.show();
    const menu = () => panel.set([
      ...(canSave() ? Array.from({ length: SLOTS }, (_, i) => ({ label: `Save ${label(i + 1)}`, act: () => {
        panel.line(store.set(slotKey(i + 1), JSON.stringify(snapshot())) ? `Saved to slot ${i + 1}.` : 'This browser refused to save.'); menu();
      } })) : []),
      ...Array.from({ length: SLOTS }, (_, i) => i + 1).filter(n => saved(n)).map(n => ({ label: `Load ${label(n)}`, act: () => {
        void restore(saved(n)!).then(() => { close(); render(); });
      } })),
      { label: 'New game', act: () => location.assign(location.pathname) },
      { label: cmd[0], act: () => close() }]);
    if (!canSave()) panel.line('Saving is possible on a town or dungeon level or on the world map.');
    menu();
  };

  let looking = false, talking = false;
  let marking: ((x: number, y: number) => void) | null = null;   // _Mark: the next direction picks a square
  view.canvas.addEventListener('click', e => {
    if (panel.open) return;
    const t = view.cellAt(e, level.loc.kind === 'room' ? 5 : lead.x, level.loc.kind === 'room' ? 4 : lead.y);
    if (marking) { const f = marking; marking = null; message = ''; f(t.x, t.y); render(); return; }   // _Mark by clicking
    look(t.x, t.y);
  });

  const KEYS: Record<string, [number, number]> = {
    ArrowUp: [0, -1], ArrowDown: [0, 1], ArrowLeft: [-1, 0], ArrowRight: [1, 0],
    w: [0, -1], s: [0, 1], a: [-1, 0], d: [1, 0],
  };
  let queue = Promise.resolve();   // steps run in order; keys pressed while a room loads are not lost
  addEventListener('keydown', e => {
    if (fight) {
      if (heading) { heading = false; return; }                   // any key ends Head (after the current action)
      const k = KEYS[e.key];
      if (k && actor && !autoHeroes.has(actor.recno)) { e.preventDefault(); fightStep(...k); }
      return;
    }
    if (panel.open) return;
    if (e.key === 'i' || e.key === 'I') { sheet(); return; }
    if (e.key === 'g' || e.key === 'G') { gameMenu(); return; }
    if (e.key === 'l' || e.key === 'L') { looking = true; message = say(comtxt[0x0d]); render(); return; }   // "Mark the target."
    if (e.key === 'c' || e.key === 'C') { campCmd(); return; }
    if (e.key === 'u' || e.key === 'U') { useCmd(); return; }
    if (e.key === 'h' || e.key === 'H') { whisper(); return; }
    if (e.key === 'm' || e.key === 'M') { magicCmd(); return; }
    if (e.key === 'Escape' && marking) { marking = null; message = ''; render(); return; }
    if (e.key === 't' || e.key === 'T') { talking = true; message = say(comtxt[0x0d]); render(); return; }
    const k = KEYS[e.key];
    if (!k) return;
    e.preventDefault();
    if (looking) { looking = false; look(lead.x + k[0], lead.y + k[1]); return; }
    if (marking) { const f = marking; marking = null; message = ""; f(lead.x + k[0], lead.y + k[1]); render(); return; }
    if (talking) { talking = false; void talkAt(lead.x + k[0], lead.y + k[1]).then(render); return; }
    queue = queue.then(() => step(...k)).catch(err => { status.textContent = String(err); console.error(err); });
  });
  if ('slot' in start) {                                       // Continue: the chosen slot
    try { await restore(JSON.parse(localStorage.getItem(`mc2.save.${start.slot}`)!)); } catch (e) { message = String(e); }
  }
  const [wx, wy] = (q.get('world') ?? '').split(',').map(n => parseInt(n));
  if (import.meta.env.DEV && wx >= 0 && wy >= 0) {             // dev aid: ?world=x,y starts on the world map
    const [x, y] = [wx, wy];
    go(await Level.load('D01'), x, y);
    await world.at(x, y, clock);
    message = '';
  }
  if (import.meta.env.DEV) Object.assign(window, { dbg: { party, world, clock, events, assigns, dunrms, get level() { return level; }, get fight() { return fight; } } });   // for scripts/shot.mjs eval:
  render();
}

main().catch(e => { status.textContent = String(e); console.error(e); });
