"""Write OUTDIR/index.html: every composed location map (OUTDIR/locs, tools/loc.py) with the rooms reachable from it
(OUTDIR/rooms, tools/render_rooms.py). usage: gallery.py OUTDIR"""
import html, os, re, sys

out = sys.argv[1]
locs = {f[:3]: f for f in sorted(os.listdir(f'{out}/locs')) if f.endswith('.png')}
rooms, names = {}, {}
for line in open(f'{out}/rooms/rooms.txt'):
    m = re.match(r'(\S{3}) (.*?)\s+\(\s*(\d+),\s*(\d+)\) P(\d+)\S* .*?id\s+(\d+) (.*): (\S+)$', line.rstrip())
    if not m: continue
    key, where, x, y, pgm, rid, name, png = m.groups()
    names[key] = where.strip()
    rooms.setdefault(key, {}).setdefault((png, name), []).append(f'({x},{y})')
h = ['<!doctype html><meta charset=utf-8><title>MC2 maps</title><style>body{background:#222;color:#ddd;font:14px sans-serif}'
     'img{image-rendering:pixelated}figure{display:inline-block;margin:4px;vertical-align:top;width:176px}'
     'figcaption{font-size:12px}h2{border-top:1px solid #555;padding-top:8px}</style><h1>Magic Candle II maps</h1>'
     '<p>Locations composed from map blocks; rooms are the 11×9 interiors behind each door. '
     'Tilesets of rooms come from the door\'s PGM record. Room sheets with every chunk: <a href="rooms/sheets/">rooms/sheets</a>.</p>']
for key in sorted(set(locs) | set(rooms)):
    title = names.get(key) or locs[key][4:-4].replace('_', ' ')
    h.append(f'<h2 id={key}>{key} {html.escape(title)}</h2>')
    if key in locs: h.append(f'<a href="locs/{locs[key]}"><img src="locs/{locs[key]}" style="max-width:100%"></a><br>')
    for (png, name), where in sorted(rooms.get(key, {}).items(), key=lambda kv: kv[0][1]):
        src = f'rooms/{png}'
        h.append(f'<figure><a href="{src}"><img src="{src}" width=176></a><figcaption>{html.escape(name)} '
                 f'{" ".join(where[:4])}{" …" if len(where) > 4 else ""}<br><small>{png}</small></figcaption></figure>')
open(f'{out}/index.html', 'w').write('\n'.join(h))
print(f'{len(locs)} maps, {sum(len(v) for v in rooms.values())} room entries -> {out}/index.html')
