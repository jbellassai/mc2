"""Resolve every door (ROOM record) of every location through the location's PGM list.
usage: doors.py ORIGDIR  -> one line per door: loc x y -> program/datafile room-id type"""
import os, sys
sys.path.insert(0, os.path.dirname(__file__))
from loc import load_loc
from locdump import recs

ROOMKIND = [(0x40, 0x47, 'inn'), (0x48, 0x5a, 'school'), (0x6c, 0x7b, 'job'), (0x7c, 0x7e, 'library'), (0x80, 0x82, 'lodge')]

def kind(pgm, rmid):
    if pgm != 5: return ''
    for lo, hi, k in ROOMKIND:
        if lo <= rmid <= hi: return k
    return 'store/tavern' if rmid < 0x40 or rmid >= 0x84 else '?'

def main(src):
    for f in sorted(os.listdir(src)):
        if not (f.startswith('D') and f.endswith('.MCV')): continue
        L = load_loc(os.path.join(src, f)); d = L['raw']; p = L['ptr']
        if not p['roomptr'] or not p['pgmptr'] or L['locnum'] == 255: continue
        ends = sorted(v for v in p.values() if v) + [len(d)]
        end = lambda k: next(e for e in ends if e > p[k])
        pgms = recs(d, p['pgmptr'], 4, (end('pgmptr') - p['pgmptr']) // 4)
        for x, y, pg, rmid, rtype in recs(d, p['roomptr'], 5):
            if pg >= len(pgms): print(f"{f} ({x},{y}) pgm-index {pg} out of range"); continue
            pn, tile, dfile, side = pgms[pg]
            print(f"{f[:3]} {L['locname']:11} ({x:3},{y:3}) -> P{pn:02} D{dfile:02} tile {tile:3} id {rmid:3} (0x{rmid:02x}) type {rtype:3} {kind(pn, rmid)}")

if __name__ == '__main__': main(sys.argv[1])
