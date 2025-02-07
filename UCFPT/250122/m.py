n = 7
from itertools import permutations
from collections import defaultdict
p = range(n)
cnt = defaultdict(int)
for perm in permutations(p):
    bal = 0
    for i, x in enumerate(perm):
        bal += abs(i-x)
    if perm[0] == 1 and perm[1] == 5 and perm[2] == 4:
        if bal == 16: print(bal, perm)
        cnt[bal] += 1
for k,v in cnt.items():
    print(k, v)
