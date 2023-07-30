sum = 0

for i in range(2, 1000000):
    s = 0
    v = i
    while v > 0:
        s += (v % 10) ** 5
        v //= 10
    if s == i:
        sum += i


print(sum)