from fractions import Fraction
a = list(map(int, input().split()))
n = a[0]
x = Fraction(a[1], a[2])
y = Fraction(a[3], a[4])
z = Fraction(a[5], a[6])

def mid(f):
    return Fraction(1, 3) < f < Fraction(2, 3)

def third(f: Fraction):
    if f < Fraction(1,3): return f * 3
    if f < Fraction(2,3): return (f - Fraction(1,3)) * 3
    return (f - Fraction(2,3)) * 3

for i in range(n):
    sm = sum(mid(f) for f in [x,y,z])
    if sm >= 2:
        print(0)
        exit()
    x = third(x)
    y = third(y)
    z = third(z)

print(1)
