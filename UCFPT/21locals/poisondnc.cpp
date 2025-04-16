#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k; cin >> n >> k;
    k = min(k, 20);
    const int bad = -1;
    const int inf = 1e9;
    vvi dp(n+1, vi(k+1, inf));
    rep(i, 1, n+1) {
        rep(j, 1, k+1) {
            if(i == 1) dp[i][j] = 0;
            else if(j == 0) dp[i][j] = inf;
            else if(j == 1) dp[i][j] = i-1;
        }
    }
    rep(left, 2, k+1) {
        int popt = 1;
        rep(len, 2, n+1) {
            int &ans = dp[len][left];
            pii opt = {1e9, -1};
            rep(t, popt, min(len, popt+2)) {
                int v = 1+max(dp[t][left-1], dp[len-t][left]);
                opt = min(opt, {v, t});
            }
            dp[len][left] = opt.first;
            popt = opt.second;
        }
    }
    cout << dp[n][k] << "\n";

    return 0;
}