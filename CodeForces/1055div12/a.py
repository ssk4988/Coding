import sys
# sys.setrecursionlimit(3 * 10 ** 5)
input = sys.stdin.readline

def solve():
    n = int(input())
    a = list(map(int, input().split()))
    b = set(a)
    ans = len(b) * 2 - 1
    # for x in b:
    #     for y in a:
    #         ans += y < x
    print(ans)

nc = int(input())
for cn in range(nc):
    solve()
