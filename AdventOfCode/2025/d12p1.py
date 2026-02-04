n, q = map(int, input().split())
cnt = [0] * n
for i in range(n):
    for j in range(5):
        s = input()
        cnt[i] += s.count("#")
print(cnt)
ans = 0
for i in range(q):
    s = input().split()
    dims = s[0][:-1].split("x")
    area = int(dims[0]) * int(dims[1])
    s = list(map(int, s[1:]))
    need = sum(x*y for x,y in zip(s, cnt))
    ans += need <= area
    print(need, area, need <= area)
print(ans)
