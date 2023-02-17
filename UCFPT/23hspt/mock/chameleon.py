n = int(input())

arr = [int(i) for i in input().split()]

ans = 1
for i in range(1, len(arr)):
    if(arr[i] != arr[i - 1]):
        ans += 1

print(ans)