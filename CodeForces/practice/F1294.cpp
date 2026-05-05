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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> parent(n, -1);
    auto dfs = [&](int u, int p, auto &&dfs) -> pair<int, int> {
        parent[u] = p;
        pair<int, int> res{-1, u};
        for(int v : adj[u]) if(v != p)
            res = max(res, dfs(v, u, dfs));
        res.first++;
        return res;
    };
    auto [dist1, a] = dfs(0, -1, dfs);
    auto [dist2, b] = dfs(a, -1, dfs);
    vector<int> diameter;
    for(int x = b; x != -1; x = parent[x])
        diameter.push_back(x);
    vi ondiam(n);
    for(auto u : diameter) ondiam[u] = 1;
    auto dfs2 = [&](int u, int p, auto &&dfs2) -> pii {
        pii best{-1, u};
        for(int v : adj[u]) if(v != p && !ondiam[v]) {
            best = max(best, dfs2(v, u, dfs2));
        }
        best.first++;
        return best;
    };
    pii best{-1, -1};
    for(auto u : diameter) {
        auto res = dfs2(u, -1, dfs2);
        if(res.second != diameter[0] && res.second != diameter.back()) best = max(best, res);
    }
    cout << (sz(diameter) - 1 + best.first) << "\n";
    cout << (diameter[0]+1) << " " << diameter.back()+1 << " " << best.second+1 << "\n";
    
    return 0;
}
