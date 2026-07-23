r, c = map(int, input().split())
g = [list(map(int, input().split())) for i in range(r)]
ans = 0
for i in range(r):
    mx = 0
    for j in range(c):
        if g[i][j] > mx:
            ans += 1
        mx = max(mx, g[i][j])
    mx = 0
    for j in range(c)[::-1]:
        if g[i][j] > mx:
            ans += 1
        mx = max(mx, g[i][j])
for j in range(c):
    mx = 0
    for i in range(r):
        if g[i][j] > mx:
            ans += 1
        mx = max(mx, g[i][j])
    mx = 0
    for i in range(r)[::-1]:
        if g[i][j] > mx:
            ans += 1
        mx = max(mx, g[i][j])
print(ans)
