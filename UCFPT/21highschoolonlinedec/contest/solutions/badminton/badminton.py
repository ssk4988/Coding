# badminton.py by Jacob Steinebronn
numtests = (int)(input().strip())

for tnum in range(numtests):
    cur, s = input().strip().split()
    cur = 1 if cur == 'A' else 0 # cur is 1 if it's alice's turn
    rounds = list(map(int, input().strip().split()))
    sa, sb = (0,0) # scores for alice and bob respectively
    for rnd in rounds:
        if rnd % 2 == 0: # if the shuttle was hit an even number of times, server changes
            cur ^= 1
        else:
            if cur == 1: sa += 1 # Award a point
            else: sb += 1 
    print(sa,sb,sep='-')