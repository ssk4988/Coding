from heapq import *
n,k = map(int, input().split())
heap = []
a = sorted([int(input()) for _ in range(n)])
for i in range(min(n, k)):
	heappush(heap, (a[i], i, 5))
tot = 0
while True:
	t, i, p = heappop(heap)
	tot += p
	if tot >= n:
		print(t)
		exit()
	heappush(heap, (t + 2 * a[i], i, 4))
