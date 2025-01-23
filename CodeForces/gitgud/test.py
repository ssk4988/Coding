import math

def f(x):
    return int(0.5 * x**4 + 2 * x**3 - 1.5 * x**2 + 5 * x)

n = int(input())
for i in range(0, n):
    print(f(i))
