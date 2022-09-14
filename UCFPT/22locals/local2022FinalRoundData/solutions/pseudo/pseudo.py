# Arup Guha
# 8/9/2022
# Solution to UCF Locals Problem: Pseudo Pseudo Random Numbers

# Returns max run of 0s or 1s in the binary representation of n.
def maxRun(n,bits):

    curBit = -1
    curRun = 0
    maxRun = 0

    # Peel off bit by bit.
    for i in range(bits):

        # Next bit. Clunky sorry.
        bit = 0
        if (n & (1<<i)) != 0:
            bit = 1
        
        # New run.
        if bit != curBit:
            curBit = bit
            curRun = 1

        # Extend old run.
        else:
            curRun += 1

        # Update and go to next bit.
        maxRun = max(maxRun, curRun)

    return maxRun
    
def main():

    # Get input.
    toks = [int(x) for x in input().split()]

    # Store result here.
    res = 0

    # Try each bit string.
    for i in range(1<<toks[0]):
        if maxRun(i, toks[0]) <= toks[1]:
            res += 1

    # Ta da!
    print(res)

# Run it!
main()
