from math import sqrt
n = int(input())
for _ in range(n):
    x1, y1, r1 = map(float, input().split())
    x2, y2, r2 = map(float, input().split())
    dx = x2 - x1
    dy = y2 - y1
    dist = sqrt(dx * dx + dy * dy)
    xc1 = x1 + dx * r1 / dist
    yc1 = y1 + dy * r1 / dist
    xc2 = x2 - dx * r2 / dist
    yc2 = y2 - dy * r2 / dist
    print(f"{xc1:.5f} {yc1:.5f} {xc2:.5f} {yc2:.5f}")
