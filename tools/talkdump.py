#!/usr/bin/env python3
"""Decode every NPC conversation script (P91 ovl_05e2 interpreter, docs/rules/dialogue.md).
usage: talkdump.py ORIGDIR OUTDIR  -> OUTDIR/Dnn.txt per location, OUTDIR/npcs.txt by NPC number
Script = entries `word resp [E ev alt | C need alt | S song]* 0`, 0xFF ends; words index the
C file's own word list (named NPCs, text ptr 1..2) or the location's gwrds (generic townsfolk, peopr → loctext)."""
import os, struct, sys, glob
sys.path.insert(0, os.path.dirname(__file__))
from loc import load_loc
from locdump import cstrings, recs

def decode(s, words, texts, chrmod=0):
    """yield (word, [lines]) for one script blob"""
    name = lambda i: words[i] if i < len(words) else f'?{i}'
    txt = lambda i: texts[i] if i < len(texts) else f'?{i}'
    pos = 0; out = []
    while pos < len(s) and s[pos] != 0xff:
        w = s[pos]; pos += 1
        if pos >= len(s): break
        r = s[pos]; pos += 1
        lines = []
        if r == 0xff:
            out.append((name(w), ['(ends the conversation)'])); continue
        lines.append(txt(r))
        while pos < len(s) and s[pos] != 0:
            c = s[pos]
            if c == 0x45 and pos + 2 < len(s):   # 'E' ev alt
                lines.append(f'  unless event {s[pos+1]} is set: {txt(s[pos+2])}'); pos += 3
            elif c == 0x43 and pos + 2 < len(s): # 'C' need alt
                lines.append(f'  if charm+tailor < {s[pos+1]}-{chrmod}: {txt(s[pos+2])}'); pos += 3
            elif c == 0x53 and pos + 1 < len(s): # 'S' song
                lines.append(f'  teaches song {s[pos+1]} (party learns it, 15 min)'); pos += 2
                break
            elif c == 0xff:
                break
            else:
                lines.append(f'  ?? byte {c:#x}'); pos += 1
        pos += 1
        out.append((name(w), lines))
    return out

def conv(root, n, cache={}):
    f = n >> 3
    if f not in cache:
        d = open(os.path.join(root, f'C{f:02d}.MCV'), 'rb').read()
        p = struct.unpack('<42H', d[:0x54])
        cache[f] = (d, p, d[p[0]:p[1]].decode('latin1').split('\0'), d[p[1]:p[2]].decode('latin1').split('\0')[:-1])
    d, p, texts, cwords = cache[f]
    sl = n & 7
    a, b = p[2 + sl], p[3 + sl] if sl < 7 else p[10]
    return d[a:b], texts, cwords

def main(src, dst):
    os.makedirs(dst, exist_ok=True)
    bynpc = {}
    for path in sorted(glob.glob(os.path.join(src, 'D[0-9][0-9].MCV'))):
        L = load_loc(path); d = L['raw']; p = L['ptr']
        if not (p['maps'] and len(L['locname']) >= 3 and all(c.isalnum() or c in " .'" for c in L['locname'])): continue
        ends = sorted(v for v in p.values() if v) + [len(d)]
        end = lambda k: next((e for e in ends if e > p[k]), len(d))
        words = cstrings(d, p['gwrds'], end('gwrds')) if p['gwrds'] else []
        texts = cstrings(d, p['loctext'], end('loctext')) if p['loctext'] else []
        fn = os.path.basename(path)[:3]
        with open(os.path.join(dst, fn + '.txt'), 'w') as o:
            o.write(f"# {fn} {L['locname']!r}  words: {' '.join(f'{i}:{w}' for i, w in enumerate(words))}\n")
            if p['peopr']:
                o.write('## townsfolk (peopr -> loctext)\n')
                for w, lines in decode(d[p['peopr']:end('peopr')], words, texts):
                    o.write(f'  {w}: ' + '\n'.join(lines) + '\n')
            if p['newsr']:
                o.write('## news (newsr: npctype, event|254=any, loctext)\n')
                for t, ev, tx in recs(d, p['newsr'], 3):
                    o.write(f"  type {t} {'' if ev == 254 else f'event {ev} '}: {texts[tx] if tx < len(texts) else tx}\n")
            nums = sorted({r[4] for r in recs(d, p['knpcptr'], 10)} | ({r[1] for r in recs(d, p['resids'], 6, (end('resids') - p['resids']) // 6)} if p['resids'] else set()))
            for n in nums:
                if n == 0 or n >= 0xfa: continue
                s, ctexts, cwords = conv(src, n)
                npcname = next((words[r[5]] for r in recs(d, p['knpcptr'], 10) if r[4] == n and r[5] < len(words)), '?')
                o.write(f'## npc {n} {npcname} (C{n>>3:02d} slot {n&7})\n')
                lines_out = []
                for w, lines in decode(s, cwords, ctexts):
                    lines_out.append(f'  {w}: ' + '\n'.join(lines))
                o.write('\n'.join(lines_out) + '\n')
                bynpc.setdefault(n, []).append((fn, L['locname'], npcname, lines_out))
    with open(os.path.join(dst, 'npcs.txt'), 'w') as o:
        for n in sorted(bynpc):
            for fn, loc, npcname, lines_out in bynpc[n]:
                o.write(f'# npc {n} {npcname} @ {fn} {loc}\n' + '\n'.join(lines_out) + '\n')

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
