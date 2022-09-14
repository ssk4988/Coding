
#include <bits/stdc++.h>

using namespace std;

// Function to count the number of sequences of length n such that 
//        len is <= k at all times
// Could be memo-ized for improvement in runtime.
// Could be converted into a Matrix Expo problem as well for very big bounds
int go(int n, int len, int k) {
    // Check if we used too long of a run
    if (k < len) return 0;

    // Check if we used all the bits
    if (!n) return 1;

    // Try to keep the chain going or reset the chain and swap values
    return go(n-1, len+1,k) + go(n-1,1,k);
}

int main() {
    int n, k;
    cin >> n >> k;

    // Call the function assuming we used no bits currently
    cout << go(n,0,k) << endl;
    return 0;
}
