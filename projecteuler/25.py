dp = [1, 1]

while len(str(dp[-1])) < 1000:
    dp.append(dp[-1] + dp[-2])
print(len(dp))