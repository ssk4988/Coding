# piano.py by Jacob Steinebronn

# The number of test cases
nt = (int)(input().strip())

for tn in range(nt):
    # Get the input string
    word = input().strip()
    # We can just use the left hand for everything!
    print("L"*len(word))
