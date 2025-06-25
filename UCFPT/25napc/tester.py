n = 10

lc = 0
st = [0]
while True:
    try:
        line = input()
        l = len(line)
        # print(l)
        if l >= 7:
            st.append(l-7)
        elif l == 5:
            x = st.pop()
            y = st.pop()
            st[x] = st[y]
        elif l == 4:
            st.append(n)
        elif l == 1:
            x = st.pop()
            y = st.pop()
            st.append(x+y)
        else:
            print("have " + l)
            raise l
        lc += 1
    except:
        break
print(st)
print("read: ", lc)
print(len(st))
