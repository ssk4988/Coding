n = int(input())

a = []
for i in range(n):
    a.append(int(input()))

works = False
for i in range(n):
    b = a.copy()
    b[i] += 1
    if b != b[::-1]: works = True
print(1 if works else 0)
