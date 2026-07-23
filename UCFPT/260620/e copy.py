x = input()
best = eval(x)
x_best = x
i = 0
while i < len(x):
    if i > 0 and (x[i-1] == '+' or x[i-1] == '-'): 
        i += 1
        continue
    if (x[i] == '+' or x[i] == '-'):
        i += 1
        continue
    allzero = True
    zerocnt = 0
    leng = 0
    for j in range(i, len(x)):
        if x[j] == '+' or x[j] == '-': break
        if x[j] == '0': zerocnt += 1
        else: allzero = False
        leng += 1
    if allzero and zerocnt > 1:
        i += 1
        continue
    try:
        x2 = x[:i] + "+" + x[i:]
        val = eval(x2)
        if val > best:
            best = val
            x_best = x2
            x = x2
    except:
        pass
    i += 1
print(x_best)
