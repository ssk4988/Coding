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

int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr-tl);
    return min(tl+pw2, tr-pw2/2);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q; cin >> n >> q;
    int s; cin >> s; s--;
    int m = 0;
    vii rl(2*n);
    vector<vll> adj;
    vi leafidx(n);
    auto build = [&](int tl, int tr, int ti, auto &&build) -> pii {
        rl[ti] = {m, m+1};
        m += 2;
        adj.resize(m);
        auto [down, up] = rl[ti];
        if(tr-tl==1) {
            adj[down].push_back({up, 0});
            adj[up].push_back({down, 0});
            leafidx[tl] = ti;
            return rl[ti];
        }
        int tm = split(tl, tr);
        auto [downl, upl] = build(tl, tm, 2*ti, build);
        auto [downr, upr] = build(tm, tr, 2*ti+1, build);
        adj[down].push_back({downl, 0});
        adj[down].push_back({downr, 0});
        adj[upl].push_back({up, 0});
        adj[upr].push_back({up, 0});
        return rl[ti];
    };
    build(0, n, 1, build);
    auto dfs = [&](int l, int r, int tl, int tr, int ti, function<void(int, int)> fun, auto &&dfs) -> void {
        if(tr <= l || r <= tl) return;
        if(l <= tl && tr <= r) {
            auto [down, up] = rl[ti];
            fun(down, up);
            return;
        }
        int tm = split(tl, tr);
        dfs(l, r, tl, tm, 2*ti, fun, dfs);
        dfs(l, r, tm, tr, 2*ti+1, fun, dfs);
    };
    rep(i, 0, q) {
        int t; cin >> t;
        if(t == 1) {
            int u, v, w; cin >> u >> v >> w; u--, v--;
            auto [downu, upu] = rl[leafidx[u]];
            auto [downv, upv] = rl[leafidx[v]];
            adj[downu].push_back({downv, w});
        } else{
            int u, l, r, w; cin >> u >> l >> r >> w; u--, l--;
            auto [downu, upu] = rl[leafidx[u]];
            auto fun = [&](int down, int up) -> void {
                if(t == 2) {
                    adj[downu].push_back({down, w});
                } else adj[up].push_back({downu, w});
            };
            dfs(l, r, 0, n, 1, fun, dfs);
        }
    }
    auto [downs, ups] = rl[leafidx[s]];
    priority_queue<pll, vll, greater<>> pq;
    pq.push({0, downs});
    vl dist(m, -1);
    while(sz(pq)) {
        auto [d_u, u] = pq.top(); pq.pop();
        if(dist[u] != -1) continue;
        dist[u] = d_u;
        for(auto [v, w] : adj[u]) {
            pq.push({w+d_u, v});
        }
    }
    rep(i, 0, n) {
        auto [down, up] = rl[leafidx[i]];
        cout << dist[down] << " ";
    }
    cout << "\n";
    
    return 0;
}
