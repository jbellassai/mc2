// Companions on assignment (rules/assignments.md): `_assgn0`, 31 records, record n − 1 for companion n. Assign
// (P88 entry 0) sends a member of the party off to wait, to travel to a stronghold, or to finish a service-room task;
// the record lives on while they are away. P92 ovl_0561 runs each record once a day at the hour it was made; Recall
// (P88 entry 1, Use the Mindstone) reports on them and can send a traveller elsewhere. Travellers can be caught on the
// road and jailed in a region's dungeon; a jailed companion is set free by entering the cell (P07 ovl_05ad).
import { json } from './pack';
import { SKILLS, type HeroRecord } from './hero';
import type { Clock } from './clock';

export type Rec = Record<string, number>;
interface Data {
  start: Rec[]; menu: string[]; texts: string[]; dests: string[]; destxy: number[][]; places: string[];
  locplace: number[]; homes: number[]; jail: number[]; rects: number[][]; cands: number[][];
  prisons: { id: number[]; loc: number[]; x: number[]; y: number[] }; rescue: string;
}
export const WAIT = 7, TRAVEL = 8, JAILED = 0x65, IDLE = 0xff;
const rnd = (n: number) => Math.floor(Math.random() * n);

export class Assignments {
  readonly recs: (Rec | null)[] = Array(31).fill(null);

  private constructor(readonly d: Data) { this.reset(); }
  static async create(): Promise<Assignments> { return new Assignments(await json<Data>('assign.json')); }

  /** New game (P81 init): all free but four companions who start in jail. */
  reset() { this.recs.fill(null); for (const r of this.d.start) this.recs[r.as_npc - 1] = { ...r }; }
  snapshot() { return this.recs.map(r => r && { ...r }); }
  restore(s: (Rec | null)[]) { s.forEach((r, i) => { this.recs[i] = r && { ...r }; }); }

  get(n: number): Rec | null { return this.recs[n - 1] ?? null; }
  take(n: number): Rec | null { const r = this.get(n); this.recs[n - 1] = null; return r; }

  /** _AssignedHere: at this location and room, not on the road, in this dungeon room (`_hroomrec`, else 0xFF). */
  here(loc: number, room: number, hroom: number): Rec[] {
    return this.recs.filter((r): r is Rec => !!r && r.as_task !== TRAVEL && r.as_loc === loc && r.as_room === room && r.as_hroom === hroom);
  }

  /** The 16 region rectangles (P88 file 0x26B = P92 file 0xC2): the first that holds (x, y). */
  region(x: number, y: number): number {
    return this.d.rects.findIndex(([x0, y0, x1, y1]) => x >= x0 && x <= x1 && y >= y0 && y <= y1);
  }
  /** P88 0x76F: travel days = (max + (min + 2)/4) >> 4 of |dx|, |dy|, the sum saturating at 255; at least 1. */
  static days(fx: number, fy: number, tx: number, ty: number): number {
    const a = Math.abs(fx - tx), b = Math.abs(fy - ty);
    return Math.max(1, Math.min(255, Math.max(a, b) + ((Math.min(a, b) + 2) >> 2)) >> 4);
  }
  /** Stronghold n's room id and square (P88 file 0xAB). */
  dest(n: number) { const [room, x, y] = this.d.destxy[n]; return { room, x, y }; }
  /** The destinations offered: the strongholds visited (`_beenflg`, bit 15 = entry 0). */
  dests(been: number): number[] { return [...Array(16).keys()].filter(n => been & 0x8000 >> n); }
  destName(n: number) { return this.d.dests[n] ?? ''; }
  text(n: number) { return this.d.texts[n]; }
  get menu() { return this.d.menu; }
  get rescueText() { return this.d.rescue; }

  /** A traveller's square (P88 0xCE9, P92 ovl_0b40): from + (to − from)·elapsed/total, rounded. The original adds
   *  (from − to), carrying them away from where they are going; the port interpolates towards it. */
  position(r: Rec): { x: number; y: number } {
    const total = r.as_godays, done = total - r.as_daysleft;
    const step = (f: number, t: number) => !total ? f : done >= total ? t : f + Math.sign(t - f) * Math.floor((Math.abs(t - f) * done + (total >> 1)) / total);
    return r.as_task !== TRAVEL ? { x: r.as_wildx, y: r.as_wildy } : { x: step(r.as_wildx, r.as_gowildx), y: step(r.as_wildy, r.as_gowildy) };
  }

  /** P88 ovl_09a8/ovl_0909: a new record for the member at (x, y) here; `go` = the stronghold they go to after. */
  make(npc: number, hero: HeroRecord, clock: Clock, at: { loc: number; room: number; hroom: number; x: number; y: number },
       wild: { x: number; y: number }, region: number, go: number | null): Rec {
    const d = go === null ? null : this.dest(go);
    const r: Rec = {
      as_npc: npc, as_loc: at.loc, as_room: at.room, as_x: at.x, as_y: at.y, as_task: IDLE, as_done: IDLE,
      as_misc: 0, as_race: hero.h_race as number, as_tile: 0, as_hroom: at.hroom, as_region: region,
      as_wildx: wild.x, as_wildy: wild.y, as_goreg: go ?? IDLE, as_gowildx: d?.x ?? 0, as_gowildy: d?.y ?? 0,
      as_gold: hero.h_gold as number, as_date: clock.date, as_hour: clock.hour, as_daysleft: 0,
      as_goloc: d ? 1 : 0, as_goroom: d?.room ?? IDLE, as_godays: d ? Assignments.days(wild.x, wild.y, d.x, d.y) : 0 };
    hero.h_gold = 0;                                                   // ovl_0a62: the purse goes along
    this.recs[npc - 1] = r;
    return r;
  }
  /** Assign *Go to*: on the road to stronghold n at once (as_loc 1 = the world map, as_room = its room). The original
   *  leaves `as_godays` unset here; the port sets it to the journey so the traveller's square can be worked out. */
  travel(r: Rec, n: number, wild: { x: number; y: number }) {
    const d = this.dest(n), days = Assignments.days(wild.x, wild.y, d.x, d.y);
    Object.assign(r, { as_task: TRAVEL, as_daysleft: days, as_godays: days, as_loc: 1, as_room: d.room, as_goloc: 1,
                       as_goroom: d.room, as_hroom: IDLE, as_goreg: n, as_gowildx: d.x, as_gowildy: d.y });
  }
  /** Recall's new destination (P88 0xC80): on the road from where the traveller is now. */
  redirect(r: Rec, n: number, clock: Clock) {
    const p = this.position(r), d = this.dest(n), days = Assignments.days(p.x, p.y, d.x, d.y);
    Object.assign(r, { as_date: clock.date, as_hour: clock.hour, as_daysleft: days, as_godays: days, as_loc: 1, as_goloc: 1,
                       as_room: d.room, as_goroom: d.room, as_wildx: p.x, as_wildy: p.y, as_gowildx: d.x, as_gowildy: d.y,
                       as_goreg: n, as_region: this.region(p.x, p.y), as_task: TRAVEL, as_done: IDLE });
  }

  /** P92 ovl_0561, every hour: each record once a day at its hour. `hero(n)` = the companion's record as they left
   *  (`_member6`); returns the companions who quit (ovl_08f7) — they go home (`_npcsta` cleared by the caller). */
  daily(clock: Clock, hero: (n: number) => HeroRecord, lrnTim: (spell: number, h: HeroRecord) => number): number[] {
    const quit: number[] = [];
    for (const r of this.recs) {
      if (!r || r.as_date === clock.date || r.as_hour !== clock.hour) continue;
      const h = hero(r.as_npc) as unknown as Rec & HeroRecord;
      if (r.as_task < 0x5a) this.step(r, h, lrnTim);
      else { r.as_date++; if (r.as_task < 0x5e) r.as_gold = Math.min(9999, r.as_gold + r.as_misc); }   // jobs: the wage
      if (this.leaves(r, h)) { h.h_gold += r.as_gold; h.h_actvty = IDLE; this.recs[r.as_npc - 1] = null; quit.push(r.as_npc); }
    }
    return quit;
  }

  /** ovl_05b1: a day of the countdown; at 0 the task's reward, then the road to the stronghold chosen. */
  private step(r: Rec, h: Rec & HeroRecord, lrnTim: (spell: number, h: HeroRecord) => number) {
    if (r.as_daysleft) {
      r.as_daysleft--;
      if (r.as_task === TRAVEL && this.caught(r, h)) return;
      if (r.as_task >= 0x28 && r.as_task < 0x2f) this.study(r, h, lrnTim);
      if (r.as_daysleft) return;
    }
    const t = r.as_done = r.as_task;
    if (t === TRAVEL) return this.arrive(r);
    if (t >= 10 && t < 0x1e) h[SKILLS[t - 10][0]] += r.as_misc;       // ovl_07b0: no cap
    else if (t >= 0x1e && t < 0x22) { const s = h.h_invitem.indexOf(t + 0x2e); if (s >= 0) h.h_invamt[s] |= 0x80; }   // deciphered
    Object.assign(r, { as_task: TRAVEL, as_loc: r.as_goloc, as_room: r.as_goroom, as_hroom: IDLE, as_daysleft: r.as_godays });
    if (!r.as_daysleft) this.arrive(r);
  }
  private arrive(r: Rec) { Object.assign(r, { as_x: 5, as_y: 2, as_wildx: r.as_gowildx, as_wildy: r.as_gowildy, as_task: IDLE }); }

  /** ovl_0828: up to 150 learn-ticks of random spells of the book's group below 99; all at 99 ends the task. */
  private study(r: Rec, h: HeroRecord, lrnTim: (spell: number, h: HeroRecord) => number) {
    const g = 6 * (r.as_task - 0x28), row = (s: number) => h.h_spells[Math.floor(s / 7)];   // spell id = row·7 + column
    for (let left = 150; ;) {
      const open = [0, 1, 2, 3, 4, 5].map(i => g + i).filter(s => row(s)[s % 7] < 99);
      if (!open.length) { r.as_daysleft = 0; return; }
      const s = open[rnd(open.length)], cost = lrnTim(s, h);
      if (cost > left) return;
      left -= cost; row(s)[s % 7]++;
    }
  }

  /** ovl_0716 / ovl_06b3: one day in ten a stealth roll; failed, the traveller is jailed in the first prison listed for
   *  the region they are in (the original's test for an occupied cell compares the wrong field, so it is always the
   *  first). Regions 0 and 7 have none. Their coins are lost. */
  private caught(r: Rec, h: Rec): boolean {
    if (rnd(10) || rnd(100) < h.h_stealth) return false;
    const p = this.position(r), cand = this.d.cands[this.region(p.x, p.y)]?.find(c => c !== 0xff);
    if (cand === undefined) return false;
    const i = this.d.prisons.id.indexOf(cand), pr = this.d.prisons;
    Object.assign(r, { as_loc: pr.loc[i], as_hroom: cand, as_room: IDLE, as_x: 2, as_y: 2, as_wildx: pr.x[i], as_wildy: pr.y[i],
                       as_task: JAILED, as_done: IDLE, as_gold: 0 });
    return true;
  }

  /** ovl_08f7, the morale check (not in jail or a god's service): travellers and waiters always, workers once their
   *  earnings >> 10 reach their loyalty (9999 coins: they quit), the others once loyalty ≤ the days left. */
  private leaves(r: Rec, h: Rec): boolean {
    const t = r.as_task;
    if (t === 100 || t === JAILED) return false;
    if (t !== WAIT && t !== TRAVEL) {
      const job = t >= 0x5a && t <= 0x5d;
      if (job && r.as_gold > 9998) return true;
      if ((job ? r.as_gold >> 10 : r.as_daysleft) < h.h_loyalty) return false;
    }
    const sum = (h.h_attitude + h.h_loyalty) & 0xff;
    h.h_attitude = sum < 15 ? 0 : sum - 15;
    return h.h_attitude <= 40 && rnd(80) > h.h_attitude && rnd(12) >= h.h_loyalty;
  }

  /** P07 ovl_05ad: entering a prison cell frees every captive in it; four of them also set an event (P07 file 0x56A). */
  rescue(loc: number, hroom: number, place: (x: number, y: number) => { x: number; y: number }, events: Set<number>): Rec[] {
    const freed = this.here(loc, IDLE, hroom).filter(r => r.as_task === JAILED);
    for (const r of freed) {
      r.as_task = IDLE;
      ({ x: r.as_x, y: r.as_y } = place(2, 4));
      const k = this.d.jail.indexOf(r.as_npc);
      if (k >= 0 && k < 4) events.add(this.d.jail[k + 4]);
    }
    return freed;
  }

  /** Recall's Assignment Report (P88 0xEB2), as lines; `name` the companion, `items` the item names. */
  report(n: number, name: string, items: string[], hero: string, tod: string): string[] {
    const r = this.get(n), T = this.d.texts;
    const f = (s: string, v: Record<string, string | number> = {}) =>
      s.replace(/%([obiah])/g, (_, k) => String(k === 'o' ? name : k === 'h' ? hero : k === 'a' ? tod : v[k] ?? ''));
    let s = '';
    if (!r) {                                                           // no record: home (P88 file 0x24B, by NPC)
      let home = this.d.homes[n];
      if (home === 3 && this.d.jail.slice(0, 4).includes(n)) home = 0;  // the event test is lost to a flags bug: Castle Oshcrun
      return [`${T[0]}`, `${name}`, this.d.places[home], f(T[46])];
    }
    const place = (loc: number) => this.d.places[this.d.locplace[loc] ?? 0];
    const stronghold = (room: number) => room >= 0x5c && room < 0x6c ? this.d.dests[room - 0x5c] : place(r.as_loc);
    const finish = () => f(T[48], { b: r.as_daysleft }) + (r.as_goroom === IDLE ? '' :
      f(T[51]) + T[52] + this.d.dests[r.as_goroom - 0x5c] + ',%n' + f(T[53], { b: r.as_godays }));
    const t = r.as_task;
    if (t === TRAVEL || t === IDLE) s = T[r.as_daysleft ? 1 : 2] + stronghold(r.as_room) + (r.as_daysleft ? f(T[49], { b: r.as_daysleft }) : '');
    else if (t === WAIT) s = T[3] + (r.as_loc === 1 ? this.d.dests[r.as_region] : place(r.as_loc)) + '%n' + f(T[48], { b: r.as_daysleft });
    else if (t < 0x1e) s = T[5] + T[13 + t - 10] + '%n' + finish();
    else if (t < 0x28) s = T[4] + T[36 + t - 0x1e] + '%n' + finish();
    else if (t < 0x5a) s = T[6] + items[0x53 + t - 0x28] + '%n' + finish();
    else if (t <= 0x5d) s = T[7] + T[32 + t - 0x5a] + '%n' + T[9] + place(r.as_loc) + '.';
    else if (t === JAILED) s = T[8];
    s += '%n';
    if (!(t === TRAVEL && r.as_daysleft)) s += f(T[55], { b: r.as_wildx, i: r.as_wildy });
    s += f(T[54], { i: r.as_gold });
    if (t !== JAILED) s += f(T[47]);
    return [T[0], name, ...s.split('%n').map(x => x.trim()).filter(Boolean)];
  }
}

