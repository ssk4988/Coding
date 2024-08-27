x = [122, 212, 221, 1220, 2120, 2210, 1202, 2102, 2201, 1022, 2012, 2021]
g = 0
from math import gcd
for i in x:
    g = gcd(g, i)
print(g)
