v = 1
for i in range(1, 101):
    v *= i
sum = 0
while v > 0:
    sum += v % 10
    v //= 10

print(sum)
