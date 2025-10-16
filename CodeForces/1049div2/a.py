import sys
input = sys.stdin.readline

# 1110
# 1111100
# 111000
# 011


def main():
    n = int(input())
    s = [c for c in input()[:-1]]
    a = [c for c in s]
    a.sort()
    x = [0] * 2
    for i in range(n):
        if a[i] != s[i]:
            x[ord(a[i])-ord('0')] += 1
    ans = min(x)
    print(ans)


nc = int(input())
for cn in range(nc):
    main()
