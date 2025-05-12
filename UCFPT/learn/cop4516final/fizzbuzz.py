nc = int(input())
for cn in range(nc):
    f, b, c, s, e = map(int, input().split())
    for v in range(s, e+1):
        if v % f == 0: print("FIZZ")
        elif v % b == 0: print("BUZZ")
        elif v % c == 0: print("CUZZ")
        else: print(v)
