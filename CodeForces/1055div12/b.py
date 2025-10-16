import sys
# sys.setrecursionlimit(3 * 10 ** 5)
input = sys.stdin.readline

def solve():
    n, rk, ck, rd, cd = map(int, input().split())
    if rd < rk:
        rd = n - rd
        rk = n - rk
    if cd < ck:
        cd = n - cd
        ck = n - ck
    ans = 0
    for _ in range(2):
        cans = -1
        dif = 2 ** 30
        while dif:
            cur = cans + dif
            rk1, ck1 = rk, ck
            # rd1, cd1 = rd, cd
            left = cur
            amt = min(rk1, left)
            left -= amt
            rk1 -= amt
            amt = min(ck1, left)
            left -= amt
            ck1 -= amt
            if max(abs(ck1 - cd), abs(rk1 - rd)) > cur:
                cans = cur
            dif //= 2
        cans += 1
        ans = max(ans, cans)
        rk, ck = ck, rk
        rd, cd = cd, rd
    # dr = abs(rd-rk)
    # dc = abs(cd-ck)
    # ans = max(dr + cd, dc + rd)
    # ans = max(rk + max(dr, cd-rk), ck + max(dc, rd-ck))
    # ans = max(dr, dc) + min(dr, dc)
    # ans = max(rk, ck)
    print(ans)
    # if dr == 0:
    #     ans = max(ans, dc)
    # else:
    #     ans = max(ans, dr + )

nc = int(input())
for cn in range(nc):
    solve()
