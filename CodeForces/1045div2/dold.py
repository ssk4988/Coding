def solve():
    n = int(input())
    adj = [[] for i in range(n)]
    for i in range(n-1):
        u, v = map(int, input().split())
        adj[u-1].append(v-1)
        adj[v-1].append(u-1)
    # if n <= 3:
    #     print(-1)
    #     return
    if max(len(adj[i]) for i in range(n)) <= 2:
        print(-1)
        return
    def farpath(start):
        q = [start]
        par = [-1] * n
        path = [[] for i in range(n)]
        for u in q:
            for v in adj[u]:
                if v == par[u]: continue
                par[v] = u
                q.append(v)
        for u in q[::-1]:
            for v in adj[u]:
                if v == par[u]: continue
                if len(path[v]) > len(path[u]):
                    path[u] = path[v]
            path[u].append(u)
        return path[start]
    diam = farpath(0)
    # print(diam)
    diam = farpath(diam[0])
    # print(diam)
    assert(len(diam) >= 3)
    best = (-1, -1, -1, -1)
    seen = False
    for i in range(1, len(diam)-1):
        if len(adj[diam[i]]) <= 2: continue
        a, b, c = diam[i+1], diam[i], diam[i-1]
        if i > len(diam)-1 - i or (i == len(diam)-1 - i and not seen):
            c, a = a, c
        cand = (min(i, len(diam)-1 - i), a+1, b+1, c+1)
        best = max(cand, best)
        # print(a+1, b+1, c+1)
        # return
        seen = True
    assert(best[0] != -1)
    print(best[1], best[2], best[3] )



nc = int(input())
for cn in range(nc):
    solve()
