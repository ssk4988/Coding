s = input()
from collections import Counter

c = Counter(s)
odd = True
even = True

for f in c.values():
    if f & 1: even = False
    else: odd = False
if not odd and not even:
    print("0/1")
elif odd: print("1")
elif even: print("0")

