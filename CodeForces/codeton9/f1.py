from math import gcd
m = int(input())
l = [i for i in range(1, m+1)]

def listgcd(v):
    g = v[0]
    for x in v: g = gcd(g, x)
    return g

def f(v):
    res = []
    res.append(listgcd(v))
    v2 = v.copy()
    while len(v2) > 1:
        v3 = [max(v2[i], v2[i+1]) for i in range(len(v2) - 1)]
        res.append(listgcd(v3))
        v2 = v3
    return res
ans = [[[]]]
while len(ans[-1]) > 0:
    nxt = []
    for v in ans[-1]:
        start = 0 if len(v) == 0 else v[-1]
        for x in range(1 + start, m+1):
            v1 = v.copy() + [x]
            res = f(v1)
            if len(set(res)) == len(v1):
                nxt.append(v1)
    ans.append(nxt)
tot = 0
from collections import defaultdict
for i in range(1, len(ans)):
    print(i, len(ans[i]))
    tot += len(ans[i]) * (1 << (i-1))
    d1 = defaultdict(list)
    d = defaultdict(int)
    for v in ans[i]:
        # print(v, f(v))
        d[tuple(f(v))] += 1
        d1[tuple(f(v))].append(v)
    for k,v in d.items():
    #     assert(v == 1 << (i-1))
    #     assert(len(k) == len(set(k)))
        print(k,v)
        for v1 in d1[k]:
            print(v1)
print(tot)
