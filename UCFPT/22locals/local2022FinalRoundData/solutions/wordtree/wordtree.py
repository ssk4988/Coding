
import sys
input = sys.stdin.readline

# Function to check a word is all upper case
def allUpper(w):
    for x in w:
        assert ord('A') <= ord(x) <= ord('Z')

# Disjoint Set class
class DS:
    # Constructor
    def __init__(s, n):
        s.p = [-1]*n

    # Find the root of a tree
    def find(s, x):
        if s.p[x] < 0:
            return x
        s.p[x] = s.find(s.p[x])
        return s.p[x]

    # Merge 2 trees
    def merge(s,a,b):
        # Find roots
        a = s.find(a)
        b = s.find(b)

        # Check if they are the same tree
        if a == b:
            return 0

        # Find the larger value
        if s.p[a] > s.p[b]:
            a,b = b,a

        # link b to a
        s.p[a] += s.p[b]
        s.p[b] = a

        # SUCCESS!!!
        return 1

# Function to find the distance between 2 strings
def dist(a,b):
    return sum(abs(ord(a[i])-ord(b[i])) for i in range(len(a)))

# Read in the first line
line = input()
n,k = map(int, line.strip().split())
assert str(n) + " " + str(k) + "\n" == line
assert 1 <= n <= 1000
assert 1 <= k <= 20

# Read in all the words
word = [None] * n
es = [None] * (((n-1)*n)//2)
index = 0
for i in range(n):
    line = input()
    word[i] = line.strip()
    assert word[i] + "\n" == line
    assert len(word[i]) == k
    allUpper(word[i])

    # Construct the edge between nodes
    for j in range(i):
        es[index] = [dist(word[i], word[j]), i, j]
        index += 1

# Sort the edges
es.sort()

# Make the disjoint set for finding the MST
ds = DS(n)

# Find the largest edge required to join all the sets
ans = 0
for tans, i, j in es:
    if ds.merge(i,j):
        ans = tans
print(ans)
