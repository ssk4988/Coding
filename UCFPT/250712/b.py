n, k = map(int, input().split())
if n == 1 and k >= 1:
    print("NO")
    exit()
if n == 2 and k >= 2:
    print("NO")
    exit()
grid = [['.' for j in range(n)] for i in range(n)]
if n % 2 == 1:
    for i in range(n):
        for j in range(n):
            if i != j and k > 0:
                k -= 1
                grid[i][j] = '#'
else:
    for i in range(n):
        for j in range(n):
            if k == 0: continue
            if i == j and i != n // 2 and i != n//2 -1: continue
            if i == n//2 and j == n//2-1: continue
            if i == n//2-1 and j == n//2: continue
            k -= 1
            grid[i][j] = '#'
if k > 0:
    print("NO")
    exit()
print("YES")
for i in range(n):
    print(''.join(grid[i]))
