'''
dp[node][turn]
order:
dp[red][turn] = turn == 1
dp[leaf][turn] = turn == 0
dp[u][turn] = any(dp[v][1^turn] == 0)
can river force moves to a red node
nodes activate to red
at some point a state will be winning for river
'''
nc = int(input())
for cn in range(nc):
    n, m, q = map(int, input().split())
    adj = [[] for _ in range(n)]
    radj = [[] for _ in range(n)]
    for i in range(m):
        u, v = map(int, input().split())
        u -= 1

        v -= 1
        adj[u].append(v)
        radj[v].append(u)
    # 0 means cry wins
    dp = [[0] * 2 for _ in range(n)]
    forward = [[0] * 2 for _ in range(n)]
    for qid in range(q):
        tp, start = map(int, input().split())
        start -= 1
        if tp == 1:
            qu = [(start, 0), (start, 1)]
            for v, t in qu:
                if dp[v][t]: continue
                dp[v][t] = 1
                # print(cn, qid, v, t)
                for u in radj[v]:
                    forward[u][t^1] += 1
                    if len(adj[u]) == forward[u][t^1]:
                        qu.append((u, t^1))
                    elif t == 0:
                        qu.append((u, t^1))
        else:
            print("NO" if dp[start][0] else "YES")
