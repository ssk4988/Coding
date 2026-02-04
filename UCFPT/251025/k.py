n = int(input())
limit = 0
res = None
for i in range(n):
    s = input()
    if s == "/":
        res = None
    else:
        s = int(s)
        while limit <= s: limit += 10
        res = s
    print(limit if res is None else res)
