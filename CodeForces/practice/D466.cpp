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
using vvl = vector<vl>;

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

ll MOD = 1e9 + 7;
ll mod(ll k){
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, h; cin >> n >> h;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vvl dp(n + 1, vl(n + 1));
    dp[0][0] = 1;
    rep(i, 0, n){
        rep(j, 0, n + 1){
            if(dp[i][j] == 0) continue;
            if(j + 1 + a[i] == h){
                // open new and close it
                dp[i + 1][j] = mod(dp[i + 1][j] + dp[i][j]);
                // open
                dp[i + 1][j + 1] = mod(dp[i + 1][j + 1] + dp[i][j]);
                if(j > 0){
                    // close pre-existing and open new one
                    dp[i + 1][j] = mod(dp[i + 1][j] + mod(j * dp[i][j]));
                }
            }
            if(j + a[i] == h){
                // do nothing
                dp[i + 1][j] = mod(dp[i + 1][j] + dp[i][j]);
                if(j > 0){
                    // close
                    dp[i + 1][j - 1] = mod(dp[i + 1][j - 1] + mod(j * dp[i][j]));
                }
            }
        }
    }
    cout << dp[n][0] << nL;
    return 0;
}
