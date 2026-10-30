// After `vite build --mode bundle` (decision 9): name the page, add a README, zip both into out/bundle.
import { renameSync, writeFileSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { resolve } from 'node:path';

const dir = resolve(import.meta.dirname, '../../out/bundle'), page = 'Magic Candle II.html';
renameSync(resolve(dir, 'index.html'), resolve(dir, page));
writeFileSync(resolve(dir, 'README.txt'), [
  'The Magic Candle II',
  '',
  `Double-click "${page}". It opens in your web browser; nothing is installed and no internet is needed.`,
  'Saved games stay in that browser on this computer, so keep using the same browser.',
  'F2 opens the scenario editor.',
  '',
].join('\r\n'));
execFileSync('zip', ['-q', '-X', '-r', 'Magic Candle II.zip', page, 'README.txt'], { cwd: dir });
console.log(`out/bundle/${page} and out/bundle/Magic Candle II.zip`);
