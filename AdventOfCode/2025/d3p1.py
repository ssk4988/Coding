n = int(input())
ans = 0
for i in range(n):
    s = [int(c) for c in input()]
    # print(s)
    best = 0
    prv = -1
    for i in s:
        best = max(best, prv * 10 + i)
        prv = max(prv, i)
    ans += best
print(ans)
