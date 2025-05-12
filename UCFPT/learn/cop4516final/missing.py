nc = int(input())
for cn in range(nc):
    n, m, p = map(int, input().split())
    ans = m * 100 >= n * p
    print(1 if ans else 0)
