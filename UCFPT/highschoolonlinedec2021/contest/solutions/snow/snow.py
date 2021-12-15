import heapq

class Node(object):

	def __init__(self, val):
		self.val = val
		self.left = None
		self.right = None

num_tests = int(input())

for q in range(num_tests):
	n = int(input())
	inp = input().split(" ")
	snowmen = []
	pq = []
	ll = []
	for i in range(n):
		x = int(inp[i])
		snowmen.append((x, True, i))
		heapq.heappush(pq, (-x, i))
	for i in range(n):
		ll.append(Node(snowmen[i]))
	for i in range(n):
		ll[i].right = ll[(i+1)%n]
		ll[i].left = ll[(i-1+n)%n]

	directions = input()

	num_snowmen = n
	curr_dir = 0
	while num_snowmen > 0:
		x = heapq.heappop(pq)
		while not snowmen[x[1]][1]:
			x = heapq.heappop(pq)
		
		x = (-x[0], x[1])
		size = x[0]
		prev = ll[x[1]].right if directions[curr_dir] == 'L' else ll[x[1]].left

		curr = ll[x[1]]
		for i in range(size):
			snowmen[curr.val[2]] = (snowmen[curr.val[2]][0], False, curr.val[2])
			num_snowmen = num_snowmen-1
			if directions[curr_dir] == 'R':
				curr = curr.right
			else:
				curr = curr.left
		
		if directions[curr_dir] == 'R':
			prev.right = curr
			curr.left = prev
		else:
			prev.left = curr
			curr.right = prev

		curr_dir = curr_dir+1

	print(curr_dir)

