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
        int n, s;
        cin >> n >> s;
        vl x(n), y(n), a(n), maxv(n), minv(n);
        vector<vl> dp(n, vl(2, -1)); // dim 1: 1 if y[i] >= x[i]
        vector<vector<bool>> ready(n, vector<bool>(2, false));
        rep(i, 0, n)
        {
            cin >> a[i];
            if (i == 0 || i == n - 1)
                continue;
            if (a[i] == 2 * s)
            {
                minv[i] = s;
                maxv[i] = s;
            }
            else if (a[i] < 2 * s)
            {
                maxv[i] = min(a[i], (ll)s);
                minv[i] = a[i] - maxv[i];
            }
            else
            {
                minv[i] = (ll)max(s, 0);
                maxv[i] = a[i] - minv[i];
            }
        }
        minv[0] = maxv[0] = a[0];
        minv[n - 1] = maxv[n - 1] = a[n - 1];
        dp[0][1] = 0;
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                ll xval = j ? minv[i] : maxv[i];
                ll yval = j ? maxv[i] : minv[i];
                dp[i][j] = LLONG_MAX;
                for (int k = 0; k < 2; k++)
                {
                    if (dp[i - 1][k] == -1)
                        continue;
                    ll prevy = k ? maxv[i - 1] : minv[i - 1];
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + prevy * xval);
                }

                if (dp[i][j] == LLONG_MAX)
                    dp[i][j] == -1;
            }
        }

        cout << dp[n - 1][0] << nL;
    }

    return 0;
}
