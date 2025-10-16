nc = int(input())
for cn in range(nc):
    t, k = map(int, input().split())
    k -= 1
    a = list(map(int, input().split()))
    tot = sum(a)
    d = int(input())
    print(f"CD #{cn+1}:")
    for di in range(d):
        ans = 0
        seg = list(map(int, input().split()))
        s = seg[0]
        seg = seg[1:]
        start = 0
        for i in range(s):
            if i % 2 == 0:
                ans += seg[i]
                start = seg[i] % a[k]
            else:
                t = seg[i]
                if start > 0:
                    amt = min(t, a[k] - start)
                    ans += amt
                    t -= amt
                ans += a[k] * (t // tot)
                t %= tot
                if t >= tot - a[k]:
                    ans += t - (tot - a[k])
        print(ans)
    print()
