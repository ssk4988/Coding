nc = int(input())
for cn in range(nc):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    samea = [True] * k
    sameb = [True] * k
    bval = [-1] * k
    for i in range(n):
        if a[i] != a[i%k]: samea[i%k] = False
        if b[i] != -1:
            if bval[i%k] == -1: bval[i%k] = b[i]
            if b[i] != bval[i%k]: sameb[i%k] = False
    works = True
    freqdiff = [0] * (n+1)
    for i in range(k):
        if samea[i] and not sameb[i]:
            works = False
        if samea[i]:
            freqdiff[a[i]] += 1
            if bval[i] != -1:
                freqdiff[bval[i]] -= 1
    for i in range(n):
        if not samea[i%k] and b[i] != -1 and b[i] != a[i]:
            works = False
    for i in range(n+1):
        if freqdiff[i] < 0: works = False
    print("YES" if works else "NO")
