// Run the in-browser converter (src/convert.ts) under Node, for checking it against tools/export_json.py:
// node web/scripts/convert.mjs ORIGDIR OUTDIR, then .venv/bin/python -I tools/packdiff.py out/pack OUTDIR
import { readdirSync, readFileSync, writeFileSync, mkdirSync } from 'node:fs';
import { dirname, join } from 'node:path';
import { convert } from '../src/convert.ts';

const [src, dst] = process.argv.slice(2);
const files = new Map(readdirSync(src, { withFileTypes: true }).filter(e => e.isFile()).map(e => [e.name.toUpperCase(), new Uint8Array(readFileSync(join(src, e.name)))]));
const t = performance.now();
const pack = await convert(files);
for (const [path, data] of pack) { mkdirSync(dirname(join(dst, path)), { recursive: true }); writeFileSync(join(dst, path), data); }
console.log(`${pack.size} files in ${Math.round(performance.now() - t)} ms`);
