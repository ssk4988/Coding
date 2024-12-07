from sys import stdin

ans = 0
enabled = True
for line in stdin:
  for i in range(len(line)):
    if line[i:i+4] == "do()":
       enabled = True
    if line[i:i+7] == "don't()":
       enabled = False
    if not enabled: continue
    if line[i:i+4] != 'mul(': continue
    idx = i+4
    while idx < len(line) and line[idx] != ')': idx += 1
    if idx >= len(line): continue
    v = line[i+4:idx].split(',')
    if len(v) != 2: continue
    try:
       ans += int(v[0]) * int(v[1])
    except:
       continue
print(ans)
