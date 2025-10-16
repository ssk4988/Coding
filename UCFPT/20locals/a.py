g, p, t = map(int, input().split())
a = p * g
b = g + t * p
if a == b:
    print(0)
elif a < b:
    print(1)
else:
    print(2)
