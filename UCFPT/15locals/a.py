nc = int(input())
for i in range(nc):
    hasmack = False
    haszack = False
    s = ""
    li = [int(v) for v in input().split()]
    for v in li:
        if v == 18:
            hasmack = True

        if v == 17:
            haszack = True
        s += str(v)
        s += " "
    print(s)
    if hasmack and haszack:
        print("both")
    elif hasmack:
        print("mack")
    elif haszack:
        print("zack")
    else:
        print("none")
    print()
