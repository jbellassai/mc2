// The player's hero from a new-game profile (docs/rules/new_game.md; HERO fields as in docs/structs.h).
import { json } from './pack';

export const PICK = 0x50;

export interface HeroRecord {
  h_name: string; h_fullnm: string; h_sex: number; h_strngth: number; h_dextrty: number; h_charm: number;
  h_lockpck: number; h_hitpts: number; h_energy: number; h_gold: number; h_invitem: number[]; h_invamt: number[];
}

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

  /** _SearchInv: inventory slot holding `item`, or -1. */
  slot(item: number): number { return this.rec.h_invitem.indexOf(item); }

  /** _DecObj: one less of the item in `slot`; the slot empties at 0 (equipment bytes 0x80|wear count as one). */
  dec(slot: number) {
    const a = this.rec.h_invamt[slot];
    if (a & 0x80 || a <= 1) { this.rec.h_invitem[slot] = 0xff; this.rec.h_invamt[slot] = 0; }
    else this.rec.h_invamt[slot] = a - 1;
  }
}
