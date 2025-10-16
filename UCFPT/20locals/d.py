n = int(input())
a = list(map(int, input().split()))
first = dict()
last = dict()
for i in range(n):
    if a[i] not in first:
        first[a[i]] = i
    last[a[i]] = i
dp = [0] * (n+1)
for i in range(n):
    if last[a[i]] == i:
        prv = 0
        if first[a[i]] > 0:
            prv = dp[first[a[i]]-1]
        dp[i] = 1 + prv
    if i > 0:
        dp[i] = max(dp[i], dp[i-1])
print(len(first) - max(dp))
