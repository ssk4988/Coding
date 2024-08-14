n = int(input())
s = input()
t = input()

add = 0
ans = 0
for i in range(n):
    a = (ord(s[i]) - ord('a' )+ add) % 26
    b = (ord(t[i]) - ord('a'))
    if a == b: continue
    ans += 1
    add += (b + 26 - a) % 26
    add %= 26
print(ans)
