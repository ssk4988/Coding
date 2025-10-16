import sys
input = sys.stdin.readline

'''
length z
x * 10 ** z + y is multiple of x+y
'''


def main():
    x = int(input())
    print(10**9-1-x)

nc = int(input())
for cn in range(nc):
    main()
