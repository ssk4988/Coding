import math
v = 900
plist = []
for i in range(2, 10000):
    works = True
    upb = int(math.sqrt(i) + 1)
    for j in range(2, upb):
        if i % j == 0:
            works = False
            break
    if works:
        v -= math.log10(i)
        plist.append(i)
        if(v <= 0):
            break
    print(i)
print(plist)
print(len(plist))
