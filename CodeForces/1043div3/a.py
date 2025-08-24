nc = int(input())
for cn in range(nc):
    n = int(input())
    mid = input()
    m = int(input())
    b = input()
    t = input()
    front = []
    back = []
    for c, w in zip(t, b):
        if c == "V":
            front.append(w)
        else:
            back.append(w)
    res = ''.join(front[::-1]) + mid + ''.join(back)
    print(res)
