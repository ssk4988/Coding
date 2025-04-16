a = list(map(int, input().split()))
from itertools import permutations
for b in permutations(a):
    if b[0] != sum(b[1:4]) or b[-1] != 3 * b[1] + b[2]: continue
    print(*b)
    break