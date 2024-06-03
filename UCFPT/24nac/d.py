input()
a = input()
a = " " + a + " " + a + " "
b = " " + input() + " "
for i in range(2):
    if b in a:
        print(1)
        exit()
    a = " ".join(a.split()[::-1])
print(0)
