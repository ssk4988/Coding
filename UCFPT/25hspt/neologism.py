b = int(input())
bigrams = set()
for i in range(b):
    s = input()
    bigrams.add(s)
from collections import defaultdict

from string import ascii_lowercase

state = defaultdict(int)
res = dict()

def dfs(cur):
    if state[cur]:
        if state[cur] == 1: return (None, None)
        return res[cur]
    res[cur] = (0, "")
    state[cur] = 1
    for c in ascii_lowercase:
        nxt = (cur + c)[-2:]
        if len(nxt) == 2 and nxt not in bigrams: continue
        dist = dfs(nxt)
        if dist[0] is None: return (None, None)
        res[cur] = max(res[cur], (1 + dist[0], c))
    state[cur] = 2
    return res[cur]

ans = dfs("")
if ans[0] is None:
    print(-1)
    exit()
print(ans[0])

w = ""
for _ in range(ans[0]):
    val = dfs(w[-2:])
    assert(val is not None)
    w += val[1]
print(w)
