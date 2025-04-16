s = input()
n = int(input())
ws = [input() for i in range(n)]
q = [[] for _ in range(26)]
ans = 0
for i, w in enumerate(ws):
    q[ord(w[0]) - ord('a')].append((i, 0))
for c in s:
    cid = ord(c) - ord('a')
    buffer = []
    for wid, idx in q[cid]:
        if idx == len(ws[wid])-1:
            ans += 1
        else:
            cid1 = ord(ws[wid][idx+1]) - ord('a')
            if cid1 != cid:
                q[cid1].append((wid, idx+1))
            else:
                buffer.append((wid, idx+1))
    q[cid].clear()
    q[cid] = buffer
print(ans)