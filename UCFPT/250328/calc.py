tot = 0
for dr in range(-10, 11):
    row = 0
    for c in range(-20, 20):
        if dr ** 2 + c ** 2 <= 100:
            row += 1
    print(dr, row)
    tot += row
print(tot)
