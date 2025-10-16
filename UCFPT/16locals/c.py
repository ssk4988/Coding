nc = int(input())
for cn in range(nc):
    n, m = map(int, input().split())
    remx = set()
    remy = set()
    ans = 0
    for i in range(m):
        x, y = map(int, input().split())
        if x in remx and y in remy:
            ans += 1
        remx.add(x)
        remy.add(y)
    print(f"Strategy #{cn+1}: {ans}\n")
