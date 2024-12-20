from collections import defaultdict
from math import gcd
d = defaultdict(int)
n = int(input())
for i in range(1, n):
    j = n-i
    assert(j > 0)
    d[gcd(i, j)] += 1
    print(i, j, gcd(i, j))
for k,v in d.items():
    print(k, v)
