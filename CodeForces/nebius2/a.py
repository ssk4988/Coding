nc = int(input())
for cn in range(nc):
    n = int(input())
    a = list(map(int, input().split()))
    print(*[min(2, n) for _ in range(n)])
