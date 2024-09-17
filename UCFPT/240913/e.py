n, m, k = map(int, input().split())
MOD = 10 ** 9 + 7

tot_pat = 0
facs = [1]
for i in range(n + 10):
    facs.append((facs[-1] * (i+1))%MOD)
inv_facs = [1] * len(facs)
inv_facs[-1] = pow(facs[-1], MOD-2, MOD)
for i in range(len(facs)-2, -1, -1):
    inv_facs[i] = (inv_facs[i+1] * (i+1)) % MOD
def comb(a, b):
    if b > a: return 0
    res = 1
    for i in range(b):
        res *= a - i
        res %= MOD
    res *= inv_facs[b]
    return res % MOD

for rep in range(1+m // 2):
    colors = m - rep
    if colors > k: continue
    color_ways = comb(k, colors) * comb(colors, rep)
    organize = facs[m] * pow(pow(2, rep, MOD), MOD-2, MOD)
    tot_pat += color_ways * organize
    tot_pat %= MOD

print(tot_pat)

ans = (n-m+1) * pow(k, n-m, MOD) * tot_pat
ans %= MOD

for rep in range(1 + m//2):
    l = 2 * m - rep
    if l > n or m - rep > k: continue
    # ans -= (n - l + 1) *
    ans -= (n-l+1) * pow(k, n - l, MOD) * comb(k, m - rep) * facs[m - rep]
ans %= MOD

print(ans)
