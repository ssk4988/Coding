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
    int n, m; cin >> n >> m;
    const ld BAD = 1e9;
    vector<vd> dp(n + 1, vd(m + 1, BAD));
    dp[0][0] = 0;
    int calcs = 0;
    rep(i, 0, n){
        for(int j = 0; j <= m; j++){
            int lim = min(m - j, (m - j + (n - i - 1)) / (n - i));
            calcs += lim + 1;
            if(dp[i][j] == BAD) continue;
            rep(k, 1, lim + 1){
                dp[i + 1][j + k] = min(dp[i + 1][j + k], dp[i][j] + ld(j) / k);
            }

        }
    }
    ld ans = BAD;
    rep(i, 0, m + 1){
        ans = min(ans, dp[n][i]);
    }
    ans = n + 2 * ans;
    cout << calcs << nL;
    cout << fixed << setprecision(12) << ans << nL;

    
    return 0;
}
