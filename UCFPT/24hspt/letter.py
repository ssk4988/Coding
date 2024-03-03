common = "irness"
b = "brightness"
f = "fairness"
p = "princess"

freq = dict()
for i in "qwertyuiopasdfghjklzxcvbnm":
    freq[i] = 0
n = int(input())
for _ in range(n):
    let, cnt = input().split()
    freq[let] = int(cnt)

mxcmn = 1000000
bcmn = 1000000
fcmn = 1000000
pcmn = 1000000
def getcnt(f, c):
    if c == 's': return f // 2
    return f
for c in common:
    mxcmn = min(mxcmn, getcnt(freq[c], c))
for c in b:
    bcmn = min(bcmn, getcnt(freq[c], c))
for c in f:
    fcmn = min(fcmn, getcnt(freq[c], c))
for c in p:
    pcmn = min(pcmn, getcnt(freq[c], c))
print(min(mxcmn, bcmn + fcmn + pcmn))