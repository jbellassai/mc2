// The import screen (decision 1): with no data pack on the server, the player chooses their own copy of the game;
// its files are converted here (convert.ts), kept in this browser (pack.ts) and never leave it.
import { panel } from './panel';
import { keepFiles } from './pack';
import type { Files } from './convert';

/** The file kinds the converter reads (everything else in the folder is left alone). */
const KINDS = /\.(MCV|MCT|MCM|MCO|MCI|MCC|MCE|VOC|CMF|MID)$/;
const EXE_SIZE = 323931;   // MC2.EXE of version 2.00 "VGA only, mouse", the version every offset was read from

/** Resolves once the files are kept; the caller then opens the pack. */
export function importGame(status: HTMLElement): Promise<void> {
  const input = Object.assign(document.createElement('input'), { type: 'file', multiple: true });
  input.setAttribute('webkitdirectory', '');
  input.hidden = true;
  document.body.append(input);   // in the page, so scripts/shot.mjs can hand it files (files:DIR)
  status.textContent = 'The Magic Candle II needs its game files';
  panel.show();
  panel.line('This is a port of The Magic Candle II (Mindcraft, 1991). It ships none of the game itself: it plays from your own copy.');
  panel.line('Choose the folder of your installed DOS game, version 2.00 (the one with MC2.EXE). Its files are converted here, ' +
    'kept in this browser, and never uploaded.');
  return new Promise(ok => {
    panel.set([{ label: 'Choose the game folder', act: () => input.click() }]);
    input.onchange = async () => {
      const files: Files = new Map();
      for (const f of Array.from(input.files ?? [])) {
        const name = f.name.toUpperCase(), depth = (f.webkitRelativePath || f.name).split('/').length;
        if ((name === 'MC2.EXE' || KINDS.test(name)) && (!files.has(name) || depth <= 2)) files.set(name, new Uint8Array(await f.arrayBuffer()));
      }
      input.value = '';
      const exe = files.get('MC2.EXE');
      if (!exe) return void panel.line('There is no MC2.EXE in that folder. Choose the folder the game was installed in.');
      if (exe.length !== EXE_SIZE) return void panel.line(`That MC2.EXE is ${exe.length} bytes; this port reads version 2.00 (${EXE_SIZE} bytes).`);
      panel.line('Converting…');
      try {
        await (await import('./convert')).convert(files);   // a trial run: a missing or odd file fails here, before anything is kept
        await keepFiles(files);
        input.remove();
        ok();
      } catch (e) {
        panel.line(`The conversion failed: ${e instanceof Error ? e.message : e}`);
      }
    };
  });
}
