#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vl t(n), h(n);
        rep(i, 0, n) {
            cin >> t[i];
        }
        rep(i, 0, n) {
            cin >> h[i];
        }
        map<pair<int, ll>, int> occ;
        int g = n;
        vvi adj(n);
        rep(i, 0, n) {
            rep(j, 0, 2) {
                rep(k, 0, 2) {
                    ll v = (j ? -h[i] : h[i]) + (k ? -t[i] : t[i]);
                    pair<int, ll> key{j*2+k, v};
                    if(!occ.count(key)) {
                        occ[key] = g++;
                        adj.push_back({});
                    }
                    adj[i].push_back(occ[key]);
                    adj[occ[key]].push_back(i);
                }
            }
        }
        vi dist(g, -2);
        queue<pii> q;
        q.push({0, 0});
        while(sz(q)) {
            auto [d, u] = q.front(); q.pop();
            if(dist[u] != -2) continue;
            dist[u] = d;
            for(int v : adj[u]) q.push({d+1, v});
        }
        cout << "Field #" << (cn+1) << ": " << dist[n-1]/2 << "\n\n";
    }

    return 0;
}
