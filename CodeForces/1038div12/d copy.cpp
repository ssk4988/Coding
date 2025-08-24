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
        const int W = n * n + 10;
        const ll inf = 1e18;
        vector dist(n, vector(n, pll{inf, 0}));
        vvi did(n, vi(n));
        using state = array<ll, 4>;
        vector<vector<state>> q(W);
        q[0].pb(state{0, 0, 0, 0});
        rep(t, 0, W-3) {
            rep(i, 0, sz(q[t])) {
                auto [d, wait, u, um] = q[t][i];
                dist[u][um] = min(dist[u][um], pll{d, wait});
            }
            rep(i, 0, sz(q[t])) {
                auto [d, wait, u, um] = q[t][i];
                if(did[u][um] || dist[u][um] != pll{d, wait}) continue;
                did[u][um] = 1;
                q[t+1].pb({d+1, wait+1, u, (d+1)%sz(adj[u])});
                int v = adj[u][um];
                q[t+1].pb({d+1, wait, v, (d+1)%sz(adj[v])});
            }
        }
        pll ans{inf, -1};
        rep(i, 0, n) {
            ans = min(ans, dist[n-1][i]);
        }
        cout << ans.f << " " << ans.s << "\n";
    }
    
    return 0;
}
