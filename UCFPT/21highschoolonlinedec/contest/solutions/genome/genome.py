# 2021 UCF HSPT Online - Genome Transformation
# Author: Billy Quiroga

mod = 1000000007

# function that multiplies two matrices together under mod
def matrix_multiply(a, b):
  c = [[0 for i in range(len(b[0]))] for j in range(len(a))]
  for i in range(len(a)):
    for j in range(len(b[0])):
      for k in range(len(b)):
        c[i][j] += a[i][k] * b[k][j]
        c[i][j] %= mod
  return c

# function that raises a matrix m to the power e under mod
def matrix_exponentiation(m, e):
  r = [[0 for i in range(len(m))] for j in range(len(m))]
  for i in range(len(m)):
    r[i][i] = 1
  while e > 0:
    if (e & 1) > 0:
      r = matrix_multiply(r, m)
    m = matrix_multiply(m, m)
    e //= 2
  return r


test_cases = int(input())

for tc in range(test_cases):

  # scan in what each letter transforms into and the starting dna sequence
  AT = input()
  CT = input()
  TT = input()
  GT = input()
  DNA = input()
  years = int(input())

  # The solution idea here is to find a recurrence relation for
  # the number of occurrences of each letter after one year. Let's
  # explore what this recurrence relation looks like just for the
  # character A.

  # Let Ac, Tc, Cc, and Gc be the number of A's, T's, C's, and G's
  # currently in our DNA respectively. If we want to know what
  # the number of A's will be after 1 year, then we can calculate
  # it based on these values.

  # We know for each A, they will all transform into the same
  # string, which I've denoted as AT. Since we know it will
  # transform into AT, just in terms of A's, we know that the
  # original A will transform into the number of A's in AT.
  # Similarly, for each C, they will all transform into the same
  # string, which we've denoted as CT. Since we know it will
  # transform into CT, just in terms of A's, we know that the
  # original C will transform into the number of A's in CT.
  # We can continue to do the same for C's and G's to get the
  # number of occurrences of A in the next year's string.
  
  # The full formula for the number of A's in the next year is:
  # Ac for next year =
  #   Ac * (A's in At) + Cc * (A's in CT) + Tc * (A's in TT) + Gc * (A's in GT)

  # We can make recurrence relations in a similar manner for the
  # number of C's, T's, and G's for the next year as well.

  # Now that we have recurrence relations for each letter, we need
  # to somehow apply the recurrence the number of years times. Since
  # the number of years can be up to 10^18, we can't just do that
  # naively. But, we can use a technique called matrix exponentiation.

  # To read more about matrix exponentiation and how it works, read
  # https://www.hackerearth.com/practice/notes/matrix-exponentiation-1/
  # This article explains what matrices are, how to multiply two matrices,
  # how to exponentiate a matrix, and how it relates to recurrence relations.

  # Create the recurrence relation matrix
  R = [
    [AT.count('A'), CT.count('A'), TT.count('A'), GT.count('A')],
    [AT.count('C'), CT.count('C'), TT.count('C'), GT.count('C')],
    [AT.count('T'), CT.count('T'), TT.count('T'), GT.count('T')],
    [AT.count('G'), CT.count('G'), TT.count('G'), GT.count('G')]
  ]

  # Get the initial counts for each letter in the starting DNA
  M = [
    [DNA.count('A')],
    [DNA.count('C')],
    [DNA.count('T')],
    [DNA.count('G')]
  ]

  # Exponentiate the recurrence to the number of years power
  R = matrix_exponentiation(R, years)

  # Multiply our exponentiated recurrence with the original occurrences
  ans = matrix_multiply(R, M)

  # After doing that, we now have what the number of occurrences are for each letter, which is the answer
  print("Genome #{}: {} {} {} {} ".format(tc + 1, ans[0][0], ans[1][0], ans[2][0], ans[3][0]))
