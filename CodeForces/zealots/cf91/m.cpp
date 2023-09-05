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
    if (n == 2)
    {
        cout << "2 2\n1 1\n";
        return 0;
    }
    int root = -1;
    rep(i, 0, n)
    {
        if (sz(adj[i]) > 1)
        {
            root = i;
            break;
        }
    }
    vi par(n);
    int ans = 0;
    vector<vvl> dp(n, vvl(2, vl(3)));
    // return if s is better than f
    auto better = [&](vl &f, vl &s) -> bool{
        if(f[0] != s[0]) return f[0] < s[0];
        if(f[1] != s[1]) return f[1] > s[1];
        return f[2] > s[2];
    };
    // 0 dim: node 1 dim: whether it is good {i, j, k} = good nodes in subtree, weight subtree, weight of node
    auto dfs = [&](int cur, int pre, auto &&dfs) -> void
    {
        par[cur] = pre;
        dp[cur][1][0] = 1;
        dp[cur][0][2] = 1;
        for (int i : adj[cur])
        {
            if (i == par[cur])
                continue;
            dfs(i, cur, dfs);
            rep(j, 0, 3){
                dp[cur][1][j] += dp[i][0][j];
            }
            int best = better(dp[i][0], dp[i][1]) ? 1 : 0;
            rep(j, 0, 2){
                dp[cur][0][j] += dp[i][best][j];
            }
        }
        if(par[cur] != -1) dp[cur][1][2] += 1;
        dp[cur][0][1] += dp[cur][0][2];
        dp[cur][1][1] += dp[cur][1][2];
    };
    dfs(root, -1, dfs);
    vl weight(n);
    auto buildback = [&](int cur, int type, auto &&buildback) -> void{
        weight[cur] = dp[cur][type][2];
        for (int i : adj[cur])
        {
            if (i == par[cur])
                continue;
            int best = better(dp[i][0], dp[i][1]) ? 1 : 0;
            buildback(i, best, buildback);
        }
    };
    int best = better(dp[root][0], dp[root][1]) ? 1 : 0;
    buildback(root, best, buildback);

    ll sum = 0;
    rep(i, 0, n)
    {
        sum += weight[i];
    }
    cout << dp[root][best][0] << " " << sum << nL;
    rep(i, 0, n)
    {
        cout << weight[i] << " ";
    }
    cout << nL;

    return 0;
}
