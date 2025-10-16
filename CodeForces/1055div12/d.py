import sys
# sys.setrecursionlimit(3 * 10 ** 5)
input = sys.stdin.readline

def solve():
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    pref = [0] * (n+1)
    cnt0 = [0] * (n+1)
    cnt1 = [0] * (n+1)
    for i in range(n):
        pref[i+1] = pref[i] + (a[i].bit_length()-1)
        cnt0[i+1] = cnt0[i] + (a[i].bit_count() == 1)
        cnt1[i+1] = cnt1[i] + ((a[i]-1).bit_count() == 1 and a[i] != 2)
    for qid in range(q):
        l, r = map(int, input().split())
        l -= 1
        ans = pref[r]-pref[l]
        c1 = cnt1[r]-cnt1[l]
        c0 = cnt0[r]-cnt0[l]
        ans += (r-l)-(c1+c0)
        ans += (c1)//2
        print(ans)

nc = int(input())
for cn in range(nc):
    solve()
