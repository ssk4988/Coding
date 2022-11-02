cnt = 0

for i in range(0, 10**7):
    if "911" in str(i):
        cnt += 1

print(cnt)