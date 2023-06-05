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
    int n;
    cin >> n;
    vvi adj(n);
    rep(i, 0, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int BLANK = -1;
    vvi dp(n, vi(2, BLANK));
    auto dfs = [&](int cur, int pre, int used, auto &&dfs) -> int
    {
        if (dp[cur][used] != BLANK)
            return dp[cur][used];
        dp[cur][used] = 0;
        int reg = 0;
        for (int i : adj[cur])
        {
            if (i == pre)
                continue;
            reg += max(dfs(i, cur, 0, dfs), dfs(i, cur, 1, dfs));
        }
        if (used)
        {
            for (int i : adj[cur])
            {
                if (i == pre)
                    continue;
                dp[cur][used] = max(dp[cur][used], 1 + reg - max(dfs(i, cur, 0, dfs), dfs(i, cur, 1, dfs)) + dfs(i, cur, 0, dfs));
            }
        }
        else{
            dp[cur][used] = reg;
        }
        return dp[cur][used];
    };
    cout << max(dfs(0, -1, 0, dfs), dfs(0, -1, 1, dfs)) << nL;

    return 0;
}
