from math import acos, sqrt

a, b, c = 5 * 10 ** 6, 5 * 10 ** 6 + 1, 10 ** 7
a, b, c = map(sqrt, [a, b, c])
print(a, b, c)

# :skull:
ANG_EPS = 1e-8
SIDE_EPS = 1e-5


A = acos((b ** 2 + c ** 2 - a ** 2) / (2 * b * c))
B = acos((a ** 2 + c ** 2 - b ** 2) / (2 * a * c))
print(abs(A - B))
# 1e-7

print(abs(sqrt(c) - sqrt(c - 1)))
# 8e-3
