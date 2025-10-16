nc = int(input())
for cn in range(nc):
    n = int(input())
    a = list(map(int, input().split()))
    ans = 0
    
    for i in range(0, n, 2):
        mn = a[i]
        if i > 0:
            mn = min(mn, a[i-1])
        if i+1 < n:
            mn = min(mn, a[i+1])
        ans += max(0, a[i] - mn)
        a[i] = mn
    
    for i in range(2, n, 2):
        sm = a[i] + a[i-2]
        if sm <= a[i-1]: continue
        if sm - a[i-1] > a[i]:
            print("bruh")
        assert(sm - a[i-1] <= a[i])
        ans += (sm - a[i-1])
        a[i] -= (sm - a[i-1])
    
    print(ans)
