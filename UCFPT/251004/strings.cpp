#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q; cin >> n >> q;
    string s; cin >> s;
    for(int qi = 0; qi < q; qi++) {
        char c; cin >> c;
        if(c == 'M') {
            int t; cin >> t;
            if(t == 1) {
                int i, j, k; cin >> i >> j >> k;
                i--;
                string t(s.substr(i, j-i));
                s.erase(begin(s)+i, begin(s)+j);
                s.insert(begin(s)+k, begin(t), end(t));
            } else if(t == 2) {
                int i, j; cin >> i >> j; i--;
                reverse(begin(s) + i, begin(s) + j);
            } else {
                int i; cin >> i >> c; i--;
                s.insert(begin(s) + i, c);
            }
        } else {
            int i, j; cin >> i >> j; i--;
            auto r = ranges::subrange(begin(s)+i, begin(s)+j);
            cout << (ranges::equal(r | views::reverse, r) ? "YES" : "NO") << "\n";
        }
    }

    return 0;
}
