// Trading with a merchant (docs/rules/economy.md; P90 Buy ovl_0792, Sell ovl_09b8, haggling ovl_0eb1/ovl_0f5e).
import { json } from './pack';
import type { Hero } from './hero';

export interface ShopItem { item: number; pays: number; charges: number }
interface P90 { haggle: [number, number][]; lots: Record<string, number> }

let p90: P90 | null = null;
export async function loadTrade() { p90 ??= await json<P90>('p90.json'); }

/** Lot size: Food 12, Arrow 24, … else 1. */
export const lot = (item: number) => p90!.lots[String(item)] ?? 1;

/** Weapons, armour, clothing and spell books are sold singly with a yes/no; the rest by lots. */
export const single = (item: number) => (item >= 0x09 && item <= 0x30) || (item >= 0x53 && item <= 0x59);

/** Haggled prices per lot: the trade-skill difference moves both prices, clamped to the list prices. */
export function prices(s: ShopItem, heroTrade: number, merchantSkill: number): { pays: number; charges: number } {
  const diff = ((heroTrade - merchantSkill) << 24) >> 24;              // signed byte
  const [step, div] = p90!.haggle[s.item] ?? [0, 0];
  const adj = div && diff ? Math.floor(Math.abs(diff) / div) * step : 0;
  let pays = s.pays, charges = s.charges;
  if (heroTrade < merchantSkill) { charges += adj; pays = Math.max(1, pays - adj); }
  else { pays += adj; charges = Math.max(1, charges - adj); }
  charges = Math.min(2 * s.pays, Math.max(s.pays, charges));
  pays = Math.min(s.charges, Math.max(s.charges >> 1, pays));
  return { pays: Math.min(pays, charges), charges };
}

/** _IncObj: add `n` of `item`; equipment takes one slot each (byte 0x80 = no wear), stacks stop at 99. */
export function incObj(h: Hero, item: number, n: number): boolean {
  const r = h.rec, free = () => r.h_invitem.indexOf(0xff);
  if (single(item) && item <= 0x30) {
    if (r.h_invitem.filter(c => c === 0xff).length < n) return false;
    for (let i = 0; i < n; i++) { const s = free(); r.h_invitem[s] = item; r.h_invamt[s] = 0x80; }
    return true;
  }
  const s = h.slot(item);
  if (s >= 0) { if (r.h_invamt[s] + n > 99) return false; r.h_invamt[s] += n; return true; }
  const e = free();
  if (e < 0 || n > 99) return false;
  r.h_invitem[e] = item; r.h_invamt[e] = n;
  return true;
}

/** How many of `item` the hero can sell: all of its slots except the one in hand and worn ones. */
export function sellable(h: Hero, item: number): number[] {
  const r = h.rec, out: number[] = [];
  r.h_invitem.forEach((c, i) => { if (c === item && i !== r.h_inhand && !r.h_wears.includes(i)) out.push(i); });
  return out;
}
