n = int(input())
a = list(map(int, input().split()))
found = False
for x in a:
    if x != 0:
        if x > 0:
            print("Good morning, Morioh!")
        else:
            print("Good night, Morioh!")
        found = True
        break
if not found:
    print("Diamond is unbreakable!")