// Deploy the private bundle as a Cloudflare Worker with static assets, behind Cloudflare Access (decision 10).
// `node scripts/deploy-private.mjs` uploads out/bundle/Magic Candle II.html as index.html; `--placeholder` uploads a
// page with no game data (the first deploy, before Access is on). The Worker name comes from MC2_WORKER so the URL
// stays out of this public repo; the config is generated in out/deploy (gitignored), preview URLs off.
import { copyFileSync, mkdirSync, rmSync, writeFileSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { resolve } from 'node:path';

const name = process.env.MC2_WORKER;
if (!name) throw new Error('set MC2_WORKER to the Worker name');
const out = resolve(import.meta.dirname, '../../out'), dir = resolve(out, 'deploy'), pub = resolve(dir, 'public');
rmSync(dir, { recursive: true, force: true });
mkdirSync(pub, { recursive: true });
if (process.argv.includes('--placeholder')) writeFileSync(resolve(pub, 'index.html'), '<!doctype html><title>MC2</title><p>Nothing here yet.</p>\n');
else copyFileSync(resolve(out, 'bundle/Magic Candle II.html'), resolve(pub, 'index.html'));
writeFileSync(resolve(dir, 'wrangler.jsonc'), JSON.stringify({
  name, compatibility_date: '2026-10-01', assets: { directory: './public' }, workers_dev: true, preview_urls: false,
}, null, 2));
execFileSync('npx', ['--yes', 'wrangler@4.151.2', 'deploy'], { cwd: dir, stdio: 'inherit' });
