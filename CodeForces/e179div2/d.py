nc = int(input())
for cn in range(nc):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    a.sort(key=lambda x: x // 100)
    ans = [[], []]
    for i in range(n // 2):
        ans[0].append(a[i])
        ans[1].append(a[m-1-i])
    for i in range(n // 2):
        ans[1].append(a[i])
        ans[0].append(a[m-1-i])
    if n % 2 == 1:
        ans[0].append(a[n // 2])
        ans[1].append(a[m-1-(n//2)])
    while len(ans) < 6:
        ans.append(ans[-2])
    for i in range(n):
        for t in range(6): print(ans[t][i], end=' ')
        print()
