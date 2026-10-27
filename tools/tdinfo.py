"""Parse Borland TLINK/Turbo Debugger symbolic info (TDInfo, magic 0x52FB) appended to a DOS MZ EXE.
Record layouts after ramikg/tdinfo-parser (MIT). Usage: tdinfo.py MC2.EXE [out.json]"""
import struct, sys, json

SYMCLASS = ['static', 'absolute', 'auto', 'pascal_var', 'register', 'constant', 'typedef', 'struct_union_enum']
TYPEID = {0:'void',1:'lstr',2:'dstr',3:'pstr',4:'schar',5:'sint',6:'slong',8:'uchar',9:'uint',10:'ulong',12:'pchar',
          13:'float',14:'tpreal',15:'double',16:'ldouble',21:'near',22:'far',23:'seg',26:'array',28:'parray',30:'struct',
          31:'union',34:'enum',35:'function',36:'label',37:'set',40:'bool',44:'funcprototype',45:'specialfunc'}

def parse(path):
    d = open(path, 'rb').read()
    last, pages = struct.unpack_from('<2H', d, 2)
    base = pages * 512 - ((512 - last) if last else 0)
    H = struct.unpack_from('<HBBI12H14xH', d, base)
    (magic, minor, major, pool_size, n_names, n_types, n_members, n_syms, n_globals, n_modules, n_locals,
     n_scopes, n_lines, n_srcs, n_segs, n_corr, ext) = H
    assert magic == 0x52FB
    p = base + 48 + ext
    def table(fmt, n):
        nonlocal p
        sz = struct.calcsize(fmt); out = [struct.unpack_from(fmt, d, p + i*sz) for i in range(n)]; p += sz*n; return out
    syms    = table('<4HB', n_syms)            # name, type, offset, segment, class(bits 0-2)
    modules = table('<H14x', n_modules)        # name
    srcs    = table('<HI', n_srcs)             # name, first line-record index (guess)
    lines   = table('<2H', n_lines)            # line, offset
    scopes  = table('<6H', n_scopes)           # symidx, symcount, parent, function, offset, length
    segs    = table('<6H4x', n_segs)           # module, seg, off, len, scopeidx, scopecount
    corr    = table('<4H', n_corr)             # segment, source file, line idx, line count (guess)
    types   = table('<BHHBH', n_types)         # id, name, size, class, member
    members = table('<BHH', n_members)
    pool = d[len(d) - pool_size:].split(b'\0')
    names = [''] + [s.decode('latin1') for s in pool]   # 1-based
    nm = lambda i: names[i] if 0 < i < len(names) else f'?{i}'
    tname = lambda t: (TYPEID.get(types[t-1][0], f'type{types[t-1][0]}') + (f'[{nm(types[t-1][1])}]' if types[t-1][1] else '')) if 0 < t <= len(types) else ''
    out = {
        'version': f'{major}.{minor:02}', 'load_module_size': base,
        'modules': [nm(m[0]) for m in modules],
        'source_files': [{'name': nm(s[0]), 'line_index': s[1]} for s in srcs],
        'segments': [{'module': nm(modules[s[0]-1][0]), 'seg': s[1], 'off': s[2], 'len': s[3], 'scope_index': s[4], 'scope_count': s[5]} for s in segs],
        'symbols': [{'i': i+1, 'name': nm(s[0]), 'type': tname(s[1]), 'off': s[2], 'seg': s[3], 'class': SYMCLASS[s[4] & 7]} for i, s in enumerate(syms)],
        'scopes': [{'sym_index': s[0], 'sym_count': s[1], 'parent': s[2], 'function': s[3], 'off': s[4], 'len': s[5]} for s in scopes],
        'correlations': corr, 'lines': lines, 'n_globals': n_globals,
    }
    return out

if __name__ == '__main__':
    r = parse(sys.argv[1])
    print('TDInfo', r['version'], 'load module', hex(r['load_module_size']))
    print('modules:', r['modules'])
    print('segments:'); [print(f"  {s['module']:14s} seg {s['seg']:04x} off {s['off']:04x} len {s['len']:04x} scopes {s['scope_index']}+{s['scope_count']}") for s in r['segments']]
    print('source files:', [s['name'] for s in r['source_files']][:40], '...')
    from collections import Counter
    print('symbol classes:', Counter(s['class'] for s in r['symbols']))
    g = [s for s in r['symbols'] if s['class'] == 'static']
    print('first 30 static symbols:'); [print(f"  {s['seg']:04x}:{s['off']:04x} {s['name']:28s} {s['type']}") for s in g[:30]]
    print('first 5 scopes:', r['scopes'][:5]); print('first 5 correlations:', r['correlations'][:5]); print('first 10 lines:', r['lines'][:10])
    if len(sys.argv) > 2: json.dump(r, open(sys.argv[2], 'w'), indent=0)


# ---- derived exports -------------------------------------------------------
def raw_tables(path):
    """Return (names, types, members) raw tables for struct reconstruction."""
    d = open(path, 'rb').read()
    last, pages = struct.unpack_from('<2H', d, 2)
    base = pages * 512 - ((512 - last) if last else 0)
    H = struct.unpack_from('<HBBI12H14xH', d, base)
    (_, _, _, pool_size, n_names, n_types, n_members, n_syms, n_globals, n_modules, n_locals,
     n_scopes, n_lines, n_srcs, n_segs, n_corr, ext) = H
    p = base + 48 + ext + n_syms*9 + n_modules*16 + n_srcs*6 + n_lines*4 + n_scopes*12 + n_segs*16 + n_corr*8
    types = [struct.unpack_from('<BHHBH', d, p + i*8) for i in range(n_types)]; p += n_types*8
    members = [struct.unpack_from('<BHH', d, p + i*5) for i in range(n_members)]
    names = [''] + [s.decode('latin1') for s in d[len(d)-pool_size:].split(b'\0')]
    return names, types, members

def c_type(t, names, types, depth=0):
    """Render TDInfo type index t as a C type string (best effort)."""
    if t == 0 or t > len(types) or depth > 8: return 'void'
    tid, nm, size, cls, mem = types[t-1]
    base = TYPEID.get(tid, f'type{tid}')
    if tid in (30, 31, 34):
        return ('struct ' if tid == 30 else 'union ' if tid == 31 else 'enum ') + (names[nm] if nm else f'anon{t}')
    if tid == 26:  # array: mem = element type, size = total bytes
        el = c_type(mem, names, types, depth+1); esz = types[mem-1][2] if 0 < mem <= len(types) else 0
        return f'{el}[{size // esz if esz else "?"}]'
    if tid in (21, 22):  # near/far pointer: mem = pointee
        return c_type(mem, names, types, depth+1) + (' *' if tid == 21 else ' far *')
    if tid in (35, 45):
        return c_type(mem, names, types, depth+1) + ' (func)'
    cmap = {'schar':'char','sint':'int','slong':'long','uchar':'unsigned char','uint':'unsigned int','ulong':'unsigned long','pchar':'char'}
    return cmap.get(base, base)

def export_structs(path):
    """Emit every struct/union/enum reachable from a typedef or tag symbol, named by the symbol."""
    names, types, members = raw_tables(path)
    r = parse(path)
    # symbol-name -> type index, for typedef and tag symbols
    want = []
    d = open(path, 'rb').read()
    last, pages = struct.unpack_from('<2H', d, 2)
    base = pages * 512 - ((512 - last) if last else 0)
    ext = struct.unpack_from('<H', d, base + 46)[0]
    n_syms = struct.unpack_from('<H', d, base + 14)[0]
    p = base + 48 + ext
    for i in range(n_syms):
        nm, t, off, seg, cls = struct.unpack_from('<4HB', d, p + i*9)
        if (cls & 7) in (6, 7) and t: want.append((names[nm], t))
    seen, out = set(), []
    for sname, t in want:
        tid, nm, size, cls, mem = types[t-1]
        if tid in (21, 22):  # typedef of pointer to struct: follow
            if 0 < mem <= len(types) and types[mem-1][0] in (30,31,34): t = mem; tid, nm, size, cls, mem = types[t-1]
        if tid not in (30, 31, 34): continue
        key = (names[nm] if nm else sname, size)
        if key in seen: continue
        seen.add(key)
        kw = {30:'struct', 31:'union', 34:'enum'}[tid]
        tag = names[nm] if nm else sname
        hdr = f'{kw} {tag}' + (f' /* typedef {sname} */' if sname != tag else '')
        out.append(f'{hdr} {{  /* size {size} */')
        off = 0; j = mem - 1
        while 0 <= j < len(members) and members[j][0] != 0xC0:
            info, mn, mt = members[j]
            if tid == 34:
                out.append(f'    {names[mn]} = {mt},')
            else:
                msz = types[mt-1][2] if 0 < mt <= len(types) else 0
                out.append(f'    {c_type(mt, names, types):28s} {names[mn]:24s} /* +{off:3d} ({msz}) */')
                if tid == 30: off += msz
            j += 1
        out.append('};\n')
    return '\n'.join(out)

def export_symbols(r, path_tsv, path_txt):
    code = [(s['seg'], s['off'], s['off'] + s['len'], s['module']) for s in r['segments']]
    def module_of(seg, off):
        for cs, lo, hi, m in code:
            if cs == seg and lo <= off < hi: return m
        return None
    rows = []
    for s in r['symbols']:
        if s['class'] != 'static' or not s['name'] or s['name'].startswith('?'): continue
        m = module_of(s['seg'], s['off'])
        kind = 'func' if (s['type'].startswith('function') or s['type'].startswith('specialfunc') or m) else 'data'
        rows.append((s['seg'], s['off'], kind, s['name'], s['type'], m or ''))
    rows.sort()
    with open(path_tsv, 'w') as f:
        for seg, off, kind, name, typ, m in rows: f.write(f'{kind}\t{seg:04x}\t{off:04x}\t{name}\n')
    with open(path_txt, 'w') as f:
        cur = None
        for seg, off, kind, name, typ, m in rows:
            if (m or seg) != cur:
                cur = m or seg; f.write(f'\n## {m or f"seg {seg:04x} (data)"}\n')
            f.write(f'{seg:04x}:{off:04x}  {kind:4s}  {name:32s} {typ}\n')
    return len(rows)
