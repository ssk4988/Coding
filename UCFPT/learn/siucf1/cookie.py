nc = int(input())
for cn in range(nc):
    c = int(input())
    if c % 4 == 0:
        print(f"NO {c*3//4}")
    else: print("YES")
