# general tree dp dfs
def dfs(u, p):
    dp[u] = init(u)
    for v in adj[u]:
        if v == p: continue
        child_dp = dfs(v, u)
        dp[u] = combine(dp[u], child_dp)
    dp[u] = finalize(dp[u])


# reroot dfs without finalize, with decombine
def dfs(u, p):
    dp[u] = init(u)
    for v in adj[u]:
        if v == p: continue
        child_dp = dfs(v, u)
        dp[u] = combine(dp[u], child_dp)

def dfs2(u, p, parent_dp):
    reroot[u] = dp[u]
    if p != -1:
        reroot[u] = combine(reroot[u], parent_dp)
    for v in adj[u]:
        if v == p: continue
        without_v = decombine(reroot[u], dp[v])
        dfs2(v, u, without_v)

# tree dp dfs
def dfs(u, p):
    dp[u] = init(u)
    for v in adj[u]:
        if v == p: continue
        child_dp = dfs(v, u)
        dp[u] = combine(dp[u], child_dp)
    dp_final[u] = finalize(dp[u]) # finalize optional
    return dp_final[u]

# reroot dfs
def dfs2(u, p, parent_dp):
    reroot[u] = dp[u]
    if p != -1:
        reroot[u] = combine(reroot[u], parent_dp)
    reroot_final[u] = finalize(reroot[u])
    for v in adj[u]:
        if v == p: continue
        without_v = decombine(reroot[u], dp_final[v])
        dfs2(v, u, finalize(without_v))

# reroot dfs with prefix suffix
def dfs(u, p):
    dp[u] = init(u)
    for v in adj[u]:
        if v == p: continue
        child_dp = dfs(v, u)
        dp[u] = combine(dp[u], child_dp)

def dfs2(u, p, parent_dp):
    children = []
    if p != -1:
        children.append((p, parent_dp))
    for v in adj[u]:
        if v == p: continue
        children.append((v, dp[v]))
    
    # compute prefix sums and reroot
    prefix = []
    reroot[u] = init(u)
    for v, child_dp in children:
        if len(prefix) == 0: prefix.append(child_dp)
        else: prefix.append(combine(prefix[-1], child_dp))
        reroot[u] = combine(reroot[u], child_dp)

    # compute suffix sums
    suffix = []
    children.reverse()
    for v, child_dp in children:
        if len(suffix) == 0: suffix.append(child_dp)
        else: suffix.append(combine(child_dp, suffix[-1]))
    children.reverse()
    suffix.reverse()

    for i in range(len(children)):
        v = children[i][0]
        if v == p: continue
        without_v = init(u)
        if i > 0:
            without_v = combine(without_v, prefix[i-1])
        if i + 1 < len(children):
            without_v = combine(without_v, suffix[i+1])
        dfs2(v, u, without_v)

