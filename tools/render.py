"""Render tilesets and maps to PNG.
  render.py tileset V01.MCT out.png
  render.py map M01E01.MCM V01.MCT out.png
"""
import sys
from PIL import Image
sys.path.insert(0, __file__.rsplit('/', 1)[0])
from mc2fmt import load_mct, load_mcm, TILE_W, TILE_H

def tile_img(ts, i):
    im = Image.new('P', (TILE_W, TILE_H))
    im.putpalette([c for rgb in ts.palette for c in rgb])
    im.putdata(ts.tiles[i])
    return im

def render_tileset(ts, cols=16):
    rows = (len(ts.tiles) + cols - 1) // cols
    sheet = Image.new('RGB', (cols * TILE_W, rows * TILE_H))
    for i in range(len(ts.tiles)):
        sheet.paste(tile_img(ts, i).convert('RGB'), ((i % cols) * TILE_W, (i // cols) * TILE_H))
    return sheet

def render_map(m, ts):
    img = Image.new('RGB', (m.w * TILE_W, m.h * TILE_H))
    cache = {}
    for y in range(m.h):
        for x in range(m.w):
            t = m.cells[y * m.w + x]
            if t >= len(ts.tiles):
                continue
            if t not in cache:
                cache[t] = tile_img(ts, t).convert('RGB')
            img.paste(cache[t], (x * TILE_W, y * TILE_H))
    return img

if __name__ == '__main__':
    cmd = sys.argv[1]
    if cmd == 'tileset':
        render_tileset(load_mct(sys.argv[2])).save(sys.argv[3])
    elif cmd == 'map':
        render_map(load_mcm(sys.argv[2]), load_mct(sys.argv[3])).save(sys.argv[4])
