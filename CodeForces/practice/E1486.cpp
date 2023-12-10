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
    const int mw = 51;
    int n2 = n * mw;
    vector<vpi> adj(n2);
    rep(i, 0, m){
        int a, b, w; cin >> a >> b >> w;
        a--, b--;
        adj[a * mw].pb({b * mw + w, 0});
        adj[b * mw].pb({a * mw + w, 0});
        rep(j, 1, mw){
            adj[b * mw + j].pb({a * mw, (w + j) * (w + j)});
            adj[a * mw + j].pb({b * mw, (w + j) * (w + j)});
        }
    }
    vi dist(n2, INT_MAX);
    dist[0] = 0;
    priority_queue<pi, vpi, greater<pi>> pq;
    pq.push({dist[0], 0});
    while(!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        for(auto [v, w] : adj[u]){
            if(d + w < dist[v]){
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    // cout << "got here" << endl;
    rep(i, 0, n){
        if(dist[i * mw] == INT_MAX) dist[i * mw] = -1;
        cout << dist[i * mw] << " ";
    }
    cout << nL;
    
    return 0;
}
