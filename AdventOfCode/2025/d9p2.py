n = int(input())
c = [list(map(int, input().split(","))) for i in range(n)]
cs = []
for i in range(n):
    c[i][0], c[i][1] = c[i][1], c[i][0]
    cs.append(c[i][0])
    cs.append(c[i][1])
cs = list(set(cs))
cs.sort()
label = dict()
m = len(cs)
for i in range(m):
    label[cs[i]] = i
for i in range(n):
    c[i][0] = label[c[i][0]]
    c[i][1] = label[c[i][1]]
inside = [[0] * (m+1) for i in range(m+1)]
for i in range(m):
    for j in range(m):
        cnt = 0
        for i1 in range(n):
            j1 = (i1+1)%n
            if c[i1][0] == c[j1][0]:
                low = min(c[i1][1], c[j1][1])
                high = max(c[i1][1], c[j1][1])
                if c[i1][0] == i and low <= j <= high:
                    inside[i+1][j+1] = 1
                elif c[i1][0] < i and low <= j-0.5 <= high:
                    cnt += 1
            else:
                low = min(c[i1][0], c[j1][0])
                high = max(c[i1][0], c[j1][0])
                if c[i1][1] == j and low <= i <= high:
                    inside[i+1][j+1] = 1
        if cnt % 2 == 1:
            inside[i+1][j+1] = 1
for i in range(1, m+1):
    for j in range(1, m+1):
        inside[i][j] += inside[i-1][j]+inside[i][j-1]-inside[i-1][j-1]


ans = 0
for a,b in c:
    for x,y in c:
        r1, r2 = min(a, x), max(a, x)+1
        c1, c2 = min(b, y), max(b, y)+1
        if inside[r2][c2]-inside[r1][c2]-inside[r2][c1]+inside[r1][c1] == (r2-r1)*(c2-c1):
            area = (cs[r2-1]+1-cs[r1])*(cs[c2-1]+1-cs[c1])
            ans = max(ans, area)
print(ans)
