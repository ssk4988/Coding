n = int(input())
from collections import Counter
a,b = Counter([input() for _ in range(n)]), Counter([input() for _ in range(n)])
ans = 0
for key in a: ans += min(a[key], b[key])
print(ans)
