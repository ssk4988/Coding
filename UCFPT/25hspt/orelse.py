m = int(input())
items = set()
requests = []
for i in range(m):
    s = input().split()
    for j in range(0, 5, 2):
        items.add(s[j][s[j][0] == '!':])
    requests.append(s)

items = list(items)
n = len(items)
requests2 = []
for r in requests:
    requests2.append([])
    for w in r[0:5:2]:
        i = w[w[0] == '!':]
        requests2[-1].append(2 * (items.index(i)) + (w[0] != '!'))

for mask in range(1 << n):
    works = True
    for r in requests2:
        rworks = False
        for v in r:
            i = v // 2
            on = (mask >> i) & 1
            if on == v&1: rworks = True
        if not rworks: works = False
    if works:
        print("Dinner is served!")
        print(mask.bit_count())
        for i in range(n):
            if (mask >> i) & 1:
                print(items[i])
        exit()
print("Better luck next year!")