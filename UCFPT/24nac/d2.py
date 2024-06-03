x = list(map(int, input().split()))
a = list(map(int, input().split()))
b = list(map(int, input().split()))
n = x[0]
m = x[1]
for i in range(2):
    works = True
    idx = a.index(b[0])
    for j in range(m):
        if a[(j + idx)%n] != b[j]: works = False
    if works:
        print(1)
        exit()
    a = a[::-1]
print(0)
