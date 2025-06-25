a, b = map(int, input().split())
primes = []
for p in range(10000, 1, -1):
    works = True
    for d in range(2, p):
        if d*d > p: break
        if p % d == 0:
            works = False
            break
    if works: primes.append(p)
def factorize(n):
    ans = []
    if n == 1: return ans
    for p in primes:
        while n % p == 0:
            ans.append(p)
            n //= p
    return ans
from collections import defaultdict
af = defaultdict(int)
bf = defaultdict(int)
for d in factorize(a):
    af[d] += 1
for d in factorize(b):
    bf[d] += 1

a1, b1 = 1, 1
for p in primes:
    cut = min(af[p], bf[p])
    af[p] -= cut
    bf[p] -= cut
    val = max(af[p], bf[p])
    if val == 0: continue
    if val % 2 == 0:
        a1 *= p
        b1 *= p
    while af[p] > 1:
        a1 *= p
        af[p] -= 2
    while bf[p] > 1:
        b1 *= p
        bf[p] -= 2
    if af[p] == 1:
        a1 *= p
        v = factorize(p-1)
        for d in v:
            bf[d] += 1
    if bf[p] == 1:
        b1 *= p
        v = factorize(p-1)
        for d in v:
            af[d] += 1
print(a1, b1)

        