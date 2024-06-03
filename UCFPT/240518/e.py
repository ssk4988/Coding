a = list(map(int, input().split()))
n = a[0]
m = a[1]
mod = 998244353
ans = pow(m, n, mod)
for i in range(1, m+1):
    ans += 2 * (pow(m, n, mod) - pow(i, n, mod))
ans %= mod
print(ans)
