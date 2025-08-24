# for i in range(30):
#     print(i, 3 ** i, 3 ** (i+1) + i * 3 ** (i-1))
nc = int(input())
for cn in range(nc):
    x, k = map(int, input().split())
    ans = 0
    cnt = [0] * 25
    for y in range(24, -1, -1):
        amt = 3 ** y
        cost = int(3 ** (y+1) + y * 3 ** (y-1))
        times = x // amt
        cnt[y] = times
        x -= times * amt
        k -= times
    if k < 0:
        print(-1)
        continue
    for y in range(24, 0, -1):
        conv = min(cnt[y], k // 2)
        k -= conv * 2
        cnt[y] -= conv
        cnt[y-1] += 3 * conv
    ans = 0
    for y in range(25):
        cost = int(3 ** (y+1) + y * 3 ** (y-1))
        ans += cnt[y] * cost
    print(ans)

