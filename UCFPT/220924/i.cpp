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

int m = 1e9 + 7;
ll mod(ll k)
{
    return k % m;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string p, s;
    cin >> p >> s;
    set<string> rots;
    ll dp[s.length() + 1];
    ll ans = 0;
    rep(i, 0, s.length())
    {
        string s2;
        rep(j, 0, s.length())
        {
            s2 += s[(i + j) % s.length()];
        }
        if (rots.find(s2) != rots.end())
        {
            continue;
        }
        rots.insert(s2);
         cout << s2 << nL;
        memset(dp, 0, sizeof dp);
        dp[0] = 1;
        rep(j, 0, p.length())
        {
            for (int k = s.length() - 1; k >= 0; k--)
            {
                if (s[k] == p[j])
                {
                    dp[k + 1] = mod(dp[k + 1] + dp[k]);
                }
            }
        }
        ans = mod(ans + dp[s.length()]);
    }
    cout << ans << nL;

    return 0;
}