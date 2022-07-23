# emoji.py by Jacob Steinebronn

# The number of test cases
nt = (int)(input().strip())

for tn in range(nt):
    # Get the input string
    word = input().strip()
    # Put the string into a set (which can't have duplicates) and see if anything was removed
    print("Emote away!" if len(set(word)) == len(word) else "Nope")
