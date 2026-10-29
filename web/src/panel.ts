// The text panel under the map: a scrolling log, a row of buttons, an optional word input.
export interface Button { label: string; act: () => void }

const box = document.getElementById('panel')!, log = document.getElementById('log')!;
const row = document.getElementById('buttons')!, form = document.getElementById('ask') as HTMLFormElement;
const input = document.getElementById('word') as HTMLInputElement;
let submit: ((s: string) => void) | null = null;
let hotkeys = new Map<string, HTMLButtonElement>();

/** A button's key: the first letter of a word of its label still free, then any letter of it, then a digit. */
function hotkey(label: string, used: Set<string>, i: number, shared: Set<string>): string {
  const words = label.toLowerCase().split(/[^a-z0-9]+/).filter(Boolean).filter((w, k) => k || !shared.has(w));   // "Save 1/2/3" → 1, 2, 3
  const tries = [...words.map(w => w[0]), ...label.toLowerCase().replace(/[^a-z]/g, ''), ...'123456789'];
  const k = tries.find(c => !used.has(c)) ?? (i < 9 ? String(i + 1) : '');
  used.add(k);
  return k;
}

// The open panel's buttons answer their keys (not while typing in the word box).
addEventListener('keydown', e => {
  if (box.hidden || e.ctrlKey || e.metaKey || e.altKey || (e.target as HTMLElement).closest?.('input, select, textarea')) return;
  const b = hotkeys.get(e.key.toLowerCase());
  if (!b || !b.isConnected) return;
  e.preventDefault(); e.stopImmediatePropagation();
  b.click();
});

form.addEventListener('submit', e => {
  e.preventDefault();
  const s = input.value.trim();
  if (!s || !submit) return;
  input.value = '';
  submit(s);
});

export const panel = {
  get open() { return !box.hidden; },
  show() { log.textContent = ''; box.hidden = false; },
  hide() { box.hidden = true; submit = null; },
  /** Arbitrary content (e.g. a table) appended to the log. */
  add(el: HTMLElement) { log.append(el); },
  line(text: string, cls = '') {
    const d = document.createElement('div');
    d.textContent = text; d.className = cls;
    log.append(d); log.scrollTop = log.scrollHeight;
  },
  /** Replace the buttons; `ask` shows the word input and calls it with what was typed. */
  set(buttons: Button[], ask: ((s: string) => void) | null = null, placeholder = '') {
    const used = new Set<string>();
    const firsts = buttons.map(b => b.label.toLowerCase().split(/[^a-z0-9]+/).filter(Boolean)[0]);
    const shared = new Set(firsts.filter((w, k) => firsts.indexOf(w) !== k));
    hotkeys = new Map();
    row.replaceChildren(...buttons.map((b, i) => {
      const el = document.createElement('button');
      el.type = 'button'; el.onclick = b.act;
      const key = hotkey(b.label, used, i, shared);
      el.append(b.label);
      if (key) { hotkeys.set(key, el); el.append(Object.assign(document.createElement('kbd'), { textContent: key.toUpperCase() })); }
      return el;
    }));
    submit = ask; form.hidden = !ask; input.placeholder = placeholder;
    if (ask) input.focus(); else (row.firstChild as HTMLElement | null)?.focus();
  },
};

input.addEventListener('keydown', e => { if (e.key === 'Escape') (row.lastChild as HTMLElement | null)?.click(); });
