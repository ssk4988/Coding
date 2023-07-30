fact = [1]
for i in range(10):
    fact.append(fact[-1] * i)
ans = 0
for i in range(10, 10000000):
    sum = 0
    s = i
    while s > 0:
        sum += fact[s % 10]
        s //= 10
    if sum == i:
        ans += i
        print(i)
print(ans)