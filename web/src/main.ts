// Milestone 1 (decision 2): walk around Telermain from a fresh start.
import { Level, type Figure } from './level';
import { Clock } from './clock';
import { View } from './view';
import { resolveRoom } from './room';
import type { Door, Exit } from './pack';

const status = document.getElementById('status')!;
const START = { level: 'D02', x: 98, y: 18 };     // new_game.md: window (93,14), leader at window cell (5,4)
const NEW_GAME_EVENTS = [10, 88, 117];

async function main() {
  const view = await View.create(document.getElementById('view') as HTMLCanvasElement);
  const clock = Clock.newGame();
  const events = new Set(NEW_GAME_EVENTS);
  const hero = { x: START.x, y: START.y, sprite: 0x3b };   // hero 0 = E00 tile 0x3B (_MCCPTile)
  let level = await Level.load(START.level);
  let outside: { level: Level; x: number; y: number } | null = null;   // where to return from a room
  let figures: Figure[] = level.figures(clock, events);
  let message = 'You have landed in Telermain.';

  const render = () => {
    const room = level.loc.kind === 'room';
    view.draw(level, room ? 5 : hero.x, room ? 4 : hero.y, figures, [hero]);
    status.textContent = `${clock}  —  ${level.loc.name.replace(/\s+[MX]$/, '')}${message ? '  —  ' + message : ''}`;
  };

  const go = (lv: Level, x: number, y: number) => {
    level = lv; hero.x = x; hero.y = y;
    figures = level.figures(clock, events);
  };

  /** Doors (rules/locations.md, Towns): type 0/3 open, bit 0x80 key door, otherwise a locked private home. */
  const enter = async (door: Door) => {
    if (door.type & 0x80) return void (message = 'The door is magically locked.');
    if (door.type !== 0 && door.type !== 3) {
      const r = level.loc.residents[door.id];
      const who = r && r.num !== 0xfe ? level.loc.words[r.name] : null;
      message = who ? `${who}'s door is locked. (Knock, pick and break come with the command menus.)` : 'The door is locked.';
      return;
    }
    const ref = await resolveRoom(door, level.loc.pgms[door.pgm]);
    if (!ref) return void (message = 'This door leads somewhere not built yet.');
    outside = { level, x: hero.x, y: hero.y };
    go(await Level.loadRoom(ref), ref.start.x, ref.start.y);
    message = `You enter ${level.loc.name}.`;
  };

  /** Room exits {x,y,pgm,tx,ty,datafile}: back to town `datafile` with the window at (tx,ty), leader at cell (5,4). */
  const leave = async (exit: Exit) => {
    const id = `D${String(exit.datafile).padStart(2, '0')}`;
    if (exit.datafile !== undefined && exit.datafile !== 255)
      go(outside?.level.id === id ? outside.level : await Level.load(id), exit.tx + 5, exit.ty + 4);
    else if (outside) go(outside.level, outside.x, outside.y);
    outside = null;
    message = '';
  };

  const step = async (dx: number, dy: number) => {
    const x = hero.x + dx, y = hero.y + dy;
    const who = figures.find(f => f.x === x && f.y === y);
    const door = level.loc.doors.find(d => d.x === x && d.y === y);
    const exit = level.loc.exits.find(e => e.x === x && e.y === y);
    if (who) message = who.name ? `${who.name} is in the way.` : 'Someone is in the way.';   // assumption: NPCs block
    else if (level.walkable(x, y) && !(level.loc.kind === 'room' && exit)) {
      hero.x = x; hero.y = y;
      message = '';
      if (clock.step()) figures = level.figures(clock, events);
    } else if (exit && level.loc.kind === 'room') await leave(exit);
    else if (door) await enter(door);
    else if (exit) message = 'The way out of town. The world map comes later.';
    else message = `Blocked by ${level.tileName(x, y)}.`;
    render();
  };

  const KEYS: Record<string, [number, number]> = {
    ArrowUp: [0, -1], ArrowDown: [0, 1], ArrowLeft: [-1, 0], ArrowRight: [1, 0],
    w: [0, -1], s: [0, 1], a: [-1, 0], d: [1, 0],
  };
  let queue = Promise.resolve();   // steps run in order; keys pressed while a room loads are not lost
  addEventListener('keydown', e => {
    const k = KEYS[e.key];
    if (!k) return;
    e.preventDefault();
    queue = queue.then(() => step(...k)).catch(err => { status.textContent = String(err); console.error(err); });
  });
  render();
}

main().catch(e => { status.textContent = String(e); console.error(e); });
