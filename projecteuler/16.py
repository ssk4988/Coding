val = 2 ** 1000
sum = 0
while val > 0:
    sum += val % 10
    val //= 10
print(sum)
