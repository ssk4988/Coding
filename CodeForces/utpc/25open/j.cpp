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
    int n, m; cin >> n >> m;
    vector<vii> adj(n), radj(n);
    rep(i, 0, m) {
        int a, b, c; cin >> a >> b >> c; a--, b--;
        adj[a].push_back({b, c});
        radj[b].push_back({a, c});
    }
    auto dijk = [&](vector<vii> &g) -> vi {
        priority_queue<pii, vii, greater<>> pq;
        vi dist(n, -1);
        pq.push({0, 0});
        while(sz(pq)) {
            auto [d_u, u] = pq.top(); pq.pop();
            if(dist[u] != -1) continue;
            dist[u] = d_u;
            for(auto [v, w] : g[u]) {
                pq.push({max(w, d_u), v});
            }
        }
        return dist;
    };
    bool works = true;
    vi to = dijk(adj), from = dijk(radj);
    rep(i, 0, n) {
        // cerr << i << " " << to[i] << " " << from[i] << endl;
        if(to[i] == -1) continue;
        if(from[i] == -1 || from[i] > to[i]) {
            works = false;
        }
    }
    cout << (works ? "YES" : "NO") << "\n";

    return 0;
}
