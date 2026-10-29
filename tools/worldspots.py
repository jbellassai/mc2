"""Catalogue the world-map features stored in the region records R32-R47 (see docs/rules/locations.md, World map).
usage: worldspots.py ORIGDIR"""
import os, sys
sys.path.insert(0, os.path.dirname(__file__))
from loc import load_loc

MUSH = {0x33: 'Sermin', 0x34: 'Gonshi', 0x35: 'Nift', 0x36: 'Mirget', 0x37: 'Luffin', 0x38: 'Turpin', 0x3c: 'Loka'}

def main(src):
    kinds = load_loc(os.path.join(src, 'D04.MCV'))['raw'][0x44:0x44 + 30]   # D04 gwrds = item code per patch id
    for n in range(32, 48):
        L = load_loc(os.path.join(src, f'R{n}.MCV')); d = L['raw']; p = L['ptr']
        pg, ex = p['pgmptr'], p['exitptr']
        pgms = [tuple(d[pg + 4 * i:pg + 4 * i + 4]) for i in range((ex - pg) // 4)]
        prog = lambda i: f'P{pgms[i][0]:02} D{pgms[i][2]:02}' if i < len(pgms) else f'pgm?{i}'
        print(f'R{n} {L["locname"]!r}')
        o = p['roomptr']
        while d[o]:
            x, y, pi, rid, ty = d[o:o + 5]; o += 5
            extra = MUSH.get(kinds[rid], '?') if pgms[pi][0] == 4 else ''
            print(f'  feature ({x},{y}) {prog(pi)} id {rid} type {ty} {extra}')
        o = ex
        while d[o]:
            x, y, pi, tx, ty = d[o:o + 5]; o += 5
            print(f'  entrance ({x},{y}) {prog(pi)} -> ({tx},{ty})')
        o = p['locptr']; evs = []
        while d[o] != 0xff:
            r = d[o:o + 10]; o += 10
            if r[7] != 0xfe: evs.append(r[7])
            print(f'  spot ({r[0]},{r[1]}) {prog(r[2])} id {r[3]} type {r[4]} window ({r[5]},{r[6]}) ev {"always" if r[7] == 0xfe else r[7]} text {r[8]} icon {r[9]}')
        nev = max(evs + [-1]) + 1  # spot ev n = n-th 0xFF-terminated list of {event, tx}
        o, lists = p['locevptr'], []
        for _ in range(nev):
            e = d.index(0xff, o); lists.append(list(d[o:e])); o = e + 1
        if lists: print(f'  event lists {lists}')
        g, nw = p['gwrds'], p['newsr']
        guards = [tuple(d[g + 3 * i:g + 3 * i + 3]) for i in range(8)]
        print(f'  guards {[x for x in guards if x[0]]} groups {list(d[nw:nw + 8])}')

if __name__ == '__main__': main(sys.argv[1])
