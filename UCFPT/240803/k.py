n, k = map(int, input().split())
a, b = map(int, input().split())
MD = 1000000007
ab = (1 - (a * pow(b, MD-2, MD))) % MD
if a == b:
    print(ab if k == 1 else 0)
    exit()

ans = pow(ab, k, MD)
denom = 1 - pow(ab, n, MD)
ans = ans * pow(denom, MD-2, MD)
# ans = ans * (1 - ab)
ans %= MD
print(ans)
