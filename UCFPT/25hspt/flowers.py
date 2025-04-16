n = int(input())
grid = [input() for _ in range(n)]
ans = False
for i in range(n-1):
    for j in range(n-1):
        if grid[i+1][j] == grid[i][j+1]:
            ans = True
if ans:
    print("duplicates")
else: print("unique")