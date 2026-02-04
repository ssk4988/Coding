n = int(input())
for a in range(-999, 1000):
    if a == 0: continue
    b = n - a
    if b == 0 or b < -999 or b > 999: continue
    print(a, b)
    break
