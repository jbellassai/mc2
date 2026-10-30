declare module 'virtual:bundle' {
  /** The data pack, path → base64 (the single-file build only, else null). */
  export const files: Record<string, string> | null;
  /** docs/events.md (the single-file build only, else null). */
  export const events: string | null;
}
