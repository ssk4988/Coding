from queue import Queue
t1 = input()
t2 = input()
t1 = [int(i) for i in t1.split(':')]
t2 = [int(i) for i in t2.split(':')]

t1 = 60 * t1[0] + t1[1]
t2 = 60 * t2[0] + t2[1]

dp = [-1 for i in range(24 * 60)]
dp[t1] = 0
mm = 24 * 60
q = Queue()
q.put(t1)
while not q.empty():
    t = q.get()
    if dp[(t + 1) % mm] == -1:
        dp[(t + 1) % mm] = 1 + dp[t]
        q.put((t + 1) % mm)
    if dp[(t + 60) % mm] == -1:
        dp[(t + 60) % mm] = 1 + dp[t]
        q.put((t + 60) % mm)


print(dp[t2])
