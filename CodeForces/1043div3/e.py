import sys
input = sys.stdin.readline
from itertools import accumulate
nc = int(input())
for cn in range(nc):
    n, m, q = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    a.sort(reverse=True)
    b.sort(reverse=True)
    apref = [0] + list(accumulate(a))
    bpref = [0] + list(accumulate(b))
    c = [(x, 0, i) for i, x in enumerate(a)] + [(x, 1, i) for i, x in enumerate(b)]
    c.sort(reverse=True)
    seen = [[0, 0] for i in range(n+m)]
    idx_a = [0] * (n+1)
    idx_b = [0] * (m+1)
    c_pref = [0]
    for i in range(len(c)):
        if i: seen[i] = seen[i-1]
        v, t, idx = c[i]
        c_pref.append(c_pref[-1] + v)
        seen[i][t] += 1
        if t == 0:
            idx_a[seen[i][0]] = i
        else:
            idx_b[seen[i][1]] = i
    for _ in range(q):
        x, y, z = map(int, input().split())
        a_i = idx_a[x]
        b_i = idx_b[y]
        ans = 0
        if min(a_i, b_i) >= z:
            ans = c_pref[z]
        elif a_i < b_i:
            ans = apref[x]
            ans += bpref[z-x]
        else:
            ans = bpref[y]
            ans += apref[z-y]
        print(ans)
