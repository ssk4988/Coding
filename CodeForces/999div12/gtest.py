n = 7
k=3
from itertools import permutations, combinations

edges = n * (n-1) // 2

tot = 0
fnd = 0
for emask in range(1 << edges):
    tot += 1
    adj = [[0] * n for _ in range(n)]
    bit = 0
    for i in range(n):
        for j in range(i+1, n):
            adj[i][j] = adj[j][i] = (emask >> bit) & 1
            bit += 1
    found = False
    for part in permutations(range(n), k):
        if found: break
        part = list(part)
        comp = []
        for  i in range(n):
            if i not in part: comp.append(i)
        for part2 in combinations(comp, k):
            if found: break
            cnt = [0] * 2
            for n1, n2 in zip(part, part2):
                cnt[adj[n1][n2]] += 1
            if max(cnt) == k:
                found = True
                break
    if not found:
        print(emask)
        print(adj)
        break
    else:
        fnd += 1
    

print(fnd, tot, n, edges)
