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

const int N = 50;
const int T = N * 1e5 + 100;
int dp[2][T];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    rep(i, 0, 2)
    {
    }
    rep(j, 0, T)
    {
        dp[0][j] = 1e9;
    }
    dp[0][0] = 0;
    int cur = 0;
    rep(i, 0, n)
    {
        int a, b;
        cin >> a >> b;
        rep(j, 0, T)
        {
            dp[cur ^ 1][j] = 1e9;
        }
        rep(j, 0, T)
        {
            dp[cur ^ 1][j] = min(dp[cur ^ 1][j], dp[cur][j] + b);
        }
        rep(j, 0, T - a)
        {
            dp[cur ^ 1][j + a] = min(dp[cur ^ 1][j + a], dp[cur][j]);
        }
        cur ^= 1;
    }
    int ans = 1e9;
    rep(i, 0, T) ans = min(ans, max(i, dp[cur][i]));
    cout << ans << "\n";

    return 0;
}
