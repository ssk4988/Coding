
import sys
input = sys.stdin.readline

line = input()
assert line.strip() +"\n" == line
n = int(line.strip())
assert 1 <= n <= 500000

vals = [0]*(n+1)

def update(index, val):
    global vals
    index += 1
    while index < len(vals):
        vals[index] += val
        index += (index&-index)
def comp(index):
    global vals
    index += 1
    res = 0
    while index:
        res += vals[index]
        index -= (index&-index)
    return res

for i in range(n):
    line = input()
    assert line.strip() + "\n" == line
    val = int(line.strip())
    assert 1 <= val <= 1000000000
    update(i, val)


line = input()
assert line.strip() + "\n" == line
q = int(line.strip())
assert 1 <= q <= 100000

for _ in range(q):
    line = input()
    assert line.strip() + "\n" == line
    let,fir,sec = line.strip().split(" ")
    assert let + " " + fir + " " + sec + "\n" == line
    fir = int(fir)
    sec = int(sec)
    if let == "R":
        assert 1 <= fir <= n
        assert 1 <= sec <= n
        print(comp(sec-1)-comp(fir-2))
    else:
        assert let == "U"
        assert 1 <= fir <= n
        assert 1 <= sec <= 1000000000
        update(fir-1, sec)

