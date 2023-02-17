arr = [int(i) for i in input().split()]
n = arr[0]
q = arr[1]

ans = [0 for i in range(1000500)]
pref = [0 for i in range(len(ans))]


ans[0] = pref[0] = 100
for i in range(1, len(ans)):
    ans[i] = pref[i - 1] - (pref[i - 1 - n] if i - 1 - n >= 0 else 0)
    ans[i] /= n
    pref[i] = pref[i - 1] + ans[i]

val = [int(input()) for i in range(q)]
for i in val:
    print(ans[i])
