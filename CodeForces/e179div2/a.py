nc = int(input())
for cn in range(nc):
    x = int(input())
    a = [0, 0, 0]
    ans = 0
    while a[0] != x:
        a[0] = min(x, a[1] * 2 + 1)
        a.sort()
        ans += 1
        # print(a)
    print(ans)
