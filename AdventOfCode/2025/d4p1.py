n, m = map(int, input().split())
grid = [input() for _ in range(n)]
deg = [[0] * m for _ in range(n)]
from collections import deque
q = deque()
for i in range(n):
    for j in range(m):
        cnt = 0
        for di in range(-1, 2):
            for dj in range(-1, 2):
                if di == 0 and dj == 0: continue
                i1 = i + di
                j1 = j + dj
                if min(i1, j1) < 0 or i1 >= n or j1 >= m: continue
                cnt += grid[i1][j1] == '@'
        deg[i][j] = cnt
        if cnt < 4: q.append((i, j))
seen = set()
while q:
    i, j = q.popleft()
    if grid[i][j] != "@": continue
    if (i, j) in seen: continue
    seen.add((i, j))
    for di in range(-1, 2):
        for dj in range(-1, 2):
            if di == 0 and dj == 0: continue
            i1 = i + di
            j1 = j + dj
            if min(i1, j1) < 0 or i1 >= n or j1 >= m: continue
            deg[i1][j1] -= 1
            if deg[i1][j1] < 4:
                q.append((i1, j1))
ans = 0
for i in range(n):
    for j in range(m):
        if grid[i][j] == '@' and deg[i][j] < 4: ans += 1
print(ans)
