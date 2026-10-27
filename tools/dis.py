"""Disassemble raw 16-bit real-mode byte ranges from an overlay file.
usage: dis.py FILE start[:end] ...   (hex offsets; end defaults to start+0x80; stops after RET/JMP when no end)"""
import sys, capstone
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_16)
d = open(sys.argv[1], 'rb').read()
for rng in sys.argv[2:]:
    s, _, e = rng.partition(':')
    s = int(s, 16); stop = int(e, 16) if e else None
    print(f'---- {s:04x}')
    for i in md.disasm(d[s:(stop or s + 0x200)], s):
        print(f'{i.address:04x}  {i.bytes.hex(" "):24} {i.mnemonic} {i.op_str}')
        if stop is None and i.mnemonic in ('ret', 'retf', 'jmp') : break
