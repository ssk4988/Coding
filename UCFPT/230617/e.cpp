#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t; cin >> t;
    rep(cn, 0, t){
        ll p; cin >> p;
        cout << (p * 6) << " " << 3 << "\n";
        cout << p << " " << (2 * p) << " " << (3 * p) << "\n";
    }
}
