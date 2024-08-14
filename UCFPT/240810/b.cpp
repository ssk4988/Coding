#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vii = vector<pii>;
using vl = vector<ll>;
using vll = vector<pll>;

vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
    int low = val[j] = ++Time, x; z.push_back(j);
    for(auto e : g[j]) if (comp[e] < 0)
        low = min(low, val[e] ?: dfs(e, g, f));

    if (low == val[j]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != j);
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

pll operator+(pll a, pll b) {
    return {a.first + b.first, a.second + b.second};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vi> adj(n);
    vector<vii> prvadj(n), wadj(n);
    vector<vector<pair<int, pll>>> finaladj(2 * n);

    rep(i, 0, m){
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back(v);
        prvadj[u].push_back({v, w});
    }
    vvi comps;
    auto trash = [&](vi v) -> void {
        comps.push_back(v);
    };
    scc(adj, trash);
    // cout << "scc done" << endl;
    // rep(i, 0, n){
    //     cout << i << " " << comp[i] << endl;
    // }
    rep(u, 0, n){
        for(auto [v, w] : prvadj[u]) {
            if (comp[u] != comp[v]) continue;
            wadj[u].push_back({v, w});
            // cout << "keep edge " << u << " " << v << " " << w << endl;
        }
    }
    // cout << "wadj done" << endl;
    vl s(n);
    auto relax = [&](int u, int v, ll w) -> bool {
        if(s[u] + w < s[v]){
            s[v] = s[u] + w;
            return true;
        }
        return false;
    };
    rep(t, 0, 2 * n + 5) {
        rep(u, 0, n){
            for(auto [v, w] : wadj[u]) relax(u, v, w);
        }
    }
    // cout << "bellman-ford done" << endl;
    vl ans(n, -1); // -1 doesnt exist -2 infinite
    const ll oo = 1e18;
    vll d(2 * n, {oo, oo});
    vi vis(2 * n);
    for(auto &sc : comps) {
        for(int u : sc) {
            for(auto [v, w] : wadj[u]) {
                // assert(w + s[u] - s[v] >= 0);
                int odd = abs(w) % 2 == 1;
                rep(t, 0, 2){
                    finaladj[u * 2 + t].push_back({v * 2 + (t ^ odd), {w + s[u] - s[v], w}});
                    // cout << (u * 2 + t) << " " << (v * 2 + (t ^ odd)) << " " << (w + s[u] - s[v]) << " " << w << endl;
                }
                // finaladj[u].push_back({v, {w + s[u] - s[v], w}});
            }
        }
        auto dfs = [&](int u, auto &&dfs) -> void {
            if(vis[u]) return;
            vis[u] = true;
            for(auto [v, w] : finaladj[u]){
                dfs(v, dfs);
            }
        };
        dfs(sc[0] * 2, dfs);
        if(!vis[sc[0] * 2 + 1]){
            for(int i : sc){
                ans[i] = -1;
            }
            continue;
        }
        bool inf = false;
        for(int u : sc){
            for(auto [v, w] : wadj[u]){
                if(relax(u, v, w)) inf = true;
            }
        }
        if(inf){
            for(int i : sc) ans[i] = -2;
            continue;
        }
        // cout << "current comp" << endl;
        for(int st : sc){
            int source = st * 2, sink = st * 2 + 1;
            for(int i : sc){
                d[i * 2] = d[i * 2 + 1] = pll{oo, oo};
            }
            priority_queue<pair<pll, int>, vector<pair<pll, int>>, greater<pair<pll, int>>> pq;
            pq.push({{0, 0}, source});
            // cout << "doing " << st << endl;
            while(!pq.empty()){
                auto [d_u, u] = pq.top(); pq.pop();
                // cout << "visit " << u << endl;
                if(d[u].first != oo) continue;
                d[u] = d_u;
                for(auto [v, w] : finaladj[u]){
                    // cout << u << " to " << v << " " << w.first << "  " << w.second << endl;
                    pq.push({d_u + w, v});
                }
            }
            // cout << "did " << st << endl;
            if(d[sink].first == oo) {
                continue;
            }
            ans[st] = d[sink].second;
        }
    }
    rep(i, 0, n){
        if(ans[i] == -2){
            cout << "Haha, stupid Honkai\n";
        } else if(ans[i] == -1) {
            cout << "Battle with the crazy Honkai\n";
        }
        else cout << ans[i] << "\n";
    }


    return 0;
}
