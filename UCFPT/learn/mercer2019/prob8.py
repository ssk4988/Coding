import sys
ans = 0
idx = 1
for line in sys.stdin:
    # if type(line) != type(str("")): break
    if line[:7] == "THE END":
        break
    if len(line) <= 1:
        cur = 0
    else:
        cur = []
        for tok in line.split():
            cur.append(str(len(tok)))
        cur = int(''.join(cur))
    ans += cur
    print(f"Line {idx} = {cur}")
    idx += 1
print(f"Sum of file = {ans}")
