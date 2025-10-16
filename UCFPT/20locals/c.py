a, b = map(int, input().split(":"))
c = a * 60 + b
c *= 59
h = c // 3600
c -= h * 3600
m = c // 60
c -= m * 60
s = c
print(f"{h:02d}:{m:02d}:{s:02d}")
