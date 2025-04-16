n = int(input())
a = list(map(int, input().split()))
b = [(v, i) for i, v in enumerate(a)]
b.sort()
a.sort()
from itertools import accumulate
pref = list(accumulate(a))
ans = [False] * n
ans[b[-1][1]] = True
for i in reversed(range(n-1)):
    if pref[i] >= b[i+1][0]:
        ans[b[i][1]] = ans[b[i+1][1]]
print(''.join("LW"[w] for w in ans))
