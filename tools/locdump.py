"""Dump the sub-tables of every Dnn.MCV location record (see docs/formats.md).
usage: locdump.py ORIGDIR OUTDIR   -> OUTDIR/Dnn.txt per location + OUTDIR/npcs.txt (all KNPCs by number)"""
import os, struct, sys
sys.path.insert(0, os.path.dirname(__file__))
from loc import load_loc

def cstrings(d, off, limit):
    out = []
    while off < limit and off < len(d):
        e = d.find(b'\0', off)
        if e < 0 or e >= limit: break
        out.append(d[off:e].decode('latin1')); off = e + 1
    return out

def recs(d, off, size, nrec=None):
    out = []
    while off + size <= len(d) and (nrec is not None or d[off] != 0xff) and (nrec is None or len(out) < nrec):
        out.append(tuple(d[off:off+size])); off += size
    return out

def dump(path, out):
    L = load_loc(path); d = L['raw']; p = L['ptr']
    ends = sorted(v for v in p.values() if v) + [len(d)]
    def end(k): v = p[k]; return next((e for e in ends if e > v), len(d))
    w = out.write
    w(f"# {os.path.basename(path)} {L['locname']!r} locnum={L['locnum']} roomno={L['roomno']} size={L['mapsizex']}x{L['mapsizey']} "
      f"lcharm={L['lcharm']} doorstn={L['doorstn']} locdiff={L['locdiff']} pearlsw={L['pearlsw']} greet={list(d[59:62])}\n")
    words = cstrings(d, p['gwrds'], end('gwrds')) if p['gwrds'] else []
    w(f"gwrds ({len(words)}): " + ' '.join(f"{i}:{s}" for i, s in enumerate(words)) + "\n")
    name = lambda i: words[i] if i < len(words) else f"?{i}"
    if p['roomptr']:
        w("rooms (x y pgm id type):\n")
        for r in recs(d, p['roomptr'], 5): w(f"  {r}\n")
    if p['pgmptr']:
        w("pgms (pgmnum tilefile datafile diskside): " + ' '.join(str(r) for r in recs(d, p['pgmptr'], 4, (end('pgmptr') - p['pgmptr']) // 4)) + "\n")
    if p['exitptr']:
        w("exits (x y pgm tx ty): " + ' '.join(str(r) for r in recs(d, p['exitptr'], 5, (end('exitptr') - p['exitptr']) // 5)) + "\n")
    if p['genptr']:
        w("gen (x y type tile num):\n")
        for r in recs(d, p['genptr'], 5): w(f"  {r}\n")
    knpcs = recs(d, p['knpcptr'], 10) if p['knpcptr'] else []
    w("knpc (x y type tile num name appear disapp ifevent ifnevent):\n")
    for r in knpcs: w(f"  {r} name={name(r[5])!r}\n")
    if p['resids']:
        w("resids (name num appear disapp ifevent ifnevent):\n")
        for i, r in enumerate(recs(d, p['resids'], 6, (end('resids') - p['resids']) // 6)): w(f"  room{i} {r} name={name(r[0])!r}\n")
    if p['peopr']:
        w("peopr (word npc x): " + ' '.join(f"{name(r[0])}->{r[1]}" for r in recs(d, p['peopr'], 3)) + "\n")
    if p['newsr']:
        w(f"newsr: {list(d[p['newsr']:end('newsr')])}\n")
    if p['weathr']:
        w(f"weathr: {list(d[p['weathr']:end('weathr')])}\n")
    for k in ('lkdata', 'spetbl', 'treasptr', 'spdoors', 'hroomptr', 'locptr', 'locevptr', 'notyet0'):
        if p[k] and p[k] != p['roomptr'] and end(k) - p[k] > 1: w(f"{k}: {list(d[p[k]:end(k)])}\n")
    if p['hroomptr'] and p['hroomptr'] != p['roomptr']:
        w("hrooms (id grp reward amt map xy*4):\n")
        for r in recs(d, p['hroomptr'], 13, (end('hroomptr') - p['hroomptr']) // 13): w(f"  {r}\n")
    texts = cstrings(d, p['loctext'], end('loctext')) if p['loctext'] else []
    w(f"loctext ({len(texts)}):\n")
    for i, s in enumerate(texts): w(f"  {i}: {s}\n")
    return L, knpcs, words

def main(src, dst):
    os.makedirs(dst, exist_ok=True)
    allnpc = []
    for fn in sorted(os.listdir(src)):
        if not (fn.startswith('D') and fn.endswith('.MCV')): continue
        L = load_loc(os.path.join(src, fn))
        if not (L['ptr']['maps'] and len(L['locname']) >= 3 and all(c.isalnum() or c in " .'" for c in L['locname'])): continue
        with open(os.path.join(dst, fn[:-4] + '.txt'), 'w') as out:
            L, knpcs, words = dump(os.path.join(src, fn), out)
        for r in knpcs:
            allnpc.append((r[4], fn[:-4], L['locname'], r))
    with open(os.path.join(dst, 'npcs.txt'), 'w') as out:
        out.write("# KNPC placements by npc number: num file locname (x y type tile num name appear disapp ifevent ifnevent)\n")
        for num, fn, ln, r in sorted(allnpc): out.write(f"{num:3d} {fn} {ln:12s} {r}\n")

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
