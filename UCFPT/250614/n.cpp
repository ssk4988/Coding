#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    while(true) {
        int n; cin >> n;
        if(n == 0) break;
        int h; cin >> h;
        vi hotel(h), ishotel(n, -1);
        rep(i, 0, h) {
            cin >> hotel[i]; hotel[i]--;
            ishotel[hotel[i]] = i;
        }
        if(ishotel[0] == -1) {
            ishotel[0] = h;
            hotel.push_back(0);
            h++;
        }
        if(ishotel[n-1] == -1) {
            ishotel[n-1] = h;
            hotel.push_back(n-1);
            h++;
        }
        const int MIN = 600;
        vector<vii> adj(n);
        int m; cin >> m;
        rep(i, 0, m) {
            int u, v, t; cin >> u >> v >> t; u--, v--;
            adj[u].push_back({v, t});
            adj[v].push_back({u, t});
        }
        vvi ed(h);
        for(int source : hotel) {
            vvi q(MIN*2+10);
            vi dist(n, -1);
            q[0].push_back(source);
            rep(t, 0, MIN+1) {
                for(int u : q[t]) {
                    if(dist[u] != -1) continue;
                    dist[u] = t;
                    for(auto [v, w] : adj[u]) {
                        if(dist[v] == -1) q[t+w].push_back(v);
                    }
                }
            }
            for(int other : hotel) {
                if(dist[other] != -1 && dist[other] <= MIN) ed[ishotel[source]].push_back(ishotel[other]);
            }
        }
        vi dist(h, -1);
        queue<pii> q;
        q.push({0, ishotel[0]});
        while(sz(q)) {
            auto [d_u, u] = q.front(); q.pop();
            if(dist[u] != -1) continue;
            dist[u] = d_u;
            for(int v : ed[u]) {
                q.push({d_u+1, v});
            }
        }
        int ans = dist[ishotel[n-1]];
        if(ans == -1) cout << ans << "\n";
        else cout << ans-1 << "\n";
    }




    

    return 0;
}
