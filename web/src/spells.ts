// Spells a hero casts in combat (rules/spells.md: _Magic, P94 ovl_1740, V06 INT 61h handlers, FFFAR HEAL/ENERGY/SHIELD).
import { FX, MISSILE } from './fx';
import type { Fight, Rec } from './combat';

type Text = (n: number, v?: Record<string, string | number>) => string;
const rnd = (n: number) => Math.floor(Math.random() * n);

/** Who a spell is aimed at: P94 TALIGN (0 own side, 1 the enemy), with the group spells and Assess/Timestop aimed at
 *  nobody; Courage (TALIGN 0xFF) at one's own side. */
export function aim(f: Fight, spell: number): 'own' | 'enemy' | null {
  if ([5, 19, 20, 21, 23, 33, 35].includes(spell)) return null;   // Assess, Zapall, Zengrl, Zishoxe, Zutyun, Terrify, Timestop
  if (spell === 38) return 'own';
  const s = f.data.spells.side[spell];
  return s === 0 ? 'own' : s === 1 ? 'enemy' : null;
}

/** Whom a hero may mark for `spell` (null: no target): the TALIGN side, or for the spells whose TALIGN is 0xFF their
 *  V06 handler's own test - Betray and Destroy any enemy (Destroy refuses `c_alignmnt` 0), Summon a monster of a race
 *  in the V06 0x14AE table, Double a hero (`c_recno` < 6), Jump anyone ("Mark who jumps.", ovl_1ef6), Restsoul a dead
 *  undead. */
export function targets(f: Fight, c: Rec, spell: number): Rec[] | null {
  const seen = f.recs.filter(t => f.visible(t));
  switch (spell) {
    case 30: case 32: return seen.filter(t => t.side !== c.side);
    case 31: return seen.filter(t => !t.hero && t.race >= 5 && f.data.spells.summon[t.race] === 0xff);
    case 34: return seen.filter(t => t.hero);
    case 24: return seen;
    case 40: return f.recs.filter(t => t.side && (t.state & 0x82) === 0x82 && !(t.state & 8));
  }
  const side = aim(f, spell);
  return side && seen.filter(t => side === 'own' ? t.side === c.side : t.side !== c.side);
}

/** The spells built here; the rest answer "The spell fails." */
export const BUILT = new Set([0, 2, 5, 6, 8, 9, 11, 12, 14, 16, 18, 19, 20, 21, 22, 23, 24, 27, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 40]);

/** A record as `_MultiFX` draws it: a hero (or double) by its number, a monster by its E01 tile. */
const person = (r: Rec) => ({ x: r.x, y: r.y, num: r.num, tile: r.tile, sheet: r.num === 0xff ? 'E01' as const : undefined });

/** `_EneUsg`: max(1, energy[spell] − magic/4). */
export const cost = (f: Fight, spell: number, magic: number) => Math.max(1, f.data.spells.energy[spell] - (magic >> 2));

/** INT61_43 spell power: max(0, magic/8 − target resist). */
const power = (c: Rec, t: Rec, m = c.mskl) => Math.max(0, (m >> 3) - t.res);

/** P94 ovl_15f8, the spell AI's "worth it" test for target `t` (spells.md, Spell AI). */
function worth(f: Fight, c: Rec, spell: number, t: Rec): boolean {
  switch (spell) {
    case 0: return !(t.state & 0x20) && power(c, t) > 0;
    case 11: return !(t.health & 0x20) && power(c, t) > 0;
    case 2: case 6: case 36: return f.missile(c, t);
    case 8: return !!(t.health & 1) || t.hp <= t.maxhp >> 1;
    case 9: return t.shield + t.armor >= 1;
    case 12: return false;                                         // Energy: monsters do not tire here
    case 14: { const near = Math.min(...f.enemies(t).map(e => Math.max(Math.abs(e.x - t.x), Math.abs(e.y - t.y))));
      return !t.invis && near <= (t.str > 15 ? 0 : 2); }
    case 16: return t.shield <= 30;
    case 18: return !!(t.health & 0x20);
    case 37: return t.hero ? t.hero.rec.h_rdyspl !== 0xff : false;
  }
  return t.wskl > 15 || t.str > 15;
}

/** P94 ovl_1553 for a monster: one of its two spells (`c_spell1/2`) with a target on the TALIGN side that passes
 *  `worth`, the first in record order; group spells need five such records (Zengrl ~ Heal, Zishoxe ~ Shield,
 *  Zutyun ~ Weaken, Zapall ~ Fireball). Null when nothing is worth casting. Only the BUILT spells are tried. */
export function monsterSpell(f: Fight, c: Rec, spells: number[]): { spell: number; target: Rec | null } | null {
  const known = spells.slice(0, 2).filter(s => s !== 0xff && BUILT.has(s) && s !== 5 && s !== 35);
  if (!known.length) return null;
  const spell = known[rnd(known.length)];
  const group: Record<number, number> = { 20: 8, 21: 16, 23: 9, 19: 6 };
  const side = f.data.spells.side[group[spell] ?? spell];
  const pool = f.recs.filter(t => f.visible(t) && (side === 0 ? t.side === c.side : t.side !== c.side));
  if (spell in group) return pool.filter(t => worth(f, c, group[spell], t)).length >= 5 ? { spell, target: null } : null;
  const target = pool.find(t => worth(f, c, spell, t));
  return target ? { spell, target } : null;
}

/** The sound of a combat spell, from its V06 handler's `_GameSound`: Fear, Betray 10 (mag1), Shatter, Fireball,
 *  Zefoar, Acidball 2 (fball), Assess 11 (mag2), Freeze, Zofir, Terrify 15 (mag3), Disappear, Jump 16 (invis), Drain
 *  24 (sick), See 10, Summon 9 (blink), Destroy 4 (explo2), Restsoul 5 (swoosh). */
const SOUND: Record<number, number> = { 0: 10, 2: 2, 5: 11, 6: 2, 11: 15, 14: 16, 18: 15, 22: 2, 24: 16, 27: 24, 28: 10,
  30: 10, 31: 9, 33: 15, 34: 9, 36: 2, 40: 5 };   // Destroy's 4 comes after its burst, on success

/** The spell's pictures (V06 handlers, FFFAR ovl_3228/ovl_3240; rules/effects.md), shown before its effect is resolved. */
function show(f: Fight, c: Rec, spell: number, t: Rec | null) {
  const fly = (type: number, to: Rec) => { const p = f.path(c, to); f.fx(FX.missile(p, MISSILE[type], undefined, type < 5)); return p[p.length - 1] ?? to; };
  const side = () => f.recs.filter(r => r.side === c.side && f.alive(r));
  switch (spell) {
    case 6: return f.fx(FX.bang(fly(1, t!)));                                             // Fireball: _Bang where it stops
    case 2: return void fly(6, t!);                                                         // Shatter
    case 36: return f.fx(FX.acidBang(fly(2, t!)));                                          // Acidball
    case 22: return f.fx(FX.bigBang(fly(1, t!)));                                           // Zefoar
    case 19: return f.fx(FX.multiBang(f.recs.filter(r => r.side !== c.side && f.visible(r) && f.missile(c, r)), 3));   // Zapall
    case 0: return f.fx(FX.spef3(t!));                                                      // Fear
    case 11: return f.fx(FX.spef3single(t!, 9));                                            // Freeze
    case 18: return f.fx(FX.spef3single(t!, 0xc));                                          // Zofir
    case 38: return f.fx(FX.spef6(t!));                                                     // Courage
    case 37: return f.fx(FX.spef5(t!));                                                     // Forget
    case 30: return f.fx(FX.spef7(t!));                                                     // Betray
    case 14: case 40: return f.fx(FX.blink(person(t!), null));                              // Disappear, Restsoul: _MultiFX out
    case 35: return f.fx(FX.invert(970, 11));                                               // Timestop: InvertWindow(0, 11)
    case 8: case 12: case 16: return f.fx(FX.spef4(t!, spell === 8 ? 10 : spell === 12 ? 0xc : 9));   // Heal, Energy, Shield
    case 20: case 21: for (const r of side()) f.fx(FX.spef4(r, spell === 20 ? 0xc : 9)); return;      // Zengrl, Zishoxe
  }
}

/** The effect of `spell` cast by `c` on `t` (null for untargeted spells; Jump's square `at`); returns the lines to print. */
export function effect(f: Fight, c: Rec, spell: number, t: Rec | null, text: Text, at?: { x: number; y: number }): string[] {
  const out: string[] = [];
  if (SOUND[spell]) f.sound(SOUND[spell]);
  show(f, c, spell, t);
  // INT61_01: a hero who used Turpin casts this spell with magic 99 (the flag is spent).
  const turpin = c.hero && (c.hero.rec.h_inuse as number) & 8;
  if (turpin) c.hero!.rec.h_inuse = (c.hero!.rec.h_inuse as number) & ~8;
  const m = turpin ? 99 : c.mskl;
  const foes = () => f.recs.filter(r => r.side !== c.side && f.visible(r));
  const mine = () => f.recs.filter(r => r.side === c.side && f.alive(r));
  const resists = (r: Rec) => [text(0x93, { a: r.name })];               // "%a resists the spell!"
  switch (spell) {
    case 6: return f.missile(c, t!) ? f.mdamage(c, t!, (m >> 1) + 5, text) : [];            // Fireball
    case 2: return f.missile(c, t!) ? f.mdamage(c, t!, rnd(m) + 5, text) : [];              // Shatter
    case 36: return f.missile(c, t!) ? f.mdamage(c, t!, Math.max(0, m - 4 * t!.res), text) : [];   // Acidball
    case 19: for (const r of foes().filter(r => f.missile(c, r))) {                          // Zapall
      if (r.race === 32) { out.push(text(0x100)); continue; }
      out.push(...f.mdamage(c, r, ((m >> 1) + 5) >> 1, text));
    } return out;
    case 22: {                                                                              // Zefoar
      if (!f.missile(c, t!)) return [];
      for (const r of f.recs.filter(r => f.visible(r) && Math.max(Math.abs(r.x - t!.x), Math.abs(r.y - t!.y)) <= 1)) {
        if (r.race === 32) { out.push(text(0x100)); continue; }
        out.push(...f.mdamage(c, r, m >> 1, text));
      }
      return out;
    }
    case 23: for (const r of f.recs.filter(r => r.side && f.visible(r))) {                 // Zutyun
      if (r.race === 32) { out.push(text(0x100)); continue; }
      r.armor = 0; r.shield = 0;
    } return [text(0x5b)];
    case 9: t!.armor = 0; t!.shield = 0; return [text(0x5b)];                              // Weaken
    case 0: {                                                                               // Fear
      const p = power(c, t!, m);
      if (!p) return resists(t!);
      t!.fear = Math.min(15, p); t!.state |= 0x20; t!.moves = 0;
      return [text(0x59, { a: t!.name, b: t!.fear })];
    }
    case 11: {                                                                              // Freeze
      const p = power(c, t!, m);
      if (!p) return resists(t!);
      t!.freeze = Math.min(15, (p >> 1) + 1); t!.health |= 0x20;
      return [text(0x5a, { a: t!.name, b: t!.freeze })];
    }
    case 18: if (!(t!.health & 0x20)) return [text(0x95)];                                 // Zofir
      t!.health &= ~0x20; t!.freeze = 0; t!.moves = 1; return [];
    case 38: t!.bravery = Math.min(12, t!.bravery + 5);                                     // Courage
      if (t!.hero) t!.hero.rec.h_bravery = t!.bravery;
      if (t!.state & 0x20) { t!.state &= 0x9f; t!.fear = 0; t!.moves = 1; }
      return [];
    case 14: t!.invis = m >> 3; return [text(0x5f, { a: t!.name, b: t!.invis })];          // Disappear
    case 28: {                                                                              // See
      const rad = 1 + (m > 49 ? 1 : 0) + (m > 74 ? 1 : 0);
      for (const r of f.recs.filter(r => r.side !== c.side && f.alive(r))) if (Math.max(Math.abs(r.x - t!.x), Math.abs(r.y - t!.y)) <= rad) r.invis = 0;
      return [];
    }
    case 37: if (!t!.hero) return [text(0x96, { a: t!.name })];                             // Forget (monsters: c_spell1)
      { const h = t!.hero.rec, s = h.h_rdyspl;
        if (s !== 0xff) { h.h_spells[Math.floor(s / 7)][s % 7] = 0; h.h_rdyspl = 0xff; } }
      return [text(0x96, { a: t!.name })];
    case 27: {                                                                              // Drain
      const n = c.side === 0 ? Math.floor(m / 10) : 1;
      if (t!.wskl >= 16) t!.wskl = Math.max(15, t!.wskl - n);
      if (t!.mskl >= 16) t!.mskl = Math.max(15, t!.mskl - n);
      return [];
    }
    case 40: if ((t!.state & 0x82) !== 0x82) return [text(0x95)];                           // Restsoul
      t!.state = (t!.state & ~2) | 8; t!.x = t!.y = -1; return [text(0x94, { l: t!.name })];
    case 35: f.timestop = true; return [];                                                  // Timestop
    case 30: if (!power(c, t!, m) || t!.res > 8) return resists(t!);                        // Betray: c_alignmnt ^= 1
      t!.side = t!.side ? 0 : 1; t!.target = 0xff;
      for (const r of f.recs) if (r.target === t!.recno) r.target = 0xff;
      return [];
    case 34: case 31: {                                                                     // Double, Summon
      const sq = f.nextTo(c);
      if (!sq) return [text(0x119)];
      const copy: Rec = spell === 34
        ? { ...t!, ...sq, recno: 22, hero: undefined, mskl: 0, fear: 0, freeze: 0, invis: 0, moves: 1, target: 0xff }
        : { ...t!, ...sq, recno: 23, side: 0, hp: t!.maxhp, invis: 0, target: 0xff, loot: undefined };
      f.spawn(copy);
      f.fx(FX.spef3single(copy, 0xf));                                                      // _movectileFX flag 0xF01
      return [];
    }
    case 32: {                                                                              // Destroy
      if (c.hero) c.hero.rec.h_spells = c.hero.rec.h_spells.map(row => row.map(() => 0));    // all 42 forgotten
      const gone = f.data.spells.destroy[t!.race] === 1;
      f.fx(FX.blast(f.distances(t!.x, t!.y, true), gone));
      if (!gone) return resists(t!);
      f.fx([{ ...FX.spef3single(t!, 0xf)[0], sound: 4 }]);
      t!.state = 0x98; t!.x = t!.y = -1;
      for (const r of f.recs) if (r.target === t!.recno) r.target = 0xff;
      return [];
    }
    case 24: {                                                                              // Jump: ovl_27e6
      const d = f.distances(at!.x, at!.y, true);
      if (!f.free(at!.x, at!.y) || d[t!.y * 11 + t!.x] >= 0x7e) return [text(0x119)];
      f.fx(FX.blink(person(t!), person({ ...t!, ...at! })));
      t!.x = at!.x; t!.y = at!.y;
      f.spring(t!, text);                                                                   // V06 0x2085: INT61_42
      return [];
    }
    case 33: for (const r of foes()) if (rnd(12) < power(c, r, m)) { r.bravery = 0; r.state |= 0x40; }   // Terrify
      return [text(0x97, { a: c.name })];                                                  // Timestop
    case 5: return f.recs.filter(r => r.side && f.alive(r)).map(r => `${r.name}: HP ${r.hp}, A ${r.armor}, SH ${r.shield}`);   // Assess
    // FFFAR: Heal / Zengrl set HP to the maximum and stand a downed target up; Energy = a Sermin; Shield = the caster's
    // magic skill; Zishoxe = half of it on the whole side.
    case 8: case 20: for (const r of spell === 8 ? [t!] : mine()) {
      r.hp = r.maxhp;
      if (r.health & 1) { r.health &= ~1; if (r.hero) { r.agi = r.hero.rec.h_agility as number; r.dex = r.hero.rec.h_dextrty; } else { const s = f.data.monsters[r.race - 5]; r.agi = s.agi; r.dex = s.dex; } }
      if (r.hero) r.hero.rec.h_hitpts = r.hp;
      out.push(text(0x5c, { a: r.name }));
    } return out;
    case 12: if (!t!.hero) return [text(0x95)];
      t!.hero.use(0x33, 0); return [text(0x5d, { a: t!.name })];
    case 16: case 21: for (const r of spell === 16 ? [t!] : mine()) {
      r.shield = spell === 16 ? m : m >> 1;
      if (r.hero) r.hero.rec.h_shield = r.shield;
      out.push(text(0x5e, { a: r.name, b: r.shield }));
    } return out;
  }
  return [text(0x119)];                                                                     // "The spell fails."
}
