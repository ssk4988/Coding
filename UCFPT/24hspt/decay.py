from math import sqrt
n, c = map(int, input().split())
a = list(map(int, input().split()))

MOD = 1000000007
sq = int(sqrt(1000000000000)) + 50
composite = [False for i in range(sq)]
composite[0] = composite[1] = True

primes = []
for i in range(sq):
    if not composite[i]:
        primes.append(i)
        for j in range(i * i, sq, i):
            composite[j] = True
first = a[0]
divs = []
for i in primes:
    if first % i == 0:
        divs.append(i)
        while first % i == 0:
            first //= i
if first > 1:
    divs.append(first)

ans = 1
memo = dict()
for x in a:
    if x in memo:
        ans *= memo[x]
        ans %= MOD
        continue
    newdivs = [d for d in divs if x % d == 0]
    divs = newdivs
    nd = len(divs)
    cur = 0
    for mask in range(1 << nd):
        prod = 1
        parity = True
        for i, d in enumerate(divs):
            if (mask >> i) & 1:
                prod *= d
                parity = not parity
        cur += (1 if parity else -1) * (c // prod)
        cur %= MOD
    memo[x] = cur
    ans *= cur
    ans %= MOD
print(ans)
    
