// Scripted quest-scene rooms, program P08 (rules/quest_scenes.md). A P08 room is an ordinary room (map, people, Talk,
// Look) whose program adds scenes keyed by (`_locspec`, room id): `_rmdata[7]` is the location the door was in (P02
// 0x792 / P01 copy `_locspec`), `_rmdata[0]` the door's room id. The ending and the epilogue are in main.ts. Not
// built: the room-wide colour flashes.
import { json } from './pack';
import { FX, type Frame } from './fx';
import { format } from './talk';
import type { Figure } from './level';
import { incObj } from './shop';
import type { Party, Member } from './party';
import type { Hero } from './hero';
import type { Level } from './level';

export interface P08 {
  texts: string[]; gifts: number[][]; junk: number[]; base: number[][]; side: { odd: number[]; even: number[] };
  ghosts: { npcs: number[]; scrolls: number[]; paras: string[]; spoken: number[]; rested: number[] };
}

export interface SceneCtx {
  party: Party; events: Set<number>; items: string[]; comtxt: string[];
  /** The people in the room now. */
  figures(): Figure[];
  /** `_scrollonfloor` (saved): the scroll item lying on the floor, 0 = none. */
  scroll: { item: number };
  /** `_disasterday = _juldate`; Jemil, Shannor and Alex (NPCs 56, 60, 61) leave their homes (`_npcsta` bits set). */
  disaster(): void;
  /** `_GameSound`. */
  sound(n: number): void;
  /** The visual effects queue (fx.ts). */
  fx(frames: Frame[]): void;
}

const KING = 26, ORB = 0x49, WHITE = 0x4c, SCROLLTILE = 0x63, FLOOR = 0x26, CELL = { x: 5, y: 2 };   // `_mapyl`+28 = cell 27

let data: P08 | null = null;

/** P08 ovl_1484: the party's base square from the sides the room's exits are on (flags 2 W, 4 N, 8 E, 16 S, from the
 *  exit list), with several exits narrowed by `_lastdir` (numpad key − '1'), through P08 table 0x183. */
export async function sceneBase(exits: { x: number; y: number }[], dx: number, dy: number): Promise<{ x: number; y: number }> {
  data ??= await json<P08>('p08.json');
  let f = 0;
  for (const e of exits) f |= e.x === 0 ? 2 : e.y === 0 ? 4 : e.x === 10 ? 8 : e.y === 8 ? 16 : 0;
  if (exits.length > 1) {
    const dir = (dy > 0 ? 0 : dy < 0 ? 6 : 3) + dx + 1;               // P02 0x46B: the step key − '1'
    f = dir & 1 ? data.side.odd[dir] : f & data.side.even[dir >> 1];
  }
  const [x, y] = data.base[f >> 1];
  return { x, y };
}

export class Scene {
  /** OV_0x1c3: the ghost here (1-3), 0 = none (ovl_1541). */
  private ghost = 0;
  /** OV_0x1c7: bits 0-3 elden brothers 144-147 present, 4 event 85, 5 event 115 (ovl_1581). */
  private elden = 0;
  /** OV_0x1c8: the Orb has persuaded the Oolau bird (room-private). */
  private bird = false;
  /** OV_0x1c9: 'L' after the White Scroll is taken - leaving transports the party (ovl_0f20). */
  transport = false;

  private constructor(private ctx: SceneCtx, private d: P08, readonly locspec: number, readonly room: number,
                      private level: Level) {}

  static async open(ctx: SceneCtx, locspec: number, room: number, level: Level): Promise<Scene> {
    const s = new Scene(ctx, data ??= await json<P08>('p08.json'), locspec, room, level);
    s.setup();
    return s;
  }

  private get t() { return this.d.texts; }
  private get loc() { return this.level.loc.texts; }
  private has = (n: number) => this.ctx.events.has(n);
  private here = (npc: number) => this.ctx.figures().some(f => f.num === npc);
  private player = () => this.ctx.party.members[0];
  private say = (s: string, h: Hero, v: Record<string, string | number> = {}, other = h.name) => format(s, h, other, v).trim();
  /** _HighStat(intellect): the cleverest member, who speaks the asides. */
  private wise = () => this.ctx.party.members.reduce((a, m) => (m.hero.rec.h_intellg as number) > (a.hero.rec.h_intellg as number) ? m : a);

  /** ovl_13bb/ovl_1541/ovl_1581: the scroll on the floor, which ghost is here, which elden. */
  private setup() {
    if (this.ctx.scroll.item) this.level.set(CELL.x, CELL.y, SCROLLTILE);
    this.ghost = this.d.ghosts.npcs.findIndex(n => this.here(n)) + 1;
    this.elden = [144, 145, 146, 147].reduce((b, n, i) => this.here(n) ? b | 1 << i : b, 0);
    if (this.elden && this.has(85)) this.elden |= 0x10;
    if (this.elden & 0x10 && this.has(115)) this.elden |= 0x20;
  }

  /** The scroll lying here (OV_0x1c5). */
  private get scroll() { return this.ctx.scroll.item; }

  /** ovl_0c92, on entering: Ziyx's spell books (location 1, room 0) for the player, whose last pack slot must be free:
   *  the Book of Emenad (0x58, event 28) once event 27 is set, else once the Book of Demaro (0x55, event 103); the
   *  Altesen shrine (location 56, room 6) before the Orb is given: "%h enters an Altesen shrine." (12). */
  enter(): string {
    const p = this.player().hero;
    if (this.locspec === 1 && this.room === 0 && p.rec.h_invitem[39] === 0xff && !this.has(28)) {
      if (this.has(27)) { incObj(p, 0x58, 1); this.ctx.events.add(28); return this.say(this.loc[1], p); }
      if (!this.has(103)) { incObj(p, 0x55, 1); this.ctx.events.add(103); return this.say(this.loc[0], p); }
    }
    if (this.locspec === 56 && this.room === 6 && !this.has(94)) return this.say(this.t[12], p);
    return '';
  }

  /** ovl_1034, Talk (`_swgreet` −2): the scene's opening in place of the normal greeting, or null. `leave` = the
   *  party is sent out through the first exit (the priest). */
  greet(who: Figure, speaker: Member): { text: string; leave?: boolean } | null {
    const h = speaker.hero, p = this.player().hero;
    if (who.num === 72) {                                               // King Rebnard (NPC 72), to the player
      if (speaker !== this.player() || this.has(13)) return null;
      const out = [this.say(this.t[0], h)];
      const brennix = this.ctx.party.members.some(m => m.hero.rec.h_invitem.includes(0x11));
      for (const [item, n] of this.d.gifts) {
        if (item === 0x11 && brennix) break;                               // OV_0x1194 = 0xFF ends the list
        if (!incObj(p, item, item === 0x11 ? 1 : n)) return { text: out.join(' ') };
        out.push(item === 0x11 ? this.say(this.t[16], p) : this.say(this.t[1], p, { b: n, a: this.ctx.items[item] }));
      }
      this.ctx.events.add(13);
      return { text: out.join(' ') };
    }
    if (this.ghost) return { text: this.say(this.t[5], h) };              // "…does not respond to %h's frightened stammers."
    if (who.num === 158) {                                                // the Altesen priest: the Orb, then out
      if (this.has(94)) return null;
      const text = this.say(this.t[13], p);
      this.give(p, ORB);
      this.ctx.events.add(94);
      return { text, leave: true };
    }
    if (!this.elden) return null;
    const king = speaker.num === KING, kingHere = this.ctx.party.members.some(m => m.num === KING);
    let n: number;
    if (who.num === 147) {                                                // Zidoni
      if (this.elden & 0x20) n = 2;
      else if (!kingHere) return null;
      else n = king ? 6 : 5;
    } else {
      if ((this.elden & 7) !== 7) return null;                            // all three brothers
      if (!(this.elden & 0x10)) {
        if (!this.has(85)) {                                              // the Blue Scroll (0x4F) for the player
          this.give(p, 0x4f);
          this.ctx.events.add(85);
          return { text: `${who.name}: ${this.say(this.loc[0], h)}` };
        }
        n = 1;
      } else if (!(this.elden & 8) || !kingHere) return null;
      else if (this.elden & 0x20) n = 2;
      else n = king ? 3 : 4;
    }
    return { text: `${who.name}: ${this.say(this.loc[n], h)}` };           // _Offer1 (KNPCSays) + ovl_1862 loctext[n]
  }

  /** ovl_0e86: give `item` to `h`, first dropping junk (P08 0xF49 list; the Conch only for the Orb) when the pack is
   *  full; a weapon or armour goes as one. */
  private give(h: Hero, item: number) {
    const r = h.rec;
    if (r.h_invitem[39] !== 0xff)
      for (const j of item === ORB ? this.d.junk : this.d.junk.slice(1)) {
        const s = r.h_invitem.indexOf(j);
        if (s < 0) continue;
        r.h_invitem.splice(s, 1); r.h_invamt.splice(s, 1); r.h_invitem.push(0xff); r.h_invamt.push(0);
        break;
      }
    incObj(h, item, 1);
  }

  /** Whisper: word 1 of the room ("Hefriti") with Maalaq (57) here and event 26 clear → the crystal key (0x5A);
   *  in the Oolau bird's room (1, 5) word 0 ("Jemil") → ovl_1339. Null = nothing answers. */
  whisper(word: number, speaker: Member): string | null {
    const h = speaker.hero;
    if (this.here(57)) {
      if (word !== 1 || this.has(26)) return null;
      const out = [this.say(this.t[2], h)];
      if (incObj(h, 0x5a, 1)) { out.push(this.say(this.t[3], h)); this.ctx.events.add(26); }
      return out.join(' ');
    }
    if (this.locspec !== 1 || this.room !== 5 || word !== 0 || this.has(120)) return null;
    if (!this.bird) return this.say(this.loc[0], h);                     // "…does not penetrate the bird's feathers."
    if (speaker.num !== KING) return this.say(this.loc[1], h);           // "Prince Jemil does not recognize %h's voice."
    this.level.set(4, 3, 0x16); this.level.set(5, 3, 0x17);
    this.ctx.events.add(120); this.ctx.sound(26);                       // the egg cracks
    return this.say(this.loc[2], h);                                      // "The egg cracks open…"
  }

  /** ovl_0d8e, Use the Orb in the bird's room (1, 5): with events 34-36 (the three Marks) the bird leaves her egg
   *  (14); else the cleverest member wonders about the Marked Ones (15). Null = not handled here. */
  use(item: number, user: Member): string | null {
    if (item !== ORB || this.locspec !== 1 || this.room !== 5 || this.bird) return null;
    if (![34, 35, 36].every(this.has)) return this.say(this.t[15], user.hero, {}, this.wise().hero.name);
    this.level.set(4, 2, 0x11); this.level.set(5, 2, 0x10); this.level.set(4, 3, 0x14); this.level.set(5, 3, 0x15);
    this.bird = true; this.ctx.sound(10); this.ctx.fx(FX.spef6(user));   // then Spef6 on the user
    return this.say(this.t[14], user.hero);
  }

  /** P08 L_04fe: with a ghost here no one moves north ('7', '8', '9'): "The ghost is terrifying! %h cannot approach
   *  it!" (4) + the room's own line. */
  step(dy: number, h: Hero): string | null {
    return this.ghost && dy < 0 ? this.say(this.t[4] + this.loc[0], h) : null;
  }

  /** Soulspeak (41, P08 slot 1 `ovl_15d5`) and Restsoul (40, slot 0x45 `0x162b`): no ghost → null (comtxt 0x24,
   *  nothing spent). Soulspeak: "The ghost reacts to %h's spell!" with its paragraph, and its event (6/23/25).
   *  Restsoul needs that event (else text 7, spent): the room's line 1 with the scroll, the ghost's leaving event
   *  (20/21/22) and the scroll on the floor where it stood. */
  spell(sp: number, h: Hero): string | null {
    const n = this.ghost, g = this.d.ghosts;
    if (!n) return null;
    if (sp === 41) {
      this.ctx.events.add(g.spoken[n - 1]);
      return this.say(this.t[6].replace('%r00', `%r${g.paras[n - 1].trim()}`), h);
    }
    if (!this.has(g.spoken[n - 1])) return this.say(this.t[7], h);
    const item = g.scrolls[n - 1];
    this.ctx.events.add(g.rested[n - 1]);
    this.ctx.scroll.item = item;
    this.level.set(CELL.x, CELL.y, SCROLLTILE);
    this.ghost = 0;
    return this.say(this.loc[1], h, { a: this.ctx.items[item] });
  }

  /** Is (x, y) the scroll on the floor (Look, ovl_16e9)? */
  scrollAt(x: number, y: number) { return !!this.scroll && x === CELL.x && y === CELL.y; }

  /** ovl_16e9: "%h sees a %a." (8) + " It is too far away to read." (9) beyond one square, else " Will %h pick it
   *  up?" (10); `near` decides which. */
  lookScroll(h: Hero, near: boolean): string {
    return this.say(this.t[8] + this.t[near ? 10 : 9], h, { a: this.ctx.items[this.scroll] });
  }

  /** Picking it up: _IncObj to the looker (refused → null), the floor back (tile 0x26), the room's line 2 and the
   *  cleverest member's "We had better ask Ziyx" (17). The White Scroll (0x4C) also sets event 7, starts the
   *  disaster countdown and makes leaving transport the party. */
  pickScroll(h: Hero): string | null {
    const item = this.scroll;
    if (!incObj(h, item, 1)) return null;
    this.level.set(CELL.x, CELL.y, FLOOR);
    this.ctx.scroll.item = 0;
    if (item === WHITE) { this.transport = true; this.ctx.events.add(7); this.ctx.disaster(); }
    return [this.say(this.loc[2], h), this.say(this.t[17], h, {}, this.wise().hero.name)].join(' ');
  }

  /** L_06fa: a scroll still on the floor once the ghost is gone holds everyone back: "%o refuses to leave the %a
   *  here." (11; %o assumed the cleverest member). */
  refuseLeave(): string | null {
    if (!this.scroll || this.ghost) return null;
    const w = this.wise().hero;
    return this.say(this.t[11], w, { a: this.ctx.items[this.scroll] }, w.name);
  }
}
