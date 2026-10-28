// Tile view centred on the party leader. Original window is 11×9 with the leader at (5,4); the port shows more.
import { image, json, type Sprites } from './pack';
import type { Level, Figure } from './level';

export const COLS = 21, ROWS = 15, TILE = 16;

export class View {
  private ctx: CanvasRenderingContext2D;
  private constructor(canvas: HTMLCanvasElement, private heroes: HTMLImageElement, private folk: HTMLImageElement,
                      private sprites: Sprites) {
    canvas.width = COLS * TILE; canvas.height = ROWS * TILE;
    canvas.style.width = `${COLS * TILE * 3}px`;
    this.ctx = canvas.getContext('2d')!;
    this.ctx.imageSmoothingEnabled = false;
  }

  static async create(canvas: HTMLCanvasElement): Promise<View> {
    return new View(canvas, await image('sprites/E00.png'), await image('sprites/E02.png'), await json<Sprites>('sprites.json'));
  }

  private sheet(im: HTMLImageElement, k: number, cols: number, cx: number, cy: number) {
    this.ctx.drawImage(im, (k % cols) * 16, Math.floor(k / cols) * 16, 16, 16, cx * TILE, cy * TILE, TILE, TILE);
  }

  draw(lv: Level, cx: number, cy: number, figures: Figure[], party: { x: number; y: number; sprite: number }[]) {
    const ox = cx - (COLS >> 1), oy = cy - (ROWS >> 1);
    const ctx = this.ctx;
    ctx.fillStyle = '#000';
    ctx.fillRect(0, 0, COLS * TILE, ROWS * TILE);
    for (let y = 0; y < ROWS; y++)
      for (let x = 0; x < COLS; x++) {
        const t = lv.tile(ox + x, oy + y);
        if (t !== 0xff) ctx.drawImage(lv.tiles, (t % 16) * 16, (t >> 4) * 16, 16, 16, x * TILE, y * TILE, TILE, TILE);
      }
    const cols = this.sprites.columns;
    for (const f of figures) {
      // _SingleNPCDraw: companions (num < 0x20) use their hero frames; anyone else the E02 sprite `tile`.
      if (f.num < 0x20) this.sheet(this.heroes, 0x3b + 18 * f.num, cols, f.x - ox, f.y - oy);
      else this.sheet(this.folk, this.sprites.npc[f.tile].start, cols, f.x - ox, f.y - oy);
    }
    for (const p of party) this.sheet(this.heroes, p.sprite, cols, p.x - ox, p.y - oy);
  }
}
