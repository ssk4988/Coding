n,m,c = map(int, input().split())
from collections import deque
adj = [[] for _ in range(n)]

for i in range(m):
    u,v,t = map(int, input().split())
    u -= 1
    v -= 1
    adj[u].append((v,t))

dist = [-10 ** 9 for _ in range(n)]
dist[0] = 0
inq = [False for _ in range(n)]
q = deque()
q.append(0)
inq[0] = True
while q:
    u = q.popleft()
    inq[u] = False
    for v,t in adj[u]:
        p = dist[v]
        dist[v] = min(c, max(dist[v], dist[u] + t))
        if dist[v] > p and not inq[v]:
            inq[v] = True
            q.append(v)
print(dist[-1])
