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

    q = []
    q.append((0, -1))
    bfs = []
    par = [-1] * n
    for u, p in q:
        par[u] = p
        bfs.append(u)
        for v in adj[u]:
            if v == p: continue
            q.append((v, u))
    seen = [False] * n
    inf = 10 ** 9
    opself = [1 for u in range(n)]
    path1 = [[0, []] for u in range(n)]
    path2 = [[0, []] for u in range(n)]
    childcnt = [0] * n
    for u in bfs[::-1]:
        pref = []
        for v in adj[u]:
            if v == par[u]: continue
            childcnt[u] += 1
            opself[u] += min(opself[v], path1[v][0], path2[v][0])
            path1[u][0] += opself[v]
            path2[u][0] += opself[v]
            pref.append((path1[v][0] - opself[v], v))
        # if childcnt[u] == 0:
        #     opself[u] = 0
        pref.sort()
        for i in range(min(1, len(pref))):
            delta, v = pref[i]
            if delta >= 0: break
            path1[u][1].append(v)
            path1[u][0] += delta
        for i in range(min(2, len(pref))):
            delta, v = pref[i]
            if delta >= 0: break
            path2[u][1].append(v)
            path2[u][0] += delta
    state = [0] * n
    state[0] = min([(opself[0], 0), (path1[0][0], 1), (path2[0][0], 2)])[1]
    ops = []
    proc = [False] * n
    adjcnt = [len(adj[u]) for u in range(n)]
    for u in bfs:
        if state[u] == 0:
            # if childcnt[u] > 0:?
            proc[u] = True
            adjcnt[u] = 0
            ops.append((2, u+1))
            for v in adj[u]:
                if proc[v]: continue
                adjcnt[v] -= 1
            for v in adj[u]:
                if v == par[u]: continue
                state[v] = min([(opself[v], 0), (path1[v][0], 1), (path2[v][0], 2)])[1]
        else:
            ls = path1[u][1] if state[u] == 1 else path2[u][1]
            for v in ls:
                state[v] = 1
    # print(par)
    # print(bfs)
    # print(opself)
    # print(path1)
    # print(path2)
    # print(proc)


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
    # assert(len(ops) <= (5 * n // 4))
