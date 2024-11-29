n = int(input())
ans = set()
anses = [set() for _ in range(n+1)]
def bt(a, k):
    anses[len(a)].add((tuple(a), k))
    if len(a) == n:
        ans.add((tuple(a),k))
        return
    for i in range(len(a)+1):
        a1 = a[:i] + [k] + a[i:]
        k1 = k
        for j in range(i):
            if k < a[j]: k1 += 1
        for j in range(i, len(a)):
            if k > a[j]: k1 += 1
        bt(a1, k1)

bt([0,1],0)
for v in ans:
    if v[1] >= 2: continue
    print(v)
print(len(ans))
for i in range(n+1):
    cnt = 0
    for v in anses[i]:
        if v[1] < 2: continue
        if v[1] in v[0]: continue
        cnt += 1
    print(i, cnt, len(anses[i]))
