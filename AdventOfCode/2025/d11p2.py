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
def dp(u, dac, fft):
    if u == label["out"]: return dac and fft
    ans = 0
    for v in adj[u]: ans += dp(v, dac or v == label["dac"], fft or v == label["fft"])
    print(u, ans)
    return ans
print(dp(label["svr"], False, False))
