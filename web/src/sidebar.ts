// The command sidebar beside the map, after the original frame's right column (VSCRA.MCE: the party list numbered
// 1-6 and the menu window): the party with health and energy, and every command as a button with its hotkey.
export interface Command { label: string; key: string; act: () => void }
export interface Row { name: string; hp: number; hpmax: number; energy: number; state: string; ok: boolean }

const side = document.getElementById('side')!, partyBox = document.getElementById('party')!, cmdBox = document.getElementById('commands')!;
const kbd = (k: string) => Object.assign(document.createElement('kbd'), { textContent: k });

let rows: HTMLElement[] = [], buttons: HTMLButtonElement[] = [];

export const sidebar = {
  show() { side.hidden = false; },
  /** The commands, once; `pick(i)` runs when a party row is clicked. */
  commands(list: Command[], pick: (i: number) => void) {
    buttons = list.map(c => {
      const b = document.createElement('button');
      b.type = 'button';
      b.append(Object.assign(document.createElement('span'), { textContent: c.label }), kbd(c.key));
      b.onclick = () => { b.blur(); c.act(); };
      return b;
    });
    cmdBox.replaceChildren(...buttons);
    partyBox.onclick = e => {
      const i = rows.indexOf((e.target as HTMLElement).closest('.member') as HTMLElement);
      if (i >= 0) pick(i);
    };
  },
  /** Called on every render: cheap updates of the party rows and whether commands are available. */
  update(party: Row[], enabled: boolean) {
    while (rows.length < party.length) {
      const r = document.createElement('div');
      r.className = 'member';
      r.innerHTML = '<span class="n"></span><span class="name"></span><span class="state"></span>' +
        '<div class="bar hp"><i></i></div><div class="bar en"><i></i></div>';
      partyBox.append(r); rows.push(r);
    }
    while (rows.length > party.length) rows.pop()!.remove();
    party.forEach((p, i) => {
      const r = rows[i], q = (s: string) => r.querySelector(s) as HTMLElement;
      q('.n').textContent = String(i + 1);
      q('.name').textContent = p.name;
      q('.state').textContent = p.state;
      r.classList.toggle('bad', !p.ok);
      r.title = `${p.name}: HP ${p.hp} / ${p.hpmax}, energy ${p.energy}`;
      (q('.hp i')).style.width = `${Math.max(0, Math.min(100, 100 * p.hp / Math.max(1, p.hpmax)))}%`;
      (q('.en i')).style.width = `${Math.max(0, Math.min(100, p.energy))}%`;
    });
    for (const b of buttons) b.disabled = !enabled;
  },
};
