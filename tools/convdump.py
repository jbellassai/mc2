#!/usr/bin/env python3
"""Dump Cnn.MCV conversation files: per-NPC trade skill, shop list, gift triggers.
usage: convdump.py ORIGDIR [Cnn ...]   (NPC number n lives in C(n>>3) slot n&7)
Layout (docs/formats.md, "Cnn.MCV"): 42 words of pointers (fixed up by adding the
buffer base), +0x54 trade skill[8], +0x5C no-buy flag[8], +0x64 unknown[8], text from +0x6C."""
import re, struct, sys, glob, os

def item_names(root):
    names = {}
    p = os.path.join(os.path.dirname(__file__), '..', 'docs', 'rules', 'items.md')
    for l in open(p):
        for m in re.finditer(r'\| ([0-9A-F]{2}) \| ([^|]+?) \|', l):
            names[int(m[1], 16)] = m[2].strip()
    return names

def dump(path, names):
    d = open(path, 'rb').read()
    p = struct.unpack('<42H', d[:0x54])
    base = int(os.path.basename(path)[1:3]) * 8
    txt = d[p[0]:p[1]].split(b'\0')
    def msg(n): return txt[n].decode('cp437', 'replace')[:60] if n < len(txt) else '?'
    print(f'== {os.path.basename(path)}  text {p[0]:#x}..{p[1]:#x}  skill {list(d[0x54:0x5c])}  nobuy {list(d[0x5c:0x64])}  x {list(d[0x64:0x6c])}')
    for n in range(8):
        shop = []
        o = p[26 + n]
        while d[o] != 0xff:
            it, a1, a2, b1, b2 = d[o:o + 5]
            shop.append(f'{names.get(it, hex(it))} pays {a1 * 100 + a2} / charges {b1 * 100 + b2}')
            o += 5
        gifts = []
        o = p[18 + n]
        while d[o] != 0xff:
            it, mn, m1, m2, ev = d[o:o + 5]
            gifts.append(f'{names.get(it, hex(it))} x{mn}: event {ev}, "{msg(m2)}" / too few: "{msg(m1)}"')
            o += 5
        if shop or gifts:
            print(f'  npc {base + n:3d} (slot {n}) skill {d[0x54 + n]} nobuy {d[0x5c + n]}')
            for s in shop: print('    shop:', s)
            for g in gifts: print('    gift:', g)

if __name__ == '__main__':
    root = sys.argv[1]
    names = item_names(root)
    files = [os.path.join(root, f + '.MCV') for f in sys.argv[2:]] or sorted(glob.glob(os.path.join(root, 'C[0-9][0-9].MCV')))
    for f in files: dump(f, names)
