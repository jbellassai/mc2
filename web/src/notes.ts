// The notepad (P70, EXE _WriteNote 1a95:0f06; docs/rules/notepad.md): a message printed with a notetaking level of
// 1-3 is kept when that level is at most the chosen amount (0 None, 1 Minimum, 2 Normal, 3 Maximum), with the date,
// time, place and the acting member's square. The original keeps it in far memory, outside the saved game, and Save
// writes NOTESnnn.MCN; the port keeps it in this browser's localStorage and Save downloads a text file.
const MONTHS = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'];
const KEY = 'mc2.notes', LEVEL = 'mc2.notelev';

export interface Note { minute: number; hour: number; date: number; month: number; year: number; x: number; y: number; place: string; text: string }

const load = <T>(k: string, d: T): T => { try { return JSON.parse(localStorage.getItem(k) ?? 'null') ?? d; } catch { return d; } };
const keep = (k: string, v: unknown) => { try { localStorage.setItem(k, JSON.stringify(v)); } catch { /* not kept */ } };

export const notes = {
  /** _e_notelev: a setting of the installed game (MC2INST), not of the save; its default is unknown, Normal assumed. */
  level: load<number>(LEVEL, 2),
  list: load<Note[]>(KEY, []),
  setLevel(n: number) { this.level = n; keep(LEVEL, n); },
  /** The date, time, place and square of a new note (set by main.ts). */
  where: null as (() => Omit<Note, 'text'>) | null,
  /** _WriteNote(text, level). */
  write(level: number, text: string) {
    const t = text.trim();
    if (!t || level > this.level || !this.where) return;
    this.list.push({ ...this.where(), text: t }); keep(KEY, this.list);
  },
  clear() { this.list = []; keep(KEY, this.list); },
  /** The view's heading (P70 ovl_07a0): place, square, month and date, time, year. */
  heading(n: Note) { return `${n.place.trim()}  ${n.x},${n.y}  ${MONTHS[n.month]} ${n.date}  ${n.hour}:${String(n.minute).padStart(2, '0')}  Year ${n.year}`; },
  /** The saved file (P70 0x9CF: each entry as viewed, lines ending CR LF). */
  file() { return this.list.map(n => `${this.heading(n)}\r\n\r\n${n.text.replace(/\n/g, '\r\n')}\r\n\r\n`).join(''); },
};
