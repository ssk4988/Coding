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
        int n, k, MOD;
        cin >> n >> k >> MOD;
        // i, a[i], a[i-1] -> i+1, x, a[i] where x + a[i-1] >= a[i] implies x >= a[i] - a[i-1] means a[i-1] >= a[i] - x
        vector<vvi> dp(n, vvi(k+1, vi(k+1)));
        vector<vvi> suff(n, vvi(k+1, vi(k+1)));
        for (int i = k; i >= 0; i--)
        {
            suff[0][i][0] = dp[0][i][0] = 1;
        }
        rep(i, 1, n)
        {
            rep(a, 0, k + 1)
            {
                rep(b, 0, k + 1)
                {
                    int c = max(b - a, 0);
                    // if(c > k) continue;
                    suff[i][a][b] = dp[i][a][b] = suff[i - 1][b][c];
                }
                for (int b = k - 1; b >= 0; b--)
                {
                    (suff[i][a][b] += suff[i][a][b + 1]) %= MOD;
                }
            }
        }
        int ans = 0;
        rep(a, 0, k + 1)
        {
            rep(b, 0, k + 1)
            {
                if (b >= a)
                    (ans += dp[n - 1][a][b]) %= MOD;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
