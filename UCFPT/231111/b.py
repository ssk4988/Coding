nc = int(input())
for cn in range(nc):
    av = input().split()
    a = list(map(float, av))
    ans = a[1] / (a[2] + a[3]) * a[4]
    print("%d %.2f" % (int(av[0]), ans))
