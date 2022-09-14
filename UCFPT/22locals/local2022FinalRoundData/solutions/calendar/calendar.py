# Kyle Dencker
# Local Contest 2022 - Final

inputline = input().split()

di = int(inputline[0])-1
mi = int(inputline[1])-1
yi = int(inputline[2])
n = int(inputline[3])-1

day1 = yi*360 + mi*30+di

inputline = input().split()

df = int(inputline[0])-1
mf = int(inputline[1])-1
yf = int(inputline[2])

day2 = yf*360 + mf*30+df

print((day2-day1 + n) % 7 + 1)

