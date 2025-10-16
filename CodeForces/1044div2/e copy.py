from heapq import *
nc = int(input())
for cn in range(nc):
    n = int(input())
    proc = [False] * n
    adj = [[] for _ in range(n)]
    for i in range(n-1):
        u, v = map(lambda x: int(x)-1, input().split())
        adj[u].append(v)
        adj[v].append(u)
    adjcnt = [len(adj[u]) for u in range(n)]
    heap = [(-len(adj[u]), u) for u in range(n)]
    heapify(heap)
    ops = []
    while heap:
        a, u = heappop(heap)
        a = abs(a)
        print("pop", a, u)
        if proc[u] or a < 3: continue
        proc[u] = True
        adjcnt[u] = 0
        ops.append((2, u+1))
        for v in adj[u]:
            if proc[v]: continue
            adjcnt[v] -= 1
            heappush(heap, (-adjcnt[v], v))
    lines = []
    vis = [False] * n
    for i in range(n):
        if vis[i]: continue
        if adjcnt[i] >= 2: continue
        u = i
        while u is not None:
            ops.append((1, u+1))
            vis[u] = True
            nxt = None
            if proc[u]:
                break
            for v in adj[u]:
                if proc[v] or vis[v]: continue
                assert(nxt is None)
                nxt = v
            u = nxt
    print(len(ops))
    for o in ops:
        print(*o)
    assert(len(ops) <= (5 * n // 4))
