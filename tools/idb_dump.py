"""Dump user-named functions, comments and segments from an IDA .idb via python-idb."""
import sys, idb, idb.analysis as A
with idb.from_file(sys.argv[1]) as db:
    api = idb.IDAPython(db)
    segs = [(api.idc.SegStart(s), api.idc.SegEnd(s), "?") for s in api.idautils.Segments()]
    print("SEGMENTS", len(segs))
    for s in segs: print(f"  {s[2]:12s} {s[0]:06x}-{s[1]:06x}")
    funcs = list(api.idautils.Functions())
    named = []
    for ea in funcs:
        n = api.idc.GetFunctionName(ea)
        if not n.startswith("sub_"):
            named.append((ea, n))
    print("FUNCTIONS", len(funcs), "USER-NAMED", len(named))
    for ea, n in named: print(f"  {ea:06x} {n}")
    cmts = 0
    for ea in funcs:
        c = api.idc.GetFunctionCmt(ea, 0) or api.idc.GetFunctionCmt(ea, 1)
        if c: cmts += 1; print(f"  CMT {ea:06x} {api.idc.GetFunctionName(ea)}: {c[:100]!r}")
    print("FUNC-COMMENTS", cmts)
    names = list(api.idautils.Names())
    print("GLOBAL-NAMES", len(names))
    for ea, n in names:
        if not any(n.startswith(p) for p in ("sub_","loc_","byte_","word_","dword_","unk_","off_","seg","asc_","a")):
            print(f"  {ea:06x} {n}")
