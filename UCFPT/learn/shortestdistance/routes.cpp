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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m, p; cin >> n >> m >> p;
        vector<vii> adj(n);
        rep(i, 0, m){
            int u, v, w; cin >> u >> v >> w; u--, v--;
            adj[u].pb({v, w});
            adj[v].pb({u, w});
        }
        const int oo = 1e9;
        vi dist(n, oo);
        priority_queue<pii, vii, greater<pii>> pq;
        pq.push({0, 0});
        while(!pq.empty()){
            auto [d_u, u] = pq.top(); pq.pop();
            if(dist[u] != oo) continue;
            dist[u] = d_u;
            for(auto [v, w] : adj[u]){
                pq.push({d_u + w, v});
            }
        }
        rep(i, 0, p){
            int u; cin >> u; u--;
            cout << dist[u] << "\n";
        }
    }
    
    return 0;
}
