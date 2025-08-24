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
        int n, m; cin >> n >> m;
        vvi adj(n);
        rep(i, 0, m) {
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        const ll inf = 1e18;
        vll dist(n, pll{inf, 0});
        dist[0] = pll{0, 0};
        vi proc(n);
        rep(_, 0, n) {
            array<ll, 3> best = array<ll, 3>{inf, 0, -1};
            rep(i, 0, n) if(!proc[i]) best = min(best, array<ll, 3>{dist[i].f, dist[i].s, i});
            auto [t, wait, u] = best;
            proc[u] = 1;
            ll d = t+1;
            ll nwait = wait;
            for(int i = t % sz(adj[u]), it = 0; it < sz(adj[u]); it++, d++, nwait++, i = (i+1)%sz(adj[u])) {
                int v = adj[u][i];
                dist[v] = min(dist[v], pll{d, nwait});
            }
        }
        cout << dist[n-1].f << " " << dist[n-1].s << "\n";
    }
    
    return 0;
}
