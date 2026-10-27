"""Render every map with the tileset implied by its name (MxxEyy -> Vyy.MCT, else Eyy.MCT)."""
import os, sys, re
sys.path.insert(0, os.path.dirname(__file__))
from mc2fmt import load_mct, load_mcm
from render import render_map

src, dst = sys.argv[1], sys.argv[2]
os.makedirs(dst, exist_ok=True)
ok = fail = 0
for f in sorted(os.listdir(src)):
    if not f.endswith('.MCM'): continue
    m = re.match(r'([GM])(\d\d)E(\d\d)\.MCM', f)
    ts = None
    for cand in (f'V{m[3]}.MCT', f'E{m[3]}.MCT'):
        if os.path.exists(f'{src}/{cand}'): ts = cand; break
    try:
        mp = load_mcm(f'{src}/{f}')
        info = f'{mp.w}x{mp.h} max_tile={max(mp.cells)}'
        if ts is None:
            print(f'NOTS {f}: {info}'); fail += 1; continue
        render_map(mp, load_mct(f'{src}/{ts}')).save(f'{dst}/{f[:-4]}.png'); ok += 1
    except Exception as e:
        print(f'FAIL {f}: {e}'); fail += 1
print(f'rendered {ok}, problems {fail}')
