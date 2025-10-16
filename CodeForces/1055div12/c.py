import sys
# sys.setrecursionlimit(3 * 10 ** 5)
input = sys.stdin.readline

def solve():
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    pref = [[0] * 2 for _ in range(n+1)]
    alt = [n] * n
    for i in range(n):
        for j in range(2):
            pref[i+1][j] = pref[i][j]
        pref[i+1][a[i]] += 1
    for i in reversed(range(n-1)):
        alt[i] = i+1 if a[i+1] == a[i] else alt[i+1]
    for qid in range(q):
        l, r = map(int, input().split())
        l -= 1
        works = True
        for i in range(2):
            if (pref[r][i] - pref[l][i]) % 3 != 0: works = False
        if not works:
            print(-1)
            continue
        ans = (r-l)//3
        if alt[l] >= r:
            ans += 1
        print(ans)
    

nc = int(input())
for cn in range(nc):
    solve()
