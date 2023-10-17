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
    int c, n;
    cin >> c >> n;
    const int l = 1005;
    vvi dp(l + 1, vi(l + 1));
    dp[0][0] = true;
    rep(i, 0, n)
    {
        int v;
        cin >> v;
        for (int j = c; j >= 0; j--)
        {
            for (int k = c; k >= 0; k--)
            {
                if (j - v >= 0 && dp[j - v][k])
                {
                    dp[j][k] = true;
                }
                if (k - v >= 0 && dp[j][k - v])
                    dp[j][k] = true;
            }
        }
    }
    pi best = {0, 0};
    rep(j, 0, l + 1)
    {
        rep(k, 0, l + 1)
        {
            if (dp[j][k])
            {
                // cout << j << " " << k << nL;
                best = max(best, {j + k, -abs(j - k)});
            }
        }
    }
    int small = (best.f + best.s) / 2, big = small - best.s;
    cout << big << " " << small << nL;

    return 0;
}
