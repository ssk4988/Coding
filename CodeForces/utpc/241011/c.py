n, k = map(int, input().split())
a = [1 for _ in range(n)]
for i in range(n):
    if i < k:
        a[i] = n - k + i + 1
    else:
        a[i] = n - k - (i - k)

print(*a)
