n, m = map(int, input().split())
grid = [input() for i in range(n)]
seen = [[0] * m for i in range(n)]
q = []
for i in range(n):
    for j in range(m):
        if grid[i][j] == 'S': q.append((i, j))
ans = 0
for i,j in q:
    if not (0 <= i < n) or not (0 <= j < m) or seen[i][j]: continue
    seen[i][j] = 1
    if grid[i][j] == '^': 
        ans += 1
        for j1 in [j-1, j+1]:
            q.append((i, j1))
    else: q.append((i+1, j))
print(ans)
