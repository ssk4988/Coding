#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    const int mod = 1e9+7;
    int N = 400;
    const int W = 1e5+10;
    vi dp(W);
    dp[0] = 1;
    vi w(n);
    rep(i, 0, n) {
        cin >> w[i];
    }
    rep(i, 0, min(N, n)) {
        vi new_dp(dp);
        int lim = min(sz(new_dp), (i+1)*(i+1)+1);
        rep(j, 0, sz(dp)){
            if(j+w[i] < lim){
                (new_dp[j+w[i]] += dp[j]) %= mod;
            }
        }
        dp = new_dp;
    }
    int ans = 0;
    rep(i, 0, sz(dp)) {
        (ans += dp[i]) %= mod;
    }
    rep(i, min(N, n), n) {
        (ans *= 2) %= mod;
    }
    cout << ans << "\n";
    return 0;
}
