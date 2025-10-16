import sys
input = sys.stdin.readline

def main():
    a, b = map(int, input().split())
    if a > b: a, b = b, a
    if a == b: print(0)
    elif b % a == 0: print(1)
    else: print(2)

nc = int(input())
for cn in range(nc):
    main()
