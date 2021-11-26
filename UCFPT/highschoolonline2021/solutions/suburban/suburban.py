from math import *
cases = int(input())
for t in range (0,cases):
    x = int(input())
    answer = 1_000_000
    # for this solution, we make the observation that the most we would ever need to travel in one direction is the square root of X
    # Thus, we can loop through all integers up to the square root of X, and assume the iterative variable is one of two directions:
    # up and to the right, and then all we need to do is compute how far we would need to travel in the other direction to fit the
    # euclidean distance requriement
    for i in range (1,int(sqrt(x)+1)):
        euc = i*i
        need = x-euc
        need_manhattan = int(sqrt(need))
        if need_manhattan*need_manhattan==need:
            answer = min(answer,need_manhattan+i)
    if answer==1_000_000:
        print(-1)
    else:
        print(answer)

