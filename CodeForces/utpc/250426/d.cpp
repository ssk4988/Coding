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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vii ints(n);
    rep(i, 0, n) {
        cin >> ints[i].f >> ints[i].s;
    }
    vector<vii> adj(n);
    rep(i, 0, m) {
        int u,v,w; cin >> u >> v >> w;
        u--, v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    vl dist(n, -1);
    priority_queue<pll, vll, greater<>> pq;
    pq.push({0, 0});
    while(sz(pq)) {
        auto [d_u, u] = pq.top(); pq.pop();
        if(dist[u] != -1) continue;
        dist[u] = d_u;
        // cout << "at " << u << " " << d_u << endl;
        for(auto [v, w] : adj[u]) {
            ll arrive = d_u + w;
            ll tot = (ints[v].f + ints[v].s);
            // cout << "before " << v << " " << arrive << endl;
            if((arrive % tot) < ints[v].f) {

            } else if(v != n-1) {
                arrive = (arrive / tot + 1) * tot;
            }
            // cout << "to " << v << " " << arrive << endl;

            pq.push(pll{arrive, v});
        }
    }
    cout << dist.back() << "\n";
    
    return 0;
}
