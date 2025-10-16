from collections import Counter, defaultdict
nc = int(input())
for cn in range(nc):
    n = int(input())
    a = list(map(int, input().split()))
    c = Counter(a)
    works = True
    for k,v in c.items():
        if v % k != 0:
            works = False
    if not works:
        print(-1)
        continue
    left = [0] * (n+5)
    use = [0] * (n+5)
    x = 1
    b = [0] * n
    for i in range(n):
        if use[a[i]] == 0:
            use[a[i]] = x
            left[x] = a[i]
            x += 1
        b[i] = use[a[i]]
        left[use[a[i]]] -= 1
        if left[use[a[i]]] == 0:
            use[a[i]] = 0
    print(*b)
