n = int(input())
for cn in range(n):
    a = list(map(int, input().split()))
    cnt = 0
    for x in a:
        cnt += x >= 10
    print(*a)
    if cnt == 3:
        print("triple-double")
    if cnt == 2:
        print("double-double")
    if cnt == 1:
        print("double")
    if cnt == 0:
        print("zilch")
    print()
