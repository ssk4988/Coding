nc = int(input())
for cn in range(nc):
    n, a, b = map(int, input().split())
    if (n&1) != (b&1):
        print("NO")
        continue
    if a > b and (n&1) != (a&1):
        print("NO")
    else:
        print("YES")
