n = int(input())
a = list(map(int, input().split()))
mxl = [a[0]]
mxr = [0] * n
for i in range(1, n):
    mxl.append(max(mxl[-1], a[i]))
mxr[-1] = a[-1]
for i in range(n-2, -1, -1):
    mxr[i] = max(mxr[i+1], a[i])
l = 1
ans = (-1, 0)
while l < n-1:
    if not (mxl[l-1] >= a[l] and a[l] <= mxr[l+1]):
        l += 1
        continue
    r = l
    while r+1 < n-1 and mxl[r] >= a[r+1] and a[r+1] <= mxr[r+2]:
        r += 1
    elev = min(a[l-1], a[r+1])
    cur = 0
    for i in range(l, r+1):
        cur += elev - a[i]
    if elev == ans[0]:
        ans = (ans[0], ans[1] + cur)
    elif elev > ans[0]:
        ans = (elev, cur)
    # print(l, r, elev, cur)
    l = r+1
print(ans[1])
