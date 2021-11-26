#rna.py by Jacob Steinebronn

# Idea of this solution: 
# Any substring can be mapped to a string of numbers from 1-20 by taking the pairs
# of 3 and mapping them as dictated by the 64 lines of input. Now, imagine constructing 
# the first substring of length *r*, and getting this string of acids. If we were to 
# take the next substring, we'd have to redo all the work we did to get this substring,
# since everything got shifted inside the triplets. However, if we take the substring
# 3 positions later, all the decodings are the same, except shifted one over, and the first 
# one is gone, and the last one is new. So, we build the substrings this way, moving 
# left to right, adding one set of 3 letters each time, starting at 0, then 1, then 2.
# Note that starting at 3 is the same as starting at 0, shifted by 3, which we 
# already did, so we're done. To do this, we're going to use rolling hashes, and
# we need to double-hash because we are recording O(n-r) substrings, which can get quite large
# and will most likely collide if we single-hashed

nt = (int)(input().strip()) # num tests

# m1, m2 are the mods for each hash, and b1, b2 are the bases for each hash
m1 = (int)(1e9+7)
m2 = (int)(1e9+9)
b1 = 31
b2 = 37

# computes a^b mod m in O(log b)
def modpow(a, b, m):
    ans = 1
    while b > 0:
        if b%2 == 0:
            a = (a*a)%m
            b/=2
        else:
            ans = (ans*a)%m
            b-=1
    return ans

for tn in range(nt):

    strr = input().strip()
    n = len(strr)

    maps = {} # map from string to int for each triplet of letters to its number
    for i in range(64):
        rna, idx = input().strip().split()
        maps[rna] = (int)(idx)


    rl = (int)(input().strip())
    acids = rl//3 # number of triplets in r

    #finalpow1 and 2, used for removing the item from the front in the rolling hashes later
    finalpow1 = modpow(b1, acids-1, m1)
    finalpow2 = modpow(b2, acids-1, m2)


    hashes = set()
    # for each start position 0-2, do the rolling hashes
    for start in range(3):
        if start+rl > n:
            break

        # cur1, cur2 the current hashes
        cur1 = 0
        cur2 = 0

        # Get the first string of acids' hashes
        for i in range(acids):
            cur1 = (cur1 * b1 + maps[strr[start+i*3:start+i*3+3]]) % m1 # roll and add
            cur2 = (cur2 * b2 + maps[strr[start+i*3:start+i*3+3]]) % m2 # roll and add

        # Add this pair of hashes to the set, and roll the hashes forward
        hashes.add((cur1, cur2))
        offsets = (n-start)//3 - acids
        for i in range(offsets):

            rem = maps[strr[start+i*3:start+i*3+3]] # the number to remove from the front
            add = maps[strr[start+(acids+i)*3:start+(acids+i+1)*3]] # the number to add to the end

            cur1 = (cur1 - rem*finalpow1 + m1) % m1 # remove rem
            cur1 = (cur1*b1 + add) % m1             # roll and add 
            cur2 = (cur2 - rem*finalpow2 + m2) % m2 # remove rem
            cur2 = (cur2*b2 + add) % m2             # roll and add

            hashes.add((cur1, cur2)) # add new hash to set
    print(len(hashes)) # gg

