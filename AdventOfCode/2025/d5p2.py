rng = []
while True:
    s = input()
    if len(s) == 0: break
    l, r = map(int, s.split("-"))
    rng.append((l, r+1))

rng.sort()
cur = [0, 0]
ans = 0
for l,r in rng:
    if l > cur[1]:
        ans += cur[1]-cur[0]
        cur = [l,r]
    else:
        cur[1] = max(cur[1], r)
ans += cur[1] - cur[0]
print(ans)
