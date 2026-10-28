// The player's hero from a new-game profile (docs/rules/new_game.md; HERO fields as in docs/structs.h).
import { json } from './pack';

export const PICK = 0x50;

export interface HeroRecord {
  h_name: string; h_fullnm: string; h_sex: number; h_strngth: number; h_dextrty: number; h_charm: number;
  h_lockpck: number; h_hitpts: number; h_hpmax: number; h_energy: number; h_gold: number;
  h_invitem: number[]; h_invamt: number[]; h_wears: number[]; h_inhand: number;
  [field: string]: unknown;
}

/** Attribute and skill fields in HERO order (structs.h), labelled for the sheet. */
export const STATS: [string, string][] = [['h_bravery', 'Bravery'], ['h_strngth', 'Strength'], ['h_dextrty', 'Dexterity'],
  ['h_endur', 'Endurance'], ['h_agility', 'Agility'], ['h_loyalty', 'Loyalty'], ['h_charm', 'Charm'], ['h_intellg', 'Intellect'],
  ['h_resist', 'Resist']];
export const SKILLS: [string, string][] = [['h_sword', 'Sword'], ['h_axe', 'Axe'], ['h_archry', 'Archery'], ['h_magic', 'Magic'],
  ['h_fist', 'Fist'], ['h_swim', 'Swim'], ['h_trade', 'Trade'], ['h_stealth', 'Stealth'], ['h_research', 'Research'],
  ['h_soulrd', 'Soulread'], ['h_lockpck', 'Lockpick'], ['h_track', 'Track'], ['h_music', 'Music'], ['h_carpent', 'Carpentry'],
  ['h_smith', 'Smith'], ['h_gemcut', 'Gemcut'], ['h_tailor', 'Tailor'], ['h_hunt', 'Hunt'], ['h_ldrshp', 'Leadership']];

export class Hero {
  constructor(readonly rec: HeroRecord, readonly items: string[]) {}

  /** Profile `profile` (0-4 = A-E). Profile gold is {hundreds, units} bytes (new_game.md). */
  static async profile(n: number): Promise<Hero> {
    const rec = { ...(await json<HeroRecord[]>('heroes.json'))[n] };
    rec.h_gold = (rec.h_gold & 0xff) * 100 + (rec.h_gold >> 8);
    return new Hero(rec, await json<string[]>('items.json'));
  }

  get name() { return this.rec.h_name; }
  get female() { return this.rec.h_sex === 1; }
  get charm() { return this.rec.h_charm; }

  /** The pack: name, count (equipment shows its wear), worn / in hand. Equipment bytes are 0x80 | wear (items.md). */
  pack(): { name: string; count: string; worn: boolean; hand: boolean }[] {
    const r = this.rec, out = [];
    for (let i = 0; i < r.h_invitem.length; i++) {
      const c = r.h_invitem[i], a = r.h_invamt[i];
      if (c === 0xff || c === 0) continue;                       // code 0 = coins, shown as gold
      out.push({ name: this.items[c] ?? `item ${c}`, count: a & 0x80 ? `wear ${a & 0x7f}` : String(a),
                 worn: r.h_wears.includes(i), hand: r.h_inhand === i });
    }
    return out;
  }

  /** _IsHeTr: energy 0 → Exhausted (cond1 0x10, Tired cleared); otherwise not Exhausted, Tired (cond2 0x20) below 15. */
  isHeTr() {
    const r = this.rec as Record<string, number>;
    if (r.h_energy === 0) { r.h_cond1 |= 0x10; r.h_cond2 &= ~0x20; return; }
    r.h_cond1 &= ~0x10;
    if (r.h_energy < 15) r.h_cond2 |= 0x20; else r.h_cond2 &= ~0x20;
  }

  /** _DecSta: lose `n` of a stat, floor 0. */
  lose(field: string, n: number) {
    const r = this.rec as Record<string, number>;
    r[field] = Math.max(0, r[field] - n);
  }

  /** _SumStat: the condition shown is the highest set bit of cond1<<8 | cond2 (`conds` = _w_conds). */
  condition(conds: string[]): string {
    const c = (this.rec.h_cond1 as number) << 8 | (this.rec.h_cond2 as number);
    for (let b = 15, i = 1; b >= 5; b--, i++) if (c & 1 << b) return conds[i];
    return conds[0];
  }

  /** _SearchInv: inventory slot holding `item`, or -1. */
  slot(item: number): number { return this.rec.h_invitem.indexOf(item); }

  /** _DecObj: one less of the item in `slot`; the slot empties at 0 (equipment bytes 0x80|wear count as one). */
  dec(slot: number) {
    const a = this.rec.h_invamt[slot];
    if (a & 0x80 || a <= 1) { this.rec.h_invitem[slot] = 0xff; this.rec.h_invamt[slot] = 0; }
    else this.rec.h_invamt[slot] = a - 1;
  }
}
