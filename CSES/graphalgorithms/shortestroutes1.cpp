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
    vector<vpi> adj(n);
    rep(i, 0, m){
        int a, b;ll c; cin >> a >> b >> c;a--,b--;
        adj[a].pb({b,c});
    }
    
    vl dist(n, LLONG_MAX);
    vi visited(n);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    
    dist[0] = 0;
    pq.push({0, 0});
    while(!pq.empty()){
        auto p = pq.top();pq.pop();
        if(visited[p.s]) continue;
        visited[p.s]= true;
        for(auto &p1 : adj[p.s]){
            if(!visited[p1.f] && dist[p1.f] > p1.s + dist[p.s]){
                dist[p1.f] = p1.s + dist[p.s];
                pq.push({dist[p1.f], p1.f});
            }
        }
    }
    rep(i, 0, n){
        cout << dist[i] << " ";
    }
    cout << nL;
    
    return 0;
}
