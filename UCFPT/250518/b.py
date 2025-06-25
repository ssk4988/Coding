h, w = map(int, input().split())
from math import comb
print(comb(h, 2) * comb(w, 2))

cuth, cutw = map(int, input().split())
ans = comb(cuth, 2) * comb(w-cutw, 2) + comb(cutw, 2) * comb(h-cuth, 2) + comb(h-cuth, 2) * comb(w-cutw, 2)
ans += comb(h-cuth, 2) * cutw * (w-cutw)
ans += comb(w-cutw, 2) * cuth * (h-cuth)
print(ans)


