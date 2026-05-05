#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
const ll mod = 1e9+7;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vl dp{1}, pref{1};
    while(sz(dp) < 3e5) {
        dp.push_back((pref.back() + 2) % mod);
        pref.push_back((pref.back() + dp.back()) % mod);
    }
    // rep(i, 0, 10) cerr << i << " " << dp[i] << " " << pref[i] << endl;
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        string s;
        vi digs;
        cin >> s;
        bool hasother = false;
        for(char c : s) {
            if(c > '1') hasother = true;
            digs.push_back((c - '0') % 2);
        }
        reverse(all(digs));
        ll ans = 0;
        if(hasother) ans++;
        rep(i, 0, sz(digs)) {
            if(digs[i] == 1) (ans += dp[i]) %= mod;
        }
        cout << ans << "\n";
    }
    return 0;
}
