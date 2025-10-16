'''
if 2+ zeros:
    k=1 simulate
    k=2 0
    k=3 n
    k=4 0
elif 0 zeros:
    k=1 0
    k=2 n
    k=3 0
else:
    0 1 2 2 3 4 6
    0 1 5 5 3 4 5
    0 1 2 2 2 2 2
    0 1 3 3 3 3 3 

'''

nc = int(input())
for cn in range(nc):
    n, k = map(int, input().split())
    a = [list(map(int, input().split()))]
    for _ in range(4):
        freq = [0] * (n+1)
        for x in a[-1]: freq[x] += 1
        mex = 0
        while freq[mex]: mex += 1
        a.append([0] * n)
        for i,x in enumerate(a[-2]):
            if x >= mex or freq[x] > 1:
                a[-1][i] = mex
            else: a[-1][i] = x
    
    if k >= len(a):
        if k % 2 == 0: k = 2
        else: k = 3
    print(sum(a[k]))


