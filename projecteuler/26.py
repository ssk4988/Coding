def cycle(n):
    ans = 1
    seen = [-1 for i in range(n)]
    cur = 1
    while seen[cur] == -1:
        seen[cur] = ans
        ans += 1
        cur *= 10
        cur %= n
    return ans - seen[cur]


best = 2
for i in range(2, 1000):
    if cycle(best) < cycle(i):
        best = i
print(best, cycle(best))