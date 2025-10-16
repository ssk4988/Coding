nc = int(input())
for cn in range(nc):
    a, b = map(int, input().split())
    if a % 2 == 0:
        if b % 2 == 0:
            c = b//2
            print(a*c+2)
        else:
            print(-1)
    else:
        if b % 2 == 0:
            if b % 4 == 0:
                c = b//2
                print(a*c+2)
            else:
                print(-1)
        else:
            print(a*b+1)
