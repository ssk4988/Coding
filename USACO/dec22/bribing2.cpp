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
    int n, a, b;
    cin >> n >> a >> b;
    vvi dp(n + 1, vi(a + b + 2, 0)); // 0 to b is all mooney left, b + 1 to a + b + 1 is no cones left
    vector<array<int, 3>> cows(n);
    for (auto &[x, p, c] : cows)
    {
        cin >> p >> c >> x;
    }
    sort(all(cows));

    rep(i, 0, n)
    {
        dp[i + 1] = dp[i];
        rep(j, 0, a + b + 2)
        {
            int mooney = j <= b ? a : j - (b + 1);
            int cones = j <= b ? j : 0;
            int nmooney = mooney, ncones = cones;
            bool added = false;
            if (cones > 0)
            {
                ncones = max(0, ncones - cows[i][0] * cows[i][2]);
            }
            if (cones - ncones < cows[i][0] * cows[i][2])
            {
                nmooney -= cows[i][2] - (cones - ncones) / cows[i][0];
                if (nmooney >= 0)
                    added = true;
            }
            else
            {
                added = true;
            }
            if (added)
            {
                int j1 = ncones == 0 ? b + 1 + nmooney : ncones;
                dp[i + 1][j1] = max(dp[i][j] + cows[i][1], dp[i + 1][j1]);
            }
        }
    }
    int ans = 0;
    rep(i, 0, a + b + 2)
    {
        ans = max(ans, dp[n][i]);
    }
    cout << ans << nL;

    return 0;
}