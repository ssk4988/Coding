n = int(input())
words = [input() for i in range(n)]
q = int(input())
for i in range(q):
    query = input()
    if query in words:
        print(1)
        continue
    works = False
    for j in range(n):
        for k in range(n):
            if query == words[j] + words[k]:
                works = True
    print(2 if works else 0)
