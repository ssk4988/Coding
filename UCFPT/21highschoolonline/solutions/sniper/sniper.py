# sniper.py by Jacob Steinebronn

numtest = (int)(input().strip())
for test in range(numtest):
    # Take input
    n, k = map(int, input().strip().split(" "))
    arr = list(map(int, input().strip().split(" ")))
    bullets = list(map(int, input().strip().split(" ")))
    
    # Make the array of either -1, 0, or 1 (the health doesn't matter, only the side)
    # Take the sum before this, though
    ans = sum(arr)
    arr = [x//abs(x) for x in arr]
    
    # Construct a prefix sum for arr
    psum = [arr[0]]*(n+1)
    for i in range(1,n):
        psum[i] = arr[i]+psum[i-1]

    # For each bullet, take it if it hits more good guys than bad guys
    # And increase the answer by the difference of good and bad guys
    for b in bullets:
        ans += 0 if psum[b - 1] < 0 else psum[b - 1]

    print(ans)
