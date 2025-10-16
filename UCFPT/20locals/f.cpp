#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

/*
dp[i][j] = cost of first i book using k boxes
dp[i][j] = 
*/

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vector<pair<ll, ll>> b(n);
    rep(i, 0, n) {
        cin >> b[i].first >> b[i].second;
    }
    vl pdp(n+1, 1e18);
    pdp[0] = 0;
    rep(_, 0, k) {
        vl dp(n+1, 1e18);
        rep(i, 0, n) {
            ll w = 0, h = 0;
            rep(j, i, n) {
                w += b[j].first;
                h = max(h, b[j].second);
                dp[j+1] = min(dp[j+1], pdp[i] + w * h);
            }
        }
        pdp = dp;
    }
    cout << pdp.back() << "\n";


    return 0;
}
