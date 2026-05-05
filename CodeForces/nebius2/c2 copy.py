nc = int(input())
for cn in range(nc):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    works = True
    freqdiff = [0] * (n+1)
    for i in range(n):
        if max(abs(i-0), abs(n-1-i)) >= k:
            if b[i] != -1 and b[i] != a[i]:
                works = False
        else:
            freqdiff[a[i]] += 1
            if b[i] != -1:
                freqdiff[b[i]] -= 1
    for i in range(n+1):
        if freqdiff[i] < 0: works = False
    arepeat = True
    brepeat = True
    bval = [-1] * k
    for i in range(n):
        if a[i] != a[i % k]:
            arepeat = False
        if b[i] != -1:
            if bval[i%k] == -1:
                bval[i%k] = b[i]
            elif bval[i%k] != b[i]:
                brepeat = False
    repfreqdiff = [0] * (n+1)
    for i in range(k):
        repfreqdiff[a[i]] += 1
        if bval[i] != -1: repfreqdiff[bval[i]] -= 1
    for i in range(n+1):
        if repfreqdiff[i] < 0:
            brepeat = False
    if arepeat and brepeat:
        works = True
    print("YES" if works else "NO")
