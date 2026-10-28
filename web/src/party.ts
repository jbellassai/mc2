// The party (rules/locations.md, Dungeon levels / A step; rules/npcs.md, Companions): up to six members, each in a
// cell of the 3×3 formation `_formatn`. A member stands at origin + (cell mod 3, cell div 3); the origin is
// window + (4,3) in town (_NewPXY) and the room's base square in P05 rooms. The leader keeps cell 0, as in every save.
import { json } from './pack';
import { Hero, type HeroRecord } from './hero';

export interface Member { hero: Hero; cell: number; x: number; y: number; sprite: number }

/** _MCCPTile: hero or companion n stands on E00 frame 0x3B + 18n (n = h_orinum). */
const sprite = (h: Hero) => 0x3b + 18 * (h.rec.h_orinum as number);

export class Party {
  readonly members: Member[] = [];
  /** `_npcsta`: companions taken out of the location tables (in the party). */
  readonly away = new Set<number>();

  constructor(lead: Hero, x: number, y: number) {
    this.members.push({ hero: lead, cell: 0, x, y, sprite: sprite(lead) });
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
    const hero = new Hero(rec, items), m = { hero, cell, x, y, sprite: sprite(hero) };
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

  static async companion(num: number): Promise<HeroRecord> {
    return structuredClone((await json<HeroRecord[]>('companions.json'))[num - 1]);
  }
}
