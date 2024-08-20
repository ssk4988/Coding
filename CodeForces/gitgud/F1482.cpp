#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vector<pair<int, ll>>> adj(n);
    vector<vl> dist(n, vl(n, 1e18));
    vector<tuple<int, int, ll>> edges;
    rep(i, 0, m){
        int a, b; ll w; cin >> a >> b >> w;
        a--, b--;
        adj[a].pb({b, w});
        adj[b].pb({a, w});
        edges.emplace_back(a, b, w);
        dist[a][b] = w;
        dist[b][a] = w;
    }
    rep(i, 0, n){
        dist[i][i] = 0;
    }
    rep(k, 0, n){
        rep(i, 0, n){
            rep(j, 0, n){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    int q; cin >> q;
    vector<tuple<int, int, ll>> triples;
    vector<vector<pair<int, ll>>> buckets(n);
    rep(i, 0, q){
        int u, v; ll l; cin >> u >> v >> l; u--, v--;
        buckets[u].pb({v, l});
        buckets[v].pb({u, l});
        triples.emplace_back(u, v, l);
    }
    vi good(m);
    rep(v, 0, n){
        vl best(n, 1e18);
        vi pd(n);

        // priority_queue<pl, vpl, greater<pl>> pq;
        for(auto [u, l] : buckets[v]){
            best[u] = -l;
            // pq.push({best[u], u});
        }
        rep(_, 0, n){
            int u = -1;
            rep(i,0, n){
                if(pd[i]) continue;
                if(u == -1 || best[i] < best[u]) u = i;
            }
            pd[u] = true;
            auto d = best[u];
            for(auto [b, w] : adj[u]){
                if(best[b] > w + d){
                    best[b] = w + d;
                }
            }
        }
        // while(!pq.empty()){
        // }
        rep(i, 0, m){
            auto [a, b, w] = edges[i];
            if(best[a] <= -w - dist[v][b]){
                good[i] = true;
            }
            if(best[b] <= -w - dist[v][a]){
                good[i] = true;
            }
        }
    }
    int ans = accumulate(all(good), 0);
    cout << ans << "\n";

    
    return 0;
}