s = input()
ans = []
i = 0
while i < len(s):
    if s[i] == '-':
        if i + 2 < len(s) and s[i+2] != '+' and s[i+2] != '-':
            onlyzeros = True
            zerocnt = 0
            use = 1
            while s[i+use+1] == '0' and i+use+2 < len(s) and s[i+use+2] != '-' and s[i+use+2] != '+':
                use += 1
            for j in range(use+1):
                ans.append(s[i+j])
            # for start in range(1, len(s)):
            #     for j in range(i+start, len(s)):
            #         if s[j] == '+' or s[j] == '-': break
            #         if s[j] == '0':
            #             zerocnt += 1
            #         else: onlyzeros = False
            #     if zerocnt > 1 and onlyzeros:

            # ans.append(s[i])
            # ans.append(s[i+1])
            ans.append('+')
            i += use+1
            continue
    ans.append(s[i])
    i += 1
print(''.join(ans))
