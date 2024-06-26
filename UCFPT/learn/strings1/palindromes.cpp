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
    string str; cin >> str;
    
    vi slink = {0, 0}, len = {-1, 0};
    vvi down(2, vi(26, -1));
    int cur = 0, t = 0;
    vl dp(2);
    for (int i = 0; i < str.size(); i++)
    {
        char c = str[i];
        int ci = c - 'a';
        while (t <= 0 || str[t - 1] != c)
            t = i - len[cur = slink[cur]];
        if (down[cur][ci] == -1)
        {
            down[cur][ci] = slink.size();
            down.emplace_back(26, -1);
            len.pb(len[cur] + 2);
            dp.pb(0);
            if (len.back() > 1)
            {
                do
                    t = i - len[cur = slink[cur]];
                while (t <= 0 || str[t - 1] != c);
                slink.pb(down[cur][ci]);
            }
            else
                slink.pb(1);
            cur = slink.size() - 1;
        }
        else
            cur = down[cur][ci];
        t = i - len[cur] + 1;
        dp[cur]++;
    }
    for(int i = slink.size() - 1; i > 0; i--){
        dp[slink[i]] += dp[i];
    }
    ll best = 0;
    rep(i, 0, sz(dp)){
        best = max(best, dp[i] * len[i]);
    }
    cout << best << nL;

    return 0;
}
