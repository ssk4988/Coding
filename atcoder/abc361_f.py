n = int(input())
mobius = [0] * 100
mobius[1] = 1
for i in range(1, 100):
    for j in range(i*2, 100, i):
        mobius[j] -= mobius[i]
ans = n
for i in range(2,100):
    cnt = int(n ** (1/i))
    while (cnt+1) ** i <= n: cnt += 1
    while cnt ** i > n: cnt -= 1
    ans += cnt * mobius[i]
print(n-ans+1)
