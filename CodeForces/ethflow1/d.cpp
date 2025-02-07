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
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vvi adj(n);
        vl l(n), r(n);
        rep(i, 0, n) cin >> l[i] >> r[i];
        rep(i, 0, n-1){
            int u, v; cin >> u >> v; u--, v--;
            adj[u].push_back(v);adj[v].pb(u);
        }
        auto dfs = [&](int u, int p, auto &&dfs) -> pll {
            ll up = 0;
            vll c;
            vl ups;
            for(int v : adj[u]) {
                if(v == p) continue;
                auto [you, upc] = dfs(v, u, dfs);
                up += upc;
                c.push_back({you, upc});
            }
            if(sz(c) == 0) return {l[u], 0};
            ll lim = r[u] + up;
            ll me = l[u] + up;
            rep(i, 0, sz(c)){
                c[i].first += up - c[i].second;
                me = min(lim, max(me, c[i].first));
            }
            ll orig = me;
            for(auto [cv, upc] : c) {
                if(cv >= orig){
                    me += cv - orig;
                    up += cv - orig;
                }
            }
            return {me, up};
        };
        auto [me, up] = dfs(0, -1, dfs);
        cout << me << "\n";
    }
    
    return 0;
}
