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

vi Blossom(vector<vi>& adj) {
    int n = adj.size(), T = -1;
    vi mate(n, -1), label(n), par(n), orig(n), aux(n, -1), q;
    auto lca = [&](int x, int y) {
      for (T++; ; swap(x, y)) {
        if (x == -1) continue;
        if (aux[x] == T) return x;
        aux[x] = T;
        x = (mate[x] == -1 ? -1 : orig[par[mate[x]]]); } };
    auto blossom = [&](int v, int w, int a) {
      while (orig[v] != a) {
        par[v] = w;
        w = mate[v];
        if (label[w] == 1) label[w] = 0, q.push_back(w);
        orig[v] = orig[w] = a, v = par[w]; } };
    auto augment = [&](int v) {
      while (v != -1) {
        int pv = par[v], nv = mate[pv];
        mate[v] = pv, mate[pv] = v, v = nv; } };
    auto bfs = [&](int root) {
      fill(all(label), -1), iota(all(orig), 0);
      q.clear(), q.push_back(root), label[root] = 0;
      for (int i = 0; i < sz(q); i++) {
        int v = q[i];
        for (auto x : adj[v]) if (label[x] == -1) {
          label[x] = 1, par[x] = v;
          if (mate[x] == -1) return augment(x);
          label[mate[x]] = 0, q.push_back(mate[x]); }
        else if (label[x] == 0 && orig[v] != orig[x]) {
          int a = lca(orig[v], orig[x]);
          blossom(x, v, a), blossom(v, x, a); } } };
    // Time halves if you start with (any) maximal matching.
    for (int i = 0; i < n; i++) if (mate[i] == -1) bfs(i);
    return mate; }


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi w;
        vvi grid(2*n, vi(2*n));
        rep(i, 0, 2*n) {
            rep(j, 0, 2*n) {
                cin >> grid[i][j];
                w.pb(grid[i][j]);
            }
        }
        sort(all(w));
        w.erase(unique(all(w)), end(w));
        rep(i, 0, 2*n) {
            rep(j, 0, 2*n) {
                grid[i][j] = lower_bound(all(w), grid[i][j])-begin(w);
            }
        }
        int ans = INT_MAX;
        rep(l, 1, sz(w)) {
            rep(u, l, sz(w)) {
                vvi adj(2*n);
                rep(i, 0, 2*n) {
                    rep(j, 0, 2*n) {
                        if(i == j) continue;
                        if(l <= grid[i][j] && grid[i][j] <= u) {
                            adj[i].pb(j);
                        }
                    }
                }
                vi m = Blossom(adj);
                int c = 0;
                rep(i, 0, 2*n) if(m[i] == -1) c++;
                if(!c) {
                    ans = min(ans, w[u]-w[l]);
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
