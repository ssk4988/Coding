# Kyle Dencker
# Local Contest 2022 - Finals

import operator


freq = []
n = int(input())

# Process Input
for i in range(n):
    word = input()
    index = 0
    for w in word:
        if index == len(freq):
            new_dict = {"a":0}
            freq.append(new_dict)
        
        if w in freq[index].keys():
            freq[index][w]+=1
        else:
            freq[index][w]=1
        index+=1

# Sort dictionary (determing longest)
# Find others that match
# sort
# print answer
for i in range(len(freq)):
    freq[i] = dict( sorted(freq[i].items(), key=operator.itemgetter(1),reverse=True))
    answer = []
    value = freq[i][list(freq[i].keys())[0]]
    for key in freq[i]:
        if (freq[i][key] == value):
                answer.append(key)
    answer.sort()
    print(str(i+1) +":",end="")
    for letter in answer:
        print(" " + letter, end="")
    print()
    
