nc = int(input())
for cn in range(nc):
    x = int(input())
    base = 1
    ans = []
    for z in range(1, 20):
        base *= 10
        z = base + 1
        if x % z == 0:
            ans.append(x // z)
    ans.sort()
    print(len(ans))
    if len(ans):
        print(*ans)
