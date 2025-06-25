'''
c to a always - use earliest operations first
b to a always - use earliest operations first
c to b - use latest operations first
c to b to a
b to c to a

given ca, cb, ba, can we do it?
build one by one
'''
from collections import deque

nc = int(input())
for cn in range(nc):
    n, q = map(int, input().split())
    s = [ord(c)-ord('a') for c in input()]
    dq = [[[] for i in range(3)] for j in range(3)]
    for i in range(q):
        x, y = input().split()
        dq[ord(x)-ord('a')][ord(y)-ord('a')].append(i)
    bca = [0]
    # how many bca can make with x ca
    p = len(dq[1][2])-1
    for i in reversed(dq[2][0]):
        while p >= 0 and dq[1][2][p] >= i: p -= 1
        if p >= 0: 
            bca.append(bca[-1]+1)
            p -= 1
        else: bca.append(bca[-1])
    p = len(dq[1][0])
    cba = [0] * len(dq[2][1]) # how many matchings using prefix of dq[2][1]
    for i in reversed(range(len(dq[2][1]))):
        while p-1 >= 0 and dq[1][0][p-1] > dq[2][1][i]:
            p -= 1
        cba[i] = i+len(dq[1][0])-p 
    for i in range(1, len(cba)):
        cba[i] = min(cba[i], cba[i-1])

    def cando(ca, ba, cb):
        if len(dq[2][1]) < cb: return False
        if len(dq[2][0]) < ca and len(dq[1][0]) < ba: return False
        if len(dq[2][0]) >= ca and len(dq[1][0]) >= ba: return True
        if len(dq[2][0]) < ca:
            ba_left = min(len(cba), len(dq[1][0]) - ba)
            return ba_left > 0 and cba[ba_left-1] >= ca - len(dq[2][0])
        else:
            # bca
            ca_left = len(dq[2][0]) - ca
            return bca[ca_left] >= ba - len(dq[1][0])
    ca, ba, cb = 0, 0, 0
    for i in range(n):
        if s[i] == 0: continue
        if s[i] == 1:
            if cando(ca, ba+1, cb):
                ba += 1
                s[i] = 0
        else:
            if cando(ca+1, ba, cb):
                ca += 1
                s[i] = 0
            elif cando(ca, ba, cb+1):
                cb += 1
                s[i] = 1
    print(''.join(chr(ord('a')+c) for c in s))
