#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi ts(n);
        rep(i, 0, n) cin >> ts[i];
        // set<int> tset(all(ts));
        // vi et(tset);
        // for(int t : ts) {
        //     rep(j, 0, 105) {
        //         et.push_back(t+j);
        //     }
        // }
        // sort(all(et));
        // et.erase(unique(all(et)), end(et));
        // rep(i, 0, sz(et)) {
        //     if()
        // }
        int c; cin >> c;
        vi r(c);
        sort(all(ts));
        rep(i, 0, c) cin >> r[i];
        if(c == 1) {
            int last = -1e9;
            int hit = 0;
            for(int t : ts) {
                if(last + r[0] <= t) {
                    last = t;
                } else hit++;
            }
            cout << "Mission #" << (cn+1) << ": " << hit << "\n";
        }else {
            vector dp(n+1, vector(r[0]+1, vi(r[1]+1, -1)));
            auto go = [&](int i, int c0, int c1, auto &&go) -> int {
                if(i == n) return 0;
                auto &ans = dp[i][c0][c1];
                if(ans != -1) return ans;
                ans = 1e9;
                int dt = i == n-1 ? 10000 : ts[i+1]-ts[i];
                ans = 1 + go(i+1, max(0, c0-dt), max(0, c1-dt), go);
                if(c0 == 0) {
                    ans = min(ans, go(i+1, max(0, r[0]-dt), max(0, c1-dt), go));
                }
                if(c1 == 0) {
                    ans = min(ans, go(i+1, max(0, c0-dt), max(0, r[1]-dt), go));
                }
                return ans;
            };
            int ans = go(0, 0, 0, go);
            cout << "Mission #" << (cn+1) << ": " << ans << "\n";
        }
        cout << "\n";
    }
    

    return 0;
}
