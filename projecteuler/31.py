dp = [0 for i in range(0, 201)]
dp[0] = 1
coins = [1, 2, 5, 10, 20, 50, 100, 200]

for i in coins:
    for j in range(0, 201 - i):
        dp[i + j] += dp[j]
print(dp[200])