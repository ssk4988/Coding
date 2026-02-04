n = int(input())
c = [list(map(int, input().split(","))) for i in range(n)]
ans = 0
for a,b in c:
    for x,y in c:
        ans = max(ans, (abs(x-a)+1)*(abs(y-b)+1))
print(ans)
