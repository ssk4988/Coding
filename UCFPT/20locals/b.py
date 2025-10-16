n = int(input())
v = [0] * 2
e = [0] * 2
for i in range(n):
    e1, v1, v2 = map(int, input().split())
    v[0] += v1
    v[1] += v2
    if v1 > v2:
        e[0] += e1
    else:
        e[1] += e1
if e[0] > e[1] and v[0] > v[1]:
    print(1)
elif e[0] < e[1] and v[0] < v[1]:
    print(2)
else:
    print(0)
