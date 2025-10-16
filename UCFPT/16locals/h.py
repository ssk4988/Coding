lim = 10 ** 7
from random import randint
print(1)
n = 10 ** 6
a = [0 if i < n//2 else randint(0, lim) for i in range(n)]
print(n)
print(*a)
