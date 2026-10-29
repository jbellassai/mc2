"""Build the web port's data pack from the original files (decision 1). Never commit or publish the output.
usage: export_json.py ORIGDIR OUTDIR -> OUTDIR/locations/*.json, tiledata/Bnn.json, tilesets/Vnn.png, sprites/E0n.png, conversations/Cnn.json,
       blocks.json, rooms.json, sprites.json, comtxt.json, items.json, heroes.json,
       commands.json, npctypes.json, p90.json, p02text.json, p91text.json, p01.json, p05.json, p09.json, p92text.json, p97.json, p93text.json, p93.json, p89.json, v02.json, p08.json, assign.json, conds.json, companions.json, exetables.json, combat.json
Schema: docs/data_schema.md. Byte strings are lowercase hex; every list is in file order."""
import json, os, struct, sys
sys.path.insert(0, os.path.dirname(__file__))
from loc import PTRS
from mc2fmt import load_mct
from render import render_tileset
from mce import vga
from PIL import Image

def strings(b):
    return [s.decode('latin1') for s in b.split(b'\0')[:-1]] if b else []

def recs(b, size, stop=None):
    """Fixed-size records; stop = predicate on a record that ends the list (terminator not included)."""
    out = []
    for i in range(0, len(b) - size + 1, size):
        r = b[i:i + size]
        if stop and stop(r): break
        out.append(list(r))
    return out

def lists(b, size):
    """Per-room-index lists (P05 ovl_16fa skips idx 0xFF-terminated lists): records of `size` bytes, each list ended by 0xFF."""
    out, cur, i = [], [], 0
    while i < len(b):
        if b[i] == 0xFF: out.append(cur); cur = []; i += 1
        else: cur.append(list(b[i:i + size])); i += size
    return out

def script(b):
    """Conversation script (P91 ovl_05e2): entries `word resp cmd* 0`, 0xFF ends; cmd = 'E' ev alt | 'C' need alt | 'S' song."""
    out, i = [], 0
    while i + 1 < len(b) and b[i] != 0xFF:
        e = {'word': b[i], 'resp': b[i + 1], 'cmds': []}; i += 2
        if e['resp'] != 0xFF:
            while i < len(b) and b[i] not in (0, 0xFF):
                c = chr(b[i])
                if c == 'S': e['cmds'].append({'op': 'S', 'song': b[i + 1]}); i += 2
                elif c in 'EC' and i + 2 < len(b): e['cmds'].append({'op': c, 'arg': b[i + 1], 'alt': b[i + 2]}); i += 3
                else: raise ValueError(f'script byte {b[i]:#x} at {i}')
            i += 1
        out.append(e)
    return out

def conversation(d):
    """Cnn.MCV: text block, word list, and per-slot script, gifts, shop, greet/bye, trade skill, no-buy, unknown-word reply."""
    p = struct.unpack_from('<42H', d)
    seg = lambda i: d[p[i]:p[i + 1]]
    slots = []
    for k in range(8):
        gb = d[p[34 + k]:].split(b'\xff')[0] + b'\xff\xff'   # 0xFF-terminated {greet[, bye]}
        slots.append({'script': script(d[p[2 + k]:p[3 + k] if k < 7 else p[10]]),
                      'gifts': [dict(zip(('item', 'min', 'fewer', 'enough', 'event'), r)) for r in recs(seg(18 + k), 5, lambda r: r[0] == 0xFF)],
                      'shop': [{'item': r[0], 'pays': r[1] * 100 + r[2], 'charges': r[3] * 100 + r[4]} for r in recs(seg(26 + k), 5, lambda r: r[0] == 0xFF)],
                      'greet': gb[0], 'bye': gb[1], 'skill': d[0x54 + k], 'nobuy': d[0x5C + k], 'unknown': d[0x64 + k]})
    return {'texts': strings(seg(0)), 'words': d[p[1]:p[2]].split(b'\xff')[0].decode('latin1').split('\0')[:-1] or [], 'slots': slots}

def struct_fields(name):
    """(field, offset, kind, dims) for one struct of docs/structs.h (from the TDInfo export)."""
    import re
    txt = open(os.path.join(os.path.dirname(__file__), '..', 'docs', 'structs.h')).read()
    body = txt[txt.index(f'struct {name} {{'):]; body = body[:body.index('};')]
    out = []
    for m in re.finditer(r'^\s+(.+?)\s+(\w+)\s+/\*\s*\+\s*(\d+)', body, re.M):
        typ, field, off = m.group(1), m.group(2), int(m.group(3))
        dims = [int(x) for x in re.findall(r'\[(\d+)\]', typ)]
        kind = 'str' if typ.startswith('char[') else 'u16' if 'int' in typ else 'u8'
        out.append((field, off, kind, dims))
    return out

def decode_struct(d, fields):
    obj = {}
    for field, off, kind, dims in fields:
        if kind == 'str': obj[field] = d[off:off + dims[0]].split(b'\0')[0].decode('latin1'); continue
        size = 2 if kind == 'u16' else 1
        n = 1
        for x in dims: n *= x
        vals = list(struct.unpack_from(f'<{n}{"H" if size == 2 else "B"}', d, off))
        if not dims: obj[field] = vals[0]
        elif len(dims) == 1: obj[field] = vals
        else: obj[field] = [vals[i:i + dims[1]] for i in range(0, n, dims[1])]
    return obj

def tables(d):
    """The 20 header pointers and each sub-table's bytes, bounded by the next larger pointer.
    A pointer equal to roomptr (other than roomptr itself) marks an unused table (locations.md)."""
    p = dict(zip(PTRS, struct.unpack_from('<20H', d)))
    ends = sorted(set(v for v in p.values() if v)) + [len(d)]
    t = {}
    for k, v in p.items():
        if not v or v >= len(d) or (k != 'roomptr' and v == p['roomptr']): t[k] = b''; continue
        t[k] = d[v:next(e for e in ends if e > v)]
    return p, t

def location(d, kind):
    p, t = tables(d)
    n = d[p['maps'] - 1] if p['maps'] else 0xFF
    n = 0 if n == 0xFF else n
    m = p['maps']
    L = {'kind': kind, 'locnum': d[40], 'roomno': d[41], 'name': d[42:53].split(b'\0')[0].decode('latin1').rstrip(),
         'lcharm': d[53], 'mapsize': [d[54], d[55]], 'doorstn': d[56], 'locdiff': d[57], 'pearlsw': d[58], 'greet': list(d[59:62]),
         'pointers': [p[k] for k in PTRS], 'tables': {k: v.hex() for k, v in t.items()},
         'blocks': [{'block': d[m + i], 'tileset': d[m + n + i], 'x': d[m + 2 * n + i], 'y': d[m + 3 * n + i]} for i in range(n)],
         'words': strings(t['gwrds']), 'texts': strings(t['loctext'])}
    if kind == 'room':
        L['roommap'] = {'g': t['maps'][0], 'chunks': list(t['maps'][1:])} if t['maps'] else None
    L['doors'] = [dict(zip(('x', 'y', 'pgm', 'id', 'type'), r)) for r in recs(t['roomptr'], 5, lambda r: r[0] == 0)]
    L['pgms'] = [dict(zip(('program', 'tileset', 'datafile', 'disk'), r)) for r in recs(t['pgmptr'], 4)]
    if kind == 'room':   # one list per room index: exits {x,y,pgm,tx,ty,datafile}, townsfolk, named NPCs
        L['exits'] = [[dict(zip(('x', 'y', 'pgm', 'tx', 'ty', 'datafile'), r)) for r in l] for l in lists(t['exitptr'], 6)]
        L['townsfolk'] = [[dict(zip(('x', 'y', 'type', 'tile', 'num'), r)) for r in l] for l in lists(t['genptr'], 5)]
        L['npcs'] = [[dict(zip(('x', 'y', 'type', 'tile', 'num', 'name', 'appear', 'disappear', 'ifevent', 'ifnevent'), r))
                      for r in l] for l in lists(t['knpcptr'], 10)]
    else:
        L['exits'] = [dict(zip(('x', 'y', 'pgm', 'tx', 'ty'), r)) for r in recs(t['exitptr'], 5, lambda r: r[0] in (0, 0xFF))]
    if kind == 'region': return L
    if kind != 'room':
        L['townsfolk'] = [dict(zip(('x', 'y', 'type', 'tile', 'num'), r)) for r in recs(t['genptr'], 5, lambda r: r[0] == 0xFF)]
        L['npcs'] = [dict(zip(('x', 'y', 'type', 'tile', 'num', 'name', 'appear', 'disappear', 'ifevent', 'ifnevent'), r))
                     for r in recs(t['knpcptr'], 10, lambda r: r[0] == 0xFF)]
    L['residents'] = [dict(zip(('name', 'num', 'appear', 'disappear', 'ifevent', 'ifnevent'), r)) for r in recs(t['resids'], 6)]
    L['script'] = script(t['peopr'])   # generic townsfolk conversation (dialogue.md): words = `words`, responses = `texts`
    L['news'] = [dict(zip(('npctype', 'event', 'text'), r)) for r in recs(t['newsr'], 3, lambda r: r[0] == 0xFF)]
    if kind == 'level':
        L['look'] = [dict(zip(('x', 'y', 'text'), r)) for r in recs(t['lkdata'], 3, lambda r: r[0] == 0)]
        L['spots'] = [dict(zip(('x', 'y', 'type', 'd1', 'd2', 'd3'), r)) for r in recs(t['spetbl'], 6, lambda r: r[0] == 0)]
        L['keydoor'] = [dict(zip(('unused', 'x', 'y', 'newtile', 'text'), r)) for r in recs(t['spdoors'], 5, lambda r: r[0] == 0xFF)]
        L['hrooms'] = [{'id': r[0], 'group': r[1], 'reward': r[2], 'amount': r[3], 'map': r[4],
                        'xy': list(struct.unpack_from('<4H', bytes(r), 5))} for r in recs(t['hroomptr'], 13, lambda r: r[0] == 0xFF)]
    return L

def entries(src):
    """(name, bytes, kind) for every location record: plain Dnn files, bank entries Dnn_r, regions Rnn."""
    for f in sorted(os.listdir(src)):
        if not f.endswith('.MCV') or f[0] not in 'DR' or f == 'D06.MCV': continue
        d = open(f'{src}/{f}', 'rb').read(); k = struct.unpack_from('<H', d)[0]
        if f[0] == 'R':
            if f != 'R90.MCV': yield f[:3], d, 'region'
            continue
        if k < 0x1F:
            offs = struct.unpack_from(f'<{k}H', d, 2)
            for r, o in enumerate(offs):
                yield f'{f[:3]}_{r:02d}', d[o:(offs[r + 1] if r + 1 < k else len(d))], 'room'
            continue
        kind = 'room' if (d[54], d[55]) == (11, 9) else 'world' if f == 'D01.MCV' else 'level'
        yield f[:3], d, kind

def tiledata(d):
    p = struct.unpack_from('<6H', d)
    seg = lambda i: d[p[i]:(p[i + 1] if i < 5 else len(d))]
    walk = seg(2).split(b'\xff') + [b'']                     # list 2 is absent in B04, B05, B61
    return {'names': strings(seg(0)), 'nameindex': list(seg(1)), 'walkable': list(walk[0]), 'walkable_los': list(walk[1]),
            'anim': seg(3).hex(), 'doors': seg(4).hex(), 'colors': list(seg(5))}

def unpack_ctile(b):
    """Creature tile RLE (_UnpackTile): c >= 0x80 -> next byte repeated c-0x7F times, else c+1 literal bytes; 128 bytes out."""
    out, i = bytearray(), 0
    while len(out) < 128:
        c = b[i]; i += 1
        if c >= 0x80: out += bytes([b[i]]) * (c - 0x7F); i += 1
        else: out += b[i:i + c + 1]; i += c + 1
    return bytes(out[:128])

def sprites(src, dst, palette, cols=32):
    """E0n.MCI (u16 offsets into E0n.MCC, 0xFFFF = none) -> sprites/E0n.png, tile k at cell k, colour 2 transparent."""
    from PIL import Image
    counts = {}
    for n in range(4):
        idx = open(f'{src}/E{n:02d}.MCI', 'rb').read(); dat = open(f'{src}/E{n:02d}.MCC', 'rb').read()
        offs = struct.unpack(f'<{len(idx) // 2}H', idx)
        im = Image.new('RGBA', (cols * 16, (len(offs) + cols - 1) // cols * 16))
        for k, o in enumerate(offs):
            if o >= len(dat): continue
            t = Image.new('RGBA', (16, 16))
            t.putdata([(0, 0, 0, 0) if c == 2 else palette[c] + (255,) for b in unpack_ctile(dat[o:o + 129]) for c in (b >> 4, b & 15)])
            im.paste(t, (k % cols * 16, k // cols * 16))
        im.save(f'{dst}/sprites/E{n:02d}.png'); counts[f'E{n:02d}'] = len(offs)
    exe = open(f'{src}/MC2.EXE', 'rb').read(); ds = 0x1800 + 0x15B50
    atc, nat = exe[ds + 0x373A:ds + 0x3744], exe[ds + 0x3744:ds + 0x37C4]   # _animtilecount, _npcanimtype
    npc, k = [], 0
    for t in nat: npc.append({'start': k, 'frames': atc[t]}); k += atc[t]
    return {'columns': cols, 'counts': counts, 'npc': npc}

ADPCM4 = ([0, 1, 2, 3, 4, 5, 6, 7, 0, -1, -2, -3, -4, -5, -6, -7, 1, 3, 5, 7, 9, 11, 13, 15, -1, -3, -5, -7, -9, -11, -13, -15,
           2, 6, 10, 14, 18, 22, 26, 30, -2, -6, -10, -14, -18, -22, -26, -30, 4, 12, 20, 28, 36, 44, 52, 60, -4, -12, -20, -28, -36, -44, -52, -60],
          [0, 0, 0, 0, 0, 16, 16, 16] * 2 + [-16, 0, 0, 0, 0, 16, 16, 16] * 4 + [-16, 0, 0, 0, 0, 0, 0, 0] * 2)
ADPCM3 = ([0, 1, 2, 3, 0, -1, -2, -3, 1, 3, 5, 7, -1, -3, -5, -7, 2, 6, 10, 14, -2, -6, -10, -14, 4, 12, 20, 28, -4, -12, -20, -28,
           5, 15, 25, 35, -5, -15, -25, -35],
          [0, 0, 0, 8] * 2 + [-8, 0, 0, 8] * 6 + [-8, 0, 0, 0] * 2)

def voc_to_wav(v, out):
    """Creative Voice File: blocks {type, u24 length}; 1 = {time constant, codec, data}, 2 = more data, 3 = silence
    {u16 samples − 1, time constant}, 6/7 = repeat (played once). Codecs 0 8-bit unsigned PCM, 1 4-bit and 2 2.6-bit
    Creative ADPCM: the first byte is the reference sample (decoders as DOSBox's sblaster.cpp)."""
    import wave
    assert v[:19] == b'Creative Voice File'
    p, rate, codec, pcm, st = struct.unpack_from('<H', v, 0x14)[0], 11025, 0, bytearray(), [128, 0]
    def adpcm(data, table, codes):
        st[0] = data[0]; pcm.append(data[0])
        for b in data[1:]:
            for c in codes(b):
                n = max(0, min(len(table[0]) - 1, c + st[1]))
                st[0] = max(0, min(255, st[0] + table[0][n])); st[1] += table[1][n]
                pcm.append(st[0])
    def data(d):
        if codec == 0: pcm.extend(d)
        elif codec == 1: adpcm(d, ADPCM4, lambda b: (b >> 4, b & 15))
        else: adpcm(d, ADPCM3, lambda b: (b >> 5, (b >> 2) & 7, (b & 3) << 1))
    while p < len(v) and v[p] != 0:
        t, ln = v[p], int.from_bytes(v[p + 1:p + 4], 'little')
        if t == 1: rate, codec, st[1] = round(1e6 / (256 - v[p + 4])), v[p + 5], 0; assert codec <= 2; data(v[p + 6:p + 4 + ln])
        elif t == 2: data(v[p + 4:p + 4 + ln])
        elif t == 3: pcm.extend(b'\x80' * (struct.unpack_from('<H', v, p + 4)[0] + 1))
        p += 4 + ln
    with wave.open(out, 'wb') as w:
        w.setnchannels(1); w.setsampwidth(1); w.setframerate(rate); w.writeframes(bytes(pcm))

def main(src, dst):
    for sub in ('locations', 'tiledata', 'tilesets', 'sprites'): os.makedirs(f'{dst}/{sub}', exist_ok=True)
    dump = lambda path, obj: json.dump(obj, open(path, 'w'), indent=1, ensure_ascii=False)
    n, index = 0, []
    for name, d, kind in entries(src):
        L = location(d, kind)
        dump(f'{dst}/locations/{name}.json', L); n += 1
        if kind != 'room': index.append({'id': name, 'name': L['name'].strip(), 'kind': kind})
    dump(f'{dst}/locations/index.json', index)                # the dev scenario editor's location list
    for f in sorted(os.listdir(src)):
        if f[0] == 'B' and f.endswith('.MCV'): dump(f'{dst}/tiledata/{f[:3]}.json', tiledata(open(f'{src}/{f}', 'rb').read()))
        if f[0] == 'V' and f.endswith('.MCT'):
            render_tileset(load_mct(f'{src}/{f}')).save(f'{dst}/tilesets/{f[:3]}.png')
    blocks = {}
    for f in sorted(os.listdir(src)):
        if f[0] == 'M' and f.endswith('.MCM'):
            d = open(f'{src}/{f}', 'rb').read()
            if d[:2] == b'**' and len(d) >= 2 + 42 * 42: blocks[f[:6]] = d[2:2 + 42 * 42].hex()   # a block is always the first 42×42
    dump(f'{dst}/blocks.json', blocks)
    rooms = {}
    for f in sorted(os.listdir(src)):
        if f[0] == 'G' and f.endswith('.MCM'):
            d = open(f'{src}/{f}', 'rb').read()
            rooms[f[:3]] = [d[i + 2:i + 101].hex() for i in range(0, len(d) - 100, 101) if d[i:i + 2] == b'\x0b\x09']
    dump(f'{dst}/rooms.json', rooms)
    dump(f'{dst}/sprites.json', sprites(src, dst, load_mct(f'{src}/V01.MCT').palette[:16]))
    os.makedirs(f'{dst}/conversations', exist_ok=True)
    for f in sorted(os.listdir(src)):
        if f[0] == 'C' and f[1:3].isdigit() and f.endswith('.MCV'):
            dump(f'{dst}/conversations/{f[:3]}.json', conversation(open(f'{src}/{f}', 'rb').read()))
    exe = open(f'{src}/MC2.EXE', 'rb').read(); ds = 0x1800 + 0x15B50
    dump(f'{dst}/items.json', [x.decode('latin1') for x in exe[ds + 0x3BB7:ds + 0x4000].split(b'\0')[:0x5D]])   # _w_objects
    p81, hero = open(f'{src}/P81.MCO', 'rb').read(), struct_fields('HERO')
    dump(f'{dst}/heroes.json', [decode_struct(p81[0x82D + 220 * i:], hero) for i in range(5)])   # new-game profiles A-E
    r90 = open(f'{src}/R90.MCV', 'rb').read()   # companions 1-31 (h_orinum), the new game's _member6.. records
    dump(f'{dst}/companions.json', [decode_struct(r90[220 * i:], hero) for i in range(len(r90) // 220)])
    dump(f'{dst}/npctypes.json', [x.decode('latin1') for x in exe[ds + 0x2296:ds + 0x2471].split(b'\0')[:60]])   # Look names by type
    dump(f'{dst}/commands.json', [x.decode('latin1') for x in exe[ds + 0x2471:ds + 0x2800].split(b'\0')[:51]])   # _menucommands
    p90 = open(f'{src}/P90.MCO', 'rb').read()   # trade: {step, div} per item at 0x038, {item, lot} pairs at 0x0F2 (economy.md)
    lots = p90[0xF2:p90.index(0xFF, 0xF2)]
    dump(f'{dst}/p90.json', {'haggle': [[p90[0x38 + 2 * i], p90[0x39 + 2 * i]] for i in range(0x5D)],
                             'lots': {str(lots[i]): lots[i + 1] for i in range(0, len(lots) - 1, 2)},
                             # Give (ovl_037c/ovl_0621): the Orb's texts (file 0x113), the Marked Ones (0x10B) and their _events+4 bits (0x10E);
                             # FAR_OK2GIVE's items no one gives away (FFFAR file 0x2235, 8 bytes)
                             'orb': {'texts': [x.decode('latin1') for x in p90[0x113:0x113 + 1200].split(b'\0')[:19]],
                                     'marked': list(p90[0x10B:0x10E]), 'bits': list(p90[0x10E:0x111])},
                             'keep': list(open(f'{src}/FFFAR.MCO', 'rb').read()[0x2235:0x223D])})
    p02 = open(f'{src}/P02.MCO', 'rb').read()
    dump(f'{dst}/p02text.json', [x.decode('latin1') for x in p02[0x67:0x28A].split(b'\0')[:17]])   # town program's own texts
    p08 = open(f'{src}/P08.MCO', 'rb').read()   # quest scene rooms (rules/quest_scenes.md)
    gifts = p08[0x1092:p08.index(0xFF, 0x1092)]
    dump(f'{dst}/p08.json', {'texts': [x.decode('latin1') for x in p08[0x123:0x500].split(b'\0')[:18]],
                             'gifts': [[gifts[i], gifts[i + 1]] for i in range(0, len(gifts), 2)],   # King Rebnard (OV_0x1192)
                             'ghosts': {'npcs': list(p08[0xBA:0xBD]), 'scrolls': list(p08[0xB7:0xBA]),
                                        'paras': [p08[0xBD + 2 * i:0xBF + 2 * i].decode('latin1') for i in range(3)],
                                        'spoken': list(p08[0xB1:0xB4]), 'rested': list(p08[0xB4:0xB7])},
                             'base': [[w & 0xFF, w >> 8] for w in struct.unpack_from('<16H', p08, 0x83)],   # by exit-side flags / 2
                             'side': {'odd': list(p08[0xA3:0xAC]), 'even': list(p08[0xAC:0xB1])},   # by _lastdir
                             'junk': list(p08[0xE49:p08.index(b'\0\0', 0xE49)]),   # dropped to make room for a gift (ovl_0e86)
                             'banquet': list(p08[0x97C:0x97C + 33])})   # epilogue (ovl_099d, cs:0xA7C): the banquet room's line per companion
    v02 = open(f'{src}/V02.MCO', 'rb').read()   # town spells (rules/spells.md)
    dump(f'{dst}/v02.json', {'disguise': {'towns': list(v02[0xCBA:0xCBD]), 'texts': [x.decode('latin1') for x in v02[0x07:0x60].split(b'\0')[:2]]},   # INT60_10
                              'hroomtype': {'ids': list(v02[0xE19:0xE27]), 'types': list(v02[0xE27:0xE35])},   # INT60_12: prison 1, candles 2-5, Vankruh 6
                             'vision': {'ids': list(v02[0x8C:0x9C]), 'texts': list(v02[0x9C:0xAC])},   # door id bands → comtxt
                             'sense': [struct.unpack_from('<H', v02, 0x7FE + 2 * i)[0] for i in range(16)]})   # direction by flags
    p89 = open(f'{src}/P89.MCO', 'rb').read()   # the Teleport picker (rules/spells.md)
    dump(f'{dst}/p89.json', {'tiers': list(p89[0x09:0x0E]), 'x0': list(p89[0x10:0x15]), 'y0': list(p89[0x15:0x1A]),
                             'x1': list(p89[0x1A:0x1F]), 'y1': list(p89[0x1F:0x24]),
                             'rects': [[p89[0x10C + i], p89[0x10F + i], p89[0x112 + i], p89[0x115 + i]] for i in range(p89[0x10A])]})
    p93 = open(f'{src}/P93.MCO', 'rb').read()
    dump(f'{dst}/p93text.json', [x.decode('latin1') for x in p93[0x3D:0x254].split(b'\0')])   # camp texts (rules/camp.md)
    sb = lambda b: b - 256 if b > 127 else b
    dump(f'{dst}/p93.json', {'hunt': {'terrain': [sb(b) for b in p93[0x03:0x0D]], 'weather': [sb(b) for b in p93[0x0D:0x19]]}})   # hunting odds, -1 = impossible
    dump(f'{dst}/conds.json', [x.decode('latin1') for x in exe[ds + 0x4204:ds + 0x4300].split(b'\0')[:12]])   # _w_conds: OK, then cond1<<8|cond2 bits 15…5
    p97 = open(f'{src}/P97.MCO', 'rb').read()
    p92 = open(f'{src}/P92.MCO', 'rb').read()
    dump(f'{dst}/p92text.json', [x.decode('latin1') for x in p92[0x39:0xC4].split(b'\0')[:2]])   # hireling payday texts
    dump(f'{dst}/p97.json', {'texts': [x.decode('latin1') for x in p97[0x17:0x1BA].split(b'\0')[:7]],   # hire / dismiss texts
                             'events': dict(zip(map(str, p97[0x68E:0x69D]), p97[0x69D:0x6AC]))})      # companion → event bit (ovl_06bc)
    p91 = open(f'{src}/P91.MCO', 'rb').read()   # small talk: {weather, line} pairs at 0x48, 0xFF, then the lines
    end = p91.index(0xFF, 0x48); pairs = p91[0x48:end]
    dump(f'{dst}/p91text.json', {'lines': [x.decode('latin1') for x in p91[end + 1:0x2E0].split(b'\0')[:16]],
                                  'weather': [[pairs[i], pairs[i + 1]] for i in range(0, len(pairs) - 1, 2)]})
    p01 = open(f'{src}/P01.MCO', 'rb').read()   # world map (rules/time_weather.md, World-map step cost; locations.md, World map)
    s8 = lambda o, n: [b - 256 if b > 127 else b for b in p01[o:o + n]]
    # terraintime / terrainenergy run to 14 entries: a swimmer's step indexes them with river 12 / water 13 and reads the
    # bytes that follow each table (skills.md, swim)
    dump(f'{dst}/p01.json', {'terraintime': list(p01[0x276:0x284]), 'weathertime': s8(0x280, 12), 'terrainenergy': list(p01[0x298:0x2A6]),
                             'swimweather': list(p01[0x2F6:0x302]),   # ovl_194e, by weather
                             'clothing': [list(p01[0x2A2 + 12 * k:0x2AE + 12 * k]) for k in range(7)],   # rows 0x2B-0x30, then none
                             'regions': [list(p01[0x236 + 4 * k:0x23A + 4 * k]) for k in range(16)],    # {x0,y0,x1,y1}, first match
                             'patchtiles': list(p01[0x36A:0x374]),   # mushroom-patch tileset by terrain class (ovl_09bf)
                             # patrols (encounters.md): 8 start squares per region, respawn interval in months per region,
                             # the step tables (ovl_17c0 / ovl_18c1): 8 directions, the two side steps per direction, wander order
                             'patrols': [list(p01[0x136 + 2 * k:0x138 + 2 * k]) for k in range(128)],
                             'respawn': list(p01[0x32A:0x33A]),
                             'steps': {k: [s8(o + 2 * i, 2) for i in range(8)] for k, o in (('dirs', 0x1790), ('side1', 0x17A0), ('side2', 0x17B0))}
                                      | {'order': [b // 2 for b in p01[0x18B7:0x18C1]]},
                             # ships (ships.md): sailing ticks by weather (+4), the six captains' daily rates and home ports
                             'ships': {'weather': s8(0x28C, 12), 'rate': list(p01[0x34A:0x350]),
                                       'homex': list(p01[0x350:0x356]), 'homey': list(p01[0x356:0x35C])}})
    p09 = open(f'{src}/P09.MCO', 'rb').read()   # special rooms (rules/special_rooms.md)
    dump(f'{dst}/p09.json', {'pieces': list(p09[0x4B:0x50]),      # teleportal pieces (items) and their pedestal tiles
                             'piecetiles': list(p09[0x50:0x55]),
                             'altars': list(p09[0x3A:0x3D]),      # altar tiles (world temples, ovl_1413)
                             'icons': list(p09[0x3D:0x45]),       # icon name indexes, by god (statue look)
                             'wake': list(p09[0xC86:0xC8E]),      # members checked for a missing blessing, by god
                             'offer': [x.decode('latin1') for x in p09[0x92:0xA1].split(b'\0')[:2]],   # %o for Balene / Fronnoxx
                             'texts': [x.decode('latin1') for x in p09[0xFB:0x1FB].split(b'\0')[:6]]})
    p81 = open(f'{src}/P81.MCO', 'rb').read()   # new game (rules/new_game.md): string table from 0x15, string 40 = intro scenes
    parts = p81[0x15:0x7B1].split(b'\0')
    scenes = [list(x) for x in parts[40].split(b'\xff')[:5]]
    dump(f'{dst}/p81.json', {'texts': [x.decode('latin1') for x in parts[:40]], 'scenes': scenes})
    p88, p92 = open(f'{src}/P88.MCO', 'rb').read(), open(f'{src}/P92.MCO', 'rb').read()   # assignments (rules/assignments.md)
    words = lambda d, a, n: [x.decode('latin1') for x in d[a:].split(b'\0')[:n]]
    ass, start, o = struct_fields('ASSIGNMENT'), [], 0x167F   # P81 init: 25-byte records until 0xFF
    while p81[o] != 0xFF: start.append(decode_struct(p81[o:], ass)); o += 25
    dump(f'{dst}/assign.json', {
        'start': start, 'menu': words(p88, 6, 4), 'texts': words(p88, 0x2D9, 58),
        'dests': words(p88, 0x24, 16), 'destxy': [list(p88[0xAB + 3 * i:0xAE + 3 * i]) for i in range(16)],   # {room, x, y}
        'places': words(p88, 0xDB, 25), 'locplace': list(p88[0x1EE:0x24B]), 'homes': list(p88[0x24B:0x26B]),
        'jail': list(p88[0xDBD:0xDC5]),   # NPCs 5, 10, 30, 28 / events 40, 42, 43, 44 (the same as P07's rescue table)
        'rects': [list(p92[0xC2 + 4 * i:0xC6 + 4 * i]) for i in range(16)],
        'cands': [list(p92[0x64E + 4 * i:0x652 + 4 * i]) for i in range(16)],
        'prisons': {k: list(p92[0x68E + 9 * i:0x697 + 9 * i]) for i, k in enumerate(('id', 'loc', 'x', 'y'))},
        'rescue': open(f'{src}/P07.MCO', 'rb').read()[0x539:].split(b'\0')[0].decode('latin1')})
    p02 = open(f'{src}/P02.MCO', 'rb').read()   # special spots (rules/locations.md, Special spots)
    v02 = open(f'{src}/V02.MCO', 'rb').read()
    dump(f'{dst}/spots.json', {'ambush': {'ids': list(p02[0x1743:0x1749]), 'events': list(p02[0x1749:0x174F])},
                               'remarks': {'ids': list(v02[0xBDB:0xBF6]), 'events': list(v02[0xBF6:0xC11]), 'locspecs': list(v02[0xC11:0xC2C])}})
    p07 = open(f'{src}/P07.MCO', 'rb').read()   # dungeon rooms (rules/locations.md): chest/fountain texts, trap bits
    dump(f'{dst}/p07.json', {'texts': [x.decode('latin1') for x in p07[0x806:0x980].split(b'\0')[:15]], 'trap': list(p07[0x804:0x806]),
                             'doorx': list(p07[3:11]), 'doory': list(p07[11:19])})   # door n squares: (x[2n+k], y[2n+k])
    p04 = open(f'{src}/P04.MCO', 'rb').read()   # mushroom patches (rules/locations.md), lists by kind = item − 0x33
    dump(f'{dst}/p04.json', {'amount': list(p04[0x72:0x7C]), 'icon': list(p04[0x7C:0x86]),   # picked per mushroom, E00 icon
                             'x': list(p04[0x88:0x97]), 'y': list(p04[0x97:0xA6])})          # the 15 growing places
    p05 = open(f'{src}/P05.MCO', 'rb').read()   # service rooms (rules/services.md); lists indexed by room id − kind base
    u8 = lambda o, n: list(p05[o:o + n])
    v05 = open(f'{src}/V05.MCO', 'rb').read()    # library books: AddScrap counts NUL-terminated strings from V05 offset 7
    dump(f'{dst}/p05.json', {
        'leave': u8(0xCD, 9),   # per _rmtyp: room text asked when leaving with a pupil, 0xFF = comtxt 0x23
        'inn': {'price': u8(0x283, 8)},
        'school': {'skill': u8(0x149, 19), 'cost': [struct.unpack_from('<H', p05, 0x4D + 2 * i)[0] for i in range(0x48, 0x5B)],
                   'days': u8(0x125, 19), 'gain': u8(0x16D, 19), 'cap': [u8(0x17F + 6 * k, 6) for k in range(19)]},  # gain[18] reads past the table (sic)
        'job': {'trade': u8(0x273, 16)},
        'library': {'subjects': [u8(0x1F7 + 5 * k, 5) for k in range(3)], 'research': u8(0x20B, 15), 'days': u8(0x21F, 15),
                    'task': u8(0x233, 15), 'lists': [list(x) for x in p05[0x28B:0x2B9].split(b'\0')],
                    'texts': [x.decode('latin1') for x in v05[7:].split(b'\0')[:48]]},
        'lodge': {'mask': u8(0x247, 3), 'cost': 200}})
    dump(f'{dst}/exetables.json', {   # small EXE rule tables (rules/items.md, time_weather.md)
        'hungerhours': list(exe[ds + 0x3AA8:ds + 0x3AAE]),                                      # HUNGERHOURS by race
        'nousetext': list(exe[ds + 0x2D9A:ds + 0x2D9A + 0x5C]),                                # _NoUse comtxt per item
        'weathers': [x.decode('latin1') for x in exe[ds + 0x424E:ds + 0x4300].split(b'\0')[:12]],   # _w_weather
        'lootvalues': list(struct.unpack_from('<93H', exe, ds + 0x2E72)),                      # item values (economy.md)
        'useall': [i + 0x31 for i in range(32) if struct.unpack_from('<H', exe, ds + 0x8AE + 2 * i)[0]],   # _AllDoit asks
        # _SetTxtToD: the time-of-day words (morning … night) and TODWORDS, the word by hour
        'attribs': [x.decode('latin1') for x in exe[ds + 0x3AAE:ds + 0x3C00].split(b'\0')[:29]],   # _w_attrib + _w_skills, by HERO offset − 13
        'speltim': list(exe[ds + 0x2B8F:ds + 0x2BB9]),   # _speltim: learn ticks per spell (_LrnTim)
        'tod': {'words': [x.decode('latin1') for x in exe[ds + 0x41E0:ds + 0x4204].split(b'\0')[:5]], 'hour': list(exe[ds + 0x38F2:ds + 0x390A])}})
    # Combat (rules/combat.md, encounters.md): monsters by code − 5, groups by number − 60, weapons by item − 9.
    p96 = open(f'{src}/P96.MCO', 'rb').read()
    p95 = open(f'{src}/P95.MCO', 'rb').read()
    v06 = open(f'{src}/V06.MCO', 'rb').read()
    d06 = open(f'{src}/D06.MCV', 'rb').read()
    ptr = struct.unpack_from('<14H', d06)   # D06 header words are file offsets
    names = [x.decode('latin1') for x in exe[ds + 0x40A4:ds + 0x4204].split(b'\0')[:37]]   # _w_monstrs
    def monster(k):
        r = exe[ds + 0x308E + 23 * k:ds + 0x308E + 23 * k + 23]
        return {'name': names[k], 'hp': struct.unpack_from('<H', r)[0], 'shield': r[2], 'weapon': r[3], 'armor': r[4],
                'bravery': r[5], 'str': r[6], 'dex': r[7], 'agi': r[8], 'res': r[9], 'int': r[10], 'wskl': r[11], 'mskl': r[12],
                'spells': list(r[13:16]), 'tile': struct.unpack_from('<H', r, 20)[0], 'anim': r[22],
                'leader': p96[0x39 + 5 + k], 'undead': p96[0x62 + 5 + k]}
    def weapon(k):
        r = exe[ds + 0x2CF6 + 9 * k:ds + 0x2CF6 + 9 * k + 9]
        hl = struct.unpack_from('<H', r, 7)[0]
        return {'minst': r[0], 'basedam': r[1], 'type': r[2], 'unbreakable': r[3], 'stbonus': r[4], 'sklbonus': r[5],
                'race': r[6], 'hitlist': list(exe[ds + hl:exe.index(b'\xff', ds + hl)]) if hl else []}
    dump(f'{dst}/combat.json', {
        'monsters': [monster(k) for k in range(37)],
        'groups': [list(exe[ds + 0x340B + 5 * k:ds + 0x3410 + 5 * k]) for k in range(163)],   # {count, m0..m3}
        'weapons': [weapon(k) for k in range(22)],
        'setupxy': list(open(f'{src}/P81.MCO', 'rb').read()[0x162F:0x165F]),   # 24 x, 24 y: formation f member m at 6f+m
        'ranges': {'x': [list(p96[0x19 + 2 * k:0x1B + 2 * k]) for k in range(8)],      # sides 6-9 melee, then casters
                   'y': [list(p96[0x29 + 2 * k:0x2B + 2 * k]) for k in range(8)]},
        'loot': {'thresholds': list(p95[0x21E:0x21E + 168]), 'items': list(p95[0x17A:0x17A + 168]),   # race·4: d100 bands, items
                 'amounts': [list(p95[k:k + 3]) for k in range(0x13A, p95.index(b'\xff', 0x13A), 3)],  # {item, lo, hi}
                 'an': list(p95[0xCDB:0xCE0])},   # races named with "an" (comtxt 0xA9)
        'resurrect': [x.decode('latin1') for x in p95[0x27:0x13A].split(b'\0')[:7]],   # P95 texts 0-6 (spells.md, Resurrect)
        'spells': {'names': [x.decode('latin1') for x in exe[ds + 0x3EDC:ds + 0x4100].split(b'\0')[:42]],
                   'energy': list(exe[ds + 0x2BC6:ds + 0x2BC6 + 42]),   # _enetbl
                   'where': list(exe[ds + 0x2BF0:ds + 0x2BF0 + 42]),    # _splocs (16 = combat)
                   'side': list(open(f'{src}/P94.MCO', 'rb').read()[0x1529:0x1529 + 42]),   # TALIGN: 0 own, 1 enemy
                   'skill': list(exe[ds + 0x390C:ds + 0x390C + 20]),   # SKLSPLS
                   'here': list(exe[ds + 0x2C1A:ds + 0x2C1A + 10])},   # _spellshere by location program
        'songs': {'instruments': list(v06[0x28FF:v06.index(0, 0x28FF)]),                 # INT61_1d: item per instrument
                  'races': [list(v06[0x4EC + 8 * k:0x4EE + 8 * k]) for k in range(4)],       # song 0/1 → monster race
                  'names': [[x.decode('latin1') for x in exe[ds + 0x4014:ds + 0x4200].split(b'\0')[8 * k:8 * k + 2]] for k in range(4)]},
        # pre-fight Talk (P96 ovl_06e7 / ovl_0b5c, combat.md Parley): V06's text table (`_txtptr` = V06 word 5), _w_kins,
        # _w_attitudes, the party's worth per hero race (P96 0xB3F) and the attitude rolls (0xB4B: 11 + 6 bytes, read as one)
        'parley': {'texts': [x.decode('latin1') for x in v06[struct.unpack_from('<H', v06, 5)[0]:0x45A].split(b'\0')[:40]],
                   'kins': [x.decode('latin1') for x in exe[ds + 0x4084:ds + 0x42AE].split(b'\0')[:40]],
                   'attitudes': [x.decode('latin1') for x in exe[ds + 0x42AE:ds + 0x4320].split(b'\0')[:8]],
                   'worth': list(struct.unpack_from('<6H', p96, 0xB3F)), 'rolls': list(p96[0xB4B:0xB5C])},
        'maxtbl': list(exe[ds + 0x2C7E:ds + 0x2C7E + 120]),   # _MaxSkill: skill·6 + race
        'guarddiff': list(open(f'{src}/P01.MCO', 'rb').read()[0x33A:0x34A]),       # world fights' difficulty by region
        'd06': {'cast': list(d06[ptr[0]:ptr[1]]), 'crit': list(d06[ptr[1]:ptr[2]]), 'crit2': list(d06[ptr[2]:ptr[3]]),
                'prey': list(d06[ptr[3]:ptr[3] + 42]), 'gonshi': list(d06[ptr[4]:ptr[5]]), 'sermin': list(d06[ptr[5]:ptr[6]]),
                'potion': list(d06[ptr[6]:ptr[7]]), 'counts': list(d06[ptr[8]:ptr[8] + 56]), 'armor': list(d06[ptr[9]:ptr[10]]),
                'dodge': list(d06[ptr[10]:ptr[11]]), 'prefs': list(d06[ptr[12]:ptr[12] + 132])}})
    # Sound (decision 5): _GameSound(n) plays FFFAR's name table entry n − 1 (file 0x3FB0, 13-byte names), converted to
    # sounds/n.wav; _song(n) plays `_cmffile[n]` (DS:3070) = MC2nnA.CMF, copied to music/n.cmf for the OPL2 synth.
    fff = open(f'{src}/FFFAR.MCO', 'rb').read()
    os.makedirs(f'{dst}/sounds', exist_ok=True); os.makedirs(f'{dst}/music', exist_ok=True)
    for n in range(1, 30):
        name = fff[0x3FB0 + 13 * (n - 1):0x3FB0 + 13 * n].split(b'\0')[0].split(b'.voc')[0].decode().upper() + '.VOC'
        if os.path.exists(f'{src}/{name}'): voc_to_wav(open(f'{src}/{name}', 'rb').read(), f'{dst}/sounds/{n}.wav')
    for n in range(1, 15):
        p = struct.unpack_from('<H', exe, ds + 0x3070 + 2 * n)[0]
        name = exe[ds + p:exe.index(b'\0', ds + p)].decode().upper()
        open(f'{dst}/music/{n}.cmf', 'wb').write(open(f'{src}/{name}', 'rb').read())
        # the MT-32 arrangement of the same song (_RolandLoad: 11-byte names after the CMF ones), for the modern music
        mid = exe[ds + p + 14 * 11:exe.index(b'\0', ds + p + 14 * 11)].decode().upper()
        open(f'{dst}/music/{n}.mid', 'wb').write(open(f'{src}/{mid}', 'rb').read())
    # VGA full screens (P81 ovl_1469, tools/mce.py): 5 the Mindcraft logo, 1 the title, E/I/M the intro's pictures
    # (A, the original's game frame, is not used by the port)
    os.makedirs(f'{dst}/screens', exist_ok=True)
    # the game font (_LoadAlphabet: I26.MCT, E26.MCT on EGA/VGA): 128 ASCII glyphs of 8x8 4bpp, ink 0 on grey 7;
    # written as a 16x8 atlas, ink opaque white and the rest clear, so the port can tint it
    f26 = open(f'{src}/E26.MCT', 'rb').read()
    font = Image.new('RGBA', (128, 64), (0, 0, 0, 0))
    for g, o in enumerate(struct.unpack_from('<128H', f26, 0)):
        o += 256
        assert (f26[o], f26[o + 1]) == (4, 8)
        for i, b in enumerate(f26[o + 2:o + 34]):
            for k, v in enumerate((b >> 4, b & 15)):
                if v == 0: font.putpixel(((g % 16) * 8 + (i % 4) * 2 + k, (g // 16) * 8 + i // 4), (255, 255, 255, 255))
    font.save(f'{dst}/font.png')
    for x in '51EIM':
        pal, px = vga(f'{src}/VSCR{x}.MCE')
        im = Image.frombytes('P', (320, 200), px); im.putpalette(pal); im.save(f'{dst}/screens/{x}.png')
    ct = ds + 0x9F8   # common text, message n = n-th string
    dump(f'{dst}/comtxt.json', [x.decode('latin1') for x in exe[ct:ct + 0x4000].split(b'\0')[:400]])
    print(f'{n} locations, {len(blocks)} blocks, {sum(map(len, rooms.values()))} room chunks')

if __name__ == '__main__': main(*sys.argv[1:3])
