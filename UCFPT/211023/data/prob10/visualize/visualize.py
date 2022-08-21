#!/bin/python

import sys

if len(sys.argv) != 3:
	print("USAGE: ./visualize.py <infile> <ansfile>")
	sys.exit(0)

inf = sys.argv[1]
outf = sys.argv[2]

with open(inf) as infile:
	infileline = infile.readlines()
with open(outf) as outfile:
	outfileline = outfile.readlines()

m, c = map(int, infileline[0].split(" "))
msx = []
msy = []
csx = []
csy = []
xx, yy = map(int, outfileline[0].split(" "))

for i in range(1, 1+m):
	x, y = map(int, infileline[i].split(" "))
	msx += [x]
	msy += [y]
for i in range(1+m, 1+m+c):
	x, y = map(int, infileline[i].split(" "))
	csx += [x]
	csy += [y]

minx = min(msx + csx + [xx])
maxx = max(msx + csx + [xx])
miny = min(msy + csy + [yy])
maxy = max(msy + csy + [yy])

if (maxx - minx) > 200 or (maxy - miny) > 200:
	print("Dimensions too large for visualization")
	sys.exit(0)

karte = [[' ' for _ in range(maxx - minx + 1)]for _ in range(maxy - miny + 1)]

for mi in range(m):
	karte[msy[mi] - miny][msx[mi] - minx] = 'M'
for ci in range(c):
	karte[csy[ci] - miny][csx[ci] - minx] = 'C'

print()
if karte[yy-miny][xx-minx] != ' ':
	karte[yy-miny][xx-minx] = '+'
	print("+ := target position where a church is already placed")
else:
	karte[yy-miny][xx-minx] = '#'
	print("# := target position")
print()

for i in range(miny, maxy + 1):
	print("{:2d}|{}".format(i, "".join(karte[i-miny])))


