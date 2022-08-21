# miracle.py
# Jacob Steinebronn
tests = (int)(input().strip())

while tests > 0:
    tests -= 1
    ans = 1.0

    # For each point
    num_points = (int)(input().strip())
    for i in range(num_points):
        # Multiply your answer by 1 + s, since that signifies the 
        # correct change

        cur = (float)(input().strip())
        cur /= 100.0
        ans *= 1.0 + cur

    # Print the output, formatted correctly
    ans *= 100.0

    print("%.4f" % (ans-100))
