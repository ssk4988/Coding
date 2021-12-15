t = int(input())

for i in range(t):
	inp = input().split(" ")

	x1 = int(inp[0])
	y1 = int(inp[1])

	x2 = int(inp[2])
	y2 = int(inp[3])

	# Euclid is always faster than Manhattan, except when they take the same path
	# They take the same path iff x1 == x2 or y1 == y2

	if x1 == x2 or y1 == y2:
		print("Dr. Manhattan wins again!")
	else:
		print("Euclid is too fast!")