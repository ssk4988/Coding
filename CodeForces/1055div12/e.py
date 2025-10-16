import sys
# sys.setrecursionlimit(3 * 10 ** 5)
input = sys.stdin.readline

def solve():
    n = int(input())
    n2 = n * n + 1
    used = [False] * n2
    adj = [[] for _ in range(n2)]
    for qid in range(n):
        a = [i+1 for i in range(n2) if not used[i]]
        print("?", len(a), *a, flush=True)
        
        b = list(map(int, input().split()))[1:]
        if len(b) > n:
            print("!", *(b[:n+1]), flush=True)
            return
        for i in range(len(b)):
            lim = n2+1
            if i + 1 < len(b):
                lim = b[i+1]
            for j in range(b[i]+1, lim):
                if not used[j-1]:
                    adj[j-1].append(b[i]-1)

        for x in b:
            used[x-1] = True
    lds = [[] for _ in range(n2)]
    for i in range(n2):
        best = -1
        for j in adj[i]:
            if best == -1 or len(lds[best]) < len(lds[j]):
                best = j
        if best != -1:
            lds[i] = lds[best].copy()
        lds[i].append(i+1)
        if len(lds[i]) > n:
            print("!", *(lds[i][:n+1]), flush=True)
            return
    assert(False)
        

nc = int(input())
for cn in range(nc):
    solve()
