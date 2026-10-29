// Combat (rules/combat.md, encounters.md): up to 24 CMBTNT records on an 11×9 arena, party slots first. Built so far:
// the wilderness arena (P96 formation 0, random monster squares), rounds and actions (P94 ovl_04a6), melee and bow
// attacks with dodge, knockdown, armour, weapon wear and skill gains (P06 ovl_050a/ovl_0cde, FAR_SKILLUP), and the
// monster AI's targeting and movement (P94 ovl_0b4b), magic damage and missiles for the heroes' spells (spells.ts).
// Monsters cast their two spells by the leader race's D06 chance (spells.ts). The pre-fight Talk (rally, hailing the leader) is here and in main.ts. Not yet: Doombeast images.
import { json } from './pack';
import type { Hero } from './hero';
import type { Level } from './level';
import { effect, monsterSpell } from './spells';

interface Monster { name: string; hp: number; shield: number; weapon: number; armor: number; bravery: number; str: number;
  dex: number; agi: number; res: number; int: number; wskl: number; mskl: number; spells: number[]; tile: number;
  anim: number; leader: number; undead: number }
interface Weapon { minst: number; basedam: number; type: number; unbreakable: number; stbonus: number; sklbonus: number;
  race: number; hitlist: number[] }
export interface CombatData { monsters: Monster[]; groups: number[][]; weapons: Weapon[]; setupxy: number[]; maxtbl: number[];
  ranges: { x: number[][]; y: number[][] }; guarddiff: number[];
  loot: { thresholds: number[]; items: number[]; amounts: number[][]; an: number[] }; resurrect: string[];
  d06: { cast: number[]; crit: number[]; crit2: number[]; prey: number[]; counts: number[]; armor: number[]; dodge: number[];
    gonshi: number[]; sermin: number[]; potion: number[] };
  spells: { names: string[]; energy: number[]; where: number[]; side: number[]; skill: number[]; here: number[] };
  songs: { instruments: number[]; races: number[][]; names: string[][] };
  parley: { texts: string[]; kins: string[]; attitudes: string[]; worth: number[]; rolls: number[] } }

/** A CMBTNT record. `side` 0 = party (`c_alignmnt` 0), 1 = monsters. */
export interface Rec {
  recno: number; side: 0 | 1; name: string; race: number; hero?: Hero; num: number; tile: number;
  x: number; y: number; hp: number; shield: number; armor: number; bravery: number; str: number; dex: number;
  agi: number; int: number; wskl: number; weapon: number; res: number; mskl: number; maxhp: number;
  invis: number;    // c_invis: turns left invisible
  fear: number;     // c_itspc1 high nibble: turns left feared (c_state 0x20)
  freeze: number;   // c_itspc1 low nibble: turns left frozen (c_health 0x20)
  nift: number;     // c_renspl3: Nift charges left (blows fully absorbed)
  state: number;    // c_state: 0x80 dead, 0x10 removed, 4 leader, 2 undead
  health: number;   // c_health: 1 knocked down
  target: number;   // c_target, 0xFF none
  moves: number;    // c_removes: actions left this round
  loot?: { item: number; amount: number };   // c_itspc1/c_qaspc2 after the fight (P95 ovl_08f6); amount 0 = nothing
}

const rnd = (n: number) => Math.floor(Math.random() * n);   // _RndCo
/** Directions 0-7: W N E S NW NE SE SW (P06 file 0x93 dx, 0x9B dy). */
const DX = [-1, 0, 1, 0, -1, 1, 1, -1], DY = [0, -1, 0, 1, -1, -1, 1, 1];
/** P06 ovl_0b2b: attacker → target direction from sign and slope bits (table P06 file 0xB0B). */
const DIRTBL = [1, 255, 5, 2, 3, 255, 6, 2, 1, 255, 4, 0, 3, 255, 7, 0];
const W = 11, H = 9, ARROWS = 0x51, NONE = 0xff;
const cheb = (a: Rec, x: number, y: number) => Math.max(Math.abs(a.x - x), Math.abs(a.y - y));

export class Fight {
  readonly recs: Rec[] = [];
  /** `_GameSound` and `_song` (sound.ts), set by the caller. */
  sound: (n: number) => void = () => {};
  music: (n: number) => void = () => {};
  private skilled = new Set<string>();   // G_sklbits: one gain per hero and combat skill per fight
  timestop = false;                       // _timestop: monsters cannot act, blows cannot miss; cleared each round
  readonly magbits = new Set<number>();   // _magbits: spells 30-35 cast this encounter
  /** P96 `OV_0x192`: the race the party can talk to, the group's starred extra entry (ovl_06b8), else 0. */
  speaker = 0;
  /** `_cmbtyp` 0: a street fight, which has no pre-fight menu. */
  street = false;
  /** `_endcmbt` set before any round: 1 the monsters surrendered (a win, with loot), 4 they left (P95 makes it a win). */
  ended: 0 | 1 | 4 = 0;
  /** P96 `OV_0x197`: the attitude rolled at set-up (`attitude()`), used by Greet. */
  mood = 0;

  private constructor(readonly data: CombatData, readonly level: Level) {}

  static async data(): Promise<CombatData> { return json<CombatData>('combat.json'); }

  /** A wilderness fight (`_cmbtyp` 1): side 6 (heroes at formation 0, monsters in side 6's rectangles). */
  static wild(data: CombatData, level: Level, heroes: { hero: Hero; num: number }[], group: number, diff: number): Fight {
    return Fight.setup(data, level, heroes, group, diff, 6, null, null);
  }

  /** A street fight (`_cmbtyp` 0, ambushes): the arena is the 11×9 view cut from the level, each hero keeps its square
   *  (`at`, relative to the view); monsters scan the arena from RndCo(99) in steps of 17 (mod 99). */
  static street(data: CombatData, level: Level, heroes: { hero: Hero; num: number }[], group: number, diff: number,
                at: { x: number; y: number }[]): Fight {
    return Fight.setup(data, level, heroes, group, diff, 6, null, at);
  }

  /** A dungeon-room fight (`_cmbtyp` 5): the door's side (type 6-9) places both sides; the flee squares are the room's
   *  doors (`doors`, P96 ovl_0e19), taken one step inside the room. */
  static room(data: CombatData, level: Level, heroes: { hero: Hero; num: number }[], group: number, diff: number, side: number,
              doors: { x: number; y: number }[]): Fight {
    return Fight.setup(data, level, heroes, group, diff, side, doors, null);
  }

  /** P96 setup: heroes at formation `side − 6` of `_setupxy` (member m at 6f + m, _PlacePerson), then the group's
   *  monsters — in a room, a random square in the side's rectangle (P96 0x19/0x29; casters, `c_magskl ≠ 0` except
   *  Vankruh and Doombeast, by the casters' rectangle), moved by _PlacePerson and re-rolled until the square is free and
   *  reachable from the first hero (`_blobmap` < 100 over the background, P96 ovl_10ec). The best leader rank leads. */
  private static setup(data: CombatData, level: Level, heroes: { hero: Hero; num: number }[], group: number, diff: number,
                       side: number, doors: { x: number; y: number }[] | null, street: { x: number; y: number }[] | null): Fight {
    const f = new Fight(data, level), k = side - 6;
    f.street = !!street;
    const taken = (x: number, y: number) => f.occupied(x, y);
    heroes.forEach(({ hero, num }, m) => {
      const r = hero.rec as Record<string, number> & typeof hero.rec, item = r.h_inhand === NONE ? NONE : r.h_invitem[r.h_inhand];
      const at = street ? street[m] : level.place(data.setupxy[6 * k + m], data.setupxy[24 + 6 * k + m], taken);
      f.recs.push({ recno: m, side: 0, name: hero.name, race: r.h_race, hero, num, tile: 0,
        x: at.x, y: at.y, hp: r.h_hitpts, shield: r.h_shield, armor: f.heroArmor(hero),
        bravery: r.h_bravery, str: r.h_strngth, dex: r.h_dextrty, agi: r.h_agility, int: r.h_intellg,
        wskl: Fight.wpnSkl(hero), weapon: item, res: r.h_resist, mskl: r.h_magic, maxhp: r.h_hpmax, invis: 0, fear: 0, freeze: 0,
        nift: r.h_inuse & 0x40 ? 3 : 0, state: r.h_cond1 & 0x80 ? 0x80 : 0, health: 0, target: NONE, moves: 0 });
    });
    for (const code of f.roster(group, diff)) {
      const s = data.monsters[(code & 0x7f) - 5], recno = 6 + f.recs.length - heroes.length;
      const reach = f.distances(f.recs[0].x, f.recs[0].y, true);
      const ok = (x: number, y: number) => x >= 0 && f.free(x, y) && reach[y * W + x] < 0x7e;
      let x = -1, y = -1;
      if (street) {
        for (let i = rnd(99), n = 0; n < 99; i = (i + 17) % 99, n++) if (ok(i % W, Math.floor(i / W))) { x = i % W; y = Math.floor(i / W); break; }
      } else {
        const c = s.mskl && (code & 0x7f) !== 28 && (code & 0x7f) !== 32 ? 4 : 0, rx = data.ranges.x[c + k], ry = data.ranges.y[c + k];
        for (let n = 0; n < 200 && !ok(x, y); n++)
          ({ x, y } = level.place(rx[0] + rnd(rx[1] - rx[0] + 1), ry[0] + rnd(ry[1] - ry[0] + 1), taken));
      }
      if (!ok(x, y)) continue;                             // no room left: the monster stays out (the original loops)
      f.recs.push({ recno, side: 1, name: s.name, race: code & 0x7f, num: NONE, tile: s.tile, x,
        y, hp: s.hp, shield: s.shield, armor: s.armor, bravery: s.bravery, str: s.str, dex: s.dex,
        agi: s.agi, int: s.int, wskl: s.wskl, weapon: s.weapon, res: s.res, mskl: s.mskl, maxhp: s.hp, invis: 0, fear: 0, freeze: 0, nift: 0, state: s.undead ? 2 : 0, health: 0, target: NONE, moves: 0 });
    }
    const lead = f.recs.filter(r => r.side && data.monsters[r.race - 5].leader !== NONE)
      .sort((a, b) => data.monsters[b.race - 5].leader - data.monsters[a.race - 5].leader)[0];
    if (lead) lead.state |= 4;
    f.flee = doors ? new Set(doors.map(d => Math.min(H - 2, Math.max(1, d.y)) * W + Math.min(W - 2, Math.max(1, d.x)))) : f.fleeSquares();
    return f;
  }

  /** P96 ovl_020a: monster codes for group `g`. Below 60, `g` itself; else row g − 60 = {count, m0..m3}, a zero count
   *  taken from D06's row for the difficulty (lo .. hi − 1); each monster is one of the four entries at random, and an entry with bit 0x80 adds
   *  one more of that code on top. (The per-entry quotas, OV_0x19b, are not modelled.) */
  private roster(g: number, diff: number): number[] {
    const row = g < 60 ? [0, g, g, g, g] : this.data.groups[g - 60];
    const c = this.data.d06.counts, lo = c[7 * diff], hi = c[7 * diff + 1];   // P96 0x334: lo + seed mod (hi − lo)
    const n = row[0] || lo + (hi > lo ? rnd(hi - lo) : 0);
    const out = Array.from({ length: n }, () => row[1 + rnd(4)] & 0x7f);
    const extra = row.slice(1).find(c => c & 0x80);
    if (extra) { out.push(extra & 0x7f); this.speaker = extra & 0x7f; }
    return out;
  }

  /** V06 INT61_00: armour = Σ D06 armour value of each worn item 0x1F-0x2A (items.md). */
  private heroArmor(h: Hero): number {
    const r = h.rec;
    return r.h_wears.reduce((s, w) => { const c = w === NONE ? 0 : r.h_invitem[w]; return s + (c >= 0x1f && c <= 0x2a ? this.data.d06.armor[c - 0x1f] : 0); }, 0);
  }

  /** _GetWpnSkl: the skill for the weapon in hand (items 9-0x11 sword, -0x19 axe, -0x1E archery), else fist. */
  static wpnSkl(h: Hero): number {
    const r = h.rec as Record<string, number> & typeof h.rec;
    const c = r.h_inhand === NONE ? NONE : r.h_invitem[r.h_inhand];
    return c < 0x12 ? r.h_sword : c < 0x1a ? r.h_axe : c < 0x1f ? r.h_archry : r.h_fist;
  }

  private weapon(r: Rec): Weapon | null { return r.weapon >= 9 && r.weapon <= 0x1e ? this.data.weapons[r.weapon - 9] : null; }
  alive(r: Rec): boolean { return !(r.state & 0x90); }
  visible(r: Rec): boolean { return this.alive(r) && !r.invis; }
  at(x: number, y: number): Rec | undefined { return this.recs.find(r => this.alive(r) && r.x === x && r.y === y); }
  private occupied(x: number, y: number) { return !!this.at(x, y); }
  free(x: number, y: number): boolean {
    return x >= 0 && y >= 0 && x < W && y < H && this.level.walkable(x, y) && !this.occupied(x, y);
  }
  enemies(r: Rec): Rec[] { return this.recs.filter(e => e.side !== r.side && this.visible(e)); }

  /** INT61_08: 1 = no monster left, 2 = every party member dead, 3 = the rest of the party fled, else 0. */
  outcome(): 0 | 1 | 2 | 3 {
    if (this.ended) return 1;
    const party = this.recs.filter(r => r.side === 0);
    if (!this.recs.some(r => r.side === 1 && this.alive(r))) return 1;
    if (party.every(r => r.state & 0x80)) return 2;
    if (!party.some(r => this.alive(r))) return 3;
    return 0;
  }

  /** P96 ovl_0b5c: the monsters' attitude (`_w_attitudes` 0-7). No speaker → 6, a speaker of race ≥ 25 → 7. Else
   *  the monsters' strength M = Σ (hp + magic skill, +10 with a bow) against the party's worth P = Σ worth[race]
   *  (P96 0xB3F): M / P ≥ 2 → 5; = 1 → rolls[11 + RndCo(6)]; 0 → rolls[M / (P / 8) + RndCo(4)] (P96 0xB4B; the second
   *  table follows the first, and the index can run into it). P = 0 would divide by zero in DOS; taken as ≥ 2 here. */
  attitude(): number {
    if (!this.speaker) return 6;
    if (this.speaker >= 25) return 7;
    let m = 0, p = 0;
    for (const r of this.recs.filter(r => !(r.state & 8))) {
      if (r.side) m += r.hp + r.mskl + (r.weapon >= 0x1a && r.weapon < 0x80 ? 10 : 0);
      else p += this.data.parley.worth[r.race] ?? 0;
    }
    const { rolls } = this.data.parley, q = p ? Math.floor(m / p) : 2;
    if (q >= 2) return 5;
    if (q === 1) return rolls[11 + rnd(6)];
    return rolls[Math.floor(m / Math.max(1, p >> 3)) + rnd(4)];
  }

  /** P96 ovl_0a22: the monsters leave ("The monsters leave."): every monster is taken off the board. */
  leave() {
    for (const r of this.recs.filter(r => r.side)) { r.state |= 0x10; r.x = r.y = -1; }
    this.ended = 4;
  }

  /** `_fleetbl` (P96 ovl_0c5c/ovl_0c6f, wilderness): the arena's edge squares the first hero can reach (`_blobmap` < 100,
   *  flood-filled over the background only). (P96 moves an edge square one step inward where the edge has a door;
   *  arenas cut from G00 have none.) */
  private fleeSquares(): Set<number> {
    const h = this.recs[0], d = this.distances(h.x, h.y, true), out = new Set<number>();
    for (let y = 0; y < H; y++) for (let x = 0; x < W; x++)
      if ((x === 0 || y === 0 || x === W - 1 || y === H - 1) && d[y * W + x] < 0x7e && this.level.walkable(x, y)) out.add(y * W + x);
    return out;
  }
  flee = new Set<number>();

  /** Off the board: a fled hero (P94 ovl_01ad) or monster (ovl_10ef): `c_state |= 0x10`, position −1. */
  remove(r: Rec) { r.state |= 0x10; r.x = r.y = -1; r.moves = 0; for (const o of this.recs) if (o.target === r.recno) o.target = NONE; }

  /** P95 ovl_08f6, after a won fight, for every slain monster (not fled or removed): a coin flip; heads 5-10 Coins,
   *  tails an item only if RndCo(20) + diff > 10, by the race's d100 bands (P95 0x21E/0x17A, race·4) with an amount from
   *  the {item, lo, hi} table (P95 0x13A), else 1; weapons and armour (9-0x30) come worn, 0x80 | RndCo(20) (ovl_0a78).
   *  Vankruh leaves nothing but sets events 150 and, if slain, 61. Returns the loot value for hirelings' `partybucks`. */
  rollLoot(diff: number, events: Set<number>, values: number[]): number {
    const L = this.data.loot;
    let value = 0;
    for (const r of this.recs.filter(m => m.side && !(m.state & 0x18))) {
      if (r.race === 28) { events.add(150); if (r.state & 0x80) events.add(61); continue; }
      let item = 0, amount = 0;
      if (rnd(2)) amount = rnd(6) + 5;
      else if (rnd(20) + diff > 10 && L.thresholds[r.race * 4]) {
        const d = rnd(100);
        let i = r.race * 4;
        while (L.thresholds[i] <= d) i++;
        item = L.items[i];
        const t = L.amounts.find(a => a[0] === item);
        amount = t ? t[1] + rnd(t[2] - t[1] + 1) : 1;
        if (item >= 9 && item <= 0x30) amount = 0x80 | rnd(20);
      }
      r.loot = { item, amount };
      value += values[item] * (amount & 0x80 ? 1 : amount);
    }
    return value;
  }

  /** P94 ovl_04a6, every round: undead rise with 1 HP; each living record gets 1 action, one more when dex·8+4 ≥ 50
   *  (then −50), and one more if RndCo(100) is below the rest: dex 0 → 1, 6 → 2, 12 → 3. */
  newRound() {
    for (const r of this.recs) {
      if (r.state & 0x80 && r.state & 2) { r.state &= 0x7f; r.health &= 0x7f; r.hp = 1; }
      if (r.state & 0xb0 || r.health & 0x20) { r.moves = 0; continue; }   // removed, dead, feared, frozen
      let n = r.dex * 8 + 4;
      r.moves = 1;
      if (n >= 50) { r.moves++; n -= 50; }
      if (rnd(100) < n) r.moves++;
      if (r.hero && (r.hero.rec.h_inuse as number) & 0x80) r.moves = 4;   // Gonshi
    }
  }

  /** P94 ovl_0655, after a side's phase: its records' invisibility, freeze and fear turns count down. */
  endSide(side: 0 | 1) {
    for (const r of this.recs.filter(o => o.side === side)) {
      if (r.invis) r.invis--;
      if (r.freeze && !--r.freeze) r.health &= ~0x20;
      if (r.fear && !--r.fear) r.state &= ~0x20;
    }
    if (side) this.timestop = false;
  }

  /** P06 ovl_1144: a missile flies the line from `a` toward `t` and stops on the first unwalkable or occupied square;
   *  true when it reaches the target. (The line is a Bresenham walk as in `clear`.) */
  missile(a: Rec, t: Rec): boolean { return this.clear(a, t); }

  /** `_MDamage` (P06 ovl_0fa9): shield points absorb first, then HP; death, and the knockdown roll with the caster's
   *  weapon skill and dexterity. Returns the blow's lines (the ovl_0bc2 format with " (SH:%b)"). */
  mdamage(c: Rec, t: Rec, n: number, text: (n: number, v?: Record<string, string | number>) => string): string[] {
    const shield = t.shield, dam = Math.max(0, n - shield);
    t.shield -= Math.min(n, shield);
    t.hp -= dam;
    let result = 1;
    if (t.hp <= 0) { t.hp = 0; result = 0xff; t.state |= 0x80; for (const r of this.recs) if (r.target === t.recno) r.target = NONE; }
    else if (dam > 0 && !(t.health & 1) && t.race !== 28 && (c.wskl >> 3) + c.dex > rnd(100)) {
      result = 2; t.health |= 1; t.agi = 0; t.dex = 0;
      if (t.hero) t.hero.rec.h_cond1 = (t.hero.rec.h_cond1 as number) | 1;
    }
    if (t.hero) { t.hero.rec.h_hitpts = t.hp; t.hero.rec.h_shield = t.shield; if (result === 0xff) t.hero.rec.h_cond1 = (t.hero.rec.h_cond1 as number) | 0x80; }
    const out = [`${text(0x46, { a: c.name })}${text(0x47)}${text(0x46, { a: t.name })}${text(0x10)}${text(0x4a)}${n}`,
      `${text(0x4b)}${dam}${text(0x57, { b: t.shield })}${text(0x4d)}${t.hp}`];
    if (result === 2) { out.push(text(0x48)); if (t.race !== 36) out.push(text(0x49, { a: t.name })); }
    return out;
  }

  /** FAR_SKILLUP for skill `idx` (0 sword … 3 magic, 4 fist): once per hero, skill and fight; chance base[idx] +
   *  (50 − skill)/4 below 50, else − (skill − 50)/2 (at least 1); never above _MaxSkill. */
  skillUp(a: Rec, idx: number, text: (n: number, v?: Record<string, string | number>) => string): string[] {
    const h = a.hero, key = `${a.recno}:${idx}`;
    if (!h || this.skilled.has(key)) return [];
    const r = h.rec as Record<string, number> & typeof h.rec, field = ['h_sword', 'h_axe', 'h_archry', 'h_magic', 'h_fist'][idx];
    const skill = r[field], chance = [30, 15, 25, 20, 25][idx] + (skill < 50 ? (50 - skill) >> 2 : -Math.max(1, (skill - 50) >> 1));
    if (skill >= this.data.maxtbl[idx * 6 + r.h_race] || rnd(100) >= chance) return [];
    this.skilled.add(key);
    r[field] = skill + 1;
    a.wskl = Fight.wpnSkl(h); a.mskl = r.h_magic;
    return [text(0x60, { h: a.name, l: ['Sword', 'Axe', 'Archery', 'Magic', 'Fist'][idx] })];
  }

  /** V06 INT61_1d, an instrument used in combat: no music skill → comtxt 0x117; no song known for it (`h_songs`
   *  bits 0/1) → "The Happy Traveller" (0x118); else each known song (0xF3) charms every living monster of its race
   *  (V06 0x4EC) when RndCo(200) ≤ music + 100: `c_state |= 0x21`, feared with no turn count, so for the whole fight. */
  song(a: Rec, item: number, text: (n: number, v?: Record<string, string | number>) => string): string[] {
    const r = a.hero!.rec as Record<string, number> & Hero["rec"], k = this.data.songs.instruments.indexOf(item);
    if (!r.h_music) return [text(0x117, { h: a.name })];
    const known = (r.h_songs as unknown as number[])[k] & 3;
    if (!known) { this.music(12); return [text(0x118, { h: a.name })]; }
    const out: string[] = [];
    for (const n of [0, 1]) if (known & 1 << n) {
      this.music(3 + 2 * k + n);                          // V06 0x2904: instrument k's songs are 3 + 2k and 4 + 2k
      out.push(text(0xf3, { h: a.name, a: this.data.songs.names[k][n] }));
      for (const m of this.recs.filter(o => o.side && this.alive(o) && o.race === this.data.songs.races[k][n]))
        if (rnd(200) <= r.h_music + 100) { m.state |= 0x21; m.moves = 0; }
    }
    return out;
  }

  /** A step of one square (`_RMove` in combat); the arena edge is not an exit here yet. */
  move(r: Rec, dx: number, dy: number): boolean {
    if (!this.free(r.x + dx, r.y + dy)) return false;
    r.x += dx; r.y += dy; r.moves--;
    return true;
  }

  /** In weapon range: Chebyshev 1, or anywhere with a bow (`_ChkRng`, `G_wrkamt` 1 or 100) and a clear line. */
  inRange(a: Rec, t: Rec): boolean {
    return this.weapon(a)?.type === 3 ? this.clear(a, t) : cheb(a, t.x, t.y) <= 1;
  }

  /** P94 ovl_1af1 `_PATHBLK`: no unwalkable square or living record between the two (a Bresenham line; assumed). */
  private clear(a: Rec, t: Rec): boolean {
    const n = cheb(a, t.x, t.y);
    for (let i = 1; i < n; i++) {
      const x = Math.round(a.x + (t.x - a.x) * i / n), y = Math.round(a.y + (t.y - a.y) * i / n);
      if (!this.level.walkable(x, y) || this.occupied(x, y)) return false;
    }
    return true;
  }

  /** `_Attack` (P06 ovl_050a → ovl_0cde): one blow; returns the lines to print. Uses one action. */
  attack(a: Rec, t: Rec, text: (n: number, vars?: Record<string, string | number>) => string): string[] {
    const w = this.weapon(a), out: string[] = [];
    a.moves--;
    if (a.hero && w?.type === 3) {                        // a hero's bow needs arrows (_SearchInv, _DecObj0)
      const s = a.hero.slot(ARROWS);
      if (s < 0) return [text(0x4f, { h: a.name })];      // "%h has no arrows."
      a.hero.dec(s);
    }
    this.sound(w?.type === 3 ? 6 : 5);                     // P06: twang for a shot, swoosh for a swing
    // P06 ovl_0b2b: the attack direction, for the dodge step.
    const dx = t.x - a.x, dy = a.y - t.y, ax = Math.abs(dx), ay = Math.abs(dy);
    const dir = DIRTBL[(dx < 0 ? 8 : 0) | (dy < 0 ? 4 : 0) | (3 * ax >= ay + 2 ? 2 : 0) | (3 * ay <= ax + 1 ? 1 : 0)];
    let result: number;
    const inuse = (a.hero?.rec.h_inuse as number | undefined) ?? 0;
    if (inuse & 0x10) a.hero!.rec.h_inuse = inuse & ~0x10;               // Luffin: this blow cannot be dodged
    const sure = inuse & 0x10 || t.health & 0x70 || a.invis || t.race === 32 || this.timestop || (w?.hitlist.includes(t.race) ?? false);
    const skill = (a.wskl + (w?.sklbonus ?? 0)) >> (t.invis ? 1 : 0), thresh = (skill + 50 - 8 * t.agi) & 0xff;
    if (!sure && (skill + 50 < 8 * t.agi || thresh === 0 || thresh < rnd(100))) {
      result = 0;                                          // dodged: a side-step from D06 ptr10 (P06 ovl_0fcf)
      for (const adj of [1, 0]) {
        const d = this.data.d06.dodge[dir * 2 + adj];
        if (this.free(t.x + DX[d], t.y + DY[d])) { t.x += DX[d]; t.y += DY[d]; break; }
      }
    } else {
      let hit = w ? (w.stbonus + a.str - w.minst) * 2 + w.basedam : a.str;
      if (t.race === 36 && a.weapon - 9 === 16) hit *= 4;  // Rhokadur against a Dreadknight
      if (a.hero && w?.type !== 3 && (a.hero.rec.h_inuse as number) & 0x20) {   // Mirget: a melee hit triples
        hit += 2 * hit; a.hero.rec.h_inuse = (a.hero.rec.h_inuse as number) & ~0x20;
      }
      const nift = t.nift > 0;                             // Nift: the blow is fully absorbed (G_SWNIFT)
      if (nift && !--t.nift && t.hero) t.hero.rec.h_inuse = (t.hero.rec.h_inuse as number) & ~0x40;
      const dam = nift ? 0 : Math.max(0, hit - t.armor);
      t.hp -= dam;
      result = 1;
      if (t.hp <= 0) { t.hp = 0; result = 0xff; t.state |= 0x80; }
      else if (dam > 0 && !(t.health & 1) && t.race !== 28 && (a.wskl >> 3) + a.dex > rnd(100)) {
        result = 2; t.health |= 1; t.agi = 0; t.dex = 0; t.moves = Math.min(t.moves, 1);   // knocked down
        if (t.hero) t.hero.rec.h_cond1 = (t.hero.rec.h_cond1 as number) | 1;              // Wounded
      }
      if (t.hero) { t.hero.rec.h_hitpts = t.hp; if (result === 0xff) t.hero.rec.h_cond1 = (t.hero.rec.h_cond1 as number) | 0x80; }
      // ovl_0bc2: "%a hits %a. -HIT" / "Dam:n (A-armour) HP:n", then "CRITICAL HIT!" and "%a is wounded." on a knockdown.
      out.push(`${text(0x46, { a: a.name })}${text(0x47)}${text(0x46, { a: t.name })}${text(0x10)}${text(0x4a)}${hit}`,
        `${text(0x4b)}${dam}${nift ? text(0x58, { b: t.nift }) : text(0x4c, { b: t.armor })}${text(0x4d)}${t.hp}`);
      if (result === 2) { out.push(text(0x48)); if (t.race !== 36) out.push(text(0x49, { a: t.name })); }
    }
    if (result) { if (a.race === 0x12) this.sound(11); this.sound(1); }   // a blow that lands (a Barg's with a flash)
    if (a.hero) out.push(...this.afterHeroBlow(a, w, result, text));
    // ovl_050a: a target that was hit turns on its attacker unless RndCo(100) ≤ its c_intel.
    if (result !== 0 && this.alive(t) && t.int < rnd(100)) t.target = a.recno;
    if (result === 0xff) for (const r of this.recs) if (r.target === t.recno) r.target = NONE;
    return out;
  }

  /** After a hero's blow: a landed one may raise the weapon skill (FAR_SKILLUP) and may break the weapon; any blow but a
   *  dodge wears it (combat.md, Weapon wear); every attack costs 2 energy (`h_energy −= 2`, _IsHeTr). */
  private afterHeroBlow(a: Rec, w: Weapon | null, result: number, text: (n: number, v?: Record<string, string | number>) => string): string[] {
    const h = a.hero!, r = h.rec as Record<string, number> & typeof h.rec, out: string[] = [];
    if (result !== 0) {
      out.push(...this.skillUp(a, w ? w.type - 1 : 4, text));
      if (w && !w.unbreakable && r.h_inhand !== NONE) {
        const wear = r.h_invamt[r.h_inhand] & 0x7f;
        if (wear >= 90 || (wear >= 25 && wear >> 1 >= rnd(100))) {
          r.h_invamt[r.h_inhand] = 0xe2; r.h_inhand = NONE; a.weapon = NONE; a.wskl = Fight.wpnSkl(h);
          out.push(text(0x76, { h: a.name }));            // "%h's weapon breaks!"
        }
      }
    }
    if (result !== 0 && r.h_inhand !== NONE && w && !w.unbreakable && (r.h_invamt[r.h_inhand] & 0x7f) < 0x7f) r.h_invamt[r.h_inhand]++;
    r.h_energy = Math.max(0, r.h_energy - 2);
    h.isHeTr();
    return out;
  }

  /** `_blobmap` (V06 0x25): steps from (x, y) to every square over free squares (8-way); the goal may be occupied. */
  distances(x: number, y: number, background = false): number[] {
    const d = new Array(W * H).fill(0x7e);
    d[y * W + x] = 0;
    const q = [[x, y]];
    while (q.length) {
      const [cx, cy] = q.shift()!;
      for (let k = 0; k < 8; k++) {
        const nx = cx + DX[k], ny = cy + DY[k];
        if (nx < 0 || ny < 0 || nx >= W || ny >= H || d[ny * W + nx] !== 0x7e) continue;
        d[ny * W + nx] = d[cy * W + cx] + 1;
        if (background ? this.level.walkable(nx, ny) : this.free(nx, ny)) q.push([nx, ny]);
      }
    }
    return d;
  }

  /** P94 ovl_0a98, a hero fighting on auto (Head, Will): by the side leader's race, eat a Gonshi when RndCo(100) is
   *  below D06 ptr4 and none is working yet, drink a Potion when HP ≤ ptr6, eat a Sermin when energy < ptr5 (each only
   *  if carried, one action); otherwise act like a monster. `use` applies the item (Hero.use + the record sync).
   *  (A hero with no target casts by the spell AI, ovl_157b — not modelled: it takes a random step.) */
  autoHero(r: Rec, use: (r: Rec, item: number) => string[], text: (n: number, v?: Record<string, string | number>) => string): string[] {
    const h = r.hero!.rec, lead = this.recs.find(o => o.side === r.side && this.alive(o) && o.state & 4) ?? this.recs[0];
    const d = this.data.d06, lr = lead.race;
    const has = (item: number) => h.h_invitem.includes(item);
    if (rnd(100) < d.gonshi[lr] && !((h.h_inuse as number) & 0x80) && has(0x34)) return use(r, 0x34);
    if (r.hp <= d.potion[lr] && has(0x32)) return use(r, 0x32);
    if ((h.h_energy as number) < d.sermin[lr] && has(0x33)) return use(r, 0x33);
    return this.monsterAct(r, text);
  }

  /** P94 ovl_0f32/ovl_10ef: on a flee square the record leaves ("%a flees!", comtxt 0xCA); otherwise it steps toward the
   *  nearest flee square. (The original heads for the exit opposite the enemies' centroid by a quadrant table, and a
   *  fleeing leader passes leadership on and may spread panic — not modelled.) */
  private fleeStep(r: Rec, text: (n: number, v?: Record<string, string | number>) => string): string[] {
    if (this.flee.has(r.y * W + r.x)) { this.remove(r); return [text(0xca, { a: r.name })]; }
    const d = this.distances(r.x, r.y), goal = [...this.flee].sort((a, b) => d[a] - d[b])[0];
    if (goal === undefined || d[goal] >= 0x7e) { r.moves--; return []; }
    const g = this.distances(goal % W, Math.floor(goal / W)), here = g[r.y * W + r.x];
    const steps = [...Array(8).keys()].filter(k => this.free(r.x + DX[k], r.y + DY[k]) && g[(r.y + DY[k]) * W + r.x + DX[k]] < here);
    if (steps.length) { const k = steps[rnd(steps.length)]; this.move(r, DX[k], DY[k]); } else r.moves--;
    return [];
  }

  /** P94 ovl_124a: the candidates best meeting criterion `c` (table at file 0x122A), ties broken at random. */
  private pick(r: Rec, c: number, ldrace: number): Rec | undefined {
    const foes = this.enemies(r);
    const best = (score: (e: Rec) => number, ok: (e: Rec) => boolean = () => true) => {
      const pool = foes.filter(ok);
      if (!pool.length) return undefined;
      const m = Math.min(...pool.map(score));
      const top = pool.filter(e => score(e) === m);
      return top[rnd(top.length)];
    };
    const dist = c === 1 ? this.distances(r.x, r.y) : [];
    switch (c) {
      case 0: return best(() => 0);
      case 1: return best(e => dist[e.y * W + e.x], e => dist[e.y * W + e.x] < 0x7e);
      case 2: return best(e => e.hp);
      case 3: return best(e => e.agi);
      case 4: return undefined;                                         // magic-users: no spells cast yet
      case 5: return best(() => 0, e => this.weapon(e)?.type === 3);
      case 6: return best(() => 0, e => e.race === this.data.d06.prey[ldrace]);
      case 7: return best(() => 0, e => !!(e.state & 4));
      case 8: { const l = this.recs.find(o => o.side === r.side && o.state & 4); return best(() => 0, e => !!l && e.target === l.recno); }
      case 9: return best(e => e.hp, e => e.target === r.recno);
    }
    return undefined;
  }

  /** One action of a monster (P94 ovl_0b4b → ovl_0db1): keep or choose a target by the leader race's D06 criteria,
   *  then shoot, strike when adjacent, or step toward it (a random lower-distance neighbour), else a random move.
   *  A routed record (`c_state & 0x40`) flees instead. */
  monsterAct(r: Rec, text: (n: number, v?: Record<string, string | number>) => string): string[] {
    if (r.state & 0x40) return this.fleeStep(r, text);
    const lead = this.recs.find(o => o.side === r.side && this.alive(o) && o.state & 4);
    const ldrace = lead ? lead.race : r.race;
    let t = this.recs[r.target === NONE ? -1 : this.recs.findIndex(o => o.recno === r.target)];
    if (!t || !this.alive(t) || t.side === r.side) {
      const [a, chance, b] = this.data.d06.crit.slice(3 * ldrace, 3 * ldrace + 3);
      t = this.pick(r, rnd(100) < chance ? a : b, ldrace) ?? this.pick(r, this.data.d06.crit2[3 * ldrace + 2], ldrace)!;
      r.target = t ? t.recno : NONE;
    }
    // D06 ptr0: the leader race's chance to cast instead (ovl_1553); a monster's spells cost it nothing here.
    if (r.side && rnd(100) < this.data.d06.cast[ldrace]) {
      const s = monsterSpell(this, r, this.data.monsters[r.race - 5].spells);
      if (s) { r.moves--; return [`${r.name}: ${this.data.spells.names[s.spell]}`, ...effect(this, r, s.spell, s.target, text)]; }
    }
    if (t && this.inRange(r, t)) return this.attack(r, t, text);
    if (t) {
      const d = this.distances(t.x, t.y), here = d[r.y * W + r.x];
      const steps = [...Array(8).keys()].filter(k => this.free(r.x + DX[k], r.y + DY[k]) && d[(r.y + DY[k]) * W + r.x + DX[k]] < here);
      if (here < 0x7e && steps.length) { const k = steps[rnd(steps.length)]; this.move(r, DX[k], DY[k]); return []; }
    }
    const k = rnd(8);                                                   // "Random move"
    if (!this.move(r, DX[k], DY[k])) r.moves--;
    return [];
  }
}
