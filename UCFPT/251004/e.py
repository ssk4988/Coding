nc = int(input())
for cn in range(nc):
    n, m, k = map(int, input().split())
    cols = set()
    for i in range(k):
        r, c = map(int, input().split())
        if c == 1: continue
        if c in cols: cols.remove(c)
        else: cols.add(c)
    if n == 1:
        print("Mimo" if 2 in cols else "Yuyu")
    else:
        print("Mimo" if len(cols) else "Yuyu")
