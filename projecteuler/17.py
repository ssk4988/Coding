letters = 11 

def chlen(v):
    if v == 1 or v == 2 or v == 6:
        return 3
    if v == 4 or v == 5 or v == 9:
        return 4
    if v == 3 or v == 7 or v == 8:
        return 5
    if v == 0:
        return 0
    return 1000000000

def chcount(i):
    letters = 0
    l = []
    v = i
    while v > 0:
        l.append(v % 10)
        v //= 10
    if i >= 100:
        if i % 100 != 0:
            letters += 3 # and
        letters += 7 # hundred
        letters += chlen(l[2])
    if(len(l) >= 2):
        # if l[1] == 1:
        #     letters += 3
        if l[1] == 2:
            letters += 6
        elif l[1] == 3:
            letters += 6
        elif l[1] == 4 or l[1] == 5 or l[1] == 6:
            letters += 5
        elif l[1] > 6:
            letters += chlen(l[1]) + 2
        if l[1] == 8:
            letters -= 1
    letters += chlen(l[0])
    b = i % 100
    if b >= 10 and b < 20:
        letters -= chlen(l[0])
        if b == 10:
            letters += 3
        if b == 11 or b == 12:
            letters += 6
        if b == 13 or b == 14 or b == 18 or b == 19:
            letters += 8
        if b == 15 or b == 16:
            letters += 7
        if b == 17:
            letters += 9
    return letters

# one thousand
for i in range(1, 1000):
    letters += chcount(i)
print(letters)
for i in range(1, 6):
    print(chcount(i))

print(chcount(342)) # 23
print(chcount(115)) # 20
print(chcount(200)) # two hundred = 10
print(chcount(999)) # nine hundred and ninety-nine = 24
