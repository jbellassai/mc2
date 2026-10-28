// Camp (P93, rules/camp.md). In town only a rented inn room is a campsite (`_CAMPSITE` 0x20, ovl_1099); elsewhere
// the reduced menu 22 has no Sleep. Built so far: Sleep. Learn, Hunt, Fix, Watch, Put/Off and Use come later.
import { panel } from './panel';
import { format } from './talk';
import type { Party } from './party';
import type { Clock } from './clock';

export interface CampCtx {
  party: Party; clock: Clock; cmd: string[]; p93: string[];
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
  const menu = () => panel.set([...(site ? [{ label: cmd[39], act: sleep }] : []), { label: cmd[0], act: end }]);   // Sleep, End
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
