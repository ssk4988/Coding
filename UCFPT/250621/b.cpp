#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, b; cin >> n >> b;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    sort(all(a));
    vector dp(n+1, vl(b+1, 1e18));
    dp[0][0] = 0;
    rep(i, 0, n) {
        rep(j, i+1, n+1) {
            rep(k, 0, b) {
                dp[j][k+1] = min(dp[j][k+1], dp[i][k] + (a[j-1]-a[i])*(a[j-1]-a[i]));
            }
        }
    }
    ll ans = dp[n][b];
    rep(i, 0, b+1) ans = min(ans, dp[n][i]);
    cout << ans << "\n";

    return 0;
}
