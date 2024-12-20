l, r = map(int, input().split())
cnt = 0
guaranteed = (r-l+1) // 2
for i in range(1, l):
    x = ((l-1) // i + 1) * i
    x_o = (l + i-1) // i * i
    assert(x == x_o)
    x1 = x + i
    x1_o = (l + 2 * i - 1) // i * i
    x1_o2 = ((l-1) // i + 2) * i
    assert(x1 == x1_o == x1_o2)
    if x1 <= r:
        cnt += 1
print(cnt, guaranteed, cnt-guaranteed)
print(r-l)
