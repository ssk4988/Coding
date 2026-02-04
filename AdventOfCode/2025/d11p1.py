n = int(input())
label = dict()
adj = [[] for i in range(n+10)]
for i in range(n):
    s = input().split()
    s[0] = s[0][:-1]
    print(s)
    for i in range(len(s)):
        if s[i] not in label:
            j = len(label)
            label[s[i]] = j
        s[i] = label[s[i]]
    print(s)
    adj[s[0]] = s[1:]
from functools import cache
@cache
def dp(u):
    if u == label["out"]: return 1
    ans = 0
    for v in adj[u]: ans += dp(v)
    print(u, ans)
    return ans
print(dp(label["you"]))
print(label["you"], label["out"])
