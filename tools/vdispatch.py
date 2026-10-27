"""Map the AH services of a V*.MCO module: entry is `jmp` at 0, dispatcher is a chain of `cmp ah,N / jne / call X`.
usage: vdispatch.py V02.MCO [SEG]  -> prints json {AH: handler file offset}; with SEG also prints 'SEG:off INT60_xx' name lines to stderr."""
import json, struct, sys
d = open(sys.argv[1], 'rb').read()
seg = sys.argv[2] if len(sys.argv) > 2 else None
p = struct.unpack_from('<H', d, 1)[0] + 3
m = {}
p = d.find(b"\x80\xfc", p, p + 48)  # skip the prologue
while p < len(d) - 8:
    if d[p] == 0x80 and d[p+1] == 0xfc:          # cmp ah, imm8
        ah = d[p+2]; q = p + 3
        if d[q] == 0x75: q += 2                     # jne short
        if d[q] == 0xe8:                             # call rel16
            m[ah] = (q + 3 + struct.unpack_from('<h', d, q+1)[0]) & 0xffff; q += 3
        if d[q] == 0xe9: q += 3
        elif d[q] == 0xeb: q += 2
        p = q
    else:
        break
print(json.dumps({f"0x{k:02x}": f"0x{v:04x}" for k, v in sorted(m.items())}, indent=0))
if seg:
    for k, v in sorted(m.items()): print(f"{seg}:{v:04x} INT_{k:02x}", file=sys.stderr)
