nc = int(input())
for cn in range(nc):
    n = int(input())
    lens = [0] * n
    for i in range(n):
        print("?", i+1, n, *range(1, n+1), flush=True)
        lens[i] = int(input())
    path = [max((l, i) for i, l in enumerate(lens))]
    while path[-1][0] > 1:
        nxt = None
        cands = [i for i in range(n) if lens[i] == path[-1][0]-1]
        for c in cands:
            print("?", path[-1][1]+1, 2, path[-1][1]+1, c+1, flush=True)
            p = int(input())
            if p == 2:
                nxt = c
                break
        assert(nxt is not None)
        path.append((lens[nxt], nxt))
    path = [b+1 for a, b in path]
    print("!", len(path), *path, flush=True)
