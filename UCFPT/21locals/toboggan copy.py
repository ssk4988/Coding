l, n, timelimit = map(int, input().split())

lo = 0.0
hi = 2 * 10 ** 9 + 10.0
eps = 1e-9

boosts = list(map(float, input().split()))
boosts.append(float(l))

def test(jump):
    pos = 0
    v = jump
    t = 0
    for b in boosts[1:]:
        dist = b - pos
        drift = pos + v ** 2 / 2
        if drift < b:
            return False
        lo = 0.0
        hi = v
        for it in range(100):
            mid = (lo + hi) / 2
            if mid * (v - mid/2) < dist:
                lo = mid
            else: hi = mid
        # insqrt = max(0, insqrt)
        reach = lo
        pos = b
        v -= reach
        v += jump
        t += reach
        # print(f"at {b} pos={pos} v={v} t={t} reach={reach} dist={dist}")
    # print(jump, works, t)
    return t <= timelimit - eps
assert(test(hi))
for it in range(200):
    mid = (lo + hi) / 2
    
    if test(mid):
        hi = mid
    else: lo = mid
print(f"{lo:.8f}")