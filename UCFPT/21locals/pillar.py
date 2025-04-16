n = int(input())
ans = 100
buildings = []
for i in range(n):
    s, w, h = map(int, input().split())
    ans += 2 * h
    buildings.append((s, w, h))
buildings.sort()
for i in range(1, n):
    if buildings[i-1][0] + buildings[i-1][1] == buildings[i][0]:
        ans -= 2 * min(buildings[i-1][2], buildings[i][2])
print(ans)