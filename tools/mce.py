"""MCE full screens (P81 ovl_1398 / ovl_1469): run-length coded; a count byte n (low 7 bits) is followed by one byte
repeated n times (bit 7 clear) or by n literal bytes (bit 7 set). VGA `VSCRx.MCE` decodes to 0xFD00 bytes: a 256-colour
palette (6-bit VGA levels) then 320x200 pixels.
usage: mce.py FILE OUT.png [planar]"""
import sys
from PIL import Image

def unrle(d, size):
    out, p = bytearray(), 0
    while len(out) < size and p < len(d):
        n = d[p] & 0x7f
        if d[p] & 0x80: out += d[p + 1:p + 1 + n]; p += 1 + n
        else: out += bytes([d[p + 1]]) * n; p += 2
    return bytes(out[:size])

def vga(path):
    raw = unrle(open(path, 'rb').read(), 0xFD00)
    pal = [min(255, v * 255 // 63) for v in raw[:768]]
    return pal, raw[768:]

if __name__ == '__main__':
    pal, px = vga(sys.argv[1])
    if len(sys.argv) > 3:   # mode X: 4 planes of 80 x 200
        lin = bytearray(64000)
        for pl in range(4):
            for i in range(16000): lin[(i // 80) * 320 + (i % 80) * 4 + pl] = px[pl * 16000 + i]
        px = bytes(lin)
    im = Image.frombytes('P', (320, 200), px); im.putpalette(pal); im.save(sys.argv[2])
