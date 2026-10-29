// Camp (P93 ovl_0271, rules/camp.md). The commands set each member's activity (`h_actvty`); Begin runs the loop.
// Where (`_CAMPSITE`, ovl_1099): 2 open camp on the world map, 4 aboard a ship, 8 a dungeon room (P07), 0x20 a rented
// inn room, 0x10 a guest room; anywhere else 1, the reduced menu 22 (Use, Recall, Put, Off, End). Not built: the camp
// formation (ovl_1151: the party drawn on fixed squares).
import { panel } from './panel';
import { format } from './talk';
import { incObj } from './shop';
import type { Party } from './party';
import type { Hero } from './hero';
import type { Clock } from './clock';

export const OPEN = 2, SHIP = 4, DUNGEON = 8, GUEST = 0x10, INNROOM = 0x20;

export interface CampCtx {
  party: Party; clock: Clock; cmd: string[]; p93: string[]; items: string[]; comtxt: string[];
  /** `_CAMPSITE`. */
  site: number;
  /** Terrain class under the party (`_curter`), for hunting. */
  terrain: number;
  hunt: { terrain: number[]; weather: number[] };
  speltim: number[]; spells: string[];
  /** _SkillUp0 for skill `idx` (`h_hunt` = 0x11): the line to print, or ''. */
  skillUp(h: Hero, idx: number): string;
  /** The Use command (_UseItem). */
  use(): void;
  /** Recall (_RecSpl): `h` readies one of their memorised spells, then `back`. */
  recall(h: Hero, back: () => void): void;
  /** Magic (_Magic): `h` casts the readied spell; `back(text)` when it is over (the panel may have been closed to mark a square). */
  magic(h: Hero, back: (text?: string) => void): void;
  /** One 5-minute tick of the world (_CalUpd). */
  tick(): void;
  /** Open camp: the patrols move and may walk into the camp (P01 cross-overlay calls 6 and 9); true when a fight
   *  starts, an ambush unless `watch` (`P01 ovl_0790`). */
  wild(watch: boolean): boolean;
  /** Aboard: the loop does one pass per sailing step instead of running (null = camp over). */
  sail(pass: (() => void) | null): void;
  /** Nights left in the rented room (`_RENTPTR`), or null outside an inn. */
  rent(): number | null;
  /** Camp is over (P93 L_046b); activities are already reset. */
  done(): void;
}

const NONE = 0xff, SLEEP = 0, LEARN = 1, HUNT = 3, FIX = 6, WATCH = 9;
type Rec = Record<string, number> & Hero['rec'];

export function camp(ctx: CampCtx) {
  const { party, cmd, p93, site } = ctx;
  const rec = (h: Hero) => h.rec as Rec;
  const say = (h: Hero, n: number, vars: Record<string, string> = {}) => format(p93[n], h, h.name, vars);
  const reset = () => { for (const { hero } of party.members) hero.rec.h_actvty = NONE; };
  const end = () => { reset(); ctx.sail(null); ctx.done(); };
  panel.show();
  const recall = { label: cmd[35], act: () => who(h => ctx.recall(h, menu)) };
  const menu = () => panel.set(site === 1
    ? [{ label: cmd[43], act: ctx.use }, recall, { label: cmd[33], act: () => who(put) }, { label: cmd[28], act: () => who(off) },
      { label: cmd[0], act: end }]                                                          // menu 22: Use, Recall, Put, Off, End
    : [{ label: cmd[43], act: ctx.use }, recall, { label: cmd[39], act: sleep }, { label: cmd[27], act: () => who(magic) }, { label: cmd[24], act: () => who(learn) },
      { label: cmd[28], act: () => who(off) }, { label: cmd[15], act: () => who(h => set(h, FIX, 6)) },
      { label: cmd[44], act: () => who(watch) }, { label: cmd[21], act: () => who(hunt) },
      { label: cmd[33], act: () => who(put) }, { label: cmd[5], act: begin }, { label: cmd[0], act: end }]);   // menu 13
  /** P93 Magic: not a magic user (`_ChkMag`, comtxt 0x2D); no readied spell (0x40); else `_Magic`. (P93 also lets a
   *  sleeper cast, marking them awake meanwhile.) */
  const magic = (h: Hero) => {
    if (!rec(h).h_magic) { panel.line(format(ctx.comtxt[0x2d], h, h.name)); return menu(); }
    if (rec(h).h_rdyspl === NONE) { panel.line(format(ctx.comtxt[0x40], h, h.name)); return menu(); }
    ctx.magic(h, text => { panel.show(); if (text) panel.line(text); menu(); });
  };
  /** The acting member (`_curpla`); the port asks when the party has more than one. */
  const who = (then: (h: Hero) => void) => {
    if (party.members.length < 2) return then(party.leader.hero);
    panel.set(party.members.map(m => ({ label: m.hero.name, act: () => then(m.hero) })));
  };
  /** ovl_1027: a Dwarf aboard a ship is seasick ("%o is too seasick to do anything!"). */
  const seasick = (h: Hero) => site === SHIP && rec(h).h_race === 4;
  const cond = (h: Hero) => rec(h).h_cond1 | rec(h).h_cond2 << 8;
  /** Fix, Watch, Hunt: refused when seasick (21) or any condition (3, "%h's condition prevents this activity!"),
   *  else the activity and its text. */
  const set = (h: Hero, act: number, text: number) => {
    panel.line(seasick(h) ? say(h, 21) : cond(h) ? say(h, 3) : (rec(h).h_actvty = act, say(h, text)));
    menu();
  };
  /** Watch only where patrols roam (sites 1|2), else "No need to stand watch here." */
  const watch = (h: Hero) => site & 3 ? set(h, WATCH, 5) : (panel.line(say(h, 12)), menu());
  /** Hunt only in an open camp, else "%h can't do that here!" (comtxt 0x24); only cond1 refuses. */
  const hunt = (h: Hero) => {
    if (!(site & OPEN)) { panel.line(format(ctx.comtxt[0x24], h, h.name)); return menu(); }
    if (seasick(h)) panel.line(say(h, 21));
    else if (rec(h).h_cond1) panel.line(say(h, 3));
    else { rec(h).h_actvty = HUNT; panel.line(say(h, 4)); }
    menu();
  };
  /** _LrnTim: `_speltim[spell] − h_intellg`, at least 2. */
  const lrnTim = (h: Hero, spell: number) => Math.max(2, ctx.speltim[spell] - rec(h).h_intellg);
  const charges = (h: Hero, spell: number) => h.rec.h_spells[Math.floor(spell / 7)][spell % 7];
  /** Learn (ovl_0a15): a magic user (else comtxt 0x2D) in good condition picks one of the six spells of a book
   *  0x53-0x59 in the pack (spell = 6·(book − 0x53) + i); `h_actmisc` = the spell, `h_lrncnt` = _LrnTim. */
  const learn = (h: Hero) => {
    if (!rec(h).h_magic) { panel.line(format(ctx.comtxt[0x2d], h, h.name)); return menu(); }
    if (cond(h)) { panel.line(say(h, 3)); return menu(); }
    const books = [0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59].filter(b => h.rec.h_invitem.includes(b));
    if (!books.length) { panel.line(say(h, 18)); return menu(); }
    const spells = books.flatMap(b => [0, 1, 2, 3, 4, 5].map(i => 6 * (b - 0x53) + i));
    panel.set([...spells.map(s => ({ label: `${ctx.spells[s]} (${charges(h, s)})`, act: () => {
      rec(h).h_actmisc = s; rec(h).h_actvty = LEARN; rec(h).h_lrncnt = lrnTim(h, s);
      panel.line(say(h, 2, { a: ctx.spells[s] }));
      menu();
    } })), { label: cmd[0], act: menu }]);
  };
  /** Garment class (P93 ovl_0d25): 1 body armour 0x1F-0x27, 2 helmet 0x28-0x2A, 4 clothing 0x2B-0x30. */
  const garment = (item: number) => item < 0x28 ? 1 : item < 0x2b ? 2 : 4;
  const line = (h: Hero, s: string, vars: Record<string, string>) => panel.line(format(s, h, h.name, vars));
  /** Put: an unworn armour or clothing item; a worn item of the same class is replaced (text 17), else the first free
   *  `h_wears` slot (text 14). No race or class restriction. */
  const put = (h: Hero) => {
    const r = h.rec, slots = r.h_invitem.map((c, i) => i).filter(i => r.h_invitem[i] >= 0x1f && r.h_invitem[i] <= 0x30 && !r.h_wears.includes(i));
    if (!slots.length) { line(h, p93[19], {}); return menu(); }                 // "%h has nothing to put on!"
    panel.set([...slots.map(i => ({ label: ctx.items[r.h_invitem[i]], act: () => {
      const a = ctx.items[r.h_invitem[i]], k = garment(r.h_invitem[i]);
      const w = r.h_wears.findIndex(s => s !== 0xff && garment(r.h_invitem[s]) === k);
      if (w >= 0) { line(h, p93[17], { f: ctx.items[r.h_invitem[r.h_wears[w]]], a }); r.h_wears[w] = i; }   // replaces
      else { r.h_wears[r.h_wears.indexOf(0xff)] = i; line(h, p93[14], { a }); }                            // puts on
      menu();
    } })), { label: cmd[0], act: menu }]);
  };
  /** Off: take off a worn item (text 15); nothing worn → "%h has nothing more to take off!". */
  const off = (h: Hero) => {
    const r = h.rec, worn = r.h_wears.map((s, w) => w).filter(w => r.h_wears[w] !== 0xff);
    if (!worn.length) { line(h, p93[16], {}); return menu(); }
    panel.set([...worn.map(w => ({ label: ctx.items[r.h_invitem[r.h_wears[w]]], act: () => {
      line(h, p93[15], { a: ctx.items[r.h_invitem[r.h_wears[w]]] }); r.h_wears[w] = 0xff; menu();
    } })), { label: cmd[0], act: menu }]);
  };
  /** "Is everyone going to sleep?" Yes = everyone, No = the acting member. Each is refused when seasick, poisoned (9),
   *  starving (10) or hungry (11), else "%o will sleep." (ovl_0bd5). */
  const sleep = () => {
    panel.line(p93[0]);
    const go = (hs: Hero[]) => {
      panel.line(hs.map(h => {
        const c = cond(h);
        if (seasick(h)) return say(h, 21);
        if (c & 8) return say(h, 9);
        if (c & 4) return say(h, 10);
        if (c & 0x4000) return say(h, 11);
        rec(h).h_actvty = SLEEP;
        return say(h, 1);
      }).join(' '));
      menu();
    };
    panel.set([{ label: cmd[3], act: () => go(party.members.map(m => m.hero)) }, { label: cmd[4], act: () => who(h => go([h])) }]);
  };
  /** ovl_1061: an activity that cannot go on: "%o can't continue the current activity." */
  const stop = (h: Hero) => {
    if (h.rec.h_actvty === NONE) return;
    h.rec.h_actvty = NONE;
    panel.line(say(h, 7));
  };
  /** ovl_0849: repair one point of damage (`h_invamt` > 0x80), the repairer's pack first, then round the party. */
  const repair = (h: Hero) => {
    const ms = party.members, k = ms.findIndex(m => m.hero === h);
    for (let n = 0; n < ms.length; n++) {
      const a = ms[(k + n) % ms.length].hero.rec.h_invamt, i = a.findIndex(v => v > 0x80);
      if (i >= 0) { a[i]--; return; }
    }
  };
  /** Open camp without a Blanket (0x52): hp up to hpmax/2 + shelter, energy to 50 + shelter, where shelter is half
   *  the party's best carpentry (ovl_1137); elsewhere hpmax and 99. Poisoned or Ill (cond1 & 0x0A) halve the caps. */
  const shelter = Math.max(...party.members.map(m => rec(m.hero).h_carpent)) >> 1;
  /** One pass of the loop (SUB_04d4): members 5…0, then _CalUpd and, in an open camp, the patrols. */
  const pass = () => {
    const c = ctx.clock;
    for (const { hero: h } of [...party.members].reverse()) {
      const r = rec(h), cw = cond(h);
      switch (r.h_actvty) {
        case SLEEP: {
          if (c.minute & 1) break;                           // every 10 minutes
          const open = site & OPEN && !h.rec.h_invitem.includes(0x52);
          let hp = open ? Math.min(r.h_hpmax, (r.h_hpmax >> 1) + shelter) : r.h_hpmax, en = open ? Math.min(99, 50 + shelter) : 99;
          if (r.h_cond1 & 0x0a) { hp >>= 1; en >>= 1; }
          if (r.h_hitpts < hp) r.h_hitpts++;
          if (r.h_energy < en) { r.h_energy++; h.isHeTr(); }
          break;
        }
        case LEARN:                                          // h_lrncnt down to 0, then a charge (up to 99)
          if (cw) { stop(h); break; }
          if (r.h_lrncnt) { r.h_lrncnt--; break; }
          { const s = r.h_actmisc, row = h.rec.h_spells[Math.floor(s / 7)];
            if (row[s % 7] < 99) row[s % 7]++;
            r.h_lrncnt = lrnTim(h, s);
            panel.line(say(h, 13, { a: ctx.spells[s] })); }  // "%o memorized %a."
          break;
        case HUNT: {                                         // on the hour and half hour
          if (r.h_cond1) { stop(h); break; }
          if (c.minute % 30) break;
          const t = [...ctx.hunt.terrain, ...ctx.hunt.weather][ctx.terrain], w = ctx.hunt.weather[c.weather];
          const roll = Math.floor(Math.random() * 100), odds = (t + w + (r.h_hunt >> 1)) & 0xff;   // a signed byte
          if (t === -1 || w === -1 || odds > 0x7f || odds < roll) break;
          incObj(h, 0x31, 1);                                // Food (_IncObj; a full pack loses it)
          panel.line([say(h, 20), ctx.skillUp(h, 0x11)].filter(Boolean).join(' '));   // "%o found food."
          break;
        }
        case FIX:                                            // one point, and another when RndCo(100) ≤ smith
          if (cw) { stop(h); break; }
          repair(h);
          if (Math.floor(Math.random() * 100) <= r.h_smith) repair(h);
          break;
        default:                                             // Watch (and idle members)
          if (r.h_cond1) stop(h);
      }
    }
    ctx.tick();
  };
  /** Begin: "Camp activities are in progress." and the loop until Stop, the rent running out or a fight. Aboard the
   *  loop does not run; each sailing step makes one pass (the P01 step hook) until End. */
  const begin = () => {
    panel.line(p93[8]);
    if (site === SHIP) { ctx.sail(pass); panel.hide(); return; }
    let timer = 0;
    const halt = () => { clearInterval(timer); end(); };
    panel.set([{ label: cmd[40], act: halt }]);             // menu 15: Stop
    timer = window.setInterval(() => {
      pass();
      if (site & OPEN && ctx.wild(party.members.some(m => m.hero.rec.h_actvty === WATCH))) { clearInterval(timer); reset(); return; }
      if (ctx.rent() === 0) halt();
    }, 15);
  };
  menu();
}
