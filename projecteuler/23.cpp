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
    int lim = 29000;
    vi abundants;
    rep(i, 1, lim)
    {
        int sum = 0;
        for (int j = 1; j * j <= i; j++)
        {
            if (j < i && i % j == 0)
            {
                sum += j;
                if ((i / j) < i && (i / j) != j)
                {
                    sum += i / j;
                }
            }
        }
        if (sum > i)
        {
            abundants.pb(i);
            // if(i < 100) cout << "abundant: " << i << " " << sum << nL;
        }
    }
    vi dp(lim);
    dp[0] = true;
    for (int i : abundants)
    {
        for (int j : abundants)
        {
            if (i + j < sz(dp))
                dp[i + j] = true;
        }
    }
    ll ans = 0;
    rep(i, 1, lim)
    {
        if (!dp[i])
        {
            ans += i;
            // cout << i << nL;
        }
    }
    cout << ans << nL;

    return 0;
}