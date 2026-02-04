n,e = map(int, input().split())
pref = 0
# how far to wrap around to make subarray sum correct
back = [-1] * n
back[0] = 0
prv = [-1] * n
prv[0] = 0
# in wraparound, how much less is the sum than cur * len
diff = [-1] * n
diff[0] = 0
cur = 1
left = n-1
while left > 0 and cur < 4 * n + 5:
    pref += cur
    x = pref % n
    print(pref, cur, x, left)
    if prv[x] == -1:
        prv[x] = cur
        diff[x] = pref
    elif back[x] == -1:
        left -= 1
        back[x] = cur - prv[x]
        diff[x] = (back[x]+1) * cur - (pref - (diff[x]-prv[x]))
    cur += 1
print("cur", cur)
print("back", back)
print("diff", diff)
cure = e
delta = 0
dist = 0
mindelta = 0
seen = [False] * n
cycled = False
adde = 0
while True:
    x = dist % n
    wrap = back[x]
    if wrap >= cure:
        break
    if seen[x]: 
        cycled = True
        break
    adde += wrap + 1
    dist += cure * (wrap + 1) - diff[x]
    cure -= wrap
    mindelta = min(mindelta, cure - e)
    cure += 1
    seen[x] = True
if cycled:
    cycledelta = cure - e
    if cycledelta >= 0:
        print("infinity")
        exit()
    numcycles = (cure + max(0, mindelta) - 1) // -cycledelta
    if numcycles > 0:
        starting = dist + cycledelta * adde
        change = cycledelta * adde
        dist += (2 * starting + change * (numcycles - 1)) * numcycles // 2
        cure -= cycledelta * numcycles
while True:
    x = dist % n
    wrap = back[x]
    if wrap >= cure:
        break
    dist += cure * (wrap + 1) - diff[x]
    cure -= wrap
    cure += 1
while cure > 0:
    dist += cure
    if dist % n == 0:
        cure += 1
    else:
        cure -= 1
print(dist)
