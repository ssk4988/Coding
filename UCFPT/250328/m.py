n = int(input())
prob = []
for i in range(n):
    t = min(x for x in map(int, (input().split()[1:] + ["3000"]))if x != -1)
    prob.append(t)
prob.sort()
ans = 0
t = 0
for p in prob:
    if t + p <= 300: 
        ans += 1
        t += p
print(ans)
# print(prob)
