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
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m, q; cin >> n >> m >> q;
        vi ws;
        vector<vii> adj(n);
        rep(i, 0, m){
            int u, v, w; cin >> u >> v >> w;
            u--, v--;
            adj[u].pb({v, w});
            adj[v].pb({u, w});
            ws.pb(w);
        }
        sort(all(ws));
        ws.erase(unique(all(ws)), end(ws));
        const int inf = 1e9;
        vector<vvi> info(n, vvi(n, vi(sz(ws), inf)));
        vector<vii> ed(sz(ws));
        rep(i,0, n){
            for(auto &[v, w] : adj[i]){
                int id = lower_bound(all(ws), w) - begin(ws);
                w = id;
                // if(i < v){
                    ed[w].pb({i, v});
                // }
            }
        }
        rep(i, 0, n){
            rep(wid, 0, sz(ws)) {
                deque<pii> q;
                q.push_back({0, i});
                while(sz(q)) {
                    auto [d, u] = q.front(); q.pop_front();
                    if(info[i][u][wid] != inf) continue;
                    info[i][u][wid] = d;
                    for(auto [v, w] : adj[u]){
                        if(w >= wid) {
                            q.push_back({d+1, v});
                        } else q.push_front({d, v});
                    }
                }
            }
        }
        rep(i, 0, q){
            int a, b, k; cin >> a >> b >> k;
            a--, b--;
            int res = lower_bound(rbegin(info[a][b]), rend(info[a][b]), k) - rbegin(info[a][b]);
            assert(res != sz(info[a][b]));
            res--;
            res = sz(info[a][b]) - 1 - res;
            res = ws[res-1];
            cout << res << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
