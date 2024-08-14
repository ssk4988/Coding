a, b, p, q = map(int, input().split())
p /= 100
q /= 100

dp = [-1] * (a + 1)

for x in range(len(dp)):
    if x < b:
        dp[x] = 0
        continue
    dp[x] = 2 * p + (1 - p) + dp[x - b]
    if b == 1:
        dp[x] = max(dp[x], 1 / (1 - q) + dp[x - b])
    else:
        dp[x] = max(dp[x], 1 + q * dp[x - b + 1] + (1 - q) * dp[x - b])



print(f"{dp[-1]:.10f}")
