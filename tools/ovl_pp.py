"""Post-process Ghidra decompiler output of a code overlay (P*.MCO loaded at 1CA8:0000) into readable form.
Facts (see docs/overlays.md): SI = 0x4CF6 bias for DS globals, BX = EXE vector table (ghidra/vectors.json),
CS:[DI+n] = overlay-private data (DI = 0x1F00 for location overlays), near calls are overlay-internal."""
import re, sys, json, bisect, os
HERE = os.path.dirname(os.path.abspath(__file__)); ROOT = os.path.dirname(HERE)
SI_BIAS = 0x4CF6; OVL_SEG = 0x1CA8
vec = {e['slot']: (e['name'] or f"slot{e['slot']:x}").lstrip('_') for e in json.load(open(f'{ROOT}/ghidra/vectors.json'))}
td = json.load(open(f'{ROOT}/out/tdinfo.json'))
ds = sorted((s['off'], s['name']) for s in td['symbols'] if s['class'] == 'static' and s['seg'] == 0x15b5)
dsoff = [o for o, _ in ds]
def gname(off):
    off &= 0xffff; i = bisect.bisect_right(dsoff, off) - 1
    if i < 0: return f'DS_{off:04x}'
    o, n = ds[i]; return n.lstrip('_') + (f'+{off-o}' if off != o else '')
def sval(s):  # '0x12' or '-0x12'
    return -int(s[1:], 16) if s.startswith('-') else int(s, 16)
def pp(text):
    t = text
    # vector calls: (*(code *)*(undefined2 *)(X + 0xNN))( -> VEC_name(
    t = re.sub(r'\(\*\(code \*\)\*\(undefined2 \*\)\((\w+) \+ (0x[0-9a-f]+)\)\)\s*\(', lambda m: f'EXE_{vec.get(int(m[2],16), "slot"+m[2])}(', t)
    t = re.sub(r'(EXE_\w+)\(0x1000(?:,\s*|(?=\)))', r'\1(', t)   # first pushed arg is the saved BX, not a parameter
    t = re.sub(r'\(\*\(code \*\)\*(\w+)\)\(', r'EXE_viaptr_\1(', t)
    # globals: *(T *)(unaff_SI + N) and bare unaff_SI + N
    t = re.sub(r'\*\((\w+(?: \*)?) \*\)\(unaff_SI \+ (-?0x[0-9a-f]+)\)', lambda m: f'G_{gname(sval(m[2]) + SI_BIAS)}', t)
    t = re.sub(r'\(unaff_SI \+ (-?0x[0-9a-f]+)\)', lambda m: f'&G_{gname(sval(m[1]) + SI_BIAS)}', t)
    t = re.sub(r'unaff_SI \+ (-?0x[0-9a-f]+)', lambda m: f'&G_{gname(sval(m[1]) + SI_BIAS)}', t)
    # overlay-private data via DI
    t = re.sub(r'\*\((\w+(?: \*)?) \*\)\(unaff_DI \+ (0x[0-9a-f]+)\)', lambda m: f'OV_{m[2]}', t)
    t = re.sub(r'\(unaff_DI \+ (0x[0-9a-f]+)\)', lambda m: f'&OV_{m[1]}', t)
    t = re.sub(r'unaff_DI \+ (0x[0-9a-f]+)', lambda m: f'&OV_{m[1]}', t)
    # near calls shown as linear addresses -> overlay offset
    t = re.sub(r'func_0x000([0-9a-f]{5})\(', lambda m: f'ovl_{int(m[1],16) - OVL_SEG*16:04x}(', t)
    t = re.sub(r'FUN_1ca8_([0-9a-f]{4})', r'ovl_\1', t)
    t = re.sub(r'LAB_1ca8_', 'L_', t)
    return t
if __name__ == '__main__':
    sys.stdout.write(pp(open(sys.argv[1]).read()))
