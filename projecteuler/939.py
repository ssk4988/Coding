from functools import cache
from itertools import product
@cache
def dp(left, right):
    left = list(left)
    right = list(right)
    if sum(left) + sum(right) == 0: return False
    for i in range(len(left)):
        if not dp(tuple(sorted(right)), tuple(sorted(left[:i] + left[i+1:]))):
            return True
    for i in range(len(right)):
        right1 = right[:i] + ([] if right[i] == 1 else [right[i]-1]) + right[i+1:]
        if not dp(tuple(sorted(right1)), tuple(sorted(left))): return True
    return False

def gen_partitions(k):
    ways = [[] for _ in range(k+1)]
    ways[0].append([])
    for part in range(1, k+1):
        for amt in range(k-part+1):
            for arr in ways[amt]:
                ways[amt+part].append(arr.copy() + [part])
    return ways

lim = 7
partitions = gen_partitions(lim)
for i in range(len(partitions)):
    print(f"num partitions of k={i} is {len(partitions[i])}")
    print(partitions[i])

wins = set()

for size in range(lim+1):
    for left_size in range(size+1):
        right_size = size - left_size
        for left_part, right_part in product(partitions[left_size], partitions[right_size]):
            if dp(tuple(left_part), tuple(right_part)):
                wins.add((tuple(left_part), tuple(right_part)))

print("ways: ", len(wins))
for left_part, right_part in wins:
    print(sum(left_part)+sum(right_part), left_part, right_part)

bools = [False, True]
for tl, tr in product(bools, bools):
    print("\n\n")
    print(tl, tr)
    cnt = 0
    for left_part, right_part in wins:
        if not dp(tuple(left_part), tuple(right_part))==tl or not dp(tuple(right_part), tuple(left_part))==tr: continue
        print(sum(left_part)+sum(right_part), left_part, right_part)
        cnt += 1
    print(cnt)
