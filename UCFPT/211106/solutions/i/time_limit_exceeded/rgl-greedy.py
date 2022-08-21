#!/usr/bin/env python

from random import randint

choose = [[0 for i in range(21)] for j in range(21)]
for i in range(21):
  for j in range(21):
    if i == j or j == 0:
      choose[i][j] = 1
    elif i < j:
      choose[i][j] = 0
    else:
      choose[i][j] = choose[i-1][j-1] + choose[i-1][j]

n, s = map(int, raw_input().split())

base = [1 for i in range(n)]
s -= 2**(n-1)

while s > 0:
  qty = 2**(randint(0, n-1))
  avail = map(lambda i: (i, choose[n-1][i]), range(n))
  avail = filter(lambda x: x[1]*qty <= s, avail)
  avail = sorted(avail, key = lambda x: base[x[0]])
  if len(avail) == 0:
    if qty == 1:
      break
    else:
      continue
  else:
    base[avail[0][0]] += qty
    s -= avail[0][1] * qty

if s != 0:
  print 'impossible'
else:
  rows = [base]
  for i in range(1,n):
    rows += [map(sum, zip(rows[-1][:-1], rows[-1][1:]))]
  for i in rows[::-1]:
    print ' '.join(map(str, i))
