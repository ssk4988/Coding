#include <bits/stdc++.h>
using namespace std;

int k, n, r;
int generated = 0;
string current;

// start represents the first character in the alphabet we are allowed to insert at idx
void bf(int idx, char start) {
    if (idx == n) {
        generated++;
        // only print out the r-th string
        if(generated == r) {
            cout << current << "\n";
        }
        return;
    }
    for(char c = start; c <= 'z'; c++) {
        current[idx] = c;
        // skip the next k letters
        bf(idx+1, c + k + 1);
        // break out early if the r-th string has been generated
        if(generated >= r) break;
    }
}

void solve() {
    cin >> k >> n >> r;
    current = string(n, 'a');
    generated = 0;
    // the first letter is allowed to be anything
    bf(0, 'a');
}

int main() {
    int nc; 
    cin >> nc;
    for(int cn = 0; cn < nc; cn++) {
        solve();
    }

    return 0;
}
