a = []
for i in range(5):
    a.append(int(input()))
works = a[0] == a[1] and a[1] == a[2] and a[2] == a[3]
for i in range(4):
    a[i] += a[4]
    works = works or (a[0] == a[1] and a[1] == a[2] and a[2] == a[3])
    a[i] -= a[4]
print(1 if works else 0)
