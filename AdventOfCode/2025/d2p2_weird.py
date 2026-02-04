strs = input().split(",")
events = []
sums = [0] * 12

def clamp(v, l, r):
    return min(max(v, l), r)

for term in strs:
    a = list(map(int, term.split("-")))
    a[0] -= 1
    for w in range(1, 12):
        p = 1
        for repeat in range(1, 12):
            if p > a[1]: break
            r = clamp(a[1] // p, 10 ** (w-1) - 1, 10 ** w - 1)
            l = clamp(a[0] // p, 10 ** (w-1) - 1, 10 ** w - 1)
            if r-l > 0: 
                sums[repeat] += (r * (r+1) // 2 - l * (l+1) // 2) * p
            p *= 10 ** w
            p += 1
for i in range(1, 12)[::-1]:
    for j in range(2*i, 12, i):
        sums[i] -= sums[j]
ans = sum(sums[2:])
print(ans)
