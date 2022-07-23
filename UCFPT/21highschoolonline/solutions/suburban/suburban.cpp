/**
 * Ryan Glaspey, 03/07/20
 * First Draft
 */ 

#include <bits/stdc++.h>

using namespace std;

int main() {
    unordered_map<int, int> isSquare;
    for (int i = 0; i * (long long int)i <= 1e9; i++) {
        isSquare[i * i] = i;
    }

    int t;
    cin >> t;
    while (t-->0) {
        int n;
        cin >> n;
        int sum = -1;
        for (int i = 0; i * (long long int)i < n; i++) {
            auto found = isSquare.find(n - (i * i));
            if (found != isSquare.end()) {
                int j = found->second;
                if (sum == -1 || i + j < sum) sum = i + j;
            }
        }
        cout << sum << "\n";
    }

    return 0;
}