n, m = map(int, input().split())
cnt = [0] * n
for i in range(m):
    a, b = map(int, input().split())
    a -= 1; b -= 1
    cnt[a] -= 1
    cnt[b] += 1

print("\n".join(list(map(str, cnt))))