from itertools import groupby
nc = int(input())
for cn in range(nc):
    n = int(input())
    a = list(map(int, input().split()))
    ans = n * n
    for key, g in groupby(a):
        l = len(list(g))
        ans = min(ans, key * (n - l))
    print(ans)
