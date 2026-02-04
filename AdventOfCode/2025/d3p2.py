n = int(input())
ans = 0
from functools import cache
a = [[int(c) for c in input()] for i in range(n)]
# print(a)
@cache
def dp(x, i, left):
    if left == 0 or i == -1: return 0
    res = max(a[x][i] + 10 * dp(x, i-1, left-1), dp(x, i-1, left))
    # print(x, i, left, res)
    return res
for x in range(n):
    best = dp(x, len(a[x]) - 1, 12)
    # print(x, ans)
    ans += best
print(ans)
