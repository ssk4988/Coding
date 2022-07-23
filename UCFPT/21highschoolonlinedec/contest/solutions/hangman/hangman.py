# hangman.py by Jacob Steinebronn

# Check if query and key (both strings) are consistent with hangman rules
def check(query, key):
    if key == query: return True
    if len(key) != len(query): return False
    placed = [False]*26 # If a letter has a True, it exists in key
    skipped = [False]*26 # if a letter has a True, it has an _
    for kc, qc in zip(key, query):
        if qc != '_':
            if qc != kc: return False
            placed[(int)(ord(qc)-ord('a'))] = True
        else:
            skipped[(int)(ord(kc)-ord('a'))] = True
    for pi, si in zip(placed, skipped):
        if pi and si: return False # If we ever saw a letter but skipped it for a _, we cheated
    return True

# The number of test cases
nt = (int)(input().strip())

for tn in range(nt):

    # Parse the input as defined
    category = input().strip()
    n = (int)(input().strip())
    words = [input().strip() for i in range(n)]
    nq = (int)(input().strip())

    for q in range(nq):
        # For each query string, check it against every word in the category
        query = input().strip()
        found = False
        for word in words:
            # If any of them is true, ans will be true
            found |= check(query, word)
        # Print the answer we found!
        print("No cheaters here!" if found else "That's not a word for a(n) "+category+"!")
