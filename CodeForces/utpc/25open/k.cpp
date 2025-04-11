#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vi a(n), b(n);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, n) cin >> b[i];
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    using a2 = array<int, 2>;
    auto dfs = [&](int u, int p, int t, auto &&dfs) -> a2 {
        a2 res{a[u], b[u]};
        a2 bestc{0, 0};
        for(int v : adj[u]) if(v != p) {
            a2 child = dfs(v, u, t^1, dfs);
            if(t) swap(child[0], child[1]);
            bestc = max(bestc, child);
        }
        if(t) swap(bestc[0], bestc[1]);
        rep(i, 0, 2) res[i] += bestc[i];
        return res;
    };
    auto [x, y] = dfs(0, -1, 0, dfs);
    cout << x << " " << y << "\n";

    return 0;
}
