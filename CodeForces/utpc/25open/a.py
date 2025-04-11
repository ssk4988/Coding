grid = [[' ' for j in range(25)] for i in range(15)]
for i in [0, -1]:
    for j in [0, -1]:
        grid[i][j] = 'o'

n = int(input())
for i in range(n):
    grid[i+1][1] = '>'
    grid[i+1][2] = '<'
    grid[i+1][3] = '>'

for j in range(1, len(grid[0])-1):
    grid[0][j] = grid[-1][j] = '-'
for i in range(1, len(grid)-1):
    grid[i][0] = grid[i][-1] = '|'
print('\n'.join((''.join(v)) for v in grid))    
