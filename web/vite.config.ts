import { defineConfig, type Plugin } from 'vite';
import { createReadStream, existsSync, statSync } from 'node:fs';
import { resolve } from 'node:path';

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

export default defineConfig({
  base: './',
  plugins: [serveDir('/pack', resolve(__dirname, '../out/pack')), serveDir('/docs', resolve(__dirname, '../docs'))],
  // /sandbox/ forwards to the game with ?sandbox: the scenario editor in the public build (decision 7)
  build: { rollupOptions: { input: { main: resolve(__dirname, 'index.html'), sandbox: resolve(__dirname, 'sandbox/index.html') } } },
});
