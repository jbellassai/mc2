"""Parsers for Magic Candle II data formats. See docs/formats.md for the spec."""
import struct
from dataclasses import dataclass

TILE_W = TILE_H = 16


@dataclass
class Tileset:
    palette: list        # 256 (r,g,b) tuples
    tiles: list          # list of bytes, each 256 pixel indices (row-major 16x16)
    kind: str            # 'vga' | 'ega'

def load_mct(path):
    d = open(path, 'rb').read()
    name = path.split('/')[-1].upper()
    if name.startswith('V'):
        pal = [tuple(d[i:i+3]) for i in range(0, 768, 3)]
        magic, count, w, h = struct.unpack_from('<HHBB', d, 768)
        assert (magic, w, h) == (0x108, 16, 16), (magic, w, h)
        off = 774
        tiles = [d[off + i*256: off + (i+1)*256] for i in range(count)]
        assert off + count*256 == len(d), (off + count*256, len(d))
        return Tileset(pal, tiles, 'vga')
    # EGA: 128 x uint16 offsets (relative to 256), each tile = 2-byte hdr (8,16) + 128 bytes 4bpp
    offs = struct.unpack_from('<128H', d, 0)
    tiles = []
    for o in offs:
        o += 256
        wb, h = d[o], d[o+1]
        assert (wb, h) == (8, 16), (wb, h)
        px = bytearray()
        for b in d[o+2:o+2+128]:
            px += bytes((b >> 4, b & 15))
        tiles.append(bytes(px))
    return Tileset(EGA_PAL, tiles, 'ega')

EGA_PAL = [(0,0,0),(0,0,170),(0,170,0),(0,170,170),(170,0,0),(170,0,170),(170,85,0),(170,170,170),
           (85,85,85),(85,85,255),(85,255,85),(85,255,255),(255,85,85),(255,85,255),(255,255,85),(255,255,255)]


@dataclass
class Map:
    w: int
    h: int
    cells: bytes   # row-major tile ids

def load_mcm(path):
    """Tile map. Layouts seen (see docs/formats.md):
      b'**' + 42*42 bytes            (1766 B)  most town/area maps
      b'**' + 84*60 bytes            (5042 B)  MxxE93 strongholds
      <w><h> + w*h bytes + junk     (5120 B)  M07E65 only: header is literal dims 84,60
    G*.MCM files are sets of 11x9 room maps (chunks of 0B 09 + 99 bytes, docs/formats.md *Room maps*); rejected here."""
    d = open(path, 'rb').read()
    name = path.split('/')[-1].upper()
    if name.startswith('G'):
        raise ValueError(f'{name}: G-file, not a tile map')
    if d[:2] == b'**':
        n = len(d) - 2
        for w, h in ((42, 42), (84, 60)):
            if w * h == n:
                return Map(w, h, d[2:])
        raise ValueError(f'{name}: {n} cells, unknown dims')
    w, h = d[0], d[1]
    if 2 + w * h <= len(d) and w >= 20 and h >= 20:
        return Map(w, h, d[2:2 + w * h])
    raise ValueError(f'{name}: unknown map layout')
