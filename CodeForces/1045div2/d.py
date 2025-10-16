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
    diam = farpath(diam[0])
    assert(len(diam) >= 3)
    for i in range(1, len(diam)-1)[::-1]:
        if len(adj[diam[i]]) <= 2: continue
        a, b, c = diam[i+1], diam[i], diam[i-1]
        for v in adj[b]:
            if v == a or v == c: 
                continue
            print(a+1, b+1, v+1)
            return
    assert(False)


nc = int(input())
for cn in range(nc):
    solve()
