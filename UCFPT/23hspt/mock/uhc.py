n = int(input())
prob = [float(i) for i in input().split()]
time = [float(i) for i in input().split()]
ans = [time[0] / prob[0]]
for i in range(1, n):
    ans.append((ans[-1] + time[i]) / prob[i])
print(ans[-1])