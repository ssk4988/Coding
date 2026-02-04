from random import randint
nc = int(input())
res = 0
for cn in range(nc):
    s = input().split()
    print(s)
    n = len(s[0])-2
    target = list(map(int, s[-1][1:-1].split(",")))
    print(target)
    toggles = []
    for j in range(1, len(s)-1):
        toggles.append(list(map(int, s[j][1:-1].split(","))))
    seen = set()
    rands = [randint(1, 10 ** 9) for i in range(n)]
    def hash(x):
        return sum(a*b for a,b in zip(rands, x))
    targethash = hash(target)
    q = [(0, [0] * n, 0)]
    ans = 0
    for d, mask, start in q:
        mask2 = hash(mask)
        if mask2 in seen: continue
        seen.add(mask2)
        if mask2 == targethash: 
            ans = d
            break
        for i in range(start, len(toggles)):
            mask2 = mask.copy()
            works = True
            for y in toggles[i]:
                mask2[y] += 1
                if mask2[y] > target[y]:
                    works = False
                    break
            if works:
                q.append((d+1, mask2, i))
    print(ans)
    res += ans
print(res)
