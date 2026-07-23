x = input()
i = 0
# when see -, add + before every digit after first until last digit or hit nonzero
while i < len(x):
    if x[i] != '-':
        i += 1
        continue
    i += 2
    while i < len(x):
        if x[i] == '+' or x[i] == '-': break
        nonzero = x[i] != '0'
        x = x[:i] + "+" + x[i:]
        i += 2
        if nonzero:
            break
assert(x.replace('-', '+').count("++") == 0)
print(x)
