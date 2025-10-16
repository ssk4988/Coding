nc = int(input())
for cn in range(nc):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    for i in range(n):
        a[i] += (a[i] % (k+1)) * k
    print(*a)
