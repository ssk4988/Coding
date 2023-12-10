#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, l; cin >> n >> l;
        l *= 2;
        vi ls(n);
        vl v(n);
        rep(i, 0, n){
            cin >> ls[i] >> v[i];
        }
        ll inf = 1e18;
        vector<vl> dp(l + 1, vl(3, -inf));
        dp[0][0] = 0;
        rep(i, 0, n){
            dp[l][2] = max(dp[l][2], dp[0][0] + v[i]);
            for(int j = sz(dp) - 1; j >= 0; j--){
                for(int k = 2; k >= 0; k--){
                    if(j + ls[i] <= l && k < 2){
                        dp[j + ls[i]][k + 1] = max(dp[j + ls[i]][k + 1], dp[j][k] + v[i]);
                    }
                    if(j + 2 * ls[i] <= l){
                        dp[j + 2 * ls[i]][k] = max(dp[j + 2 * ls[i]][k], dp[j][k] + v[i]);
                    }
                }
            }
        }
        ll ans = 0;
        rep(i, 0, l + 1){
            rep(j, 0, 3) ans = max(ans, dp[i][j]);
        }
        cout << "Case #" << (cn + 1) << ": " << ans << "\n";
    }
    return 0;
}
