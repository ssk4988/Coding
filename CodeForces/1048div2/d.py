import sys
input = sys.stdin.readline

def main():
    n, q = map(int, input().split())
    a = list(map(lambda x: int(x)-1, input().split()))
    l = [-1] * n
    r = [-1] * n
    st = []
    for i in range(n):
        while len(st) and a[st[-1]] < a[i]:
            st.pop()
        if len(st):
            l[i] = st[-1]
        st.append(i)
    st = []
    for i in reversed(range(n)):
        while len(st) and a[st[-1]] > a[i]:
            st.pop()
        if len(st):
            r[i] = st[-1]
        st.append(i)
    bad = [-1] * n
    for i in range(n):
        if l[i] != -1 and r[i] != -1:
            bad[r[i]] = max(bad[r[i]], l[i])
    for i in range(1, n):
        bad[i] = max(bad[i], bad[i-1])
    for qid in range(q):
        l, r = map(int, input().split())
        l -= 1
        r -= 1
        print("YES" if bad[r] < l else "NO")

nc = int(input())
for cn in range(nc):
    main()
