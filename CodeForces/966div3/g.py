print(1)
n = 5 * 10 ** 4
edges = []
for i in range(2, n//2-2):
    edges.append([1, i, 1, 2])
    edges.append([i, n//2-2, 1, 2])
for i in range(n//2-1, n):
    edges.append([n//2-2, i, 1, 2])
    edges.append([i, n, 1, 2])
m = len(edges)
print(n, m)
print(10, 7, 8)
for e in edges:
    print(" ".join(map(str, e)))
