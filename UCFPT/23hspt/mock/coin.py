inp = [float(i) for i in input().split()]

areaex = inp[1] - 2 * inp[0]
areaex = max(0, areaex)
areaex /= inp[1]
areaex **= 2

print(1 - areaex)