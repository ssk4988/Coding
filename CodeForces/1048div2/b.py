import sys
input = sys.stdin.readline

def main():
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    a.sort(reverse=True)
    ans = 0
    for i, x in enumerate(a):
        ans += x * max(0, m-i)
    print(ans)

nc = int(input())
for cn in range(nc):
    main()
