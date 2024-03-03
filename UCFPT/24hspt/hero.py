n = int(input())
a = list(map(int, input().split()))
pref_max = [0] * (n + 1)
suff_max = [0] * (n + 1)
suff_sum = [0] * (n + 1)
for i in range(n):
    pref_max[i+1] = max(a[i], pref_max[i])
for i in range(n-1, -1, -1):
    suff_max[i] = max(suff_max[i+1], a[i])
    suff_sum[i] = (suff_sum[i+1] + a[i])

first_occ = dict()
last_occ = dict()
for i, x in enumerate(a):
    if x not in first_occ:
        first_occ[x] = i
        last_occ[x] = i+1
    last_occ[x] = i+1

rev = a
rev.sort()
rev = rev[::-1]
best = 0
first = n
last = -1
for x in rev:
    first = min(first, first_occ[x])
    last = max(last, last_occ[x])
    best = max(best, (suff_sum[first] - suff_sum[last]) / (last - first) - max(pref_max[first], suff_max[last]))
print(f"{best:.4f}")