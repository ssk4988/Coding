strs = input().split(",")
ans = 0
events = []
mx = 0
for term in strs:
    a = list(map(int, term.split("-")))
    events.append(a)
    mx = max(mx, a[1])
print(mx)
pl = -1
seen = set()
p11s = [dict() for _ in range(10)]
p10s = [dict() for _ in range(10)]
for x in range(1, 100000):
    l = len(str(x))
    if l != pl:
        pl = l
        p10s[l] = 10 ** l
    p10 = p10s[l]
    for r in range(2, 12):
        if r not in p11s[l]:
            p = 1
            for i in range(r-1):
                p *= p10
                p += 1
            p11s[l][r] = p
        p = p11s[l][r]
        y = x * p
        works = False
        for c,d in events:
            if c <= y <= d:
                works = True
                break
        if works and y not in seen:
            seen.add(y)
            ans += y
            # print(y, x, l, r)
print(ans)
for i in range(10):
    print(i)
    print(p10s[i])
    print(p11s[i])
