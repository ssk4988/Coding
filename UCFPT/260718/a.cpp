#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    int sm = accumulate(all(a), 0);
    const int inf = 1e9;
    vi dp(2 * sm+1, -inf);
    dp[sm] = 0;
    rep(i, 0, n) {
        vi new_dp(dp);
        rep(j, 0, sz(new_dp)-a[i]) {
            new_dp[j+a[i]] = max(new_dp[j+a[i]], dp[j] + a[i]);
        }
        rep(j, a[i], sz(dp)) {
            new_dp[j-a[i]] = max(new_dp[j-a[i]], dp[j] + a[i]);
        }
        dp = new_dp;
    }
    int ans = dp[sm]/2;
    cout << ans + sm - ans*2 << "\n";

    return 0;
}
