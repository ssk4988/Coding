#include <bits/stdc++.h>
using namespace std;

int k, n, r;
string cur;

void bf(int idx, char start) {
    if(idx == n) {
        r--;
        if(r == 0) {
            cout << cur << "\n";
        }
        return;
    }
    for(char c = start; c <= 'z'; c++) {
        cur[idx] = c;
        bf(idx+1, c + k + 1);
        if(r == 0) break;
    }
}

void solve() {
    cin >> k >> n >> r;
    cur = string(n, 'a');
    bf(0, 'a');
}

int main() {
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++) {
        solve();
    }
}
