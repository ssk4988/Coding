#!/usr/bin/env python

from math import hypot
def hype(xyz): return hypot(hypot(xyz[0],xyz[1]),xyz[2])

n,k = map(int, raw_input().split())
print '%.9f' % (([0] + sorted(map(hype, [map(float, raw_input().split()) for i in range(n)])))[k])
