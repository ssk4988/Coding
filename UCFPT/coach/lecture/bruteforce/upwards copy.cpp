#include <bits/stdc++.h>
using namespace std;

int k, n, r;
int generated = 0;
string current;

void bf(int idx, char start) {
    if (idx == n) {
        generated++;
        if(generated == r) {
            cout << current << "\n";
        }
        return;
    }
    for(char c = start; c <= 'z'; c++) {
        current[idx] = c;
        bf(idx+1, c + k + 1);
        if(generated >= r) break;
    }
}
/*
abcd
3
2.5


abcd 3 2.5

*/
void solve() {
    string x;
    int a;
    double c;
    cin >> x >> a >> c;
    cin >> k >> n >> r;
    current = string(n, 'a');
    generated = 0;
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
