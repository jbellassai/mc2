"""Map MC2.EXE file offsets to the enclosing TDInfo function. usage: exesym.py hexoff..."""
import sys
funcs=[]
for l in open('docs/symbols.txt'):
    p=l.split()
    if len(p)>=4 and p[1]=='func' and ':' in p[0]:
        s,o=p[0].split(':'); funcs.append((int(s,16)*16+int(o,16),p[0],p[2]))
funcs.sort()
for a in sys.argv[1:]:
    la=int(a,16)-0x1800
    best=max((f for f in funcs if f[0]<=la),key=lambda f:f[0])
    print(f'{a}: load {la:05x} = {best[1]} {best[2]} +{la-best[0]:x}')
