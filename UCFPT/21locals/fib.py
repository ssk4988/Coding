a, b = map(int, input().split())
a1 = a
b1 = b
ans = 0
while True:
    c = (a + b) % 10
    a = b
    b = c
    ans += 1
    if a == a1 and b == b1:
        break
print(ans+2)