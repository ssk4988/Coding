n = int(input())
c = [list(map(int, input().split(","))) for i in range(n)]

e = [-1] * n
def find(u):
    if e[u] < 0: return u
    e[u] = find(e[u])
    return e[u]

def join(u, v):
    u = find(u)
    v = find(v)
    if u == v: return False
    if e[u] > e[v]: u,v = v,u
    e[u] += e[v]
    e[v] = u
    return True

def dist(a, b):
    return sum((i-j)**2 for i,j in zip(a, b))

edges = [(dist(c[i], c[j]), i, j) for i in range(n) for j in range(i)]
edges.sort()
ans = 0
for d,i,j in edges:
    if join(i,j):
        ans = c[i][0] * c[j][0]
print(ans)
