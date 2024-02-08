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

const ll inf = 1e18;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll a, b; cin >> a >> b;
    int n, m; cin >> n >> m;
    vector<vector<pair<int, ll>>> adj(n), radj(n);
    rep(i, 0, m){
        int u, v, t; cin >>u >> v >> t; u--, v--;
        adj[u].pb({v, t});
        radj[v].pb({u, t});
    }
    auto dijkstra = [](int source, vector<vector<pair<int, ll>>> &graph) -> vl {
        int n = sz(graph);
        vl dist(n, inf);
        dist[source] = 0;
        priority_queue<pl, vpl, greater<pl>> pq;
        pq.emplace(dist[source], source);
        while(!pq.empty()){
            auto [d, u] = pq.top(); pq.pop();
            if(d > dist[u]) continue;
            for(auto [v, w] : graph[u]){
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
        return dist;
    };
    vl from = dijkstra(0, adj), to = dijkstra(n - 1, radj);
    auto test = [&](ll delay) -> bool {
        // cout << "testing " << delay << endl;
        int nodes = n;
        auto graph = adj;
        vector<vector<pair<int, ll>>> dag(nodes);
        vector<bool> good(nodes); // can make it to n - 1
        good[n-1] = true;
        rep(v, 0, n){
            if(to[v] > delay) continue;
            good[v] = true;
            for(auto [u, w] : radj[v]){
                if(to[v] + w <= delay){
                    good[u] = true;
                    dag[u].pb({v, w});
                }
                else if(to[v] < delay){
                    graph.pb({});
                    dag.pb({});
                    dag[nodes].pb({v, delay - to[v]});
                    graph[nodes].pb({v, delay - to[v]});
                    graph[u].pb({nodes, w - (delay - to[v])});
                    good.pb(true);
                    nodes++;
                }
            }
        }
        vl from1 = dijkstra(0, graph);
        vi state(nodes);
        auto dfs = [&](int u, auto &&dfs) -> bool {
            if(state[u] == 2) return false;
            if(state[u] == 1) return true;
            state[u] = 1;
            for(auto [v, w] : dag[u]){
                if(dfs(v, dfs)) return true;
            }
            state[u] = 2;
            return false;
        };
        rep(i, 0, nodes){
            if(good[i] && from1[i] <= a && dfs(i, dfs)) {
                // infinite cycle we can reach before getting called
                return true;
            }
        }
        vl dp(nodes, -1);
        auto calc = [&](int u, auto &&calc) -> ll {
            if(dp[u] != -1) return dp[u];
            dp[u] = 0;
            for(auto [v, w] : dag[u]){
                // if(!good[v]) continue;
                dp[u] = max(dp[u], calc(v, calc) + w);
            }
            return dp[u];
        };
        ll longest = -inf;
        rep(i, 0, nodes){
            if(good[i] && from1[i] <= a) longest = max(longest, calc(i, calc));
        }
        return longest >= b - a;
    };
    ll ans = -1;
    for(ll dif = 1LL << 45; dif > 0; dif /= 2){
        if(!test(ans + dif)) ans += dif;
    }
    ans++;
    cout << ans << "\n";
    
    return 0;
}
