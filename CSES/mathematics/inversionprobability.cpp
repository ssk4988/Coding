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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi r(n);
    rep(i, 0, n){
        cin >> r[i];
    }
    ld ans = 0;
    vector<vector<ld>> dp(n + 1, vector<ld>(101));
    rep(i, 0, n){
        dp[i + 1] = dp[i];
        rep(j, 1, r[i] + 1){
            rep(j1, j + 1, 101){
                ans += dp[i][j1] / r[i];
            }
            dp[i + 1][j] += ld(1) / r[i];
        }
    }
    cout << fixed << setprecision(6) << ans << nL;
    
    return 0;
}