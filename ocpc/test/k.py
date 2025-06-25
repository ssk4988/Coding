from functools import cache

# @cache
# def dp(n, t):
#     if n == 0: return 1
#     if t > n: return 0
#     ans = dp(n - t, t) + dp(n, t+1)
#     print(n, t, ans)
#     return ans
# print(dp(22, 1))
