arr = [i for i in input().split()]

time = int(arr[1])
str = arr[0]

freq = [0 for i in range(26)]

for i in range(len(str)):
    freq[ - 97] += 1

sepa = ' '
for i in range(26):
    if freq[i] == 0:
        sepa = chr('a' + i)


for i in range(time):
    print(str, end='')
    if i + 1 < time:
        print(sepa, end='')

print()