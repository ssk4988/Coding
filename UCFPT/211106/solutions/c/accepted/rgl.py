#!/usr/bin/env python

n,m = map(int, raw_input().split())
v = sorted(map(int, raw_input().split()), reverse=True)

for i in range(n):
  if i+1 < len(v) and v[i] + v[-1] <= m:
    v.pop()

print len(v)
