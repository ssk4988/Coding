s = input()
from collections import Counter
n = len(s)
c = Counter(s)
mid = ""
if n % 1 == 0:
    for i in range(26):
        ch = chr(i + ord('a'))
        if c[ch] % 2 == 1:
            mid = ch
            c[ch] -= 1
            break
a = []
for i in range(26):
    ch = chr(i + ord('a'))
    while c[ch] > 0:
        a.append(ch)
        c[ch] -= 2
a = ''.join(a)
res = a + mid + a[::-1]
print(res)
