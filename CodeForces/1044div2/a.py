nc = int(input())
for cn in range(nc):
    n = int(input())
    a = list(map(int, input().split()))
    print("YES" if len(set(a)) != len(a) else "NO")
