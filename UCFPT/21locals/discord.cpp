#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

// 76b5c9
vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
    int low = val[j] = ++Time, x; z.push_back(j);
    for(auto e : g[j]) if(comp[e] < 0)
        low = min(low, val[e] ?: dfs(e, g, f));
    if(low == val[j]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while(x != j);
        f(cont); cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
    int n = sz(g);
    val.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i, 0, n) if(comp[i] < 0) dfs(i, g, f);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    int k; cin >> k;
    vvi adj(n);
    rep(i, 0, k) {
        int c; cin >> c; c--;
        int v; cin >> v;
        rep(j, 0, v) {
            int a; cin >> a; a--;
            adj[c].push_back(a);
        }
    }
    scc(adj, [](vi s)->void {});
    int root = -1, cnt = 0;
    rep(i, 0, n) if(comp[i] == ncomps-1) root = i, cnt++;
    assert(root != -1);
    vi seen(n);
    auto dfs = [&](int u, auto &&dfs) -> void {
        if(seen[u]) return;
        seen[u] = true;
        for(int v : adj[u]) dfs(v, dfs);
    };
    dfs(root, dfs);
    if(accumulate(all(seen), 0) != n) {
        cout << 0 << "\n";
    } else cout << cnt << "\n";

    return 0;
}