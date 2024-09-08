nc = int(input())

RNG = 27

def gen(val):
    # res = "".join(map(str, range(max(1, val - RNG), val + RNG)))
    # return res, max(1, val - RNG)
    res = ""
    cnt, times = 0, 0
    for i in range(val, val + RNG):
        res += str(i)
        cnt += len(str(i))
        if cnt >= RNG: times += 1
        if times >= 2: break
    cnt, times = 0, 0
    mn = val
    for i in range(val-1, max(1, val - RNG) - 1, -1):
        res = str(i) + res
        cnt += len(str(i))
        mn = i
        if cnt >= RNG: times += 1
        if times >= 2: break
    return res, mn

def matches(s, wild):
    return all(a == b or b == "?" for a,b in zip(s, wild))

for cn in range(nc):
    s = input()
    ans = None
    def try_val(val):
        global ans
        res, st = gen(val)
        st -= 1
        # print(res, s)
        start_idx = 0
        pw, digs = 1, 1
        while pw <= st:
            start_idx += (min(pw * 10 - 1, st) - pw + 1) * digs
            pw *= 10
            digs += 1
        for i in range(0, len(res) - len(s) + 1):
            if matches(res[i:i + len(s)], s):
                cand = start_idx + i + 1
                # print(val, cand, res, s)
                if ans is None or cand < ans: ans = cand
                break
    for i in range(RNG):
        try_val(10 ** i)
    for digs in range(1, len(s) + 1):
        for offset in range(digs):
            # if offset + digs > len(s):
            #     break
            deductions = [set() for _ in range(digs)]
            for i in range(offset - digs, len(s), digs):
                for j in range(digs):
                    if i + j >= 0 and i + j < len(s) and s[i + j] != "?":
                        deductions[j].add(ord(s[i + j]) - ord('0'))
            deductions = list(map(list, deductions))
            pref = ""
            for bf in range(digs):
                for dig in range(1 if bf == 0 else 0, 10):
                    cur = pref + str(dig) + "9" * (digs - 1 - bf)
                    try_val(int(cur))

                if len(deductions[bf]) > 1: break
                if len(deductions[bf]):
                    pref += str(deductions[bf][0])
                else:
                    pref += str(1 if bf == 0 else 0)
                if pref[0] == "0": break
            if len(pref) == digs and pref[0] != "0":
                try_val(int(pref))
    if not ans: 
        ans = -1
        assert(False)
    print(ans % 998244353)
