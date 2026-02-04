strs = input().split(",")
ans = 0
events = []
mx = 0
for term in strs:
    a = list(map(int, term.split("-")))
    events.append(a)
    mx = max(mx, a[1])
print(mx)
p10 = 1
pl = -1
for x in range(1, 100000):
    l = len(str(x))
    if l != pl:
        pl = l
        p10 = 10 ** l
    y = x * p10 + x
    works = False
    for c,d in events:
        if c <= y <= d:
            works = True
            break
    if works:
        ans += y
print(ans)
