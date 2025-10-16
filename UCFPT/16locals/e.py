nc = int(input())
dr = [1, 0, -1, 0]
dc = [0, 1, 0, -1]
dirs = "DRUL"
for cn in range(nc):
    n, m = map(int, input().split())
    grid = [input() for i in range(n)]
    q = int(input())
    print(f"Word search puzzle #{cn+1}:")
    for id in range(q):
        w = input()
        found = False
        for dir in range(4):
            for si in range(n):
                for sj in range(m):
                    if found:
                        break
                    ci, cj = si, sj
                    ans = 0
                    while ans < len(w) and grid[ci][cj] == w[ans]:
                        ans += 1
                        ci += dr[dir]
                        ci %= n
                        cj += dc[dir]
                        cj %= m
                    if ans == len(w):
                        found = True
                        print(dirs[dir], si+1, sj+1, w)
        assert(found)
    print()
