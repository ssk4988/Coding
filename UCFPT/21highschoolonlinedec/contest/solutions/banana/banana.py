import itertools
import math

def dist(a, b, c, d):
    xDist = a - c
    yDist = b - d
    return math.sqrt(xDist * xDist + yDist * yDist)

testCases = int(input())

for tt in range(testCases):
    n = int(input())
    badX = []
    badY = []
    goodX = []
    goodY = []
    
    for i in range(n):
        inp = input().split(" ")
        badX.append(int(inp[0]))
        badY.append(int(inp[1]))
        
    for i in range(n):
        inp = input().split(" ")
        goodX.append(int(inp[0]))
        goodY.append(int(inp[1]))
        
    perm = []
    for i in range(n):
        perm.append(i)
    
    allPerm = list(itertools.permutations(perm))
    bestDist = 10000.0
    
    for p in allPerm:
        curr = 0.0
        for i in range(n):
            curr += dist(badX[p[i]], badY[p[i]], goodX[i], goodY[i])
        bestDist = min(bestDist, curr)
    print(bestDist)
