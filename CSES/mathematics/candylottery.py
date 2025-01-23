from fractions import Fraction
n, k = list(map(int, input().split()))

ans = 0
choose = [0] * (n+1)
choose[0] = 1
for i in range(1, len(choose)):
    choose[i] = choose[i-1] * (n-i+1) // i
# print(choose)
for mx in range(1, k+1):
    for c in range(0, n+1):
        ans += choose[c] * mx * (mx-1) ** 
# dp = [[Fraction(0, 1) for i in range(k+1)] for i in range(n+1)]
# dp[0][0] = Fraction(1, 1)
# for i in range(n):
#     for j in range(0, k+1):
#         if j == 0 and i > 0: continue

# whole = ans.numerator // ans.denominator
# part = ans - whole
# whole *= 1000000
# part *= Fraction(1000000, 1)
# whole2 = part.numerator // part.denominator
# part -= whole2
# whole += whole2
# if part.numerator * 2 == part.denominator:
#     if whole % 2 == 1: whole += 1
# elif part.numerator * 2 < part.denominator:
#     pass
# else:
#     whole += 1
# print(f"{whole/1000000:.6f}")
