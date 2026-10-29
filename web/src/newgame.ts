// A new game (P81, rules/new_game.md): continue a saved game, or pick a Hero Profile A-E, optionally give the hero a
// true name and a nickname, then the intro scenes (P81 string 40: FF-separated lists of string numbers).
// Port additions: the title's saved-game list, and each profile's figures on its button (the original refers the player
// to the printed Gamebook).
import { song } from './sound';
import { json } from './pack';
import { panel } from './panel';
import { format } from './talk';
import { Hero, type HeroRecord } from './hero';

interface P81 { texts: string[]; scenes: number[][] }
export type Start = { slot: number } | { hero: Hero };

/** The P81 flow; `saves` = the occupied slots with a label, `cmd` = command words (Yes/No/End…). */
export async function newGame(saves: { slot: number; label: string }[], cmd: string[]): Promise<Start> {
  const [p81, heroes, items] = await Promise.all([json<P81>('p81.json'), json<HeroRecord[]>('heroes.json'), json<string[]>('items.json')]);
  const t = (n: number, h: Hero) => format(p81.texts[n], h, h.name);
  void song(1);                                                         // P81 ovl_1343: the title's fanfare
  panel.show();
  return new Promise<Start>(done => {
    const title = () => {
      panel.set([...saves.map(s => ({ label: `Continue: ${s.label}`, act: () => done({ slot: s.slot }) })),
        { label: 'New game', act: profiles }]);
    };
    const yesNo = (yes: () => void, no: () => void) => panel.set([{ label: cmd[3], act: yes }, { label: cmd[4], act: no }]);
    /** "Refer to your Gamebook to select the Hero Profile you want to use (A-E)." (string 14). */
    const profiles = () => {
      panel.show();
      panel.line(p81.texts[14]);
      panel.set(heroes.map((r, i) => {
        const gold = (r.h_gold & 0xff) * 100 + (r.h_gold >> 8);
        return { label: `${'ABCDE'[i]}: ${r.h_fullnm} — Str ${r.h_strngth} Dex ${r.h_dextrty} Agi ${r.h_agility}, ` +
          `Sword ${r.h_sword} Archery ${r.h_archry} Magic ${r.h_magic}, ${gold} coins`, act: () => pick(i) };
      }));
    };
    const pick = (i: number) => {
      const rec = structuredClone(heroes[i]);
      rec.h_gold = (rec.h_gold & 0xff) * 100 + (rec.h_gold >> 8);       // {hundreds, units}
      const h = new Hero(rec, items);
      panel.line(t(13, h));                                              // "Legends tell of a hero named %h."
      ask(h);
    };
    /** "Do you want to disclose %p true name?" (15): full name (16, up to 12 letters), nickname (17, up to 5), "Are
     *  these names correct?" (29). A typed name keeps its first letter and the rest is lower-cased (P81 @0x220C). */
    const ask = (h: Hero) => {
      panel.line(t(15, h));
      yesNo(() => names(h), () => intro(h, 0));
    };
    const fix = (s: string, n: number) => (s.slice(0, 1) + s.slice(1).toLowerCase()).slice(0, n);
    const names = (h: Hero) => {
      panel.line(p81.texts[16]);
      panel.set([], full => {
        panel.line(`> ${full}`, 'you');
        panel.line(p81.texts[17]);
        panel.set([], nick => {
          panel.line(`> ${nick}`, 'you');
          h.rec.h_fullnm = fix(full, 12); h.rec.h_name = fix(nick, 5);
          panel.line(`${h.rec.h_fullnm} / ${h.rec.h_name}`);
          panel.line(p81.texts[29]);
          yesNo(() => intro(h, 0), () => names(h));
        }, 'Nickname (5 letters)');
      }, 'Full name (12 letters)');
    };
    /** The intro: each scene's lines, then "%h has landed in Telermain." (19). Scene 3 is empty for a new hero (assumed
     *  to hold the imported hero's line, 27). */
    const intro = (h: Hero, k: number) => {
      if (k === 0) void song(2);                                        // P81 0x1A42: the intro's theme
      if (k >= p81.scenes.length) return done({ hero: h });
      if (!p81.scenes[k].length) return intro(h, k + 1);
      panel.show();
      for (const n of p81.scenes[k]) panel.line(t(n, h));
      panel.set([{ label: cmd[11], act: () => intro(h, k + 1) }]);      // Cont
    };
    if (saves.length) title(); else profiles();
  });
}

/** "%h has landed in Telermain." */
export async function landed(h: Hero): Promise<string> { return format((await json<P81>('p81.json')).texts[19], h, h.name); }
