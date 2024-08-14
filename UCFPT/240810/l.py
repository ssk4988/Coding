from collections import defaultdict
nc = int(input())
for cn in range(nc):
    w, h, l = map(int, input().split())
    n = int(input())
    sm = w * h * l
    pts = defaultdict(int)
    def add(xl, yl, zl, xr, yr, zr):
        pts[(xl, yl, zl)] ^= 1
        pts[(xl, yl, zr)] ^= 1
        pts[(xl, yr, zr)] ^= 1
        pts[(xl, yr, zl)] ^= 1
        pts[(xr, yl, zl)] ^= 1
        pts[(xr, yl, zr)] ^= 1
        pts[(xr, yr, zr)] ^= 1
        pts[(xr, yr, zl)] ^= 1
    for i in range(n):
        xl, yl, zl, xr, yr, zr = map(int, input().split())
        sm -= (xr - xl) * (yr - yl) * (zr - zl)
        add(xl, yl, zl, xr, yr, zr)
    add(0, 0, 0, w, h, l)
    works = sm == 0 and max(pts.values()) == 0
    print("Yes" if works else "No")
