n, p = map(int, input().split())
x = 0
for i in range(n):
    c = int(input())
    if x + (i+1)*(c-1) >= p:
        print(i)
        exit()
    x += c
print(n)
