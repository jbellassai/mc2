// A new game (P81, rules/new_game.md): continue a saved game, or pick a Hero Profile A-E, optionally give the hero a
// true name and a nickname, then the intro scenes (P81 string 40: FF-separated lists of string numbers).
// Port additions: the title's saved-game list, and each profile's figures on its button (the original refers the player
// to the printed Gamebook).
import { song, prepare, audible } from './sound';
import { json } from './pack';
import { panel } from './panel';
import { format } from './talk';
import { Hero, type HeroRecord } from './hero';

interface P81 { texts: string[]; scenes: number[][] }
export type Start = { slot: number } | { hero: Hero };

/** `_SetTxtWnd` windows in screen pixels (EXE DS:9A6/9BA/9CE/9E2, x and width in units of 4): the title's box
 *  (P81 0x12BF), window 8 (the scroll on pictures E and I) and window 9 (on M). */
type Win = [number, number, number, number];
const TITLEBOX: Win = [4, 114, 72, 40], SCROLL: Record<string, Win> = { E: [16, 16, 144, 40], I: [16, 16, 144, 40], M: [152, 12, 144, 40] };
const gesture = () => new Promise<void>(ok => { addEventListener('keydown', () => ok(), { once: true }); addEventListener('pointerdown', () => ok(), { once: true }); });
const sleep = (ms: number) => new Promise(ok => setTimeout(ok, ms));

/** The P81 flow; `saves` = the occupied slots with a label, `cmd` = command words (Yes/No/End…), `view` draws the
 *  full screens. P81 shows screen 5 (the Mindcraft logo) while song 1 plays to its end (ovl_1343: at least 1.5 s),
 *  then screen 1 (the title) with "IBM/Tandy Version 2.00" (text 0) in its box. The port first renders the two songs
 *  ("Loading...": the fanfare now, the intro's theme while the hero is chosen) and, since browsers start audio only after a key or click, asks for one, so that the logo and its
 *  fanfare start together; a key or click skips the logo. */
export async function newGame(saves: { slot: number; label: string }[], cmd: string[],
                              view: { screen(name: string, texts?: { win: Win; text: string }[], fade?: boolean): Promise<void>; notice(lines: string[]): Promise<void> }): Promise<Start> {
  await view.notice(['Loading...']);
  const [p81, heroes, items] = await Promise.all([json<P81>('p81.json'), json<HeroRecord[]>('heroes.json'), json<string[]>('items.json'),
    prepare(1)]);
  void prepare(2);                                                      // renders while the hero is chosen
  const t = (n: number, h: Hero) => format(p81.texts[n], h, h.name);
  if (!audible()) { await view.notice(['Press any key to begin']); await gesture(); }
  await view.screen('5');
  await Promise.race([Promise.all([song(1), sleep(1500)]), gesture()]);
  await view.screen('1', [{ win: TITLEBOX, text: p81.texts[0] }]);
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
    /** The intro (P81 0x1A42-0x1AB6): song 2, then a picture per scene (E, I, M, M) whose lines are printed one by one
     *  into its scroll (window 8 or 9), each waiting for a key (ovl_1b03: `_IModTxt` + "%k"); then "%h has landed in
     *  Telermain." (19). Scene 3 is empty for a new hero (assumed to hold the imported hero's line, 27). The other
     *  songs render in the background meanwhile. */
    const intro = async (h: Hero, k: number, j = 0) => {
      if (k === 0 && j === 0) {
        await prepare(2);
        void song(2);
        void (async () => { for (let n = 3; n <= 14; n++) await prepare(n); })();
      }
      if (k >= p81.scenes.length) return done({ hero: h });
      if (!p81.scenes[k].length) return intro(h, k + 1);
      const pic = 'EIMM'[k] ?? 'M', last = j + 1 >= p81.scenes[k].length;
      void view.screen(pic, [{ win: SCROLL[pic], text: t(p81.scenes[k][j], h) }], j === 0);
      panel.show();
      panel.set([{ label: cmd[11], act: () => void (last ? intro(h, k + 1) : intro(h, k, j + 1)) }]);   // Cont
    };
    if (saves.length) title(); else profiles();
  });
}

/** "%h has landed in Telermain." */
export async function landed(h: Hero): Promise<string> { return format((await json<P81>('p81.json')).texts[19], h, h.name); }
