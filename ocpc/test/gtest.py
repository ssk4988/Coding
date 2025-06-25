from math import sqrt
a = list(map(int, "-123353 -257 3897 160801 -34417 -131 -192397 -424159 56723".split()))
n = len(a)
ans = -1
prods = []
for mask in range(1 << n):
    prod = 1
    for i in range(n):
        if (mask >> i)&1:
            prod *= a[i]
    good = True
    prods.append(prod)
    for sub in range(1, mask+1):
        if (sub & mask) == sub and int(sqrt(abs(prods[sub]))) ** 2 == abs(prods[sub]):
            good = False
            break
    if good and ((mask >> (n-1))&1 > 0) and (ans == -1 or prod > ans):
        ans = prod
print(ans, ans % 998244353)
for i in range(len(prods)):
    if prods[i] == ans:
        for j in range(n):
            if (i >> j)&1:
                print(a[j])
