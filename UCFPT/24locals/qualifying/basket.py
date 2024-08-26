scores = []
for i in range(2):
    p = list(map(int, input().split()))
    scores.append(0)
    for i, x in enumerate(p):
        scores[-1] += (i+1)*x
if scores[0] < scores[1]:
    print(2)
elif scores[0] == scores[1]:
    print(0)
else:
    print(1)
