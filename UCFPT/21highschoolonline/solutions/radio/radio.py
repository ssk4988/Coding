# radio.py by Jacob Steinebronn

# Solution idea: Treat the radio stations like an array.
# Without presets, the answer would be the shortest distance 
# allowing looping on the array between two indices, which can
# be calculated with a simple formula min(abs(j-i), n-abs(j-i)).
# Each preset can be treated as a new start point, except with 1
# additional step, so just take the min of each of these.

# O(p*s) per day

nt = (int)(input().strip())
for tn in range(nt):
    n, p, s = map((int), input().strip().split())

    # Map from the string version of each station to the "index"
    # of the array it represents
    stat = {}
    for i, rad in enumerate(input().strip().split()):
        stat[rad] = i
    # presets, an array of indices, those that are addressed by the presets
    presets = [stat[x] for x in input().strip().split()]
    
    print("Day #{}:".format(tn+1))
    for i in range(s):
        # See solution idea for explanation
        sidx, eidx = map(lambda x: stat[x], input().strip().split())
        ans = min(abs(eidx-sidx), n-abs(eidx-sidx))

        for preset in presets:
            ans = min(ans, 1+min(abs(eidx-preset), n-abs(eidx-preset)))

        print(ans)
        
    print()
