'''
1000: 9
10000: 11
100000: 50
skips elements

1000: 22
10000: 70
100000: 223
.7 sqrt n


k1 for every m is m * (2m - 2) = 2 * m * (m-1) = 2m^2 - 2m

k2 for every m is m * (2m - 2) * (4m - 3) + m-1 = (m-1) * (2 * m * (4m-3) + 1) = (m-1) * (8m^2 - 6m + 1)
k3 for every m is m * (2m-2) * (4m-3) * (4m-2) = m * 2 * (m-1) * (4m-3) * 2 * (2m-1)
k4 for every m is m * (2m-2) * (4m-3) * (4m-2) * ()
29/5 for m=2
89/9
((4m-3)*(4m-2)-1)/(4m-3)

replace m with m+1:
(m+1)*2*m*(4m+1)+m=m*(1 + (m+1)*2*(4m+1)) = m * (8m^2 + 10m + 3) = m * (2m+1) * (4m+3)
2*(m+1)*m*(4m+1)*2*(2m+1)
m * (2m-2) * (4m-3) + 2*(m-1)

m * 2 * (m-1) * (4m-3) * 2 * (2m-1) -> 2 * m * (m+1) * (4m+1) * 2 * (2m+1)

14            14 * 26 * 53
15 1596 23940 15 * 28 * 57
16 1830 29280 16 * 30 * 61
17 2080 35360 17 * 32 * 65

a[0]=1,a[1]=4,a[2]=21
a[n] = 6 * a[n-1] - a[n-2] - 2

b[n] = 10*(b[n-1]-2) - (b[n-2]-2) + 10 = 10*b[n-1] - b[n-2] - 8
b[0]=2,b[1]=12,b[2]=110
b[n] = 10*b[n-1] - b[n-2] - 8

c[0]=3,c[1]=24,c[2]=315
c[n] = 14*c[n-1] - c[n-2] - 18


recurrence of k-m
4x+3?
m=3: 15,-15,1
m=4: 19,-19,1
m=5: 23,-23,1
m=6: 27,-27,1
m=7: 31,-31,1
m=8: 7,-7,1 (35, -35, 1)
m=9: 39,-39,1
m=10: 

m=24 is weird 11,-11,1 (99,-99,1)
m=48 is weird
m=49 also???

'''


n = 1000000
dicts = [dict() for _ in range(n+1)]
for m in range(1, n):
    window = 0
    found = False
    for i in range(1, m):
        window += i ** 2
    for k in range(m, n):
        window -= (k-m) ** 2
        window += k ** 2
        dicts[m][window] = k
        if window in dicts[m-1]:
            l = dicts[m-1][window]
            if l-(m-1)+1 <= k: continue
            found = True
            print(f"m={m-1} [{k-m+1},{k}]={window} [{l-(m-1)+1},{l}]={window}", flush=True)
    if not found and m > 10:
        break
