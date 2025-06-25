t = 5000
n = 4 * 2 * t + 1
print(n, 1)
for i in range(t):
    for j in range(1, 5):
        print(j, end=' ')
print(5, end=' ')
for i in range(t):
    for j in reversed(range(1, 5)):
        print(j, end=' ')
print()
print(1, 2)
