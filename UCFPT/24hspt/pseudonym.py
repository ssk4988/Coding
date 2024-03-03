from collections import defaultdict
from queue import PriorityQueue

q = int(input())

seen = dict()
qs = dict()
name = dict()
revname = dict()
for _ in range(q):
    x = input().split()
    if x[0] == "Enter":
        init = x[1][0] + x[2][0]
        fullname = x[1] + " " + x[2]
        if init not in qs:
            qs[init] = PriorityQueue()
            seen[init] = 0
        if qs[init].qsize() == 0:
            qs[init].put(seen[init])
            seen[init] += 1
        val = qs[init].get()
        pseud = init + str(val)
        name[pseud] = fullname
        revname[fullname] = pseud
    elif x[0] == "Leave":
        init = x[1][0] + x[2][0]
        fullname = x[1] + " " + x[2]
        pseud = revname[fullname]
        val = int(pseud[2:])
        del revname[fullname]
        del name[pseud]
        qs[init].put(val)
    else:
        pseud = x[1]
        if pseud in name:
            print(name[pseud])
        else:
            print("404 PERSON NOT FOUND")
        