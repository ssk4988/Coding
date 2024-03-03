b = int(input())
for i in range(0, 1000000, 2):
    if i * i >= b * 2:
        print((i * i - b * 2) // 2)
        break