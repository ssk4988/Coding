nc = int(input())
for cn in range(nc):
    p = int(input())
    ps = dict()
    for i in range(p):
        a, b = input().split()
        if ord(a) > ord(b): a, b = b, a
        ps[b] = a
    n = int(input())
    print(f"Test case #{cn+1}:")
    for i in range(n):
        s = input()
        t = s
        s = [ps[x] if x in ps else x for x in s]
        print(t, "YES" if s == s[::-1] else "NO")
    print()
