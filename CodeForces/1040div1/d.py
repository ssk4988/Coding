n = int(input())
a = list(range(n))
from itertools import permutations
for p in permutations(a):
    s = [0] * n
    for x in p:
        closest = 2 * n
        for y in p:
            if y == x: break
            if (abs(y-x), y) < (abs(closest-x), closest):
                closest = y
        if closest != 2 * n:
            s[closest] += 1
    print(p, s)
n = 100
cnt = 0
for l in range(n):
    for r in range(l, n):
        cnt += r-l+1
print(cnt)
