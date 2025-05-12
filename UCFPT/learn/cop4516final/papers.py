mod = 1000000007

fact = [1] * 400
for i in range(1, len(fact)):
    fact[i] = fact[i-1] * i % mod

def comb(n, k):
    if n < k or n < 0 or k < 0: return 0
    return fact[n] * pow(fact[k], mod-2, mod) * pow(fact[n-k], mod-2, mod) % mod

nc = int(input())
for cn in range(nc):
    n, a, p, s = map(int, input().split())
    groups = comb(n, s)
    other1 = comb(n-s, p-s)
    other2 = comb(n-s-(p-s), a-s)
    num = groups * other1 * other2 % mod
    denom = comb(n, a) * comb(n, p) % mod
    print(num * pow(denom, mod-2, mod) % mod)
