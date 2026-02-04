rng = []
while True:
    s = input()
    if len(s) == 0: break
    l, r = map(int, s.split("-"))
    rng.append((l, r))

ans = 0
while True:
    s = input()
    if len(s) == 0: break
    x = int(s)
    works = any(l <= x <= r for l,r in rng)
    ans += works
print(ans)
