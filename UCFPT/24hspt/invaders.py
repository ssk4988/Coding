a, b = map(int, input().split())
s = input()

for x in s:
    if x == 'L':
        b -= 1
    else: b += 1
print("Challenge completed!" if b == 0 else "Better luck next time!")