nc = int(input())
for cn in range(nc):
    n = int(input())
    h = list(map(int, input().split()))
    # saved if kill at index i
    dp = [0] * n
    best = 0
    for i in range(n-1, -1, -1):
        if i + 2 < n:
            best += 1
            best = max(best, dp[i+2])
        if i + 1 < n:
            add = min(i+1, h[i+1])
            dp[i] = add + best
        # print("at", i, dp[i], best)
    print(sum(h) - max(dp))

