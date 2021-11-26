
# Read in number of contests
contests = int(input())

# Loop over each contest
for i in range (0, contests):
   # Read in highest judge ID and number of problems
   n, m = map(int, input().split())

   # Track starts and ends
   starts = [0] * (n + 2)
   ends = [0] * m

   # Loop over the problems
   for j in range (0, m):
      # Read the range
      left, right = map(int, input().split())

      # Track how many intervals start at the "left" value
      starts[left] += 1;

      # Then, just store for each problem where its interval ends
      ends[j] = right;

   # Start by assuming all ranges cannot be combined
   result = m

   # Then, check each interval end and see if it "runs up" against
   # any starting interval (if so, we can combine this interval)
   for j in range (0, m):
      # See if an interval starts right after this one ends
      if starts[ends[j]+1] > 0:
         # If so, decrement the range count and "combine" the start
         # by reducing it by one in count
         result -= 1
         starts[ends[j]+1] -= 1

   # Print the answer!
   print(result)

