#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

void solve() {
    int n; cin >> n;
    vector<string> g(2);
    rep(i, 0, 2) cin >> g[i];
    vvi grid(2, vi(n));
    rep(i, 0, 2){
        rep(j, 0, n) grid[i][j] = g[i][j] == 'A';
    }
    vvi dp(n+10, vi(10, -1e9));
    dp[0][5] = 0;
    rep(i, 0, n+1) {
        rep(j, 0, 10) {
            // top 3
            if(j >= 3 && i+3 <= n) {
                dp[i+3][j-3] = max(dp[i+3][j-3], dp[i][j] + ((grid[0][i] + grid[0][i+1] + grid[0][i+2]) >= 2));
            }
            // bottom 3
            if(j + 3 < 10 && i + j - 5 >= 0 && i + j - 5 + 2 < n) {
                dp[i][j+3] = max(dp[i][j+3], dp[i][j] + ((grid[1][i + j - 5] + grid[1][i + j - 5 + 1] + grid[1][i + j - 5 + 2]) >= 2));
            }
        }
        if(i+2 <= n) {
            dp[i+1][6] = max(dp[i+1][6], dp[i][5] + ((grid[0][i] + grid[1][i] + grid[1][i+1]) >= 2));
            dp[i+2][4] = max(dp[i+2][4], dp[i][5] + ((grid[0][i] + grid[1][i] + grid[0][i+1]) >= 2));
            dp[i+2][5] = max(dp[i+2][5], dp[i][6] + ((grid[0][i] + grid[0][i+1] + grid[1][i+1]) >= 2));
        }
        if(i > 0 && i+1 <= n) dp[i+1][5] = max(dp[i+1][5], dp[i][4] + ((grid[0][i] + grid[1][i] + grid[1][i-1]) >= 2));
    }
    cout << dp[n][5] << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }
    
    return 0;
}
