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
    vvi adj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;a--,b--;
        adj[a].pb(b);adj[b].pb(a);
    }
    
    vi dist(n, INT_MAX);
    vi visited(n);
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    
    dist[0] = 0;
    pq.push({0, 0});
    while(!pq.empty()){
        auto p = pq.top();pq.pop();
        if(visited[p.s]) continue;
        visited[p.s]= true;
        for(int i : adj[p.s]){
            if(!visited[i] && dist[i] > 1 + dist[p.s]){
                dist[i] = 1 + dist[p.s];
                pq.push({dist[i], i});
            }
        }
    }
    if(visited[n - 1]){
        // cout << dist[b.f][b.s] << nL;
        vi path;
        path.pb(n - 1);
        while(path.back() != 0){
            for(int i : adj[path.back()]){
                if(dist[i] == dist[path.back()] - 1){
                    path.pb(i);
                    break;
                }
            }
        }
        reverse(all(path));
        cout << sz(path) << nL;
        for(int i : path){
            cout << (i+1) << " " ;
        }
        cout << nL;
    }
    else{
        cout << "IMPOSSIBLE\n";
    }
    
    return 0;
}
