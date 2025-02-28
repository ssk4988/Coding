from functools import cache
while True:
    lim = input()
    if int(lim) < 0: break
    digs = [int(d) for d in lim]
    p10 = [1] * len(digs)
    for i in reversed(range(len(digs)-1)):
        p10[i] = p10[i+1] * 10
    # ways, sum
    @cache
    def dp(idx, match):
        if idx == len(digs): return [1, 0]
        ways, sm = 0, 0
        for d in range(2):
            if d > digs[idx] and match: continue
            ways1, sm1 = dp(idx+1, match and d == digs[idx])
            ways += ways1
            sm += d * p10[idx] * ways1 + sm1
        return [ways, sm]
    print(dp(0, True)[1])
