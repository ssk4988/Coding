n, m = map(int, input().split())
grid = [input() for i in range(n)]
seen = [[0] * m for i in range(n)]
cnt = [[0] * m for i in range(n)]
q = []
for i in range(n):
    for j in range(m):
        if grid[i][j] == 'S': 
            cnt[i][j] = 1
            q.append((i, j))
for i,j in q:
    if not (0 <= i < n) or not (0 <= j < m) or seen[i][j]: continue
    seen[i][j] = 1
    if i+1 == n: continue
    if grid[i][j] == '^': 
        for j1 in [j-1, j+1]:
            if not (0 <= i < n) or not (0 <= j1 < m): continue
            cnt[i+1][j1] += cnt[i][j]
            q.append((i+1, j1))
    else: 
        if i+1 < n: cnt[i+1][j] += cnt[i][j]
        q.append((i+1, j))
print(sum(cnt[-1]))
