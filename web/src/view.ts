// Tile view centred on the party leader. Original window is 11×9 with the party's 3×3 formation at (4,3)-(6,5); the port shows more.
import { image, json, type Sprites } from './pack';
import type { Level, Figure } from './level';

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
  }

  /** _MCCPTile: hero or companion n stands on E00 frame 0x3B + 18n; companions from 0x18 on use E03 frame 18(n − 0x18).
   *  Maps load only frame 0 and frames 10-17 of the 18 (_TileApplies, DS:0x4CA); there is no walking animation. */
  private hero(n: number, cx: number, cy: number) {
    const cols = this.sprites.columns;
    if (n < 0x18) this.sheet(this.heroes, 0x3b + 18 * n, cols, cx, cy); else this.sheet(this.more, 18 * (n - 0x18), cols, cx, cy);
  }

  /** A full screen (P81's VGA screens, `screens/x.png`, 320×200) fitted to the view's width with black above and
   *  below, faded in from black over 0.4 s as the original fades its palette in. */
  async screen(name: string) {
    const im = await image(`screens/${name}.png`), ctx = this.ctx, w = this.canvas.width, h = Math.round(w * 200 / 320);
    const y = (this.canvas.height - h) >> 1, t0 = performance.now();
    ctx.imageSmoothingEnabled = false;
    await new Promise<void>(done => {
      const frame = (now: number) => {
        const a = Math.min(1, (now - t0) / 400);
        ctx.globalAlpha = 1; ctx.fillStyle = '#000'; ctx.fillRect(0, 0, w, this.canvas.height);
        ctx.globalAlpha = a; ctx.drawImage(im, 0, y, w, h); ctx.globalAlpha = 1;
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
  /** `icons`: E00 frames (mushrooms, guards) or E01 frames (monsters in combat) under the figures. */
  draw(lv: Level, cx: number, cy: number, figures: Figure[], party: { x: number; y: number; num: number; frame?: number }[], phase = 0,
       icons: Icon[] = []) {
    const ox = cx - (COLS >> 1), oy = cy - (ROWS >> 1);
    const ctx = this.ctx;
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
  }
}
