eps = 1e-6
from math import sqrt
class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __add__(self, p):
        return Point(self.x + p.x, self.y + p.y)
    def __sub__(self, p):
        return Point(self.x - p.x, self.y - p.y)
    def __mul__(self, c):
        return Point(self.x * c, self.y * c)
    def __truediv__(self, c):
        return Point(self.x / c, self.y / c)
    def cross(self, p):
        return self.x * p.y - self.y * p.x
    def dot(self, p):
        return self.x * p.x + self.y * p.y
    def norm(self):
        return Point(-self.y, self.x)
    def dist2(self):
        return self.x ** 2 + self.y ** 2
    def dist(self):
        return self.dist2() ** .5
    def unit(self):
        return self / self.dist()
    def __eq__(self, p):
        return (self.x, self.y) == (p.x, p.y)

def proj(d, p):
    # projection of p onto d
    return p - d.norm() * (d.cross(p) / d.dist2())

def circleLine(s, e, c, r):
    c_proj = s + proj(e - s, c - s)
    dist_c = (c_proj - c).dist()
    insqrt = r ** 2 - dist_c ** 2
    if insqrt < 0:
        return []
    sides = sqrt(r ** 2 - dist_c ** 2)
    dv = (e - s).unit() * sides
    return [c_proj + dv, c_proj - dv]

n = int(input())
pts = []
for i in range(n):
    x, y = map(int, input().split())
    pts.append(Point(x, y))


xs, ys, xe, ye = map(int, input().split())
start = Point(xs, ys)
end = Point(xe, ye)

# p = proj(Point(1, 5), Point(3, 5))
# print(p.x, p.y)

# p = proj(Point(5, 0), Point(2, 2))
# print(p.x, p.y)


# s = Point(-5, 0)
# e = Point(5, 0)
# r = 3
# c = Point(0, 3)
# res = circleLine(s, e, c, r)
# for p in res:
#     print(p.x, p.y)

from functools import cmp_to_key

def get_key(p):
    return (p - start).dot(end - start)
def keyevents(e):
    return (get_key(e[0]), e[1])
def test(r):
    start_key = get_key(start)
    end_key = get_key(end)
    line = [(start_key, 0), (end_key, 0)]
    for p in pts:
        inter = circleLine(start, end, p, r)
        if len(inter) == 0: continue
        if get_key(inter[0]) > get_key(inter[1]):
            line.append((get_key(inter[0]), -1))
            line.append((get_key(inter[1]), 1))
        else:
            line.append((get_key(inter[0]), 1))
            line.append((get_key(inter[1]), -1))
    line.sort()
    uncovered = 0
    cover = 0
    seen = 0
    prv = line[0][0]
    # print(line)
    for p, dt in line:
        dl = p - prv
        assert(cover >= 0)
        if cover == 0 and seen == 1:
            uncovered += dl
        prv = p
        cover += dt
        if (p, dt) == (start_key, 0): seen += 1
        if (p, dt) == (end_key, 0): seen += 1
    return uncovered <= eps

# print(test(5))
lo = 0
hi = 2e6
assert(test(hi))
ans = hi
for it in range(100):
    mid = (lo + hi) / 2
    if test(mid):
        ans = min(ans, mid)
        hi = mid
    else: lo = mid
print(f"{ans:.8f}")
