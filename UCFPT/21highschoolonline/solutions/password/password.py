n = int(input())
for i in range(0, n):
    length = int(input())
    # Answer is 4^length, because each digit can be 0, 3, 6, 9 and any combination of these digits works
    print(4**length)
