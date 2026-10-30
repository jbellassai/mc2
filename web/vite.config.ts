import { defineConfig, type Plugin } from 'vite';
import { createReadStream, existsSync, readdirSync, readFileSync, statSync } from 'node:fs';
import { relative, resolve } from 'node:path';

// Dev only: serve the locally built data pack (../out/pack, decision 1) at /pack/ and the docs (the scenario editor
// reads docs/events.md) at /docs/. Neither is copied into a build.
const serveDir = (route: string, dir: string): Plugin => ({
  name: `serve${route.replace('/', '-')}`,
  apply: 'serve',
  configureServer(server) {
    server.middlewares.use(route, (req, res, next) => {
      const file = resolve(dir, '.' + decodeURIComponent((req.url ?? '/').split('?')[0]));
      if (!file.startsWith(dir) || !existsSync(file) || !statSync(file).isFile()) return next();
      res.setHeader('Content-Type', file.endsWith('.png') ? 'image/png' : file.endsWith('.md') ? 'text/plain; charset=utf-8' : 'application/json');
      createReadStream(file).pipe(res);
    });
  },
});

// virtual:bundle: in the private single-file build (`--mode bundle`, decision 9) the data pack (path → base64) and
// docs/events.md; null in every other build.
const bundleData = (on: boolean): Plugin => ({
  name: 'bundle-data',
  resolveId: id => id === 'virtual:bundle' ? '\0virtual:bundle' : null,
  load(id) {
    if (id !== '\0virtual:bundle') return null;
    if (!on) return 'export const files = null, events = null;';
    const pack = resolve(__dirname, '../out/pack'), files: Record<string, string> = {};
    const walk = (dir: string): void => readdirSync(dir, { withFileTypes: true }).forEach(e => e.isDirectory()
      ? walk(resolve(dir, e.name)) : void (files[relative(pack, resolve(dir, e.name))] = readFileSync(resolve(dir, e.name)).toString('base64')));
    if (!existsSync(resolve(pack, 'comtxt.json'))) throw new Error('Build the data pack first: tools/export_json.py original out/pack');
    walk(pack);
    return `export const files = ${JSON.stringify(files)}, events = ${JSON.stringify(readFileSync(resolve(__dirname, '../docs/events.md'), 'utf8'))};`;
  },
});

// The single-file build: the script and styles inlined into the page, and the title font (Google Fonts, fetched once
// at build time) as data URLs, so the page runs opened straight from disk with no network.
const singleFile = (): Plugin => ({
  name: 'single-file',
  apply: 'build',
  enforce: 'post',
  async transformIndexHtml(html) {
    const link = html.match(/<link href="(https:\/\/fonts\.googleapis\.com\/css2[^"]+)" rel="stylesheet">/);
    if (!link) return html;
    let css = await (await fetch(link[1], { headers: { 'User-Agent': 'Mozilla/5.0 Chrome/120' } })).text();
    for (const url of [...new Set(css.match(/https:\/\/fonts\.gstatic\.com\/[^)]+/g) ?? [])]) {
      const font = Buffer.from(await (await fetch(url)).arrayBuffer()).toString('base64');
      css = css.split(url).join(`data:font/woff2;base64,${font}`);
    }
    return html.replace(/<link rel="preconnect"[^>]*>\n/g, '').replace(link[0], `<style>${css}</style>`);
  },
  generateBundle(_, bundle) {
    const page = Object.values(bundle).find(f => f.fileName.endsWith('.html'));
    if (!page || page.type !== 'asset') return;
    let html = String(page.source);
    for (const [name, f] of Object.entries(bundle)) {
      if (f.type === 'chunk') {
        html = html.replace(new RegExp(`<script type="module" crossorigin src="[./]*${f.fileName}"></script>`),
          () => `<script type="module">${f.code.replace(/<\/script/gi, '<\\/script')}</script>`);
        delete bundle[name];
      } else if (f.fileName.endsWith('.css')) {
        html = html.replace(new RegExp(`<link rel="stylesheet" crossorigin href="[./]*${f.fileName}">`), () => `<style>${f.source}</style>`);
        delete bundle[name];
      }
    }
    page.source = html;
  },
});

export default defineConfig(({ mode }) => ({
  base: './',
  plugins: [serveDir('/pack', resolve(__dirname, '../out/pack')), serveDir('/docs', resolve(__dirname, '../docs')),
            bundleData(mode === 'bundle'), ...(mode === 'bundle' ? [singleFile()] : [])],
  build: mode === 'bundle'
    ? { outDir: resolve(__dirname, '../out/bundle'), emptyOutDir: true, assetsInlineLimit: Infinity, cssCodeSplit: false,
        rollupOptions: { input: resolve(__dirname, 'index.html'), output: { inlineDynamicImports: true } } }
    // /sandbox/ forwards to the game with ?sandbox: the scenario editor in the public build (decision 7)
    : { rollupOptions: { input: { main: resolve(__dirname, 'index.html'), sandbox: resolve(__dirname, 'sandbox/index.html') } } },
}));
