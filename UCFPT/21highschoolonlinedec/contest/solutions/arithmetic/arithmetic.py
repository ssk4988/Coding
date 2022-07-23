# The sum of an arithmetic sequence of n elements, starting at x, with a difference d, with a sum of S
# Can be represented by the equation S = nx+n(n-1)/2d, which is also 2S/n = 2x+(n-1)d

# nx Is the sum of all the elements if the difference between them was 0
# n(n-1)/2d Is the sum of all the differences accumulated in the sequence
# Which is calculated by the summation of n multiplied by d


days = int(input())
for t in range(days):
    n, s = map(int, input().split())
    if 2*s%n==0:
        # The answer is possible
        if ((2*s)/n)%2==0:
            # All elements are equal so the value we need is the sum / n
            value = int(s/n)
            # Print all elements on the same line
            for i in range(n):
                if i < n-1:
                    print(value,end=" ")
                else:
                    print(value)
        else:
            # We can show that if there is an arithmetic sequence of n elements, that sums up to s, we can create such a sequence
            # Where the difference between each element is equal to 1
            # We need to find the first value
            start = int(((2*s)/n-(n-1))/2);
            # The rest of the elements build off of this one
            # Cool way to print our answer on 1 line
            print(" ".join([str(start + i) for i in range(n)]))
    else:
        print('IMPOSSIBLE')
