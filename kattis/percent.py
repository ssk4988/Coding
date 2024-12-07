for i in range(300):
    for j in range(1, 300):
        frac = i / j
        s = int(round(frac * 10000))
        # print(s)
        if s == 1273 or s == 1236:
            print(i, j, s)

months = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

for start in range(12):
    sm = 0
    for i in range(9):
        sm += months[(start + i) % 12]
    if sm == 275:
        print(start)
