tc = int(input())
print(tc)
from random import randint
for i in range(tc):
    r = randint(1, 50)
    c = randint(1, 50)
    while r == 1 and c == 1:
        c = randint(1, 50)
    r1 = randint(1, r)
    c1 = randint(1, c)
    r2 = randint(1, r)
    c2 = randint(1, c)
    while r2 == r1 and c1 == c2:
        r2 = randint(1, r)
        c2 = randint(1, c)
    print(r, c, r1, c1, r2, c2)
