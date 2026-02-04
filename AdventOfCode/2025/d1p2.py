n = int(input())
c = 50
cnt = 0
for i in range(n):
    s = input()
    x = int(s[1:])
    while x:
        if s[0] == 'L': c -= 1
        else: c += 1
        c %= 100
        cnt += c == 0
        x -= 1
print(cnt)
