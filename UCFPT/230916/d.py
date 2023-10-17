freq = list(map(int, input().split()))
sides = [4, 6, 8, 12, 20]

def cmp(c1, c2):
    return c2[0] - c1[0]

a = [1]
for i in range(5):
    for j in range(freq[i]):
        a1 = [0] * (len(a) + sides[i])
        for k, v in enumerate(a):
            for l in range(1, sides[i] + 1):
                a1[k + l] += v
            a = a1
        # print(a)

cands = []
for i, v in enumerate(a):
    cands.append((v, i))
from functools import cmp_to_key
cands = sorted(cands, key=cmp_to_key(cmp))

for i in cands:
    if i[0] == 0:
        continue
    print(i[1], end=' ')
print()
