
# Read in number of cabinets
cabinets = int(input())

# Loop over each cabinet
for i in range (0, cabinets):
   # Read in number of snacks
   s = int(input())

   # Loop over the snacks
   snackList = []
   for j in range (0, s):
      # Read the snack name
      snack = input()

      # Count the number of each vowel
      cnt = list(map(snack.count, "aeiouy"))

      # Sum the score (y counts twice)
      sum = cnt[0] + cnt[1] + cnt[2] + cnt[3] + cnt[4] + 2 * cnt[5]

      # Add to list
      snackList.append((sum, snack))

   # Sort list first by descending vowel score and then alphabetical
   snackList = sorted(snackList, key=lambda element: (160-element[0], element[1]))

   # Output list
   print("Cabinet #{0}:".format(i + 1))
   for j in snackList:
      print(j[1])
   print()
