"""Location (LOCTYPE, Dnn.MCV) parser and mosaic composer. See docs/formats.md."""
import os, struct, sys
sys.path.insert(0, os.path.dirname(__file__))
from mc2fmt import load_mcm, Map

PTRS = ['roomptr','genptr','knpcptr','resids','maps','loctext','lkdata','pgmptr','exitptr','gwrds','newsr',
        'weathr','peopr','hroomptr','spetbl','treasptr','spdoors','locptr','locevptr','notyet0']

def load_loc(path):
    d = open(path, 'rb').read()
    p = dict(zip(PTRS, struct.unpack_from('<20H', d, 0)))
    loc = {'raw': d, 'ptr': p, 'locnum': d[40], 'roomno': d[41],
           'locname': d[42:53].split(b'\0')[0].decode('latin1').rstrip(),
           'lcharm': d[53], 'mapsizex': d[54], 'mapsizey': d[55], 'doorstn': d[56], 'locdiff': d[57], 'pearlsw': d[58]}
    m = p['maps']; n = d[m-1] if m else 0
    if n == 0xff: n = 0
    loc['blocks'] = [dict(block=d[m+i], tileset=d[m+n+i], x=d[m+2*n+i], y=d[m+3*n+i]) for i in range(n)]
    return loc

def compose(loc, src, report=print):
    """Overlay each block's 42x42 window at (x,y). Returns (Map, tileset number used by most blocks)."""
    w = max(b['x'] for b in loc['blocks']) + 42; h = max(b['y'] for b in loc['blocks']) + 42
    cells = bytearray(b'\xff' * (w * h)); tilesets = {}
    for b in loc['blocks']:
        if b['block'] == 0: continue
        f = f"{src}/M{b['block']:02d}E{b['tileset']:02d}.MCM"
        if not os.path.exists(f): report(f'  missing {f}'); continue
        m = load_mcm(f); tilesets[b['tileset']] = tilesets.get(b['tileset'], 0) + 1
        if m.w != 42: m = Map(42, 42, open(f, 'rb').read()[2:2 + 42 * 42])   # 5042-byte files: the block is the first 42×42
        same = diff = 0
        for yy in range(min(m.h, 42)):
            for xx in range(min(m.w, 42)):
                i = (b['y'] + yy) * w + b['x'] + xx; v = m.cells[yy * m.w + xx]
                if cells[i] != 0xff:
                    same += cells[i] == v; diff += cells[i] != v
                cells[i] = v
        if same + diff: report(f"  block {b['block']:2d} E{b['tileset']:02d} at ({b['x']},{b['y']}): overlap {same+diff} cells, {diff} differ")
    return Map(w, h, bytes(cells)), max(tilesets, key=tilesets.get) if tilesets else None

if __name__ == '__main__':
    from mc2fmt import load_mct
    from render import render_map
    src, dst = sys.argv[1], sys.argv[2]; os.makedirs(dst, exist_ok=True)
    for f in sorted(os.listdir(src)):
        if not (f.startswith('D') and f.endswith('.MCV')): continue
        loc = load_loc(f'{src}/{f}')
        print(f"{f}: #{loc['locnum']} {loc['locname']!r} {loc['mapsizex']}x{loc['mapsizey']} blocks={[(b['block'],b['tileset'],b['x'],b['y']) for b in loc['blocks']]}")
        if not loc['blocks'] or not any(b['block'] for b in loc['blocks']): continue
        m, ts = compose(loc, src)
        if ts is None: continue
        tsf = f'{src}/V{ts:02d}.MCT'
        if os.path.exists(tsf):
            render_map(m, load_mct(tsf)).save(f"{dst}/{f[:-4]}_{loc['locname'].replace(' ','_') or 'x'}.png")
