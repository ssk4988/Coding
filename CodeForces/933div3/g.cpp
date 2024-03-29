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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vector<map<int, vi>> adj(n);
        rep(i, 0, m){
            int a, b, c; cin >> a >> b >> c; a--, b--;
            adj[a][c].pb(b);
            adj[b][c].pb(a);
        }
        int source, dest; cin >> source >> dest; source--, dest--;
        if(source == dest){
            cout << 0 << "\n";
            continue;
        }
        map<pi, int> dist;
        dist[{source, 0}] = 1;
        // for()
        deque<pi> q;
        q.push_back({source, 0});
        set<pi> vis;
        auto relax = [&](pi state, int prevD, int w) -> void {
            int newD = prevD + w;
            if(!dist.count(state)){
                dist[state] = 1e9;
            }
            int curD = dist[state];
            if(newD < curD){
                dist[state] = newD;
                if(w == 0) q.push_front(state);
                else q.push_back(state);
            }
        };
        int ans = -1;
        while(!q.empty()){
            auto [u, c] = q.front(); q.pop_front();
            if(vis.count({u, c})) continue;
            vis.insert({u, c});
            int d = dist[{u, c}];
            if(u == dest){
                ans = d;
                break;
            }
            if(c == 0){
                for(auto &[key, val] : adj[u]){
                    relax({u, key}, d, 0);
                }
            }
            else{
                for(auto v : adj[u][c]){
                    relax({v, c}, d, 0);
                }
                relax({u, 0}, d, 1);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
