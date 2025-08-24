# for i in range(10):
#     print(3 ** i, 3 ** (i+1) + i * 3 ** (i-1))
nc = int(input())
for cn in range(nc):
    x = int(input())
    ans = 0
    for y in range(30, -1, -1):
        amt = 3 ** y
        cost = int(3 ** (y+1) + y * 3 ** (y-1))
        times = x // amt
        ans += cost * times
        x -= times * amt
    print(ans)
