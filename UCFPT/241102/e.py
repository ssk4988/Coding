n, k = map(int, input().split())
a = [list(map(int, input().split())) for _ in range(n)]
pos = [(x,t) for x,t in a if x > 0]
neg = [(-x,t) for x,t in a if x < 0]
pos.sort(), neg.sort()
pos.reverse(), neg.reverse()
b = []
for v in [pos, neg]:
    cur = []
    prv = None
    for x,t in v:
        while t:
            if prv is None:
                cur.append(x)
                prv = k
            amt = min(t, prv)
            prv -= amt
            t -= amt
            if prv == 0: prv = None
                
    b.append(cur)

ans = 2 * sum(b[0]) + 2 * sum(b[1])
print(ans)
            
