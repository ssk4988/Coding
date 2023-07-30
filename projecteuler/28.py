ans = 1
w = 2
v = 1
for i in range(500):
    for j in range(4):
        v += w
        ans += v
    w += 2

print(ans)