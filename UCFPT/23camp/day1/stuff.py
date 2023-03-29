numberofmeasurements = int(input())
myDict = {}
listi = {"M": 7, "B": 7, "E": 7}
for mm in range(numberofmeasurements):
    measurement = input().split()
    myDict[int(measurement[0])] = [measurement[1], measurement[2]]

counting = 0
myKeys = list(myDict.keys())
myKeys.sort()
# sorted_dict = {i: myDict[i] for i in myKeys}
winners = [0]
for k in myKeys:
    v = myDict[k][0]
    v2 = myDict[k][1]
    for item in listi.keys():
        if item in v:
            listi[item] += int(v2)
            print(listi[item])
            # if "+" in v2:
            #     listi[item] += int(v2.replace("+", ""))
            # if "-" in v2:
            #     listi[item] -= int(v2.replace("-", ""))
        for itemss in winners:
            if int(listi[item]) > itemss:
                winners.append(int(listi[item]))
                winners.remove(itemss)
                counting += 1
            if int(listi[item]) == itemss:
                winners.append(int(listi[item]))
                counting += 1
print(counting)
