notebooks = [(2, 7), (0, 1), (2, 7), (1, 3), (4, 4), (0, 6), (2, 3), (8, 9), (2, 8), (0, 1)] 
drawers = [(2, 4), (6, 6), (3, 3), (1, 9), (8, 9), (3, 6), (0, 6), (2, 9), (7, 8), (3, 9)]

n = int(input())
for i in range(n//10):
    for x,y in notebooks:
        print(500-i*10+x, 500+i*10+y)
for i in range(n % 10):
    print(1000, 1)
print()
for i in range(n//10):
    for x,y in drawers:
        print(500-i*10+x, 500+i*10+y)
for i in range(n % 10):
    print(1000, 1)
