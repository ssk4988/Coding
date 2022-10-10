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

int dp[22][80];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    memset(dp, -1, sizeof dp);
    int t, a, n, t1, a1, w;
    cin >> t >> a >> n;
    dp[0][0] = 0;
    rep(i, 0, n)
    {
        cin >> t1 >> a1 >> w;
        for (int j = t; j >= 0; j--)
        {
            for (int k = a; k >= 0; k--)
            {
                if (dp[j][k] == -1)
                    continue;
                dp[min(t, j + t1)][min(a, k + a1)] = dp[min(t, j + t1)][min(a, k + a1)] == -1 ? dp[j][k] + w : min(dp[min(t, j + t1)][min(a, k + a1)], dp[j][k] + w);
            }
        }
    }
    cout << dp[t][a] << nL;

    return 0;
}