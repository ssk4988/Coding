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
    vector<vpl> adj(n * 2);
    rep(i, 0, m){
        int a, b; ll w; cin >> a >> b >> w;
        a--,b--;
        adj[a*2].pb({b*2, w});
        // adj[b*2].pb({a*2, w});
        adj[a*2+1].pb({b*2+1, w});
        // adj[b*2+1].pb({a*2+1, w});
        adj[a*2].pb({b*2+1, w / 2});
        // adj[b * 2].pb({a*2+1, w/2});
        // adj[a*2].pb({a*2+1, 0});
        // adj[b * 2].pb({b * 2 + 1, 0});
    }
    vl dist(2 * n, LLONG_MAX);
    dist[0] = 0;
    vi visited(2 * n);
    priority_queue<pl, vpl, greater<pl>> pq;
    pq.push({0, 0});
    while(!pq.empty()){
        pl p = pq.top();pq.pop();
        if(visited[p.s])continue;
        visited[p.s] = true;
        for(pl &p1 : adj[p.s]){
            if(dist[p1.f] > dist[p.s] + p1.s){
                dist[p1.f] = dist[p.s] + p1.s;
                pq.push({dist[p1.f], p1.f});
            }
        }
    }
    cout << min(dist[2 * (n - 1)], dist[2 * (n - 1) + 1]) << nL;
    
    return 0;
}