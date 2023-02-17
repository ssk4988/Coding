str = input()

ans = True
for i in range(1, len(str)):
    if str[i] == str[i - 1]:
        ans = False

if ans:
    print("Goodnight!")
else:
    print("No sleep here.")