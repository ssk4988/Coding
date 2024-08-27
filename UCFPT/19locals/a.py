n, d = map(int, input().split())
a = [int(input()) for i in range(n)]
tot = sum(a)
for i in range(n):
    print(a[i] * d // tot)
    