n = int(input())
adj = dict()
cnt = dict()
for _ in range(n):
    a, b = input().split()
    if a not in adj:
        adj[a] = []
        cnt[a] = 0
    if b not in adj:
        adj[b] = []
        cnt[b] = 0
    adj[a].append(b)
    adj[b].append(a)
words = input().split()
for x in words:
    if x not in cnt:
        cnt[x] = 0
        adj[x] = []
    cnt[x] += 1

seen = set()


def dfs(u):
    global seen
    if u in seen: return 0
    ans = cnt[u]
    seen.add(u)
    for v in adj[u]:
        ans += dfs(v)
    return ans

ans = 0

for x in words:
    if x in cnt:
        c = dfs(x)
        if c > 0: 
            ans += c * (c - 1) // 2
print(ans)