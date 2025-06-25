n = int(input())
m, a = 0, 1
for x in [int(input()) for _ in range(n)]:
    if x > m:
        a += x-m+1
    m = x
print(a)
