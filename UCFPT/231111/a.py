nc = int(input())
for cn in range(nc):
    a = list(map(int, input().split()))
    ans = 0
    for i in range(2, len(a)):
        for j in range(i, len(a) - 1):
            mn = a[i]
            for k in range(i, j + 1):
                mn = min(mn, a[k])
            if mn > a[i - 1] and mn > a[j + 1]:
                ans += 1
    print("%d %d" % (a[0], ans))
