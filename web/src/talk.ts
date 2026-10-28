// Conversations (docs/rules/dialogue.md): P91 greeting, keyword scripts, News, farewell.
import { json, type Location } from './pack';
import type { Figure } from './level';

interface Cmd { op: 'E' | 'C' | 'S'; arg?: number; alt?: number; song?: number }
interface Entry { word: number; resp: number; cmds: Cmd[] }
interface Slot { script: Entry[]; greet: number; bye: number; unknown: number; skill: number; nobuy: number; shop: { item: number; pays: number; charges: number }[] }
interface Conversation { texts: string[]; words: string[]; slots: Slot[] }
interface SmallTalk { lines: string[]; weather: [number, number][] }

/** What conversations need to know about the speaker's side. */
export interface Speaker { readonly name: string; readonly female: boolean; readonly charm: number }

/** _MCSTRICMP: case-insensitive; matches when the typed word begins with the whole list word. */
export function wmatch(typed: string, words: string[]): number {
  const t = typed.trim().toLowerCase();
  return words.findIndex(w => w.length > 0 && t.startsWith(w.toLowerCase()));
}

/** FAR_PRTAWRD format codes (dialogue.md, Text format codes); `vars` fills the print parameters: %a object or word, %b and %i numbers. */
export function format(s: string, hero: Speaker, other: string, vars: Record<string, string | number> = {}): string {
  return s.replace(/\r/g, '\n').replace(/%(r(\d+)|[a-zA-Z])/g, (_, c: string, para?: string) => {
    if (para) return `[Read Paragraph ${para}.]`;
    switch (c) {
      case 'h': return hero.name;
      case 'o': return other;
      case 'd': return hero.female ? 'her' : 'him';
      case 'p': return hero.female ? 'her' : 'his';
      case 'w': return hero.female ? 'She' : 'He';
      case 'y': return hero.female ? "ma'am" : 'sir';
      case 'n': return '\n';
      case 'q': return '"';
      default: return String(vars[c] ?? '');
    }
  });
}

export class Talk {
  private constructor(private loc: Location, private who: Figure, private hero: Speaker, private events: Set<number>,
                      private comtxt: string[], private small: SmallTalk, private conv: Conversation | null) {}

  static async open(loc: Location, who: Figure, hero: Speaker, events: Set<number>): Promise<Talk> {
    const [comtxt, small] = await Promise.all([json<string[]>('comtxt.json'), json<SmallTalk>('p91text.json')]);
    const named = who.num < 0xfa;
    const conv = named ? await json<Conversation>(`conversations/C${String(who.num >> 3).padStart(2, '0')}.json`) : null;
    return new Talk(loc, who, hero, events, comtxt, small, conv);
  }

  get name(): string { return this.who.name ?? ''; }
  /** Merchant data (economy.md): shop list, trade skill, no-buy flag. Empty for townsfolk. */
  get shop() { return this.slot?.shop ?? []; }
  get skill() { return this.slot?.skill ?? 0; }
  get nobuy() { return (this.slot?.nobuy ?? 0) !== 0; }
  private get slot(): Slot | null { return this.conv ? this.conv.slots[this.who.num & 7] : null; }
  private say(s: string): string { return format(s, this.hero, this.name); }

  /** ovl_045d: the slot's greet text, else "Well met, adventurer. My name is <name>." (common texts 0x17, 0x19, 0x10). */
  greeting(): string {
    const s = this.slot;
    if (s && s.greet !== 0xff) return this.say(this.conv!.texts[s.greet]);
    return this.say(this.comtxt[0x17] + (this.name ? this.comtxt[0x19] + this.name + this.comtxt[0x10] : ''));
  }

  farewell(): string | null {
    const s = this.slot;
    return s && s.bye !== 0xff ? this.say(this.conv!.texts[s.bye]) : null;
  }

  /** ovl_05e2: find the typed word's entry, apply E/C/S commands, print the response; no entry → ovl_0a08. */
  ask(typed: string): { text: string; end: boolean } {
    const words = this.conv ? this.conv.words : this.loc.words;
    const texts = this.conv ? this.conv.texts : this.loc.texts;
    const script = this.slot ? this.slot.script : this.loc.script;
    const w = wmatch(typed, words);
    const e = w < 0 ? undefined : script.find(x => x.word === w);
    if (!e) {
      const u = this.slot?.unknown ?? 0xff;
      return { text: this.say(u !== 0xff ? texts[u] : this.comtxt[0x1b]), end: false };
    }
    if (e.resp === 0xff) return { text: '', end: true };
    let resp = e.resp, extra = '';
    for (const c of e.cmds) {
      if (c.op === 'E' && !this.events.has(c.arg!)) resp = c.alt!;
      // _tailorcharm and _chrmods start at 0 (not modelled yet)
      if (c.op === 'C' && this.hero.charm < c.arg!) { resp = c.alt!; extra = '\n' + this.small.lines[15]; }   // dialogue.md
    }
    return { text: this.say(texts[resp] + extra), end: false };
  }

  /** Menu item 1: a random small-talk line for the current weather (P91 pairs at file 0x48). */
  weather(weather: number): string | null {
    const run = this.small.weather.filter(([w]) => w === weather);
    return run.length ? this.say(this.small.lines[run[Math.floor(Math.random() * run.length)][1]]) : null;
  }

  /** ovl_0b0e: a random newsr line for this speaker's type and the events that are set (townsfolk). */
  news(): string | null {
    const ok = this.loc.news.filter(n => (n.npctype === 0xfe || n.npctype === this.who.type) &&
                                         (n.event === 0xfe || this.events.has(n.event)));
    return ok.length ? this.say(this.loc.texts[ok[Math.floor(Math.random() * ok.length)].text]) : null;
  }
}
