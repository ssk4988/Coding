from itertools import permutations, product
n = int(input())
grid = [input() for _ in range(n)]
# print("parsed grid")

ac = [-1] * n
bc = [-1] * n
ar = [-1] * n
br = [-1] * n
for c in range(n):
    for r in range(n):
        if grid[r][c] == 'A': 
            ac[c] = r
            ar[r] = c
        if grid[r][c] == 'B': 
            bc[c] = r
            br[r] = c

cnt = 0
tot = 0
s = set()
for x,y in product(permutations([i for i in range(n)]), permutations([i for i in range(n)])):
    if any(x[i] == i for i in range(n)): continue
    tot += 1
    x1 = [(y[i], x[y[i]]) for i in range(n)]
    works = True
    for i in range(n):
        if ac[i] != -1 and x1[i][0] != ac[i]: works = False
        if bc[i] != -1 and x1[i][1] != bc[i]: works = False
    if not works: continue
    g = [['.' for j in range(n)] for i in range(n)]
    for i in range(n):
        g[x1[i][0]][i] = 'A'
        g[x1[i][1]][i] = 'B'
    # g1 = g.copy()
    # rs = [g[r] for r in range(n) if ar[r] == -1 and br[r] == -1]
    # rs.sort()
    # p = 0
    # for r in range(n):
    #     if ar[r] == -1 and br[r] == -1:
    #         g1[r] = rs[p]
    #         p += 1
    # if g1 != g: continue
    # cs = [''.join(g1[r][c] for r in range(n)) for c in range(n) if ac[c] == -1 and bc[c] == -1]
    # print(cs, sorted(cs))
    # # cs.sort()
    # # p = 0
    # # for c in range(n):
    # #     if ac[c] == -1 and bc[c] == -1:
    # #         for r in range(n):
    # #             g1[r][c] = cs[p][r]
    # #         p += 1
    # if g1 != g: continue
    cnt += 1
    # print(x1)
    s.add(x)
    # for i in range(n):
    #     print(''.join(g[i]))
    # print()
print(cnt)
# print(len(s))
# for x in s:
    # print(x)
