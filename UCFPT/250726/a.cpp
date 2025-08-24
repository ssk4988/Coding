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

const int mod = 998244353;
const int N = 2005;
int dp[N][N][2];


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    memset(dp, 0, sizeof dp);
    dp[0][0][0] = 1;
    // rep(m, 0, N) {
    //     dp[0][m][0] = 1;
    // }
    rep(n, 1, N) {
        rep(m, 0, N) {
            if(m > 0){
                int &ans = dp[n][m][1];
                (ans += dp[n][m-1][1]) %= mod;
                if(n >= m) {
                    (ans += dp[n-m][m][0]) %= mod;
                }
            }
            {
                int &ans = dp[n][m][0];
                (ans += dp[n-1][m][0]) %= mod;
                (ans += dp[n][m][1]) %= mod;
            }
        }
    }
    rep(n, 0, 10) {
        rep(m, 0, 10) {
            rep(k, 0, 2) {
                cerr << n << "," << m << "," << k << " = " << dp[n][m][k] << endl;
            }
        }
    }
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m; cin >> n >> m;
        int ans = 0;
        rep(f, 1, m+1) {
            (ans += dp[n-1][m-f][0]) %= mod;
        }
        cout << ans << "\n";
    }

    return 0;
}
