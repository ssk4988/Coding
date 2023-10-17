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

const ll MOD = 998244353;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    const int maxn = 2e5 + 100, maxk = 500;
    const ll BAD = -1;
    vector<vl> dp(maxn, vl(maxk));
    // dp[0] = vl(maxk, 1);
    dp[0][0] = 1;
    rep(i, 0, sz(dp)){
        rep(j, 0, sz(dp[i])){
            if(i - j >= 0 && j > 0){
                dp[i][j] = (dp[i][j] + dp[i - j][j]) % MOD;
            }
            if(j - 1 >= 0) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            // if(i < 10 && j < 10) cout << i << " " << j << " " << dp[i][j] << nL;
        }
    }
    int nc; cin >> nc;
    rep(cn,0,nc){
        int n; cin >> n;
        ll ans = 0;
        rep(i, 1, n + 1){
            if(i * i > n) break;
            if((n - i * i) % 2 != 0) continue;
            ll left = (n - i * i) / 2;
            ans = (ans + dp[left][i]) % MOD;
            // cout << n << " " << i << " " << left << " " << dp[left][i] << "\n";
        }
        cout << ans << nL;
    }
    return 0;
}
