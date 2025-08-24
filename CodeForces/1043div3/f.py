import sys
input = sys.stdin.readline
sys.setrecursionlimit(4*10**5)
from collections import deque

nc = int(input())
for cn in range(nc):
    n, m = map(int, input().split())
    adj = [[] for _ in range(n)]
    for i in range(m):
        u, v = map(int, input().split())
        u -= 1
        v -= 1
        adj[u].append((v, i))
        adj[v].append((u, i))

    tin = [-1] * n
    low = [10 ** 9] * n
    t = 0
    par = [-1] * n
    def dfs(u, p):
        global t
        tin[u] = t
        t += 1
        low[u] = tin[u]
        for v, i in adj[u]:
            if v == p: continue
            if tin[v] == -1:
                par[v] = u
                dfs(v, u)
                low[u] = min(low[u], low[v])
            else:
                low[u] = min(low[u], tin[v])
    dfs(0, -1)
    cur = n-1
    q = deque()
    inf = 10 ** 9
    min_edge = [inf] * n
    while cur != 0:
        p = par[cur]
        if low[cur] > tin[p]:
            for v, i in adj[cur]:
                if v != p: continue
                min_edge[cur] = min(min_edge[cur], i)
                min_edge[p] = min(min_edge[p], i)
        cur = p
    ord = []
    for i in range(n):
        if min_edge[i] != inf:
            ord.append((min_edge[i], i))
    ord.sort()
    for x, y in ord:
        q.append((x, y))
    closest = [-2] * n
    while q:
        d, u = q.popleft()
        if closest[u] != -2: continue
        closest[u] = d
        for v, i in adj[u]:
            q.append((d, v))
    queries = int(input())
    for i in range(queries):
        c = int(input())-1
        print(closest[c]+1, end=' ')
    print()
