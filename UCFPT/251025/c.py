days = ["Mon","Tue","Wed","Thu","Fri","Sat","Sun"]
times = []
for _ in range(2):
    s = input()
    day, t = s.split()
    h,m = map(int, t.split(":"))
    times.append(days.index(day) * 24 * 60 + h * 60 + m)
if times[1] <= times[0]: times[1] += 24 * 60 * 7
dt = times[1] - times[0]
names = ["day","hour","minute"]
vals = [24 * 60, 60, 1]
components = []
for i in range(3):
    components.append(dt//vals[i])
    dt %= vals[i]
prints = [(c,n + ("s" if c != 1 else "")) for c,n in zip(components, names) if c != 0]
if len(prints) == 2:
    print(prints[0][0],prints[0][1],"and",prints[1][0],prints[1][1])
else:
    print(", ".join(map(lambda x: str(x[0]) + " " + x[1], prints)))
