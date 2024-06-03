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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        int a, b; cin >> a >> b; a--, b--;
        vvi adj(n);
        rep(i, 0, n-1){
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vi depth(n), maxd(n);
        vi path;
        auto dfs = [&](int u, int p, int d, auto &&dfs) -> bool {
            maxd[u] = depth[u] = d;
            bool seen = u == b;
            for(int v : adj[u]){
                if(v == p) continue;
                if(dfs(v, u, d+1, dfs)) seen = true;
                maxd[u] = max(maxd[u], maxd[v]);
            }
            if(seen) path.pb(u);
            return seen;
        };
        dfs(a, -1, 0, dfs);
        int ans = 2 * (n-1) - maxd[a] + depth[b];
        if(sz(path) > 1){
            auto deepest = [&](int u, int p, int d, auto &&deepest) -> int {
                int best = d;
                for(int v : adj[u]){
                    if(v == p) continue;
                    best = max(best, deepest(v, u, d+1, deepest));
                }
                return best;
            };
            // int idx = sz(path) % 2 == 1 ? sz(path)/2 : sz(path)/2-1;
            int idx = sz(path)/2;
            ans = min(ans, 2 * (n-1) + (sz(path) - 1 - idx) - deepest(path[idx], -1, 0, deepest) + (sz(path) % 2 == 0));
            // int mid = path[sz(path) / 2];
            // int nex = path[1];
            // int deep = 0;
            // for(int v : adj[a]){
            //     if(v != nex){
            //         deep = max(deep, maxd[v]);
            //     }
            // }
            // ans = min(ans, 2 * (n-1) - deep + (depth[b] % 2));
        }
        cout << ans << "\n";
    }
    
    return 0;
}
