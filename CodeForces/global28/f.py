prod = 1
primes = []
lim = 10 ** 8
for p in range(2, 100):
    if prod * p > lim: break
    pr = True
    for i in range(2, p):
        if p % i == 0:
            pr = False
    if pr:
        primes.append(p)
        prod *= p
print(primes)
print(len(primes))
res = []
def dfs(idx, mult, plim):
    global res
    if idx == len(primes):
        res.append(mult)
        return
    mult1 = mult
    pw = 0
    while mult1 <= lim:
        dfs(idx+1, mult1, pw)
        mult1 *= primes[idx]
        pw += 1

dfs(0, 1, 1000)
print(len(res))
res = list(set(res))
print(len(res))
