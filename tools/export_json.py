"""Build the web port's data pack from the original files (decision 1). Never commit or publish the output.
usage: export_json.py ORIGDIR OUTDIR -> OUTDIR/locations/*.json, tiledata/Bnn.json, tilesets/Vnn.png, sprites/E0n.png, conversations/Cnn.json,
       blocks.json, rooms.json, sprites.json, comtxt.json, items.json, heroes.json,
       commands.json, npctypes.json, p90.json, p02text.json, p91text.json, p05.json, p97text.json, p93text.json, conds.json, companions.json, exetables.json
Schema: docs/data_schema.md. Byte strings are lowercase hex; every list is in file order."""
import json, os, struct, sys
sys.path.insert(0, os.path.dirname(__file__))
from loc import PTRS
from mc2fmt import load_mct
from render import render_tileset

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

def main(src, dst):
    for sub in ('locations', 'tiledata', 'tilesets', 'sprites'): os.makedirs(f'{dst}/{sub}', exist_ok=True)
    dump = lambda path, obj: json.dump(obj, open(path, 'w'), indent=1, ensure_ascii=False)
    n = 0
    for name, d, kind in entries(src):
        dump(f'{dst}/locations/{name}.json', location(d, kind)); n += 1
    for f in sorted(os.listdir(src)):
        if f[0] == 'B' and f.endswith('.MCV'): dump(f'{dst}/tiledata/{f[:3]}.json', tiledata(open(f'{src}/{f}', 'rb').read()))
        if f[0] == 'V' and f.endswith('.MCT'):
            render_tileset(load_mct(f'{src}/{f}')).save(f'{dst}/tilesets/{f[:3]}.png')
    blocks = {}
    for f in sorted(os.listdir(src)):
        if f[0] == 'M' and f.endswith('.MCM'):
            d = open(f'{src}/{f}', 'rb').read()
            if d[:2] == b'**' and len(d) == 2 + 42 * 42: blocks[f[:6]] = d[2:].hex()
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
                             'lots': {str(lots[i]): lots[i + 1] for i in range(0, len(lots) - 1, 2)}})
    p02 = open(f'{src}/P02.MCO', 'rb').read()
    dump(f'{dst}/p02text.json', [x.decode('latin1') for x in p02[0x67:0x28A].split(b'\0')[:17]])   # town program's own texts
    p93 = open(f'{src}/P93.MCO', 'rb').read()
    dump(f'{dst}/p93text.json', [x.decode('latin1') for x in p93[0x3D:0x254].split(b'\0')])   # camp texts (rules/camp.md)
    dump(f'{dst}/conds.json', [x.decode('latin1') for x in exe[ds + 0x4204:ds + 0x4300].split(b'\0')[:12]])   # _w_conds: OK, then cond1<<8|cond2 bits 15…5
    p97 = open(f'{src}/P97.MCO', 'rb').read()
    dump(f'{dst}/p97text.json', [x.decode('latin1') for x in p97[0x17:0x1BA].split(b'\0')[:7]])   # hire / dismiss texts
    p91 = open(f'{src}/P91.MCO', 'rb').read()   # small talk: {weather, line} pairs at 0x48, 0xFF, then the lines
    end = p91.index(0xFF, 0x48); pairs = p91[0x48:end]
    dump(f'{dst}/p91text.json', {'lines': [x.decode('latin1') for x in p91[end + 1:0x2E0].split(b'\0')[:16]],
                                  'weather': [[pairs[i], pairs[i + 1]] for i in range(0, len(pairs) - 1, 2)]})
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
        'useall': [i + 0x31 for i in range(32) if struct.unpack_from('<H', exe, ds + 0x8AE + 2 * i)[0]]})   # _AllDoit asks
    ct = ds + 0x9F8   # common text, message n = n-th string
    dump(f'{dst}/comtxt.json', [x.decode('latin1') for x in exe[ct:ct + 0x4000].split(b'\0')[:400]])
    print(f'{n} locations, {len(blocks)} blocks, {sum(map(len, rooms.values()))} room chunks')

if __name__ == '__main__': main(*sys.argv[1:3])
