import string

# use a prime sieve to speed up finding large jenny numbers
def getPrimes(LIMIT):
    isPrime = [True]*LIMIT
    isPrime[0], isPrime[1] = False, False

    i = 2
    while i*i <= LIMIT:
        if isPrime[i]:
            for k in range(i+i, LIMIT, i):
                isPrime[k] = False
        i += 1

    listOfPrimes = []
    for i in range(LIMIT):
        if isPrime[i]:
            listOfPrimes.append(i)
    return listOfPrimes

primes = getPrimes(100000)

def nextOddNumber(N):
    return (N+1) // 2 * 2 + 1

def isPrimeAndSoIsNextOddNumber(N, primes):
    if N < 2:
        return False
    O = nextOddNumber(N)

    i = 0
    while i < len(primes):
        p = primes[i]
        if p*p > O:
            return True
        if N % p == 0:
            return False
        if O % p == 0:
            return False
        i += 1
    return True

# (int, int, int, int, bool, int[], int[])
def go(number, digsRemaining, digsUsed, numsLeft, isFirst, jennyNumbers, primes):
    
    # base case
    if digsRemaining == 0:
        
        if not isPrimeAndSoIsNextOddNumber(number, primes):
            return numsLeft

        # add to list of jenny numbers
        jennyNumbers.append(number)
        return numsLeft - 1

    s = 0
    while s < 10:
        
        # i use a bitmask instead of a list of booleans
        if ((1 << s) & digsUsed) != 0:
            s += 1
            continue

        # use this digit
        digsUsed += (1 << s)
        
        # recursive call
        if not (isFirst and s == 0):
            numsLeft = go(
                number * 10 + s,
                digsRemaining - 1,
                digsUsed,
                numsLeft,
                False,
                jennyNumbers,
                primes,
            )

        # put this digit back
        digsUsed -= (1 << s)

        # break condition
        if numsLeft <= 0:
            break

        s += 1
        
    return numsLeft
    

T = int(input())

jennyNumbers = [[] for _ in range(10)]
for t in range(T):
    line = input().split(' ')
    D, I = int(line[0]), int(line[1])

    guaranteedFail = False
    if D > 9:
        # the sum of all digits is divisible by three so there are no jenny numbers of 10 digits
        # and our counting system is base 10, so there are no jenny numbers with more than 10 digits
        guaranteedFail = True
        
    if not guaranteedFail:
        if len(jennyNumbers[D]) == 0:
            go(
                0,
                D,
                0,#[False for i in range(10)],
                999999999,
                True,
                jennyNumbers[D],
                primes,
            )
        
        if len(jennyNumbers[D]) < I:
            guaranteedFail = True
        else:
            print(jennyNumbers[D][I-1])

    if guaranteedFail:
        print("Brice doesn't stand a chance!")
    
