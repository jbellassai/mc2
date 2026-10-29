"""Compare two data packs (decision 1): the Python exporter's (the reference) and the in-browser converter's.
JSON by value, PNG by RGBA pixels, WAV by parameters and frames, anything else byte for byte.
usage: packdiff.py REFDIR OTHERDIR"""
import json, os, sys, wave
from PIL import Image

def files(root):
    return {os.path.relpath(os.path.join(d, f), root) for d, _, fs in os.walk(root) for f in fs}

def same(a, b):
    ext = a.rsplit('.', 1)[-1]
    if ext == 'json': return json.load(open(a)) == json.load(open(b))
    if ext == 'png':
        x, y = Image.open(a).convert('RGBA'), Image.open(b).convert('RGBA')
        return x.size == y.size and x.tobytes() == y.tobytes()
    if ext == 'wav':
        with wave.open(a) as x, wave.open(b) as y:
            return x.getparams()[:4] == y.getparams()[:4] and x.readframes(x.getnframes()) == y.readframes(y.getnframes())
    return open(a, 'rb').read() == open(b, 'rb').read()

ref, other = sys.argv[1:3]
r, o = files(ref), files(other)
bad = sorted(f for f in r & o if not same(os.path.join(ref, f), os.path.join(other, f)))
for f in sorted(r - o): print('missing', f)
for f in sorted(o - r): print('extra', f)
for f in bad: print('differs', f)
print(f'{len(r & o) - len(bad)} of {len(r)} files match')
sys.exit(1 if bad or r != o else 0)
