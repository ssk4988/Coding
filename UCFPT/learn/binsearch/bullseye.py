nc = int(input())
for cn in range(nc):
    a = list(map(int, input().split()))
    r = a[0]
    t = a[1]
    # 2 * (r + 2 * x) + 1 for x=0 to rings-1
    # 2 * r + 4 * x + 1 for x=0 to rings-1
    # rings * 2 * r + rings + 2 * rings * (rings-1)

    ans = 1
    dif = 1 << 70
    while dif > 0:
        rings = ans + dif
        use = rings * 2 * r + rings + 2 * rings * (rings-1)
        if use <= t: ans += dif
        dif //= 2
    print(f"Case #{cn+1}: {ans}")
