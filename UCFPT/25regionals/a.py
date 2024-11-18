r, c = map(int, input().split())
left = False
for x in range(r):
    s = input()
    half = (c - len(s)) // 2
    odd = (c - len(s)) % 2
    print('.' * (half + (odd and left)) + s + '.' * (half + (odd and not left)))
    if odd: left = not left
