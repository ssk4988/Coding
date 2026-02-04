from math import tan, acos
tc = int(input())
for i in range(tc):
    n, l, d, g = map(int, input().split())
    apothem = l / 2 / tan(acos(-1) / n)
    area = apothem * l / 2 * n
    tot = area + n * l * d * g + acos(-1) * (d * g) ** 2
    print(f"{tot:.10f}")
