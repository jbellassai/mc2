// Ships and captains (rules/ships.md): six captains sail the world map; the party hires one by the day. P01 ovl_0cb2
// (step), ovl_0f5c / ovl_0f95 / ovl_0fcc (hire, time is up, buy days), ovl_1070 (boat lookup), ovl_15e4 (per-step
// states), ovl_1664 (voyage home); P92 ovl_040d / ovl_0447 (daily countdown, Amos).

export interface ShipData { weather: number[]; rate: number[]; homex: number[]; homey: number[] }

export const AMOS = 2;

export class Ships {
  /** `_capsta`: 0 sailing home, 1 anchored for the party, 2 waiting expired, 3 at home for hire, 4 credit ran out
   *  aboard, 5 party aboard, 6/7 Amos' theft pending/done. A new game has all six at home. */
  sta = Array<number>(6).fill(3);
  /** `_capdays`: credit left (1, 5) or days until home (0). */
  days = Array<number>(6).fill(0);
  /** `_boatx/_boaty`. */
  x: number[]; y: number[];
  /** `_curcap` (−1 = ashore; `_sailsw` is set exactly while this is ≥ 0). */
  cur = -1;
  /** OV_0x1c6, overlay-private (not saved): 0 paid, 1 working for passage, 2 the "time is up" prompt is running. */
  passage = 0;

  constructor(readonly d: ShipData) { this.x = [...d.homex]; this.y = [...d.homey]; }

  get sailing() { return this.cur >= 0; }

  /** ovl_1070: the boat on (x, y) whose state is not 0, or −1. */
  boatAt(x: number, y: number): number {
    for (let i = 0; i < 6; i++) if (this.sta[i] && this.x[i] === x && this.y[i] === y) return i;
    return -1;
  }

  /** EXE `_ShowMap`: boats with state ≠ 0 are drawn (E00 frame 0x12). */
  boats(): { x: number; y: number }[] {
    return this.sta.flatMap((s, i) => s ? [{ x: this.x[i], y: this.y[i] }] : []);
  }

  /** ovl_1664: days home = (max(dx,dy) + (min(dx,dy)+2)/4, byte-saturated) / 16. */
  voyageHome(i: number): number {
    const dx = Math.abs(this.d.homex[i] - this.x[i]), dy = Math.abs(this.d.homey[i] - this.y[i]);
    return Math.min(255, Math.max(dx, dy) + ((Math.min(dx, dy) + 2) >> 2)) >> 4;
  }

  /** P92 at the day change: ovl_040d counts every captain's days down (0 → home, 1 → expired, 5 → credit ran out);
   *  ovl_0447 springs Amos' theft (state 6 → 7, no credit). Returns true when the party's coins are to be taken. */
  daily(): boolean {
    for (let i = 0; i < 6; i++) {
      if (this.days[i]) this.days[i]--;
      if (this.days[i]) continue;
      this.sta[i] = ({ 0: 3, 1: 2, 5: 4 } as Record<number, number>)[this.sta[i]] ?? this.sta[i];
    }
    if (this.sta[AMOS] !== 6) return false;
    this.sta[AMOS] = 7; this.days[AMOS] = 0;
    return true;
  }

  /** ovl_15e4, every world-map step: expired boats head home, docked boats sit at their port; the result names the
   *  dialogue to run: 'timeup' (state 4 unless working for passage) or 'stolen' (state 7 → 5). */
  step(): 'timeup' | 'stolen' | null {
    let out: 'timeup' | 'stolen' | null = null;
    for (let i = 0; i < 6; i++) {
      if (this.sta[i] === 2) { this.days[i] = this.voyageHome(i); this.sta[i] = 0; }
      else if (this.sta[i] === 3) { this.x[i] = this.d.homex[i]; this.y[i] = this.d.homey[i]; }
      else if (this.sta[i] === 4 && this.passage !== 1) { this.passage = 2; out = 'timeup'; }
      else if (this.sta[i] === 7) { this.sta[i] = 5; out = 'stolen'; }
    }
    return out;
  }

  /** Boarding (ovl_0cb2 @0xEDB): `_sailsw`, `_curcap`, state 5 (Amos 6), paid passage. */
  board(i: number) {
    this.cur = i; this.passage = 0;
    this.sta[i] = i === AMOS ? 6 : 5;
  }

  /** Landing (@0xDF6): with credit (or `extra` days bought) the boat anchors (state 1); without, it sails home. */
  land(extra: number) {
    const i = this.cur;
    if (extra) this.days[i] += extra;
    if (this.days[i]) this.sta[i] = 1;
    else { this.days[i] = this.voyageHome(i); this.sta[i] = 0; }
    this.cur = -1; this.passage = 0;
  }

  /** Saved state (`_capsta`, `_boatx/y`, `_capdays`, `_curcap`). */
  snapshot() { return { sta: [...this.sta], days: [...this.days], x: [...this.x], y: [...this.y], cur: this.cur }; }
  restore(s: ReturnType<Ships['snapshot']>) {
    this.sta = [...s.sta]; this.days = [...s.days]; this.x = [...s.x]; this.y = [...s.y]; this.cur = s.cur; this.passage = 0;
  }
}
