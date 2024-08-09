n = int(input())

cnt = [0] * n
for i in range(n-1):
    a, b = list(map(int, input().split()))
    cnt[a-1] += 1
    cnt[b - 1] += 1
MD = 1000000007
ans = 0
for i in range(n):
    ans += pow(2, cnt[i], MD)
ans -= n
ans -= n-1
ans += MD
ans %= MD
print(ans)
