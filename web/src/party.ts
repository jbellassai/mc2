// The party (rules/locations.md, Dungeon levels / A step; rules/npcs.md, Companions): up to six members, each in a
// cell of the 3×3 formation `_formatn`. A member stands at origin + (cell mod 3, cell div 3); the origin is
// window + (4,3) in town (_NewPXY) and the room's base square in P05 rooms. The leader keeps cell 0, as in every save.
import { json } from './pack';
import { Hero, type HeroRecord } from './hero';

/** `num` = `_party` value = h_orinum (0 the player); the view picks the sprite from it (_MCCPTile). */
export interface Member { hero: Hero; cell: number; x: number; y: number; num: number }

const num = (h: Hero) => h.rec.h_orinum as number;

/** P92 ovl_0a9d/0af7: the week's attitude. Under 100 coins' worth of gifts: attitude·mybucks/120, capped at mybucks;
 *  else against a quarter of the party's loot, unchanged when equal to within 32. Rounded; large inputs scaled down. */
function fairShare(att: number, party: number, my: number): number {
  const scaled = (dx: number, ax: number, cap: number) => {
    if (dx >> 8) { const k = dx >> 8 < 0x10 ? 4 : 8; dx >>= k; ax >>= k; }
    ax ||= 1;
    return Math.min(Math.floor((dx * att + (ax >> 1)) / ax), 200, cap);
  };
  if (my < 100) return scaled(my, 120, my);
  const share = party >> 2;
  return (share & ~31) === (my & ~31) ? att : scaled(my, share, 200);
}

export class Party {
  readonly members: Member[] = [];
  /** `_npcsta`: companions taken out of the location tables (in the party). */
  readonly away = new Set<number>();
  /** `_member6…`: a companion's record as they left the party (P97 copies it back on dismissal). */
  private readonly roster = new Map<number, HeroRecord>();

  constructor(lead: Hero, x: number, y: number) {
    this.members.push({ hero: lead, cell: 0, x, y, num: num(lead) });
  }

  get leader(): Member { return this.members[0]; }

  /** Everyone into formation from the origin (x, y). */
  place(x: number, y: number) {
    for (const m of this.members) { m.x = x + m.cell % 3; m.y = y + Math.floor(m.cell / 3); }
  }

  shift(dx: number, dy: number) { for (const m of this.members) { m.x += dx; m.y += dy; } }

  at(x: number, y: number): Member | undefined { return this.members.find(m => m.x === x && m.y === y); }

  /** _Invite: the first free formation cell whose square passes `ok` (_ChkForm, town only), or −1. */
  freeCell(ok: (x: number, y: number) => boolean): number {
    const ox = this.leader.x, oy = this.leader.y;
    for (let c = 0; c < 9; c++)
      if (!this.members.some(m => m.cell === c) && ok(ox + c % 3, oy + Math.floor(c / 3))) return c;
    return -1;
  }

  /** P97 ovl_03f7: the companion's record (`_member6[num − 1]`) joins where the NPC stood. */
  add(rec: HeroRecord, items: string[], cell: number, x: number, y: number): Member {
    const hero = new Hero(rec, items), m = { hero, cell, x, y, num: num(hero) };
    this.members.push(m);
    this.away.add(rec.h_orinum as number);
    return m;
  }

  /** _DecEnergy, minute 0 and 30: every member not asleep (h_actvty 0) loses 1, 4 if Poisoned or Ill, +1 holding a weapon. */
  decEnergy() {
    for (const { hero } of this.members) {
      const r = hero.rec as Record<string, number>;
      if (r.h_actvty === 0) continue;
      hero.lose('h_energy', (r.h_cond1 & 0x0a ? 4 : 1) + (r.h_inhand !== 0xff ? 1 : 0));
      hero.isHeTr();
    }
  }

  /** P02 ovl_0fca: walking in town, every second tick costs everyone 1 energy. */
  walkTired() { for (const { hero } of this.members) { hero.lose('h_energy', 1); hero.isHeTr(); } }

  /** P92 ovl_039d, hourly: h_lastmeal++ (cap 255); at the race's hunger hours a member holding more than 5 Food
   *  eats one (_DoUse → _EatMeal, silent), otherwise _IsHeHu marks Hungry/Starving. */
  hunger(hungerhours: number[]) {
    for (const { hero } of this.members) {
      const r = hero.rec as Record<string, number>, hours = hungerhours[r.h_race];
      if (r.h_lastmeal < 0xff) r.h_lastmeal++;
      if (r.h_lastmeal < hours) continue;
      const slot = hero.slot(0x31);
      if (slot >= 0 && hero.rec.h_invamt[slot] > 5) { hero.use(0x31, hours); hero.dec(slot); }
      else hero.isHeHu(hours);
    }
  }

  /** P92 ovl_09ff at 17:00 and 18:00 on a hireling's payday (`h_paydays`, rules/economy.md): the attitude the week earns.
   *  Returns [member, new attitude] for each hireling paid today; at 18:00 it is applied and the counters reset. */
  payday(date: number, apply: boolean): [Member, number][] {
    const out: [Member, number][] = [];
    for (const m of this.members) {
      const r = m.hero.rec as Record<string, number>, days = m.hero.rec.h_paydays as number[];
      if (r.h_relatn !== 2 || !days.includes(date)) continue;
      const att = fairShare(r.h_attitude, r.h_partybucks, r.h_mybucks);
      if (apply) { r.h_attitude = att < 4 ? 0xff : att; r.h_partybucks = r.h_mybucks = 0; }   // 0xFF: leaves (ovl_0a88)
      out.push([m, att]);
    }
    return out;
  }

  /** _ChkDepartures → P97 ovl_05f7: members with attitude 0xFF leave; their attitude is reset to 5. */
  departures(): Member[] {
    const gone = this.members.filter(m => m.hero.rec.h_attitude === 0xff);
    for (const m of gone) { m.hero.rec.h_attitude = 5; this.remove(m); }
    return gone;
  }

  /** The record a companion joins with: as they last left, else their starting record (R90). */
  async record(num: number): Promise<HeroRecord> {
    return this.roster.get(num) ?? structuredClone((await json<HeroRecord[]>('companions.json'))[num - 1]);
  }

  /** P97 ovl_01fd: out of the party and its formation cell, back to the location tables, nothing in hand. */
  remove(m: Member) {
    this.members.splice(this.members.indexOf(m), 1);
    this.away.delete(m.num);
    m.hero.rec.h_inhand = 0xff;
    this.roster.set(m.num, m.hero.rec);
  }

  /** P97 ovl_06ac/06bc on joining or leaving: the companion's paired event (`pairs`) set or cleared (Lady Subia joining
   *  also sets event 33); then events 88 and 117 are set and cleared again while a Halfling (88) or Dwarf (117) is in
   *  the party. On leaving this runs before the member is removed, so they still count. */
  partyEvents(events: Set<number>, pairs: Record<string, number>, num: number, join: boolean) {
    const e = pairs[num];
    if (e !== undefined) { if (join) events.add(e); else events.delete(e); }
    if (join && num === 29) events.add(33);
    events.add(88); events.add(117);
    for (const { hero } of this.members) {
      if (hero.rec.h_race === 3) events.delete(88);
      if (hero.rec.h_race === 4) events.delete(117);
    }
  }
}
