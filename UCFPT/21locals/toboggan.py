l, n, timelimit = map(int, input().split())

lo = 0.0
hi = 2e20 + 10.0
eps = 1e-9

boosts = list(map(float, input().split()))
boosts.append(float(l))
boosts.sort()

def test(jump):
    pos = 0
    v = jump
    t = 0
    for b in boosts[1:]:
        dist = b - pos
        drift = pos + v ** 2 / 2
        if drift < b:
            return False
        insqrt = v ** 2 - 2 * dist
        insqrt = max(0, insqrt)
        reach = v - insqrt ** 0.5
        pos = b
        v -= reach
        v += jump
        t += reach
        # print(f"at {b} pos={pos} v={v} t={t} reach={reach} dist={dist}")
    # print(jump, works, t)
    return t <= timelimit
assert(test(hi))
for iter in range(500):
    mid = (lo + hi) / 2
    
    if test(mid):
        hi = mid
    else: lo = mid
print(f"{lo:.30f}")