#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;
using pll = pair<ll, ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

vi tin, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int cur, G& g, F& f) {
    int low = tin[cur] = ++Time, x; z.push_back(cur);
    for(auto nxt : g[cur]) if (comp[nxt] < 0)
        low = min(low, tin[nxt] ?: dfs(nxt, g, f));
    if (low == tin[cur]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != cur);
        f(cont);
        cont.clear();
        ncomps++;
    }
    return tin[cur] = low;
}
template<class G, class F> void scc(G& g, F f) {
    int n = sz(g);
    tin.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i, 0, n) if(comp[i] < 0) dfs(i, g, f);
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, q; cin >> n >> m >> q;
    vector<vector<pll>> wadj(n);
    vvi adj(n);
    rep(i, 0, m) {
        int a, b; cin >> a >> b;
        a %= n;
        (a += n) %= n;
        int b1 = (a + b) % n;
        (b1 += n) %= n;
        adj[a].push_back(b1);
        wadj[a].push_back(pll{b1, b});
    }
    vector<vl> dists(n);
    vi hascyc(n);
    scc(adj, [&](vi s) -> void {
        queue<pll> q;
        dists[s[0]].push_back(0);
        q.push(pll{0, s[0]});
        bool cyc = false;
        while(sz(q)) {
            auto [d, u] = q.front(); q.pop();
            for(auto [v, w] : wadj[u]) {
                if(comp[v] != comp[u]) continue;
                if(sz(dists[v]) == 0) {
                    dists[v].push_back(d + w);
                    q.push(pll{d+w, v});
                } else if(sz(dists[v]) == 1 && dists[v][0] != d + w) {
                    cyc = true;
                    break;
                }
            }
        }
        for(int u : s) {
            // cerr << "vis " << comp[u] << " " << u << endl;
            for(int v : adj[u]) {
                if(hascyc[comp[v]]) cyc = true;
            }
        }
        hascyc[comp[s[0]]] = cyc;
        // cerr << "hascyc: " << cyc << endl;
    });
    rep(i, 0, q) {
        int x; cin >> x;
        x %= n;
        (x += n) %= n;
        cout << (hascyc[comp[x]] ? "Yes" : "No") << "\n";
    }



    return 0;
}
