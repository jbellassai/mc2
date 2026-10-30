// The dev tools (scenario editor, URL aids, `dbg` for scripts): dev builds, and the private single-file build
// (`npm run bundle`, decision 9), which also carries the data pack and docs/events.md (virtual:bundle).
export const TOOLS = import.meta.env.DEV || import.meta.env.MODE === 'bundle';
