from random import randint, choice
def gen(n):
    notebooks = [(randint(0, n-1), randint(0, n-1)) for i in range(n)]
    drawers = [(randint(0, n-1), randint(0, n-1)) for i in range(n)]
    for i in range(n):
        if notebooks[i][0] > notebooks[i][1]:
            notebooks[i] = (notebooks[i][1], notebooks[i][0])
        if drawers[i][0] > drawers[i][1]:
            drawers[i] = (drawers[i][1], drawers[i][0])

    return (notebooks, drawers)

def fit(a, b):
    return a[0] <= b[0] and a[1] <= b[1]

def test(notebooks, drawers):
    n = len(notebooks)

    for iteration in range(n):
        best_notebooks = [10 ** 9, []]
        matches_n = [0] * len(notebooks)
        matches_d = [0] * len(drawers)
        for i in range(len(notebooks)):
            for j in range(len(drawers)):
                if notebooks[i][0] <= drawers[j][0] and notebooks[i][1] <= drawers[j][1]:
                    matches_n[i] += 1
                    matches_d[j] += 1
        mn = min(matches_n + matches_d)
        if mn == 0:
            return False
        choices = [(0, i) for i,x in enumerate(matches_n) if x == mn] + [(1, i) for i,x in enumerate(matches_d) if x == mn]
        t, idx = choice(choices)
        
        if t == 0:
            choices = [j for j in range(len(drawers)) if fit(notebooks[idx], drawers[j])]
            idx1 = choice(choices)
            del notebooks[idx]
            del drawers[idx1]
        elif t == 1:
            choices = [j for j in range(len(notebooks)) if fit(notebooks[j], drawers[idx])]
            idx1 = choice(choices)
            del notebooks[idx1]
            del drawers[idx]
    return True

n = 5
cnt = 0
while True:
    notebooks, drawers = gen(n)
    worked = 0
    failed = 0
    for i in range(1000):
        res = test(notebooks.copy(), drawers.copy())
        if res: worked += 1
        else: failed += 1
    if worked and failed:
        print(notebooks, drawers)
        print(f"fail rate {failed / 1000 * 100:.4f}%")
        break
    print(f"do iteration, worked:{worked} failed:{failed} ")
