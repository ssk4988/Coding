#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi adj(n);
        rep(i, 0, n-1){
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v); adj[v].pb(u);
        }
        vvi dp(n, vi(4));
        // 0 - don't use this
        // 1 - use this
        // 2 - don't use this, leaf taken
        // 3 - use this (not as leaf), leaf taken
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            bool isleaf = sz(adj[u]) <= 1;
            dp[u][1] = 1;
            int sum = 0;
            for(int v : adj[u]){
                if(v == p) continue;
                dfs(v, u, dfs);
                dp[u][1] += dp[v][0];
                dp[u][0] += max(dp[v][0], dp[v][1]);
            }
            for(int v : adj[u]){
                if(v == p) continue;
                dp[u][2] = max(dp[u][2], dp[u][0] - max(dp[v][0], dp[v][1]) + max(dp[v][2], dp[v][3]));
                dp[u][3] = max(dp[u][3], dp[u][1] - dp[v][0] + dp[v][2]);
            }
            if(isleaf) dp[u][2] = max(dp[u][2], 1 + dp[u][0]);
        };
        dfs(0, -1, dfs);
        cout << *max_element(all(dp[0])) << "\n";
    }    
    
    return 0;
}
