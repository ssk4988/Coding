import math

def fact(n):
    if n <= 1: return 1
    return n * fact(n - 1)
def choose(n, r):
    return fact(n) / fact(r) / fact(n - r)

bestx = -1
besty = -1
ratio = 0
gsize = 1000
gridsize = 12
for x in range(1, gridsize):
    for y in range(1, gridsize):
        
        grid = [[choose(i + j, i) for j in range(y)] for i in range(x)]

        rowends = [grid[i][-1] for i in range(x - 1)]
        colends = [grid[-1][i] for i in range(y - 1)]
        ub = 1 << len(rowends)
        rset = set()
        for mask in range(ub):
            sum = 0
            for i in range(len(rowends)):
                if (mask & (1 << i)) > 0: sum += rowends[i]
            rset.add(sum)
        cset = set()
        ub = 1 << len(colends)
        for mask in range(ub):
            sum = 0
            for i in range(len(colends)):
                if (mask & (1 << i)) > 0: sum += colends[i]
            cset.add(sum)
        digset = set()
        for i in rset:
            for j in cset:
                digset.add(i + j)
        exc = 0
        # print(x, y)
        for i in range(1, int(grid[-1][-1])):
            if i not in digset:
                exc += 1
        if exc != 0: continue
        newratio = (choose(x + y - 2, x - 1) ** 2) / (x + y - 1)
        # if x == 3 and y == 11:
        #     print("bs" + str(grid[-1][-1]))
        #     print((x + y - 1) * math.ceil(math.log(10**18, grid[-1][-1] ** 2)))
        if(grid[-1][-1] <= 1): continue
        # print(grid[-1][-1])
        newgsize = (x + y - 1) * math.ceil(math.log(10**18, grid[-1][-1] ** 2))
        
        if newgsize < gsize:
            ratio = newratio
            gsize = newgsize
            bestx = x
            besty = y
print(bestx, besty, ratio, gsize, (choose(bestx + besty - 2, bestx - 1) ** 2), bestx + besty - 1)

grid = [[choose(i + j, i) for j in range(besty)] for i in range(bestx)]
for g1 in grid:
    print(g1)
print(int(grid[-1][-1]))
