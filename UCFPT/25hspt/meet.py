r, p = map(int, input().split())
sr, sp = map(int, input().split())
ans = (p-r)/(sr+sp)
print(f"{ans:.8f}")