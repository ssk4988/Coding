def solve():
    n = int(input())
    ops = (3 * n + 1) // 2
    def query(t, v):
        nonlocal ops
        ops -= 1
        assert(ops >= 0)
        print(t, v, flush=True)
        if t == "throw":
            res = int(input())
            return res
    a = [0] * n
    cur = [0] * n
    dist = [0] * (n+2)
    v = query("throw", n-2+1)
    if v == 1:
        a[n-2] = 2
    else:
        a[n-2] = 1
    query("swap", n-2+1)
    v = query("throw", n-2+1)
    if v == 1:
        a[n-1] = 2
    else:
        a[n-1] = 1
    cur[n-2] = a[n-1]
    cur[n-1] = a[n-2]
    for i in range(n-2, n)[::-1]:
        dist[i] = 1 + dist[cur[i]+i]
    f = n-2
    while f >= 2:
        if dist[f] != dist[f+1]:
            assert(dist[f] == 1 + dist[f+1])
            v = query("throw", f-1+1)
            a[f-1] = 1 + (v == 1 + dist[f+1])
            dist[f-1] = 1 + dist[f-1 + a[f-1]]
            cur[f-1] = a[f-1]
            f -= 1
        else:
            v = query("throw", f-2+1)
            a[f-2] = 2 if v == 1 + dist[f] else 1
            cur[f-1] = a[f-2]
            query("swap", f-2+1)
            v = query("throw", f-2+1)
            a[f-1] = 2 if v == 1 + dist[f] else 1
            cur[f-2] = a[f-1]
            f -= 2
            for i in range(f, f+2)[::-1]:
                dist[i] = 1 + dist[cur[i]+i]
    
    if f >= 1:
        if dist[1] != dist[2]:
            v = query("throw", 1)
            a[0] = 1 if v == 1 + dist[1] else 2
        else:
            query("swap", 1)
            v = query("throw", 2)
            a[0] = 1 if v == 1 + dist[2] else 2
    print("!", *a, flush=True)

nc = int(input())
for cn in range(nc):
    solve()
