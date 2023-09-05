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
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n, k;
        cin >> n >> k;
        using vvl = vector<vl>;
        ll BAD = -1e16;
        vvl dp(n + 1, vl(n + 1));
        vvl best(n + 1, vl(4, BAD));
        vl a(n + 1), b(n + 1);
        rep(i, 1, n + 1) cin >> a[i];
        rep(i, 1, n + 1) cin >> b[i];
        // rep(j, 0, n + 1)
        // {
            best[0][0] = a[1] + b[1];
            best[0][1] = a[1] - b[1];
            best[0][2] = -a[1] + b[1];
            best[0][3] = -a[1] - b[1];
            // rep(l, 0, 4){
            //     best[j][l] = (l % 2 == 0 ? -1 : 1) * a[1] + (l / 2 == 0 ? -1 : 1) * b[1];
            // }
        // }
        rep(i, 1, n + 1)
        {
            rep(j, 0, k + 1)
            {
                int dif = i - j;
                if(dif < 0) continue;
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                // if (i && j)
                //     dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
                dp[i][j] = max(dp[i][j], best[dif][0] - b[i] - a[i]);
                dp[i][j] = max(dp[i][j], best[dif][1] - b[i] + a[i]);
                dp[i][j] = max(dp[i][j], best[dif][2] + b[i] - a[i]);
                dp[i][j] = max(dp[i][j], best[dif][3] + b[i] + a[i]);
                // rep(l, 0, 4){
                //     ll m = (l / 2 == 0 ? 1 : -1) * a[i] + (l % 2 == 0 ? 1 : -1) * b[i];
                //     dp[i][j] = max(dp[i][j], m + best[j][l]);
                // }
                if (i + 1 <= n)
                {
                    best[dif][0] = max(best[dif][0], dp[i][j] + a[i + 1] + b[i + 1]);
                    best[dif][1] = max(best[dif][1], dp[i][j] + a[i + 1] - b[i + 1]);
                    best[dif][2] = max(best[dif][2], dp[i][j] + -a[i + 1] + b[i + 1]);
                    best[dif][3] = max(best[dif][3], dp[i][j] + -a[i + 1] - b[i + 1]);
                    // rep(l, 0, 4){
                    //     ll m = (l % 2 == 0 ? -1 : 1) * a[i + 1] + (l / 2 == 0 ? -1 : 1) * b[i + 1];
                    //     best[j][l] = max(best[j][l], m + dp[i][j]);
                    // }
                }
            }
        }
        ll ans = 0;
        rep(j, 0, n + 1)
        {
            ans = max(ans, dp[j][k]);
        }
        cout << ans << nL;
    }

    return 0;
}
