// Service rooms run by P05 (docs/rules/services.md): inn, school, jobs, library, wizards' lodge.
// Texts are the room D-file's own (D07-D11) plus common text; tables come from p05.json.
import { json } from './pack';
import { format, wmatch } from './talk';
import { SKILLS, type Hero } from './hero';
import { panel } from './panel';
import type { Clock } from './clock';

interface P05 {
  leave: number[];
  inn: { price: number[] };
  school: { skill: number[]; cost: number[]; days: number[]; gain: number[]; cap: number[][] };
  job: { trade: number[] };
  library: { subjects: number[][]; research: number[]; days: number[]; task: number[]; lists: number[][]; texts: string[] };
  lodge: { mask: number[]; cost: number };
}

export interface ServiceCtx {
  hero: Hero; clock: Clock; cmd: string[]; comtxt: string[]; items: string[];
  /** One 5-minute tick of the world, hour changes included. */
  tick(): void;
  close(msg?: string): void;
}

export const INN = 1, SCHOOL = 2, JOB = 3, LIBRARY = 4, LODGE = 5;
const NONE = 0xff;
/** Inn rent counters (`_rmdata − 8 + id`, ids 0x40-0x47), decremented at 12:00 (P92 ovl_04b0). */
export const rent = new Array(8).fill(0);
/** The hour tick at noon; returns the inn ids whose rent ran out. */
export function noon(): number[] {
  const out: number[] = [];
  rent.forEach((n, i) => { if (n && !--rent[i]) out.push(0x40 + i); });
  return out;
}

let p05: P05;

export class ServiceRoom {
  private constructor(private ctx: ServiceCtx, readonly room: number, readonly kind: number,
                      private texts: string[], private words: string[]) {}

  /** Any P05 room; only kinds 1-5 have a service (region camps, ids ≥ 0x5C forced to the inn kind, are not built). */
  static async open(ctx: ServiceCtx, room: number, kind: number, texts: string[], words: string[]): Promise<ServiceRoom> {
    p05 ??= await json<P05>('p05.json');
    return new ServiceRoom(ctx, room, kind, texts, words);
  }

  private get serves() { return this.kind >= INN && this.kind <= LODGE && !(this.kind === INN && this.room >= 0x5c); }

  private get rec() { return this.ctx.hero.rec as unknown as Record<string, number>; }
  private say(s: string, vars: Record<string, string | number> = {}) { return format(s, this.ctx.hero, this.ctx.hero.name, vars); }
  private line(s: string, vars: Record<string, string | number> = {}) { panel.line(this.say(s, vars)); }
  private t(n: number, vars: Record<string, string | number> = {}) { return this.say(this.texts[n] ?? '', vars); }
  private yesNo(yes: () => void, no: () => void = () => this.done()) {
    panel.set([{ label: this.ctx.cmd[3], act: yes }, { label: this.ctx.cmd[4], act: no }]);
  }
  /** GetNum: a number 0…max; 0 cancels. */
  private number(max: number, then: (n: number) => void, tooMany = '') {
    panel.set([{ label: this.ctx.cmd[0], act: () => this.done() }], w => {
      const n = Number(w);
      panel.line(`> ${w}`, 'you');
      if (!Number.isInteger(n) || n < 0) return;
      if (n > max) { if (tooMany) panel.line(tooMany); return; }
      if (n === 0) return this.done();
      then(n);
    }, `0–${max}`);
  }
  /** Back to the room: Pass while the hero has a task here, End otherwise. */
  private done() {
    const b = [{ label: this.ctx.cmd[0], act: () => this.ctx.close() }];
    if (this.busy) b.unshift({ label: this.ctx.cmd[30], act: () => this.pass() });   // Pass
    panel.set(b);
  }
  private begin() { if (!panel.open) panel.show(); }

  /** The member engaged here (ovl_1742); one hero for now. */
  get busy(): boolean { return this.rec.h_actvty !== NONE && this.rec.h_actroom === this.room; }

  private engage(task: number, misc: number, days: number) {
    const r = this.rec, c = this.ctx.clock;
    Object.assign(r, { h_actvty: task, h_actmisc: misc, h_actdate: c.date, h_acthour: c.hour, h_actroom: this.room, h_actdays: days });
  }

  /** `_swgreet`: the inn, school and job keepers speak when the party walks in. */
  greet() {
    if (this.kind <= JOB) this.talk(true);
  }

  /** Talking to the keeper (`_swgreet = −3`); the inn only speaks on entry. False: ordinary conversation. */
  talk(entry = false): boolean {
    if (!this.serves || this.kind === INN && !entry) return false;
    this.begin();
    ({ [INN]: this.inn, [SCHOOL]: this.school, [JOB]: this.job, [LIBRARY]: this.library, [LODGE]: this.lodge })[this.kind]!.call(this);
    return true;
  }

  private inn() {
    const i = this.room - 0x40, price = p05.inn.price[i], left = rent[i];
    if (!left) { this.line(this.texts[0], { b: price }); this.line(this.texts[1]); }
    else if (left > 98) { this.line(this.texts[7], { b: left }); return this.done(); }
    else this.line(this.texts[7] + this.texts[8], { b: left });
    const max = 99 - left;
    this.yesNo(() => {
      this.line(this.texts[2], { b: max });
      this.number(max, n => {
        const cost = n * price;
        if (this.ctx.hero.rec.h_gold < cost) this.line(this.ctx.comtxt[0x25]);
        else { this.ctx.hero.rec.h_gold -= cost; rent[i] += n; this.line(this.texts[4]); }
        this.done();
      }, this.t(5));
    }, () => { this.line(this.texts[3]); this.done(); });
  }

  private school() {
    if (this.busy) { this.line(this.texts[29]); return this.done(); }
    const k = this.room - 0x48, s = p05.school.skill[k], cost = p05.school.cost[k], field = SKILLS[s][0];
    this.line(this.texts[5] + this.texts[6 + s] + this.texts[26] + this.texts[27], { i: cost });
    this.yesNo(() => {
      const r = this.rec, skill = r[field], race = r.h_race;
      if (p05.school.cap[s][race] <= skill) {
        this.line(skill === 0 ? this.texts[44]
          : this.texts[35] + this.texts[36 + race] + this.texts[42] + this.texts[6 + s] + this.texts[43]);
        return this.done();
      }
      const quick = r.h_intellg > 4 ? (r.h_intellg - 4) >> 1 : 0;
      const days = Math.max(1, p05.school.days[k] - quick);
      this.line(this.texts[28], { b: days });
      this.yesNo(() => {
        if (this.ctx.hero.rec.h_gold < cost) this.line(this.ctx.comtxt[0x25]);
        else { this.ctx.hero.rec.h_gold -= cost; this.engage(10 + s, p05.school.gain[s], days); this.line(this.texts[30]); }
        this.done();
      });
    });
  }

  private job() {
    if (this.busy) { this.line(this.texts[14]); return this.done(); }
    const trade = p05.job.trade[this.room - 0x6c], r = this.rec;
    const wage = r[['h_carpent', 'h_smith', 'h_gemcut', 'h_tailor'][trade]], a = this.texts[6 + trade];
    if (r.h_relatn >= 2) { this.line(this.texts[4] + this.texts[15]); return this.done(); }
    if (!wage) { this.line(this.texts[4] + this.texts[5], { a }); return this.done(); }
    this.line(this.texts[4] + this.texts[10] + this.texts[11], { a, b: wage });
    this.yesNo(() => { this.engage(0x5a + trade, wage, 0); this.line(this.texts[12]); this.done(); });   // text 13 is for other members
  }

  private library() {
    const lib = this.room - 0x7c, L = p05.library;
    if (this.busy) return this.done();
    this.line(this.texts[0]);
    panel.set([{ label: this.ctx.cmd[0], act: () => this.done() }], word => {
      panel.line(`> ${word}`, 'you');
      const s = L.subjects[lib]?.indexOf(wmatch(word, this.words)) ?? -1;
      if (s < 0) { this.line(this.texts[1]); return this.done(); }
      const g = lib * 5 + s, research = this.rec.h_research;
      this.line(this.texts[2]);
      this.yesNo(() => {
        if (research < L.research[g]) { this.line(this.texts[6]); return this.done(); }
        if (!L.days[g]) {
          for (let n = (100 - research >> 2) + 1; n; n--) this.ctx.tick();   // the party waits while the hero reads
          this.line(this.texts[5]);
          for (const t of L.lists[L.task[g]] ?? []) this.line(L.texts[t] ?? '');
          return this.done();
        }
        const item = L.task[g] + 0x2e, a = this.ctx.items[item];
        if (this.ctx.hero.slot(item) < 0) { this.line(this.texts[16], { a }); return this.done(); }
        const days = Math.max(1, L.days[g] - (research >> 4));
        this.line(this.texts[3], { b: days });
        this.yesNo(() => { this.engage(L.task[g], item, days); this.line(this.texts[4], { a }); this.done(); });
      });
    }, 'Subject… (type a word, Enter)');
  }

  /** The leader asks on behalf of the party's wizards (`_curpla == 0`); a wizard's own booth comes with companions. */
  private lodge() {
    this.line(this.texts[11]);
    this.yesNo(() => { this.line(this.texts[12]); this.done(); }, () => { this.line(this.texts[13]); this.done(); });
  }

  /** ovl_17bd, once an hour (minute 0): a day of the task passes at the hour it started. */
  hour(): boolean {
    const r = this.rec, c = this.ctx.clock;
    if (!this.busy || c.minute !== 0 || r.h_actdate === c.date || r.h_acthour !== c.hour) return false;
    if (r.h_actvty >= 0x5a) {                                    // jobs: open-ended, paid daily
      r.h_actdays++;
      if (r.h_actvty < 0x5e) this.ctx.hero.rec.h_gold += r.h_actmisc;
      return false;
    }
    if (r.h_actdays && --r.h_actdays) return false;
    if (this.kind === SCHOOL) {
      const s = r.h_actvty - 10, field = SKILLS[s][0];
      r[field] = Math.min(99, r[field] + r.h_actmisc);
      this.line(this.texts[33] + this.texts[6 + s] + this.texts[34], { b: r.h_actmisc });
    } else if (this.kind === LIBRARY) {
      const slot = this.ctx.hero.slot(r.h_actmisc);
      if (slot >= 0) this.ctx.hero.rec.h_invamt[slot] |= 0x80;
      this.line(this.texts[8], { a: this.ctx.items[r.h_actmisc] });
    }
    r.h_actvty = NONE;
    return true;
  }

  /** The Pass loop: five-minute ticks until a key or the task is done. */
  pass() {
    this.begin();
    let timer = 0;
    const stop = () => { clearInterval(timer); this.done(); };
    panel.set([{ label: this.ctx.cmd[40], act: stop }]);   // Stop
    timer = window.setInterval(() => {
      this.ctx.tick();
      if (this.hour() || !this.busy) stop();
    }, 15);
  }

  /** Stepping onto the exit (P05 L_068d): "leave without completing?" with a pupil here, else "Do you want to leave now?". */
  leave(go: () => void) {
    this.begin();
    const n = p05.leave[this.kind];
    if (this.busy && n !== NONE) this.line(this.texts[n], { o: this.ctx.hero.name });
    else this.line(this.ctx.comtxt[0x23]);
    this.yesNo(() => { this.rec.h_actvty = NONE; this.ctx.close(); go(); }, () => this.done());
  }
}
