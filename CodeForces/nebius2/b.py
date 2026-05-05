nc = int(input())
N = 2 * 10 ** 5 + 10
divcnt = [0] * N
for i in range(1, N):
    for j in range(i, N, i):
        divcnt[j] += 1
divcnt[0] = 1
for cn in range(nc):
    x, y = map(int, input().split())
    a = [1] * x + [-1] * y
    print(divcnt[abs(x-y)])
    print(*a)
