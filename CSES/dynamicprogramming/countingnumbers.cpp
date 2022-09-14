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

ll pref(ll num, ll dp[18][10])
{
    ll p10 = 1;
    int pow = 0;
    while (p10 * 10 <= num)
    {
        p10 *= 10;
        pow++;
    }
    int lastdig = num / p10;
    ll ans = dp[pow][lastdig];
    ll n = num;
    n %= p10;
    pow--;
    p10 /= 10;
    while (pow >= 0)
    {
        rep(i, num / p10 + 1, 10)
        {
            ans -= dp[pow][i];
        }
        n %= p10;
        pow--;
        p10 /= 10;
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll a, b;
    cin >> a >> b;
    ll dp[18][10];
    memset(dp, 0, sizeof dp);
    ll p10 = 1;
    rep(i, 1, 18)
    {
        rep(j, 0, 10)
        {
            rep(k, 0, 10)
            {
                if (k == j)
                    dp[i][j] += p10;
                else
                    dp[i][j] += dp[i - 1][k];
            }
        }
        p10 *= 10;
    }
    cout << pref(b, dp) - pref(a, dp) << nL;
    return 0;
}