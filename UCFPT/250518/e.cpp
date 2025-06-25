#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vii> adj(n);
    rep(i, 0, m) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back({v, 2*i});
        adj[v].push_back({u, 2*i+1});
    }
    vi bfspar(n, -1), bfsdist(n, -1);
    queue<array<int, 3>> q;
    q.push({0, n-1, -1});
    vvi badj(n);
    while(sz(q)) {
        auto [d, u, p] = q.front(); q.pop();
        if(bfsdist[u] != -1) continue;
        bfsdist[u] = d;
        bfspar[u] = p;
        if(p != -1) badj[p].push_back(u);
        for(auto [v, eid] : adj[u]) q.push({d+1, v, u});
    }
    // cerr << "bfs: " << endl;
    // rep(i, 0, n) {
    //     cerr << i << " " << bfsdist[i] << " " << bfspar[i] << endl;
    // }
    vector<set<int>> eset(n);
    vi lz(n);
    vector<multiset<int>> others(n);
    vi ev(2*m);
    const int inf = 1e9;
    vi notpar(n, inf);
    auto dfs = [&](int u, auto &&dfs) -> void {
        for(auto [v, eid] : adj[u]) {
            if(v == bfspar[u]) continue;
            if(bfspar[v] == u) continue;
            ev[eid] = bfsdist[v]+1;
            eset[u].insert(eid);
            others[u].insert(ev[eid]);
            // cerr << "adding to " << u << " e from " << v << " " << ev[eid] << endl;
        }
        for(int v : badj[u]) {
            dfs(v, dfs);
            lz[v]++;
            if(sz(others[v]) > sz(others[u])) {
                swap(others[v], others[u]);
                swap(eset[u], eset[v]);
                swap(lz[u], lz[v]);
                // cerr << "swapped " << u << " " << v << endl;
            }
        }
        for(int v : badj[u]) {
            vi rem;
            for(int eid : eset[v]) {
                if(eset[u].count(eid^1)) {
                    eset[u].erase(eid^1);
                    rem.push_back(eid);
                    others[u].erase(others[u].find(ev[eid^1]));
                    others[v].erase(others[v].find(ev[eid]));
                }
            }
            for(int eid : rem) eset[v].erase(eid);
            for(int eid : eset[v]) {
                eset[u].insert(eid);
                int newev = ev[eid] + lz[v] - lz[u];
                others[u].insert(newev);
                ev[eid] = newev;
            }
            eset[v] = set<int>();
            others[v] = multiset<int>();
        }
        if(sz(others[u])) notpar[u] = *begin(others[u]) + lz[u];
    };
    dfs(n-1, dfs);
    notpar[n-1] = 0;
    // cerr << "notpar: ";
    // rep(i, 0, n) {
    //     cerr << notpar[i] << " ";
    // }
    // cerr << endl;
    priority_queue<pii, vii, greater<>> pq;
    pq.push({notpar[n-1], n-1});
    // rep(i, 0, n) pq.push({notpar[i], i});
    vi best(n, -1);
    while(sz(pq)) {
        auto [d, u] = pq.top(); pq.pop();
        if(best[u] != -1) continue;
        best[u] = d;
        // d = best[u];
        for(auto [v, eid] : adj[u]) {
            pq.push({max(notpar[v], d+1), v});
        }
    }
    // cerr << "Best: ";
    // rep(i, 0, n) {
    //     cerr << best[i] << " ";
    // }
    // cerr << endl;
    if(best[0] >= inf) {
        best[0] = -1;
    }
    cout << best[0] << "\n";
    
    return 0;
}
