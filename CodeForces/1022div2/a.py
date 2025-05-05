nc = int(input())
for cn in range(nc):
    n = int(input())
    a = [i for i in range(n)]
    b = a[::-1]
    print(sum(abs(i-j) for i,j in zip(a, b))//2+1)
