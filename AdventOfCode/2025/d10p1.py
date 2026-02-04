nc = int(input())
res = 0
for cn in range(nc):
    s = input().split()
    print(s)
    n = len(s[0])-2
    need = 0
    print(s[0], n)
    for i in range(n):
        need += (s[0][1+i] == '#') << i
    toggles = []
    for j in range(1, len(s)-1):
        toggles.append(0)
        for i in list(map(int, s[j][1:-1].split(","))):
            toggles[-1] += 1 << i
    seen = set()
    q = [(0, 0)]
    ans = 0
    for d, mask in q:
        if mask in seen: continue
        seen.add(mask)
        if mask == need: ans = d
        for x in toggles:
            q.append((d+1, mask ^ x))
    print(ans)
    res += ans
print(res)
