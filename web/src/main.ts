// Milestone 1 (decision 2): walk around Telermain from a fresh start.
import { Level, type Figure } from './level';
import { Clock } from './clock';
import { View } from './view';

const status = document.getElementById('status')!;
const START = { level: 'D02', x: 98, y: 18 };     // new_game.md: window (93,14), leader at window cell (5,4)
const NEW_GAME_EVENTS = [10, 88, 117];

async function main() {
  const view = await View.create(document.getElementById('view') as HTMLCanvasElement);
  const level = await Level.load(START.level);
  const clock = Clock.newGame();
  const events = new Set(NEW_GAME_EVENTS);
  const hero = { x: START.x, y: START.y, sprite: 0x3b };   // hero 0 = E00 tile 0x3B (_MCCPTile)
  let figures: Figure[] = level.figures(clock, events);
  let message = `${level.loc.name.replace(/\s+\S$/, '')}. You have landed in Telermain.`;

  const render = () => {
    view.draw(level, hero.x, hero.y, figures, [hero]);
    status.textContent = `${clock}  —  ${message}`;
  };

  const step = (dx: number, dy: number) => {
    const x = hero.x + dx, y = hero.y + dy;
    const who = figures.find(f => f.x === x && f.y === y);
    const door = level.loc.doors.find(d => d.x === x && d.y === y);
    const exit = level.loc.exits.find(e => e.x === x && e.y === y);
    if (who) message = who.name ? `${who.name} is in the way.` : 'Someone is in the way.';   // assumption: NPCs block
    else if (level.walkable(x, y)) {
      hero.x = x; hero.y = y;
      message = '';
      if (clock.step()) figures = level.figures(clock, events);
    } else if (door) message = `A door (room id ${door.id}). Rooms come next.`;
    else if (exit) message = 'The way out of town. The world map comes later.';
    else message = `Blocked by ${level.tileName(x, y)}.`;
    render();
  };

  const KEYS: Record<string, [number, number]> = {
    ArrowUp: [0, -1], ArrowDown: [0, 1], ArrowLeft: [-1, 0], ArrowRight: [1, 0],
    w: [0, -1], s: [0, 1], a: [-1, 0], d: [1, 0],
  };
  addEventListener('keydown', e => {
    const k = KEYS[e.key];
    if (k) { e.preventDefault(); step(...k); }
  });
  render();
}

main().catch(e => { status.textContent = String(e); console.error(e); });
