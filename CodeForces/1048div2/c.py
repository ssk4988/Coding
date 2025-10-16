import sys
input = sys.stdin.readline

'''
8 5

4 4
6 2
3 5


16 11

8 8
4 12
2 14
9 7


5 11
10 6  5 3
      2 6  1 3
           2 2
'''

def main():
    k, x = map(int, input().split())
    ans = []
    a, b = x, (2 ** (k+1))-x
    while a != b:
        while a % 2 == 0 and b % 2 == 0:
            a //= 2
            b //= 2
        # print(a, b)
        if a < b:
            ans.append(1)
            b = (a+b)-2*a
            a *= 2
        else: 
            ans.append(2)
            a = (a+b)-2*b
            b *= 2
    ans.reverse()
    print(len(ans))
    print(*ans)


nc = int(input())
for cn in range(nc):
    main()
