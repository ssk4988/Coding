nc = int(input())
for cn in range(nc):
    n, m = map(int, input().split())
    f = [1, 2]
    while len(f) < n:
        f.append(f[-1]+f[-2])
    for i in range(m):
        a = list(map(int, input().split()))
        a.sort()
        print(1 if a[0] >= f[-1] and a[2] >= f[-1]+f[-2] else 0, end='')
    print()
