
import sys
input = sys.stdin.readline

# Check if a number is prime
def primeCheck(a):
    assert a > 1
    i = 2
    while i * i < a:
        assert a % i
        i += 1
            

# Read in the header line
line = input()
n, k = map(int, line.strip().split())
assert str(n) + " " + str(k) + "\n" == line
assert 1 <= n <= 10**17
assert 1 <= k <= 14

# Read in the values
line = input()
arr = list(map(int, line.strip().split()))
assert " ".join(str(x) for x in arr) + "\n" == line
product = 1
for x in arr:
    primeCheck(x)
    product *= x
assert 1 <= product <= 10**17

# Make the array of the divisor the inclusion exclusion
masks = [0] * (1<<k)
masks[0] = 1
for i in range(k):
    masks[1<<i] = -arr[i]
for i in range(1<<k):
    if masks[i]:
        continue
    masks[i] = masks[i-(i&-i)] * masks[i&-i]

# Use inclusion exclusion to find how many numbers are spoken up to some given value
def pos(value):
    global arr,masks
    safe = 1
    for x in arr:
        if (value%x) == 0:
            safe = 0
    ans = sum((value // abs(x))*(1 if x > 0 else -1) for x in masks)
    return ans, safe

# Find the initial bounds for our binary search
lo = 0
# Actual high bound should be less than 5*10**17
hi = 10**19

# Binary search for the value by counting how many numbers are spoken up to the given point
while lo < hi:
    m = (lo + hi) // 2
    p,safe = pos(m)
    if p == n and safe:
        print(m)
        exit()
    if p < n:
        lo = m + 1
    else:
        hi = m
assert 0
