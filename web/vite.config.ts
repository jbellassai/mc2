import { defineConfig, type Plugin } from 'vite';
import { createReadStream, existsSync, statSync } from 'node:fs';
import { resolve } from 'node:path';

// Dev only: serve the locally built data pack (../out/pack, decision 1) at /pack/. It is never copied into a build.
const PACK = resolve(__dirname, '../out/pack');
const servePack = (): Plugin => ({
  name: 'serve-pack',
  apply: 'serve',
  configureServer(server) {
    server.middlewares.use('/pack', (req, res, next) => {
      const file = resolve(PACK, '.' + decodeURIComponent((req.url ?? '/').split('?')[0]));
      if (!file.startsWith(PACK) || !existsSync(file) || !statSync(file).isFile()) return next();
      res.setHeader('Content-Type', file.endsWith('.png') ? 'image/png' : 'application/json');
      createReadStream(file).pipe(res);
    });
  },
});

export default defineConfig({ base: './', plugins: [servePack()] });
