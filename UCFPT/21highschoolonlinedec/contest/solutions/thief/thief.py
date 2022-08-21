# thief.py by Jacob Steinebronn

import sys
# We're using a recursive solution that calls
# O(p) deep, so set this recursion limit
sys.setrecursionlimit(10010) 

# The number of test cases
nt = (int)(input().strip())

# Set up some variables to be populated later
dp = []
values = []
p = 0

def solve(idx, cutters):
    # If we're off the end of the array, we get no more value
    if idx >= p: return 0
    # If we've solved this exact problem before, return the answer we calculated and saved beforehand
    if dp[cutters][idx] != -1: return dp[cutters][idx]
    # We could take this guy, but have to skip the next one
    take = values[idx] + solve(idx+2, cutters)
    # We could not take this one and just move on
    leave = solve(idx+1, cutters)
    # We could use cutters on the NEXT one, which means we take this and the next for sure,
    # plus the remaining solution thereafter
    cut = values[idx] + values[idx+1] + solve(idx+2, 0)  if idx+1 < p and cutters > 0 else 0
    
    # The answer is the best of the 3 options. Save it for later, in case we try to re-solve this same subproblem.
    dp[cutters][idx] = max(take, leave, cut)
    return dp[cutters][idx]

for tn in range(nt):
    # Get the input and set up our dp.
    values = list(map(int, input().strip().split()))
    p, values = values[0], values[1:]
    dp = [[-1]*p, [-1]*p]

    # Solve!
    print(solve(0, 1))

