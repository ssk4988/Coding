from fractions import Fraction
n = int(input())
r = list(map(int, input().split()))

ans = Fraction(0, 1)
dp = [[Fraction(0, 1) for i in range(101)] for i in range(n+1)]
for i in range(n):
    dp[i+1] = dp[i].copy()
    for j in range(1, r[i]+1):
        for j1 in range(j+1, 101):
            ans += dp[i][j1] * Fraction(1, r[i])
        dp[i+1][j] += Fraction(1, r[i])

print(ans)
whole = int(ans.numerator / ans.denominator)
print(whole)
part = Fraction(ans.numerator - whole * ans.denominator, ans.denominator)
part *= Fraction(1000000, 1)
whole = int(part.numerator / part.denominator)
part = Fraction(part.numerator - whole * part.denominator, part.denominator)
print(part, f"{part:.6f}")
print(f"{float(ans):.6f}")
print(f"{float(ans):.10f}")
