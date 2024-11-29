lim = int(input())
divs = [0 for _ in range(lim)]
for d in range(1, lim):
    for j in range(d, lim, d):
        divs[j] += 1
ans = 0
for d in divs:
    ans += d ** 2
print(ans)
print(divs[:10])
