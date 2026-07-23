#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using pii = pair<int,int>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int r, c; cin >> r >> c;
    int k; cin >> k;
    ll ans = 0;
    map<int, vector<array<int, 3>>> mp;
    rep(i, 0, r) {
        string s; cin >> s;
        rep(j, 0, c) {
            if(s[j] == '#') {
                mp[i - k].push_back({1, j-k, j+k+1});
                mp[i + k + 1].push_back({-1, j-k, j+k+1});
            }
        }
    }
    set<array<int, 3>> s;
    int prvk = -1e9;
    int key = 0;
    for(auto [k, v] : mp) {
        ll dk = k - prvk;
        int cover = 0;
        int prv = -1e9;
        for(auto [x, d, inc] : s) {
            ll dx = x - prv;
            if(cover > 0 && dk * dx > 0) {
                ans += dk * dx;
                // cerr << "cover " << cover << " " << dk << " " << dx << endl;
            }
            prv = x;
            cover += d;
        }
        for(auto [d, l, r] : v) {
            s.insert({l, d, key++});
            s.insert({r, d*-1, key++});
        }
        prvk = k;
    }
    cout << ans << "\n";
    return 0;
}
