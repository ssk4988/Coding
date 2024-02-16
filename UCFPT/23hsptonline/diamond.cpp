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
    vi d(n);
    rep(i, 0, n){
        string str; cin >> str;
        d[i] = str == "diamond";
    }
    vvi adj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b); adj[b].pb(a);
    }
    vi dist(n, 1e9);
    dist[0] = 0;
    queue<int> q;
    q.push(0);
    vi vis(n);
    vis[0] = true;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : adj[u]){
            if(!vis[v]){
                vis[v] = true;
                dist[v] = 1 + dist[u];
                q.push(v);
            }
        }
    }
    int ans = 1e9;
    rep(i, 0, n){
        if(d[i]) ans = min(ans, dist[i]);
    }
    cout <<  ans << "\n";
    
    return 0;
}