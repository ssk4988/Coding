
n = int(input())
m = int(input())

from random import randint

s = []
t = []
for i in range(n):
    s.append(chr(ord('a') + randint(0, 25)))
for i in range(m):
    t.append(chr(ord('a') + randint(0, 25)))
k = randint(1, 8 * 10 ** 18)
print(''.join(s))
print(''.join(t))
print(k)
