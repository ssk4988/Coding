from math import log
n = int(input())
ans = 0
for i in range(n):
    a = list(map(float, input().split()))
    c = log(a[1] / a[0]) / log(2 ** (1/12))
    ans += round(c)
ans = int(abs(ans))
ans = min(ans % n, (-ans) % n)
print(ans)