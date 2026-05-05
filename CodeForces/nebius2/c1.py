nc = int(input())
for cn in range(nc):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    revb = [-1] * (n+1)
    works = True
    for i in range(n):
        if b[i] != -1: 
            if revb[b[i]] != -1: works = False
            revb[b[i]] = i
    for i in range(n):
        if max(abs(i-0), abs(n-1-i)) >= k:
            if revb[a[i]] != -1 and revb[a[i]] != i:
                works = False
        elif revb[a[i]] != -1:
            j = revb[a[i]]
            if max(abs(j-0), abs(n-1-j)) >= k:
                works = False
    print("YES" if works else "NO")
