import sys
input = sys.stdin.readline

# -2 * a[even] + 2 * a[odd]

def main():
    n = int(input())
    a = list(map(int, input().split()))
    ans = 0
    for i in range(n):
        if i&1:
            ans -= a[i]
        else: ans += a[i]
    delta = (n-1)//2*2
    best = [-(10 ** 10)] * 2
    for i in range(n):
        delta = max(delta, i + (2 * a[i] if i&1 else -2 * a[i]) + best[(i&1)^1])
        best[i&1] = max(best[i&1], (2 * a[i] if i&1 else -2 * a[i]) - i)
    print(ans + delta)

nc = int(input())
for cn in range(nc):
    main()
