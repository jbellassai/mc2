// The text panel under the map: a scrolling log, a row of buttons, an optional word input.
export interface Button { label: string; act: () => void }

const box = document.getElementById('panel')!, log = document.getElementById('log')!;
const row = document.getElementById('buttons')!, form = document.getElementById('ask') as HTMLFormElement;
const input = document.getElementById('word') as HTMLInputElement;
let submit: ((s: string) => void) | null = null;

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
    row.replaceChildren(...buttons.map(b => {
      const el = document.createElement('button');
      el.type = 'button'; el.textContent = b.label; el.onclick = b.act;
      return el;
    }));
    submit = ask; form.hidden = !ask; input.placeholder = placeholder;
    if (ask) input.focus(); else (row.firstChild as HTMLElement | null)?.focus();
  },
};

input.addEventListener('keydown', e => { if (e.key === 'Escape') (row.lastChild as HTMLElement | null)?.click(); });
