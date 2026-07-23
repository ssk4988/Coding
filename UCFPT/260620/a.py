a, b = map(int, input().split())
if a < b:
    a, b = b, a
ans = max(min(a/3, b), min(a/2, b/2))
print(f"{ans:.6f}")
