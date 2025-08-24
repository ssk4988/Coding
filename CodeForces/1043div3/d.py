from functools import cache

# numbers, digits, sum of digits
@cache
def dp(zeros, lead, start):
    if zeros == 0:
        return (1 if start else 0, 1 if start else 0, lead)
    nums, digs, digsum = 0, 0, 0
    for next in range(10):
        c_nums, c_digs, c_digsum = dp(zeros-1, next, start or next > 0)
        nums += c_nums
        digs += c_digs + (1 if start else 0) * c_nums
        digsum += c_digsum + lead * c_nums
    return (nums, digs, digsum)

nc = int(input())
for cn in range(nc):
    k = int(input())

    nums, digs, digsum = 0, 0, 0
    last = 0
    last_sum = 0
    last_digs = 0
    for zeros in range(15, -1, -1):
        use = -1
        for lead in range(10):
            c_nums, c_digs, c_digsum = dp(zeros, lead, last_digs > 0 or lead > 0)
            n_nums = nums + c_nums
            n_digs = digs + c_digs + last_digs * c_nums
            n_digsum = digsum + c_digsum + last_sum * c_nums
            if n_digs > k:
                use = lead
                break
            else:
                digs = n_digs
                nums = n_nums
                digsum = n_digsum
        assert(use != -1)
        last *= 10
        last += use
        last_sum += use
        if lead: last_digs += 1
        elif last_digs: last_digs += 1
    # print("status", last, last_sum, last_digs, nums, digs, digsum)
    s = str(last)
    k -= digs
    for i, c in enumerate(s):
        if k:
            k -= 1
            digsum += ord(c) - ord("0")
    print(digsum)

