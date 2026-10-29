// Tile view centred on the party leader. Original window is 11×9 with the party's 3×3 formation at (4,3)-(6,5); the port shows more.
import { image, json, type Sprites } from './pack';
import type { Level, Figure } from './level';
import { ORDER, type Overlay, type Ghost } from './fx';

/** The 16 EGA colours, for the effects' colour flashes. */
const EGA = ['#000', '#00a', '#0a0', '#0aa', '#a00', '#a0a', '#a50', '#aaa', '#555', '#55f', '#5f5', '#5ff', '#f55', '#f5f', '#ff5', '#fff'];

export const COLS = 21, ROWS = 15, TILE = 16;
export interface Icon { x: number; y: number; frame: number; sheet?: 'E01' }

export class View {
  private ctx: CanvasRenderingContext2D;
  private constructor(readonly canvas: HTMLCanvasElement, private heroes: HTMLImageElement, private folk: HTMLImageElement,
                      private more: HTMLImageElement, private monsters: HTMLImageElement, private sprites: Sprites) {
    canvas.width = COLS * TILE; canvas.height = ROWS * TILE;
    canvas.style.width = `${COLS * TILE * 3}px`;
    canvas.style.aspectRatio = `${COLS} / ${ROWS}`;   // keeps square tiles when max-height shrinks it
    this.ctx = canvas.getContext('2d')!;
    this.ctx.imageSmoothingEnabled = false;
  }

  static async create(canvas: HTMLCanvasElement): Promise<View> {
    const [e00, e02, e03, e01] = await Promise.all(['E00', 'E02', 'E03', 'E01'].map(n => image(`sprites/${n}.png`)));
    return new View(canvas, e00, e02, e03, e01, await json<Sprites>('sprites.json'));
  }

  private sheet(im: HTMLImageElement, k: number, cols: number, cx: number, cy: number) {
    this.ctx.drawImage(im, (k % cols) * 16, Math.floor(k / cols) * 16, 16, 16, cx * TILE, cy * TILE, TILE, TILE);
    this.drawn.set(`${cx},${cy}`, [im, k, cols]);
  }
  private drawn = new Map<string, [HTMLImageElement, number, number]>();   // the sprite last drawn in each cell, for tints
  private tintBuf = document.createElement('canvas');

  /** A person's sprite, as `draw` picks it. */
  private spriteOf(num: number, tile: number): [HTMLImageElement, number] {
    if (num < 0x18) return [this.heroes, 0x3b + 18 * num];
    if (num < 0x20) return [this.more, 18 * (num - 0x18)];
    return [this.folk, this.sprites.npc[tile].start];
  }
  /** `_MultiFX` part way: the pixels of the person's sprite that the pass has reached (fx.ts, Ghost). */
  private ghost(g: Ghost, cx: number, cy: number) {
    const [im, k] = this.spriteOf(g.num, g.tile), cols = this.sprites.columns, b = this.tintBuf, c = b.getContext('2d', { willReadFrequently: true })!;
    b.width = b.height = 16;
    c.drawImage(im, (k % cols) * 16, Math.floor(k / cols) * 16, 16, 16, 0, 0, 16, 16);
    const img = c.getImageData(0, 0, 16, 16), d = img.data;
    ORDER.forEach((p, i) => {
      if (!d[p * 4 + 3]) return;
      const on = g.out ? i >= g.shown : i < g.shown, rb = on ? g.rainbow : g.under;
      if (!on && !g.under) { d[p * 4 + 3] = 0; return; }
      if (rb) {
        const v = parseInt(EGA[(i + g.shown) & 15].slice(1), 16);
        d[p * 4] = (v >> 8 & 15) * 17; d[p * 4 + 1] = (v >> 4 & 15) * 17; d[p * 4 + 2] = (v & 15) * 17;
      }
    });
    c.putImageData(img, 0, 0);
    this.ctx.drawImage(b, cx * TILE, cy * TILE, TILE, TILE);
  }

  /** _movectileFX's XOR recolouring: the figure in the cell, its own pixels blended with `color` (difference). */
  private tint(cx: number, cy: number, color: string) {
    const s = this.drawn.get(`${cx},${cy}`);
    if (!s) return;
    const [im, k, cols] = s, b = this.tintBuf, c = b.getContext('2d')!;
    b.width = b.height = 16;
    c.drawImage(im, (k % cols) * 16, Math.floor(k / cols) * 16, 16, 16, 0, 0, 16, 16);
    c.globalCompositeOperation = 'difference'; c.fillStyle = color; c.fillRect(0, 0, 16, 16);
    c.globalCompositeOperation = 'destination-in';
    c.drawImage(im, (k % cols) * 16, Math.floor(k / cols) * 16, 16, 16, 0, 0, 16, 16);
    this.ctx.drawImage(b, cx * TILE, cy * TILE, TILE, TILE);
  }

  /** _MCCPTile: hero or companion n stands on E00 frame 0x3B + 18n; companions from 0x18 on use E03 frame 18(n − 0x18).
   *  Maps load only frame 0 and frames 10-17 of the 18 (_TileApplies, DS:0x4CA); there is no walking animation. */
  private hero(n: number, cx: number, cy: number) {
    const cols = this.sprites.columns;
    if (n < 0x18) this.sheet(this.heroes, 0x3b + 18 * n, cols, cx, cy); else this.sheet(this.more, 18 * (n - 0x18), cols, cx, cy);
  }

  /** A full screen (P81's VGA screens, `screens/x.png`, 320×200) fitted to the view's width with black above and
   *  below, faded in from black over 0.4 s as the original fades its palette in (`fade` false: drawn at once, as when
   *  the original prints into a window on a screen already shown). `texts` are printed into text windows
   *  (`_SetTxtWnd` rectangles in screen pixels) in the game font, black on the scrolls' grey. */
  async screen(name: string, texts: { win: [number, number, number, number]; text: string }[] = [], fade = true) {
    const im = await image(`screens/${name}.png`), page = document.createElement('canvas');
    page.width = 320; page.height = 200;
    const pc = page.getContext('2d')!;
    pc.drawImage(im, 0, 0);
    for (const t of texts) await this.print(pc, t.text, t.win, '#000');
    await this.present(page, fade ? 400 : 0);
  }

  /** A message in the game font, centred on black (loading, "press a key"). */
  async notice(lines: string[]) {
    const page = document.createElement('canvas');
    page.width = 320; page.height = 200;
    const pc = page.getContext('2d')!;
    pc.fillStyle = '#000'; pc.fillRect(0, 0, 320, 200);
    for (const [k, l] of lines.entries())
      await this.print(pc, l, [160 - l.length * 4, 96 - lines.length * 6 + k * 12, l.length * 8, 8], '#aaa');
    await this.present(page, 0);
  }

  /** `_PrtScrap`-like: words wrapped to the window's width in 8-pixel characters, lines 8 pixels apart, cut at its
   *  height. */
  private async print(pc: CanvasRenderingContext2D, text: string, [x, y, w, h]: [number, number, number, number], ink: string) {
    const font = await this.font(ink), cols = Math.floor(w / 8), lines: string[] = [];
    let line = '';
    for (const word of text.split(/\s+/).filter(Boolean)) {
      if (line && line.length + 1 + word.length > cols) { lines.push(line); line = ''; }
      line = line ? `${line} ${word}` : word;
    }
    if (line) lines.push(line);
    lines.slice(0, Math.floor(h / 8)).forEach((l, r) => [...l].forEach((c, i) => {
      const g = c.charCodeAt(0) & 127;
      pc.drawImage(font, (g % 16) * 8, (g >> 4) * 8, 8, 8, x + i * 8, y + r * 8, 8, 8);
    }));
  }

  private fonts = new Map<string, Promise<HTMLCanvasElement>>();
  /** The font atlas (pack `font.png`, ink as alpha) in one colour. */
  private font(ink: string): Promise<HTMLCanvasElement> {
    if (!this.fonts.has(ink)) this.fonts.set(ink, image('font.png').then(im => {
      const c = document.createElement('canvas'), x = c.getContext('2d')!;
      c.width = im.width; c.height = im.height;
      x.drawImage(im, 0, 0); x.globalCompositeOperation = 'source-in'; x.fillStyle = ink; x.fillRect(0, 0, c.width, c.height);
      return c;
    }));
    return this.fonts.get(ink)!;
  }

  /** Draws a 320×200 page on the view, fading it in over `ms`. */
  private present(page: CanvasImageSource, ms: number): Promise<void> {
    const ctx = this.ctx, w = this.canvas.width, h = Math.round(w * 200 / 320), y = (this.canvas.height - h) >> 1, t0 = performance.now();
    ctx.imageSmoothingEnabled = false;
    return new Promise<void>(done => {
      const frame = (now: number) => {
        const a = ms ? Math.min(1, (now - t0) / ms) : 1;
        ctx.globalAlpha = 1; ctx.fillStyle = '#000'; ctx.fillRect(0, 0, w, this.canvas.height);
        ctx.globalAlpha = a; ctx.drawImage(page, 0, y, w, h); ctx.globalAlpha = 1;
        if (a < 1) requestAnimationFrame(frame); else done();
      };
      requestAnimationFrame(frame);
    });
  }

  /** The map square under a mouse event, for a view centred on (cx, cy). */
  cellAt(e: MouseEvent, cx: number, cy: number): { x: number; y: number } {
    const r = this.canvas.getBoundingClientRect();
    const col = Math.floor((e.clientX - r.left) / r.width * COLS), row = Math.floor((e.clientY - r.top) / r.height * ROWS);
    return { x: cx - (COLS >> 1) + col, y: cy - (ROWS >> 1) + row };
  }

  /** `phase` counts animation steps: tile cycles advance every step, animated NPCs flip every few (_NPCANIMATE). */
  /** `icons`: E00 frames (mushrooms, guards) or E01 frames (monsters in combat) under the figures; `fx` on top. */
  draw(lv: Level, cx: number, cy: number, figures: Figure[], party: { x: number; y: number; num: number; frame?: number }[], phase = 0,
       icons: Icon[] = [], fx?: Overlay) {
    const ox = cx - (COLS >> 1), oy = cy - (ROWS >> 1);
    const ctx = this.ctx;
    this.drawn.clear();
    ctx.fillStyle = '#000';
    ctx.fillRect(0, 0, COLS * TILE, ROWS * TILE);
    for (let y = 0; y < ROWS; y++)
      for (let x = 0; x < COLS; x++) {
        let t = lv.tile(ox + x, oy + y);
        const cyc = lv.anim.get(t);
        if (cyc) t = cyc[phase % cyc.length];
        if (t !== 0xff) ctx.drawImage(lv.tiles, (t % 16) * 16, (t >> 4) * 16, 16, 16, x * TILE, y * TILE, TILE, TILE);
      }
    const cols = this.sprites.columns;
    for (const i of icons) this.sheet(i.sheet === 'E01' ? this.monsters : this.heroes, i.frame, cols, i.x - ox, i.y - oy);
    for (const f of figures) {
      // _SingleNPCDraw: companions (num < 0x20) use their hero frames; anyone else the E02 sprite `tile`.
      if (f.num < 0x20) this.hero(f.num, f.x - ox, f.y - oy);
      else {
        const n = this.sprites.npc[f.tile];
        this.sheet(this.folk, n.start + (n.frames > 1 ? (phase >> 2) & 1 : 0), cols, f.x - ox, f.y - oy);   // frames 0/1 only
      }
    }
    for (const p of party) if (p.frame === undefined) this.hero(p.num, p.x - ox, p.y - oy); else this.sheet(this.heroes, p.frame, cols, p.x - ox, p.y - oy);
    if (!fx) return;
    for (const i of fx.icons) this.sheet(i.sheet === 'E01' ? this.monsters : this.heroes, i.frame, cols, i.x - ox, i.y - oy);
    for (const g of fx.ghosts ?? []) this.ghost(g, g.x - ox, g.y - oy);
    for (const t of fx.tints) this.tint(t.x - ox, t.y - oy, EGA[t.color & 15]);
    if (fx.invert) {
      ctx.globalCompositeOperation = 'difference';
      ctx.fillStyle = '#fff';                                   // the original's 11×9 map window around the centre
      ctx.fillRect(((COLS >> 1) - 5) * TILE, ((ROWS >> 1) - 4) * TILE, 11 * TILE, 9 * TILE);
      ctx.globalCompositeOperation = 'source-over';
    }
  }
}
