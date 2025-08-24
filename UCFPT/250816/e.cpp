#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m, max_d; cin >> n >> m >> max_d;
        vvi adj(n);
        rep(i, 0, m) {
            int u, v; cin >> u >> v; u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        const int inf = 1e9;
        vvi dist(n, vi(2, inf));
        {
            queue<array<int, 3>> q;
            int k; cin >> k;
            rep(i, 0, k) {
                int u; cin >> u; u--;
                q.push(array<int, 3>{0, u, 0});
            }
            while(sz(q)) {
                auto [d, u, p] = q.front(); q.pop();
                if(dist[u][p] != inf || d > max_d) continue;
                dist[u][p] = d;
                for(int v : adj[u]) {
                    q.push(array<int, 3>{d+1, v, p^1});
                }
            }
        }
        queue<array<int, 4>> q;
        vector<vii> trav(n, vii(2, pii{inf, -1}));
        q.push(array<int, 4>{0, 0, 0, 0});
        while(sz(q)) {
            auto [d, prv, u, p] = q.front(); q.pop();
            if(dist[u][p] <= d || trav[u][p].first != inf) continue;
            // cerr << u << " " << p << " " << d << " " << dist[u][p] << endl;
            trav[u][p] = pii{d, prv};
            for(int v : adj[u]) {
                q.push(array<int, 4>{d+1, u, v, p^1});
            }
        }
        int p = -1;
        rep(i, 0, 2) {
            if(trav[n-1][i].first == inf) continue;
            if(p == -1 || trav[n-1][p].first > trav[n-1][i].first)
            p = i;
        }
        // cerr << "p=" << p << endl;
        if(p == -1) {
            cout << "-1\n";
            continue;
        }
        int u = n-1;
        vi path;
        while(u != 0 || p != 0) {
            path.push_back(u);
            // cerr << "at u=" << u << " p=" << p << " " << trav[u][p].first << "," << trav[u][p].second << endl;
            u = trav[u][p].second;
            p ^= 1;
        }
        path.push_back(0);
        reverse(all(path));
        cout << sz(path)-1 << "\n";
        for(int u : path) cout << u+1 << " ";
        cout << "\n";
    }

    return 0;
}
