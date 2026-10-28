"""Render every room interior reachable from a door, world-map feature or spot, plus every G-file chunk.
usage: render_rooms.py ORIGDIR OUTDIR  -> OUTDIR/Gnn_cc_Vtt.png per (map file, chunk, tileset) in use,
OUTDIR/sheets/Gnn_Vtt.png (all chunks), OUTDIR/rooms.txt (door -> room name -> image). See docs/formats.md, Room maps."""
import os, struct, sys
sys.path.insert(0, os.path.dirname(__file__))
from loc import load_loc, PTRS
from locdump import rooms
from mc2fmt import load_mct, Map
from render import render_map
from PIL import Image

BOUND = [0x40, 0x48, 0x6C, 0x7C, 0x80, 0x84, 0x90, 0x98, 0xA0, 0xA8, 0xBB, 0xC0, 0xC8, 0xD0, 0xD8]  # P05 0x2BA, P09 0x66

def subrec(src, dfile, rid):
    """The LOCTYPE record a room program uses: the whole Dnn file, or entry rid of a bank (word0 < 0x1F, P05 ovl_12bc)."""
    d = open(f'{src}/D{dfile:02d}.MCV', 'rb').read()
    k = struct.unpack_from('<H', d)[0]
    if k < 0x1F:
        if rid >= k: return None
        d = d[struct.unpack_from('<H', d, 2 + 2 * rid)[0]:]
    p = dict(zip(PTRS, struct.unpack_from('<20H', d)))
    return d, p, d[42:53].split(b'\0')[0].decode('latin1').rstrip()

def resolve(src, loc, pgmnum, dfile, rid, rtype):
    """-> (name, G file, chunk) or None. Follows P04/P05/P07/P08/P09 (`docs/formats.md`, Room maps)."""
    if rtype in (6, 7, 8, 9) or pgmnum in (6, 7):        # guarded dungeon room: HROOM of this level, G05
        d, p = loc['raw'], loc['ptr']
        o = p['hroomptr']
        while o + 13 <= len(d) and d[o] != 0xFF:
            if d[o] == rid: return f'dungeon room {rid}', 5, d[o + 4] & 0xF
            o += 13
        return None
    if pgmnum == 4: return 'mushroom patch', 0, None  # chunk = terrain under the party
    if pgmnum not in (5, 8, 9): return None
    r = subrec(src, dfile, rid)
    if r is None: return None
    d, p, name = r
    if p['maps'] >= len(d): return None
    m = p['maps']
    bank = struct.unpack_from('<H', open(f'{src}/D{dfile:02d}.MCV', 'rb').read())[0] < 0x1F
    if bank or pgmnum == 8: return name, d[m], d[m + 1]
    t = sum(b <= rid for b in BOUND); idx = rid - (BOUND[t - 1] if t else 0)
    if pgmnum == 5 and t == 2 and rid > 0x5B: idx -= 0x14   # P05 ovl_1315: late school ids are inns
    return name, d[m], d[m + 1 + idx]

def doors(src):
    """(where, x, y, pgmnum, tileset, dfile, rid, rtype) for every door / world-map feature / spot."""
    for f in sorted(os.listdir(src)):
        if not f.endswith('.MCV') or f[0] not in 'DR': continue
        L = load_loc(f'{src}/{f}'); d, p = L['raw'], L['ptr']
        if f == 'D06.MCV' or struct.unpack_from('<H', d)[0] < 0x1F or L['locnum'] == 255 or (L['mapsizex'], L['mapsizey']) == (11, 9): continue
        pg = p['pgmptr']; pgms = [tuple(d[pg + 4 * i:pg + 4 * i + 4]) for i in range((p['exitptr'] - pg) // 4)]
        where = f"{f[:3]} {L['locname']}"
        recs = [(x, y, pi, rid, ty) for x, y, pi, rid, ty in rooms(d, p['roomptr'])]
        if f[0] == 'R':
            o = p['locptr']
            while d[o] != 0xFF: recs.append((d[o], d[o + 1], d[o + 2], d[o + 3], 3)); o += 10
        for x, y, pi, rid, ty in recs:
            if ty == 2 and chr(pi) in 'xy' and chr(rid) in '+-' or pi >= len(pgms): continue
            pn, ts, df, _ = pgms[pi]
            yield L, where, x, y, pn, ts, df, rid, ty

def chunk(src, g, c):
    d = open(f'{src}/G{g:02d}E00.MCM', 'rb').read()
    return Map(11, 9, d[c * 101 + 2:c * 101 + 101])

def main(src, dst):
    os.makedirs(f'{dst}/sheets', exist_ok=True)
    tsets, used, lines = {}, {}, []
    T = lambda n: tsets.setdefault(n, load_mct(f'{src}/V{n:02d}.MCT'))
    for L, where, x, y, pn, ts, df, rid, ty in doors(src):
        if pn in (1, 2, 3): continue                     # leads to a map (world, town, dungeon level), not a room
        r = resolve(src, L, pn, df, rid, ty)
        if r is None: lines.append(f'{where:16} ({x:3},{y:3}) P{pn:02} D{df:02} id {rid:3}: unresolved'); continue
        name, g, c = r
        used.setdefault((g, ts), set())
        if c is None: lines.append(f'{where:16} ({x:3},{y:3}) P{pn:02} id {rid:3} {name}: sheets/G{g:02d}_V{ts:02d}.png'); continue
        used[(g, ts)].add(c)
        png = f'G{g:02d}_{c:02d}_V{ts:02d}.png'
        if not os.path.exists(f'{dst}/{png}'): render_map(chunk(src, g, c), T(ts)).save(f'{dst}/{png}')
        lines.append(f'{where:16} ({x:3},{y:3}) P{pn:02} D{df:02} id {rid:3} {name}: {png}')
    used.setdefault((0, 1), set())                       # wilderness arenas: G00 chunk = terrain, world tileset
    for g, ts in sorted(used):
        n = os.path.getsize(f'{src}/G{g:02d}E00.MCM') // 101
        ims = [render_map(chunk(src, g, c), T(ts)) for c in range(n)]
        w, h = ims[0].size; cols = 6
        sheet = Image.new('RGB', (cols * (w + 8), (n + cols - 1) // cols * (h + 8)), (40, 40, 40))
        for c, im in enumerate(ims): sheet.paste(im, (c % cols * (w + 8), c // cols * (h + 8)))
        sheet.save(f'{dst}/sheets/G{g:02d}_V{ts:02d}.png')
    open(f'{dst}/rooms.txt', 'w').write('\n'.join(lines) + '\n')
    print(f'{len(lines)} doors, {sum(1 for l in lines if "unresolved" in l)} unresolved, '
          f'{len([f for f in os.listdir(dst) if f.endswith(".png")])} room images, {len(used)} sheets')

if __name__ == '__main__': main(*sys.argv[1:3])
