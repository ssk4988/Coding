b, w = map(int, input().split())
n = 300
n2 = n // 2
grid = [[i >= n2 for j in range(n)] for i in range(n)]
b -= 1
w -= 1
for i in range(0, n2-1, 2):
    for j in range(0, n, 2):
        if b:
            b -= 1
            grid[i][j] = True
for i in range(n2+1, n, 2):
    for j in range(0, n, 2):
        if w:
            w -= 1
            grid[i][j] = False
print(n, n)
for i in range(n):
    for j in range(n):
        print('@' if grid[i][j] else '.', end='')
    print()
