"""Guess a grid's row width by vertical autocorrelation: the true width maximises cell[i]==cell[i+w]."""
import sys
def best_widths(d, lo=20, hi=130, top=5):
    n = len(d)
    res = []
    for w in range(lo, hi + 1):
        m = sum(1 for i in range(n - w) if d[i] == d[i + w])
        res.append((m / (n - w), w))
    return sorted(res, reverse=True)[:top]
if __name__ == '__main__':
    for arg in sys.argv[1:]:
        path, off = (arg.split(':') + ['0'])[:2]
        d = open(path, 'rb').read()[int(off):]
        print(path, f'off={off} n={len(d)}', [(w, round(s, 3)) for s, w in best_widths(d)])
