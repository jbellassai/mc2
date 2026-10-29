// Special rooms run by P09 (rules/special_rooms.md): casinos, temples, gates and the elven prince. The room kind is P09's `_rmtyp`
// (7 casino, 10 teleportal, 11 meeting hall, 12 world temple, 13 dungeon temple, 14 gate) and `index` its OV_0x181
// (`id − base`; for a temple, the god).
import { format, wmatch } from './talk';
import { panel } from './panel';
import { json, hex } from './pack';
import { FX, type Frame } from './fx';
import type { Hero } from './hero';
import type { Clock } from './clock';
import type { Level } from './level';
import type { Exit } from './pack';
import type { Party, Member } from './party';

export const CASINO = 7, TELEPORTAL = 10, HALL = 11, TEMPLE = 12, SHRINE = 13, GATE = 14;

export interface SpecialCtx {
  hero: Hero; clock: Clock; cmd: string[]; comtxt: string[]; party: Party; events: Set<number>;
  /** `_w_tod` (EXE DS:0x41E0) and TODWORDS (DS:0x38F2, by hour) for `_SetTxtToD`. */
  tod: { words: string[]; hour: number[] };
  /** `_w_attrib` + `_w_skills` by HERO offset − 13, and `_w_kins` (races 0-4). */
  attribs: string[]; kins: string[];
  /** A member leaves into a god's service (ovl_1290: assignment task 100, the Mindstone left behind, P97 `_swass` 2). */
  serve(m: Member): void;
  close(msg?: string): void;
  /** `_GameSound`. */
  sound(n: number): void;
  /** Draw the map again after the room's tiles change. */
  redraw(): void;
  /** The visual effects queue (fx.ts). */
  fx(frames: Frame[]): void;
}

interface P09 { pieces: number[]; piecetiles: number[]; altars: number[]; icons: number[]; wake: number[]; offer: string[]; texts: string[] }
let p09: P09;
/** HERO fields from offset 13 (structs.h), the order of `attribs`. */
const FIELDS = ['h_bravery', 'h_strngth', 'h_dextrty', 'h_endur', 'h_agility', 'h_loyalty', 'h_charm', 'h_intellg', 'h_resist',
  'h_helped', 'h_sword', 'h_axe', 'h_archry', 'h_magic', 'h_fist', 'h_swim', 'h_trade', 'h_stealth', 'h_research', 'h_soulrd',
  'h_lockpck', 'h_track', 'h_music', 'h_carpent', 'h_smith', 'h_gemcut', 'h_tailor', 'h_hunt', 'h_ldrshp'];

/** `_casino`: the eight house banks, 1000 in a new game; +200 a month up to 1000 (P92 ovl_02ac). */
export const casino = new Array(8).fill(1000);
export function refill() { casino.forEach((b, i) => casino[i] = Math.min(1000, b + 200)); }
/** `_dnggates`: the gates opened by their password, bit = gate index. */
export const gates = new Set<number>();

const rnd = (n: number) => Math.floor(Math.random() * n);

export class Special {
  /** OV_0x155-0x157: the pieces set on the three pedestals at (4,3)-(6,3), this visit only. */
  private pedestals = [0, 0, 0];
  private constructor(private ctx: SpecialCtx, readonly kind: number, readonly index: number, private level: Level) {
    if (kind === GATE && gates.has(index)) this.openGate();       // ovl_15ee: an opened gate stays open
  }

  static async open(ctx: SpecialCtx, kind: number, index: number, level: Level): Promise<Special> {
    p09 ??= await json<P09>('p09.json');
    return new Special(ctx, kind, index, level);
  }

  private get texts() { return this.level.loc.texts; }
  private say(s: string, v: Record<string, string | number> = {}) { return format(s, this.ctx.hero, this.ctx.hero.name, v); }
  private yesNo(yes: () => void, no: () => void) {
    panel.set([{ label: this.ctx.cmd[3], act: yes }, { label: this.ctx.cmd[4], act: no }]);
  }

  /** Talk to one of the room's `resids` (`_swgreet` 2 → −2, meeting halls only: FFFAR ovl_31bc), P09 ovl_0611: the
   *  elven prince (NPC 113, Llendora's hall). Event 4 set → the normal conversation (null); event 8 clear → P09 text 4
   *  ("Begone…"); else text 5 ("The elf greets %h.") and event 4, the conversation from the next Talk on. */
  greet(num: number, h: Hero): string | null {
    const ev = this.ctx.events;
    if (this.kind !== HALL || num !== 113 || ev.has(4)) return null;
    if (!ev.has(8)) return format(p09.texts[4], h, h.name);
    ev.add(4);
    return format(p09.texts[5], h, h.name);
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
    if (this.kind === SHRINE && n === this.index) return this.awaken();
    if (this.kind !== GATE || n !== this.index || gates.has(n)) return false;
    gates.add(n);
    this.ctx.sound(0x16);                                                    // P09 0x153F: the creak
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
        this.ctx.sound(18);                                         // P09 0x7F1 / 0x82F: the dice
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

  /** Look (P09 @0x0480): text appended to the normal look line. World temple altar tiles (P09 0x3A): "There is a tiny
   *  word engraved on it." and, from an adjacent square (`_ChkRng` 1), "The word on it is: <gwrds[god]>"; from afar
   *  `_Advice` (intelligence): the party's most intelligent member may suggest moving closer (ovl_1413). Any temple's
   *  god icons (name indexes P09 0x3D) name this temple's god and domain (ovl_14a0, texts 24 and 25 + god). */
  look(x: number, y: number, from: Member): string {
    if (this.kind !== TEMPLE && this.kind !== SHRINE) return '';
    const T = this.texts, g = this.index, h = from.hero, tile = this.level.tile(x, y);
    if (this.kind === TEMPLE && p09.altars.includes(tile)) {
      if (Math.max(Math.abs(from.x - x), Math.abs(from.y - y)) <= 1) return this.say(p09.texts[0] + p09.texts[1]) + this.level.loc.words[g];
      return this.say(p09.texts[0]) + this.advice(p09.texts[3], p09.texts[2], 'h_intellg', h);
    }
    if (!p09.icons.includes(this.level.data.nameindex[tile])) return '';
    return format(T[24] + T[25 + g], h, h.name, { f: T[g], l: T[9 + this.record[0]] });   // " %w recognizes the symbol of %f, %lof …"
  }

  /** `_Advice(self, other, stat)`: RndCo(12) (an attribute) against the party's best; that member speaks, `self` when
   *  it is the acting member. */
  private advice(self: string, other: string, stat: string, actor: Hero): string {
    const best = this.ctx.party.members.reduce((a, m) => (m.hero.rec[stat] as number) > (a.hero.rec[stat] as number) ? m : a);
    if ((best.hero.rec[stat] as number) < rnd(12)) return '';
    return best.hero === actor ? format(self, actor, actor.name) : format(other, actor, best.hero.name);
  }

  /** D59 `resids`, 5 bytes per god (ovl_1777): 0 god / 1 goddess, then the statue's awakening tiles and square. */
  private get record(): Uint8Array { return hex(this.level.loc.tables.resids).slice(5 * this.index, 5 * this.index + 5); }

  /** Whispering a dungeon temple's own god name (P09 @0x0C9F). The god wakes only if a member still lacks its
   *  blessing (`h_godseen` bit g; Balene, Fronnoxx and Ghartel only look at slot 0, P09 0xC86); otherwise the word
   *  does nothing. "The god/goddess <name> awakens!", then the god's demand (handler table P09 0xFCB). */
  private awaken(): boolean {
    const g = this.index, bit = 1 << g, T = this.texts, ms = this.ctx.party.members;
    if (!ms.slice(0, p09.wake[g]).some(m => !((m.hero.rec.h_godseen as number) & bit))) return false;
    const h = this.ctx.hero, line = (s: string, v: Record<string, string | number> = {}, o = h.name) => panel.line(format(s, h, o, v));
    const [, top, low, sx, sy] = this.record, was = [this.level.tile(sx, sy), this.level.tile(sx, sy + 1)];
    const slumber = (s = '') => {                                            // "<god> returns to slumber."
      line(s + T[g] + T[12]);
      panel.set([{ label: this.ctx.cmd[0], act: () => {                     // P09 0xF43: the statue as it was (the port
        this.level.set(sx, sy, was[0]); this.level.set(sx, sy + 1, was[1]);  // waits for End, the original's text pages)
        this.ctx.close();
      } }]);
    };
    const thunder = () => {                                                  // ovl_123e: every member HP 1, energy 1
      for (const m of ms) { m.hero.rec.h_hitpts = 1; m.hero.rec.h_energy = 1; m.hero.isHeTr(); this.ctx.fx(FX.bang(m)); }   // a Bang on each
      slumber(T[18]);                                                        // "'Begone, mortals!' With a great clap of thunder, "
    };
    panel.show();
    this.ctx.sound(0x16);                                                    // P09 0xCDB
    this.flash();
    this.level.set(sx, sy, top); this.level.set(sx, sy + 1, low);            // P09 0xD6A: the statue awake, until slumber
    this.ctx.redraw();
    line(T[9 + this.record[0]] + T[g] + T[8]);
    const d = this.demand(g);
    if (d === null && g < 4) { line(T[13], { a: this.ctx.kins[[3, 2, 0, 4][g]] }); return slumber(), true; }   // "I see no %a in your assemblage."
    if (d === null) { line(T[16] + T[10 + g]); return thunder(), true; }   // "You dare to waken me without offering …"
    const bless = () => {
      line(T[11]);                                                           // "I am well pleased, and bestow upon you my blessing!"
      this.bless(g);
      if (g >= 4 && g !== 6) line(T[23], {}, d.name);                        // "…%o is now in my service! Begone!"
      for (const { hero } of this.ctx.party.members) hero.rec.h_godseen = (hero.rec.h_godseen as number) | bit;
      slumber();
    };
    if (!d.take) return bless(), true;
    line(T[19] + T[10 + g] + (g === 7 ? T[20] : '') + T[21], {}, d.name);   // "Welcome, mortals. I demand the sacrifice of …"
    this.yesNo(() => { d.take!(); bless(); }, thunder);
    return true;
  }

  /** P09 0xCE5/0xD51, `_ChangeMap`: the first three window tiles starting with 52 become 48, 49, 55 while "awakens!"
   *  prints, then change back (the port holds them for a second, an assumption). */
  private flash() {
    const L = this.level, [w, h] = L.loc.mapsize, from = [52, 53, 54], to = [48, 49, 55];
    for (let i = 0; i < w * h; i++) {
      const x = i % w, y = Math.floor(i / w);
      if (L.tile(x, y) !== from[0]) continue;
      to.forEach((t, k) => L.set(x + k, y, t));
      setTimeout(() => { from.forEach((t, k) => L.set(x + k, y, t)); this.ctx.redraw(); }, 1000);
      return;
    }
  }

  /** The god's demand: null = not met; `take` = the offering, taken on Yes; `name` = %o of text 23. */
  private demand(g: number): { name: string; take?: () => void } | null {
    const ms = this.ctx.party.members, race = (r: number) => ms.some(m => m.hero.rec.h_race === r);
    switch (g) {
      case 0: if (ms.some(m => ((m.hero.rec.h_godseen as number) & 0x0e) === 0x0e)) return { name: '' };   // blessed by 1-3
        return race(3) ? { name: '' } : null;                                // a Halfling
      case 1: return race(2) ? { name: '' } : null;                          // an Elf
      case 3: return race(4) ? { name: '' } : null;                          // a Dwarf
      case 4: {                                                              // Brennix (0x11) in anyone's pack
        const m = ms.find(m => m.hero.slot(0x11) >= 0);
        return m ? { name: p09.offer[0], take: () => m.hero.dec(m.hero.slot(0x11)) } : null;
      }
      case 5: {                                                              // Somona (companion 31) in the party
        const m = ms.find(m => m.num === 31);
        return m ? { name: p09.offer[1], take: () => this.ctx.serve(m) } : null;
      }
      case 7: {                                                              // _HighStat(strength) of the volunteers, ≥ 8
        const vs = ms.filter(m => m.hero.rec.h_relatn === 1);
        const m = vs.reduce<Member | null>((a, v) => !a || v.hero.rec.h_strngth > a.hero.rec.h_strngth ? v : a, null);
        return m && m.hero.rec.h_strngth >= 8 ? { name: m.hero.name, take: () => this.ctx.serve(m) } : null;
      }
    }
    return { name: '' };                                                     // Marior, Senvara: no demand
  }

  /** P09 0x1108: every member without the god's bit gets D59 `hroomptr` list 8 + g, pairs {HERO offset, amount}
   *  (amount | 0x80 = only if the stat is non-zero); endurance also adds 8 × amount to `h_hpmax`. `_IncSta` refuses a
   *  total of 100 or more. "%o's %a increases (+%b) to %i." for each gain; a member whose first stat rises gets
   *  `_Spef1` on their square (P09 0xDB88). */
  private bless(g: number) {
    const lists: number[][] = [[]];
    for (const b of hex(this.level.loc.tables.hroomptr)) if (b === 0xff) lists.push([]); else lists[lists.length - 1].push(b);
    const pairs = lists[8 + g] ?? [];
    for (const m of this.ctx.party.members) {
      const hero = m.hero, r = hero.rec as Record<string, number>;
      if (r.h_godseen & (1 << g)) continue;
      for (let k = 0; k + 1 < pairs.length; k += 2) {
        const f = FIELDS[pairs[k] - 13], n = pairs[k + 1] & 0x7f, old = r[f];
        if (pairs[k + 1] & 0x80 && !old) continue;
        if (pairs[k] === 0x10 && r.h_hpmax + 8 * n < 100) r.h_hpmax += 8 * n;
        if (old + n >= 100) continue;
        r[f] = old + n;
        if (k === 0) this.ctx.fx(FX.spef1(m));
        panel.line(format(this.texts[22], hero, hero.name, { a: this.ctx.attribs[pairs[k] - 13], b: n, i: old + n }));
      }
    }
  }

  /** Is `item` a teleportal piece that can be set here (Cylinder, Cone, Cube, Sphere, Pyramid; P09 file 0x4B)? */
  piece(item: number): boolean { return this.kind === TELEPORTAL && p09.pieces.includes(item); }

  /** A piece used on the marked square (P09 @0x0390): off the pedestals → "Nothing happens." (`_comtxtptr`, assumed
   *  0x83); else the piece is used up, drawn (P09 file 0x50) and, once all three are set, the triple is looked up in
   *  D61 `hroomptr` (13-byte rows {p0, p1, p2, curlev, curseg, locspec, currm, curmpg, curtils, curvar, ?, x, y}).
   *  A hit returns the world-map window; a miss prints the same text and clears the pedestals (pieces lost). */
  place(item: number, x: number, y: number, from: Hero): { x: number; y: number } | null {
    if (y !== 3 || x < 4 || x > 6) return this.ctx.close(this.ctx.comtxt[0x83]), null;
    this.pedestals[x - 4] = item;
    from.dec(from.slot(item));
    this.ctx.sound(19);                                             // P09 0xAA8: the piece slots in
    this.level.set(x, 3, p09.piecetiles[p09.pieces.indexOf(item)]);
    if (this.pedestals.includes(0)) return null;
    const t = hex(this.level.loc.tables.hroomptr);
    for (let k = 0; k + 13 <= t.length && t[k] !== 0xff; k += 13)
      if (t[k] === this.pedestals[0] && t[k + 1] === this.pedestals[1] && t[k + 2] === this.pedestals[2]) {
        this.ctx.sound(20);                                         // P09 0xC6E: the party is swept away
        return { x: t[k + 11], y: t[k + 12] };
      }
    for (let i = 0; i < 3; i++) this.level.set(4 + i, 3, 0x70);
    this.pedestals = [0, 0, 0];
    return this.ctx.close(this.ctx.comtxt[0x83]), null;
  }

  private done() { panel.set([{ label: this.ctx.cmd[0], act: () => this.ctx.close() }]); }
}
