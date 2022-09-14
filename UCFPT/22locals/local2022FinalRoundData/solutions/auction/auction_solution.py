
# Author: Travis Meade
# The solution to the share auction problem from LPC Finals 2022

from math import *

# Read in the number of auctions and vouchers
A,V = map(int, input().split())

# Read in all the auctions information
aucts = [list(map(int, input().split())) for _ in range(A)]

# Binary search for the profit per voucher placed
lo = 0
hi = 1

# The function that checks if the limit does not use too many vouchers
def canDo(profit):
    global V,aucts
    used = 0
    for pi,vi in aucts:
        # quadratic equation time!!!
        a = profit
        b = 2*profit*vi + profit
        c = profit*vi*vi + profit*vi - pi*vi
        x = (-b + sqrt(b*b - 4*a*c)) / (2*a)
        x += 1
        x = max(x, 0)
        used += int(x)

    # Check that we did not use too many vouchers
    return used <= V

# Function to find out how much money is made using some profit as a target
def compute(profit):
    global V,aucts
    used = 0
    ans = 0
    for pi,vi in aucts:
        # quadratic equation time!!!
        a = profit
        b = 2*profit*vi + profit
        c = profit*vi*vi + profit*vi - pi*vi
        x = int((-b + sqrt(b*b - 4*a*c)) // (2*a))
        x += 1
        x = max(x, 0)
        ans += (pi * x) / (vi + x)
        used += x

    # Check that we did not use too many vouchers
    return ans + (V - used) * profit


# Find the actual upper bound
while not canDo(hi):
    lo = hi
    hi *= 2


# NOW search
for _ in range(60):
    m = (lo+ hi) / 2
    if canDo(m):
        hi = m
    else:
        lo = m

# Print the answer
print(compute(hi))
