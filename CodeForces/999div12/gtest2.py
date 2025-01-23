n = 10
edges = n * (n-1) // 2
# 01 0 23 1 45 0 67 1 89 0

edge_list = []
for i in range(n):
    for j in range(i+1, n):
        if i % 2 == 0 and j == i+1: continue
        edge_list.append((i, j))

from itertools import combinations

for query in combinations(edge_list, 5):
    