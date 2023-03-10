def fact(n):
    if n <= 1: return 1
    return n * fact(n - 1)
for i in range(50):
    print(str(i) + " " + str(fact(2 * i) / fact(i) / fact(i)))