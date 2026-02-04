n = int(input())
digits = []
for i in range(n-1):
    s = input()
    if i == 0: digits = [0] * len(s)
    for j in range(len(s)):
        if s[j] == ' ': continue
        digits[j] *= 10
        digits[j] += ord(s[j]) - ord('0')
print(digits)
ops = input()
terms = []
ans = 0
for j in range(len(ops))[::-1]:
    if digits[j]: terms.append(digits[j])
    if ops[j] == ' ': continue
    print(terms, ops[j])
    cur = 1 if ops[j] == '*' else 0
    for x in terms:
        if ops[j] == '*': cur *= x
        else: cur += x
    terms = []
    ans += cur
print(ans)
