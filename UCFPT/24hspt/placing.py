n = int(input())
grid = [input() for i in range(n)]

suff = [[0 for i in range(n + 1)] for j in range(n + 1)]
for i in range(n-1, -1, -1):
    for j in range(n-1, -1, -1):
        suff[i][j] = grid[i][j] == '.'
        suff[i][j] += suff[i+1][j] + suff[i][j+1] - suff[i+1][j+1]


ans = [0 for i in range(n+1)]

for i in range(n):
    for j in range(n):
        best = 0
        dif = 1 << 10
        while dif > 0:
            if i + best + dif <= n and j + best + dif <= n and suff[i][j] - suff[i + best + dif][j] - suff[i][j + best + dif] + suff[i + best + dif][j + best + dif] == (best + dif) * (best + dif):
                best += dif
            dif >>= 1
        ans[best] += 1
for i in range(n-1, -1, -1):
    ans[i] += ans[i + 1]
for i in range(1, n+1):
    print(ans[i])
