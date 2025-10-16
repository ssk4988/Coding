nc = int(input())
for cn in range(nc):
    a, b = map(int, input().split())
    print(b * (2 ** a))
