// Special rooms run by P09 (rules/special_rooms.md): casinos and gates so far. The room kind is P09's `_rmtyp` (7
// casino, 10 teleportal, 11 meeting hall, 12/13 temple, 14 gate) and `index` its OV_0x181 (`id − base`).
import { format, wmatch } from './talk';
import { panel } from './panel';
import type { Hero } from './hero';
import type { Clock } from './clock';
import type { Level } from './level';
import type { Exit } from './pack';

export const CASINO = 7, GATE = 14;

export interface SpecialCtx {
  hero: Hero; clock: Clock; cmd: string[]; comtxt: string[];
  /** `_w_tod` (EXE DS:0x41E0) and TODWORDS (DS:0x38F2, by hour) for `_SetTxtToD`. */
  tod: { words: string[]; hour: number[] };
  close(msg?: string): void;
}

/** `_casino`: the eight house banks, 1000 in a new game; +200 a month up to 1000 (P92 ovl_02ac). */
export const casino = new Array(8).fill(1000);
export function refill() { casino.forEach((b, i) => casino[i] = Math.min(1000, b + 200)); }
/** `_dnggates`: the gates opened by their password, bit = gate index. */
export const gates = new Set<number>();

const rnd = (n: number) => Math.floor(Math.random() * n);

export class Special {
  constructor(private ctx: SpecialCtx, readonly kind: number, readonly index: number, private level: Level) {
    if (kind === GATE && gates.has(index)) this.openGate();       // ovl_15ee: an opened gate stays open
  }

  private get texts() { return this.level.loc.texts; }
  private say(s: string, v: Record<string, string | number> = {}) { return format(s, this.ctx.hero, this.ctx.hero.name, v); }
  private yesNo(yes: () => void, no: () => void) {
    panel.set([{ label: this.ctx.cmd[3], act: yes }, { label: this.ctx.cmd[4], act: no }]);
  }

  /** Talk (`_swgreet` −3): only the casino answers. */
  talk(): boolean {
    if (this.kind !== CASINO) return false;
    this.gamble();
    return true;
  }

  /** Whisper: the typed word's index in the room's `gwrds` (−1 none). A gate opens to its own password (P09 @0x05xx,
   *  `_whspnum == index`); false = nothing here answers. */
  whisper(word: string): boolean {
    const n = wmatch(word, this.level.loc.words);
    if (this.kind !== GATE || n !== this.index || gates.has(n)) return false;
    gates.add(n);
    this.openGate();
    this.ctx.close(this.say(this.texts[8], { a: this.texts[n] }));   // "The gate of the %a slowly creaks open!"
    return true;
  }

  /** A gate's two door squares (this room's exit records 1 and 2) get D14 `hroomptr` tiles (4 bytes per gate: tile,
   *  ?, tile, ?). */
  private openGate() {
    const t = this.level.loc.tables.hroomptr.match(/../g)!.map(h => parseInt(h, 16)).slice(4 * this.index, 4 * this.index + 4);
    const ex = this.level.loc.exits;
    this.level.set(ex[1].x, ex[1].y, t[0]);
    this.level.set(ex[2].x, ex[2].y, t[2]);
  }

  /** Stepping onto an exit: a closed gate is "magically locked" (10); an open one asks "Will the party enter the %a?"
   *  (9); any other exit "Do you want to leave now?" (comtxt 0x23). Yes runs `go`. */
  exit(exit: Exit, go: () => void) {
    const gate = this.kind === GATE && exit !== this.level.loc.exits[0];
    if (gate && !gates.has(this.index)) return this.ctx.close(this.texts[10]);
    panel.show();
    panel.line(gate ? this.say(this.texts[9], { a: this.texts[this.index] }) : this.ctx.comtxt[0x23]);
    this.yesNo(() => { panel.hide(); go(); }, () => this.ctx.close());
  }

  /** The casino (P09 L_066f): the acting member's gold against the house bank `_casino[index]`. */
  private gamble() {
    const h = this.ctx.hero, r = h.rec, i = this.index;
    const a = this.ctx.tod.words[this.ctx.tod.hour[this.ctx.clock.hour]];
    const t = (n: number, v: Record<string, string | number> = {}) => panel.line(this.say(this.texts[n], { a, ...v }));
    const start = r.h_gold;
    panel.show();
    if (!r.h_gold) { t(2); return this.done(); }                    // "You can't be bold without some gold."
    if (!casino[i]) { t(1); return this.done(); }                   // "The house tables are closed."
    t(0);                                                           // "Good %a, sport. Care to try your luck?"
    // "Good %a, sport." and, when the hero leaves poorer, " Come again soon!" (12, 13)
    const bye = () => { panel.line(this.say(this.texts[12] + (r.h_gold < start ? this.texts[13] : ''), { a })); this.done(); };
    const bet = () => {
      const max = Math.min(r.h_gold, casino[i]);
      t(4, { i: max });                                             // "How much will %h bet (0-%i)?"
      panel.set([{ label: this.ctx.cmd[0], act: bye }], w => {
        const b = Number(w);
        panel.line(`> ${w}`, 'you');
        if (!Number.isInteger(b) || b < 0 || b > max) return bet();
        if (!b) return bye();
        const dealer = rnd(6) + 1 + rnd(6) + 1, roll = rnd(6) + rnd(6) + 2;
        t(5, { i: dealer }); t(6, { i: roll });                    // "The gambler rolls %i." "%h rolls %i."
        if (roll === 2 || roll > dealer) { t(7, { i: b }); r.h_gold += b; casino[i] -= b; }   // "%h wins %i coins!"
        else { t(8, { i: b }); r.h_gold -= b; casino[i] += b; }                                 // "%h loses %i coins."
        if (!casino[i]) { t(10); return bye(); }                    // "%h has broken the bank!"
        if (!r.h_gold) { t(11); return bye(); }                     // "So goes the last of %h's gold."
        t(9);                                                       // "Will %h play again?"
        this.yesNo(bet, bye);
      }, `0–${max}`);
    };
    this.yesNo(() => { t(3); bet(); }, () => this.ctx.close());     // "The rules are simple. …"
  }

  private done() { panel.set([{ label: this.ctx.cmd[0], act: () => this.ctx.close() }]); }
}
