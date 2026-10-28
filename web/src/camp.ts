// Camp (P93, rules/camp.md). In town only a rented inn room is a campsite (`_CAMPSITE` 0x20, ovl_1099); elsewhere
// the reduced menu 22 (Use, Recall, Put, Off, End) has no Sleep. Built: Sleep, Put, Off, Use. Learn, Hunt, Fix, Watch,
// Recall come later.
import { panel } from './panel';
import { format } from './talk';
import type { Party } from './party';
import type { Hero } from './hero';
import type { Clock } from './clock';

export interface CampCtx {
  party: Party; clock: Clock; cmd: string[]; p93: string[]; items: string[];
  /** The Use command (_UseItem). */
  use(): void;
  /** One 5-minute tick of the world (_CalUpd). */
  tick(): void;
  /** Nights left in the rented room (`_RENTPTR`), or null outside an inn. */
  rent(): number | null;
  /** Camp is over (P93 L_046b); sleepers' activities are already reset. */
  done(): void;
}

const NONE = 0xff, SLEEP = 0;

export function camp(ctx: CampCtx) {
  const { party, cmd, p93 } = ctx, lead = party.leader.hero;
  const site = ctx.rent() !== null;
  const say = (s: string, other: string) => format(s, lead, other);
  const end = () => {
    for (const { hero } of party.members) if (hero.rec.h_actvty === SLEEP) hero.rec.h_actvty = NONE;
    ctx.done();
  };
  panel.show();
  const menu = () => panel.set([{ label: cmd[43], act: ctx.use }, ...(site ? [{ label: cmd[39], act: sleep }] : []),
    { label: cmd[33], act: () => who(put) }, { label: cmd[28], act: () => who(off) }, { label: cmd[0], act: end }]);   // Use, Sleep, Put, Off, End
  /** The acting member (`_curpla`); the port asks when the party has more than one. */
  const who = (then: (h: Hero) => void) => {
    if (party.members.length < 2) return then(lead);
    panel.set(party.members.map(m => ({ label: m.hero.name, act: () => then(m.hero) })));
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
  /** "Is everyone going to sleep?" Yes = everyone (party slot order), No = the acting member only. */
  const sleep = () => {
    panel.line(p93[0]);
    const go = (who: typeof party.members) => {
      for (const { hero } of who) { hero.rec.h_actvty = SLEEP; panel.line(say(p93[1], hero.name)); }
      run();
    };
    panel.set([{ label: cmd[3], act: () => go(party.members) }, { label: cmd[4], act: () => go([party.leader]) }]);
  };
  /** The camp loop (ovl_0271 SUB_04d4): members 5…0, then _CalUpd; stops on a key or when the rent runs out.
   *  Assumption: the loop starts as soon as activities are set (the command that starts it is not traced). */
  const run = () => {
    panel.line(p93[8]);                                    // "Camp activities are in progress."
    let timer = 0;
    const stop = () => { clearInterval(timer); end(); };
    panel.set([{ label: cmd[40], act: stop }]);            // Stop
    timer = window.setInterval(() => {
      for (const { hero } of [...party.members].reverse()) {
        const r = hero.rec as Record<string, number>;
        if (r.h_actvty !== SLEEP || ctx.clock.minute & 1) continue;   // sleepers recover on even minutes (every 10 min)
        const ill = r.h_cond1 & 0x0a;                       // Poisoned or Ill halve the caps
        const hpCap = ill ? r.h_hpmax >> 1 : r.h_hpmax, enCap = ill ? 49 : 99;   // indoors: hpmax and 99 (ovl_07e5/0813)
        if (r.h_hitpts < hpCap) r.h_hitpts++;
        if (r.h_energy < enCap) { r.h_energy++; hero.isHeTr(); }
      }
      ctx.tick();
      if (ctx.rent() === 0) stop();
    }, 15);
  };
  menu();
}
