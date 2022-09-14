
# Author: Travis Meade
# The solution to the fence problem from UCF LPC 2022 final round
# Use binary search + half-plane intersection

from math import *

PI = 3.1415926535897932384626433832795

oo = 10**9
EPS = 10**-9

class Point:
    def __init__(s, x, y):
        s.x,s.y = x,y
    def __add__(s, o):
        return Point(s.x+o.x, s.y+o.y)
    def __sub__(s, o):
        return Point(s.x-o.x, s.y-o.y)
    def __mul__(s, o):
        return Point(s.x*o, s.y*o)
    def dot(s,o):
        return s.x*o.x+s.y*o.y
    def cross(s,o):
        return s.x*o.y - s.y*o.x
    def rot(s,a):
        global PI
        co = cos(a*PI/180)
        si = sin(a*PI/180)
        return Point(s.x*co-s.y*si,s.y*co+s.x*si)
    def mag(s):
        return sqrt(s.x*s.x+s.y*s.y)
    def norm(s):
        m = s.mag()
        return Point(s.x/m,s.y/m)
    def __str__(s):
        return "("+str(s.x)+", "+str(s.y)+")"

class HP:
    def __init__(s, a, b):
        s.p = Point(a.x, a.y)
        s.pq = b - a
        s.ang = atan2(s.pq.y, s.pq.x)

    def out(s, p):
        return s.pq.cross(p - s.p) < -EPS
    
    def parallel(s,o):
        return s.pq.cross(o.pq) < EPS

    def __lt__(s, o):
        return s.ang < o.ang

    def __str__(s):
        return str(s.p) + " " + str(s.pq)

def inter(s, t):
    alpha = (t.p - s.p).cross(t.pq) / s.pq.cross(t.pq)
    return s.p + (s.pq * alpha)


def hp_intersect(hps):
    box = [Point(oo, oo), Point(-oo, oo), Point(-oo, -oo), Point(oo, -oo)]

    # Very far half-planes are initially added
    for i in range(4):
        hps.append(HP(box[i],box[(i+1)&3]))

    # Sort the halfplanes by angle
    hps.sort()
    q = []
    fptr = 0
    bptr = 0
    

    # Sweep and add halfplanes as necessary
    for i in range(len(hps)):
        # Remove half planes that are hidden at the end
        while bptr - fptr > 1 and hps[i].out(inter(q[bptr-1],q[bptr-2])):
            #print("removed (b) ", q[bptr-1])
            #print("by          ", hps[i])
            #print("by          ", q[bptr-2])
            #pnt = inter(q[bptr-1], q[bptr-2])
            #print("inter       ", pnt)
            #print("v2          ", pnt - hps[i].p)
            #print("cross ", hps[i].pq.cross(pnt - hps[i].p))
            bptr -= 1

        # Remove half planes that are hidden at the front
        while bptr - fptr > 1 and hps[i].out(inter(q[fptr], q[fptr+1])):
            #print("removed (f) ", q[fptr])
            fptr += 1

        # Parallel Case
        if bptr - fptr > 0 and abs(hps[i].pq.cross(q[bptr-1].pq)) < EPS:
            #print("HERE")
            #print(hps[i], q[bptr-1])
            if hps[i].pq.dot(q[bptr-1].pq) < 0:
                return []
            if hps[i].out(q[bptr-1].p):
                #print("removed (p1)", q[bptr-1])
                bptr -= 1
            else:
                #print("removed (p2)",hps[i])
                continue
        
        # Add to the q the new half plane
        if len(q) > bptr:
            q[bptr] = hps[i]
        else:
            q.append(hps[i])
        bptr += 1

    # Final front clean up
    while bptr - fptr > 2 and q[fptr].out(inter(q[bptr-1],q[bptr-2])):
        bptr -=1

    # Final back clean up
    while bptr - fptr > 2 and q[bptr-1].out(inter(q[fptr],q[fptr+1])):
        fptr += 1
   
    # Check that we have enough half-planes
    if bptr - fptr <= 2:
        return []

    res = [inter(q[i], q[i+1]) for i in range(fptr, bptr-1)]
    res.append(inter(q[bptr-1], q[fptr]))

    # Return the set of points
    return res



n,dist = map(int, input().split())
pts = [None] * (n+1)
for i in reversed(range(n)):
    x,y = map(int, input().split())
    pts[i] = Point(x,y)

pts[n] = pts[0]

def cross(a,b,c):
    v1 = a-b
    v2 = c-b
    return abs(v1.cross(v2))

# Rotating calipers to find the farthest 2 points 
def calipers(p):
    n = len(p)
    if not n:
        return 0
    p.append(p[0])
    i = 0
    runner = 1
    res = 0
    for i in range(n):
        cres = (p[i]-p[runner]).mag()
        res = max(res, cres)
        nres = (p[i]-p[runner+1]).mag()
        while cres < nres:
            runner += 1
            if runner == n:
                runner = 0
            res = max(res, nres)
            cres = nres
            nres = (p[i]-p[runner+1]).mag()
    return res
    
def canDo(tar):
    global pts, dist
    hps = [HP(pts[i], pts[i+1]) for i in range(n)]
    for i in range(n):
        hps[i].p = hps[i].p + hps[i].pq.rot(90).norm() * tar
    pts2 = hp_intersect(hps)

    return calipers(pts2) > dist

lo = 0
hi = 1
while canDo(hi): 
    lo = hi
    hi *= 2

for _ in range(60):
    #print(lo,hi)
    mid = (lo+hi)/2
    if canDo(mid):
        lo = mid
    else:
        hi = mid
print(lo)
