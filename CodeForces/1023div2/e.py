n = 10 ** 5
ans = 0
for i in range(n):
    ans += i * (n-1-i)
print(ans)
