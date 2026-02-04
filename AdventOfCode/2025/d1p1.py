n = int(input())
c = 50
cnt = 0
for i in range(n):
    s = input()
    x = int(s[1:])
    if s[0] == 'L': c -= x
    else: c += x
    c %= 100
    cnt += c == 0
print(cnt)
