s = input()
n = len(s)
inf = 10 ** 9
dp = [[inf] * 5 for _ in range(n+1)]

tyler = "tyler"
dp[0][0] = 0
for i in range(n):
    for it in range(2):
        for j in range(5):
            # delete this character
            dp[i+1][j] = min(dp[i+1][j], dp[i][j]+1)
            j1 = (j + 1) % 5
            # use/edit character
            dp[i+1][j1] = min(dp[i+1][j1], dp[i][j] + (tyler[j] != s[i]))
            # add character
            dp[i][j1] = min(dp[i][j1], 1+dp[i][j])
for j in range(5):
    j1 = (j + 1) % 5
    dp[-1][j1] = min(dp[-1][j1], 1+dp[-1][j])
print(dp[-1][0])