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
ll mod(ll k)
{
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k;
    cin >> n >> k;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    sort(all(a));
    vector<vvl> dp(n + 1);
    rep(i, 0, n + 1){
        dp[i] = vvl(i + 1, vl(k + 1));
    }
    dp[0][0][0] = 1;
    rep(i, 0, n)
    {
        int newi = i + 1;
        int dif = a[i] - (i == 0 ? 0 : a[i - 1]);
        rep(j, 0, i + 1)
        {
            rep(l, 0, k + 1)
            {
                if (dp[i][j][l] == 0)
                    continue;
                int newl = l + j * dif;
                if (newl > k)
                    continue;
                // add and close immediately
                dp[i + 1][j][newl] = mod(dp[i + 1][j][newl] + dp[i][j][l]);
                // extend open
                dp[i + 1][j][newl] = mod(dp[i + 1][j][newl] + mod(j * dp[i][j][l]));
                // close one
                if (j > 0)
                {
                    dp[i + 1][j - 1][newl] = mod(dp[i + 1][j - 1][newl] + mod(j * dp[i][j][l]));
                }
                // open one
                if (j < n)
                {
                    dp[i + 1][j + 1][newl] = mod(dp[i + 1][j + 1][newl] + dp[i][j][l]);
                }
            }
        }
    }
    ll ans = 0;
    rep(i, 0, k + 1){
        ans = mod(ans + dp[n][0][i]);
    }
    cout << ans << nL;

    return 0;
}
