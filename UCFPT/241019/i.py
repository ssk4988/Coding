from itertools import combinations, permutations, product
n, targ = map(int, input().split())
d = [list(map(int, input().split())) for _ in range(n)]
def precomp(p):
    ways = [[set() for _ in range(n)] for _ in range(n)]
    for perm in permutations(p):
        dist = 0
        for i in range(len(perm)-1): dist += d[perm[i]][perm[i+1]]
        ways[perm[0]][perm[-1]].add(dist)
    return ways
for l in combinations(range(n), n//2):
    r = [i for i in range(n) if i not in l]
    pl, pr = precomp(l), precomp(r)
    for w,x,y,z in product([l[0]], l, r, r):
        t = targ - d[z][w] - d[x][y]
        p0, p1 = 0, len(pr[y][z])-1
        for p0 in pl[w][x]:
            if t - p0 in pr[y][z]:
                print("possible")
                exit()
print("impossible")
