// password.cpp
// by Jacob Steinebronn
#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int NUM_TESTS;
    cin >> NUM_TESTS;
    // For each test case...
    while(NUM_TESTS--){
        int n;
        cin >> n;
        
        // Number of passwords is 4^n = 2^(2*n)
        // This is because every digit can be either 0, 3, 6, or 9
        // Because if the digits were any other, the substring of length 1
        // representing individual digits wouldn't be divisible by 3! 
        cout << (1<<(2*n)) << endl;
    }
}
