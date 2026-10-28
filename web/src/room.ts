// Which room interior a door leads to (docs/formats.md, Room maps; rules/services.md, How a door becomes a room).
import { json, two, type Door, type Pgm, type RoomRecord } from './pack';

const BOUND = [0x40, 0x48, 0x6c, 0x7c, 0x80, 0x84, 0x90, 0x98, 0xa0, 0xa8, 0xbb, 0xc0, 0xc8, 0xd0, 0xd8]; // P05 0x2BA, P09 0x66
const BANKS = new Set([15, 16, 17, 18, 36, 55, 60, 75, 80, 81, 82, 83, 90, 91]);                       // LOCTYPE banks
/** P05 ovl_1411: party base square by `_rmtyp` (P05 file 0x1F / 0x28); members fill a 3×3 formation from it. */
export const BASE_X = [4, 7, 4, 4, 4, 4, 4, 4, 7], BASE_Y = [5, 5, 5, 5, 5, 5, 5, 5, 1];   // entry 8 = inn guest side

/** `room` = the door's room id (`_rmdata[0]`), `kind` = P05's `_rmtyp` (rules/services.md). */
export interface RoomRef { id: string; pgm: Pgm; index: number; room: number; kind: number; map: { g: number; chunk: number }; start: { x: number; y: number } }

export async function resolveRoom(door: Door, pgm: Pgm): Promise<RoomRef | null> {
  if (![5, 8, 9].includes(pgm.program)) return null;          // P04 patches, P06/P07 dungeon rooms: later milestones
  const bank = BANKS.has(pgm.datafile);
  const id = bank ? `D${two(pgm.datafile)}_${two(door.id)}` : `D${two(pgm.datafile)}`;
  let loc: RoomRecord;
  try { loc = await json<RoomRecord>(`locations/${id}.json`); } catch { return null; }
  const rm = loc.roommap;
  if (!rm) return null;
  let rmtyp = BOUND.filter(b => b <= door.id).length;
  let idx = door.id - (rmtyp ? BOUND[rmtyp - 1] : 0);
  if (pgm.program === 5 && rmtyp === 2 && door.id > 0x5b) { rmtyp = 1; idx -= 0x14; }   // P05 ovl_1315: camps use the inn kind
  if (bank) rmtyp = 0;                                                                   // P05 ovl_12bc
  if (bank) idx = 0;
  if (pgm.program === 9 && rmtyp === 13) idx += 8;                   // P09 OV_0x158: dungeon temples use entries 8-15
  const chunk = pgm.program === 8 ? rm.chunks[0] : rm.chunks[idx];
  if (chunk === undefined) return null;
  // P05's base table covers rmtyp 0-8; P09 ovl_1720 uses (4,5), a gate (4,6) (P09 file 0x0F / 0x18 by rmtyp); P08
  // placement is not traced yet, so it uses the store base.
  const k = pgm.program === 5 && rmtyp < BASE_X.length ? rmtyp : 0;
  const start = pgm.program === 9 ? { x: 4, y: rmtyp === 14 ? 6 : 5 } : { x: BASE_X[k], y: BASE_Y[k] };
  // `start` = formation origin; members stand at start + (cell mod 3, cell div 3) (P05 ovl_19b0, FFSAVE).
  return { id, pgm, index: idx, room: door.id, kind: rmtyp, map: { g: rm.g, chunk }, start };
}
