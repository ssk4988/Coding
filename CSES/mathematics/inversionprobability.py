from fractions import Fraction
n = int(input())
r = list(map(int, input().split()))

ans = Fraction(0, 1)
dp = [[Fraction(0, 1) for i in range(101)] for i in range(n+1)]
for i in range(n):
    for j in range(i+1, n):
        m = min(r[i], r[j])
        pairs = m * (m-1) // 2
        if r[i] > r[j]:
            pairs += r[j] * (r[i] - r[j])
        ans += Fraction(pairs, r[i] * r[j])
    
# print(ans)
whole = ans.numerator // ans.denominator
# whole = int(ans.numerator / ans.denominator)
# print(whole)
part = ans - whole
# part = Fraction(ans.numerator - whole * ans.denominator, ans.denominator)
whole *= 1000000
part *= Fraction(1000000, 1)
whole2 = part.numerator // part.denominator
part -= whole2
whole += whole2
if part.numerator * 2 == part.denominator:
    # print("is halfway!!!")
    if whole % 2 == 1: whole += 1
elif part.numerator * 2 < part.denominator:
    # print("round down")
    pass
else:
    # print("round up")
    whole += 1
# part = Fraction(part.numerator - whole * part.denominator, part.denominator)
# print(part, f"{part:.6f}")
# print(f"{float(ans):.6f}")
# print(f"{float(ans):.10f}")
print(f"{whole/1000000:.6f}")
