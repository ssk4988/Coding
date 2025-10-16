import sys
input = sys.stdin.readline

'''
1 10
2 4
8 9


2 10
2 9


1 9
2 9

1 10
2 4
7 8

2 10
2 8

1 8
2 8
'''

def main():
    n = int(input())
    ls = []
    rs = []
    base = 0
    x = (n)//2
    for i in range(n):
        l, r = map(int, input().split())
        base += r-l
        ls.append((l, i))
        rs.append((r, i))
    delta = 0
    rs.sort(reverse=True)
    ls.sort()
    for i in range(min(n, 3)):
        for j in range(n):
            if ls[j][1] == rs[i][1]: continue
            delta = max(delta, x * (rs[i][0] - ls[j][0]))
            break
        for j in range(n):
            if ls[i][1] == rs[j][1]: continue
            delta = max(delta, x * (rs[j][0] - ls[i][0]))
    print(base, base + delta)
    


nc = int(input())
for cn in range(nc):
    main()
