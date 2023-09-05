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
    if(m % 2 == 1){
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    vi visited(n);
    vi deg(n);
    vpi edges;
    vvi adj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int t = 1;
    auto dfs = [&](int cur, int par, auto &&dfs)->void{
        visited[cur] = t++;
        for(int nex : adj[cur]){
            if(nex == par) continue;
            if(visited[nex] && visited[nex] < visited[cur]){
                edges.pb({cur, nex});
                deg[cur] ^= 1;
            }
            else if(!visited[nex]){
                dfs(nex, cur, dfs);
                if(deg[nex]){
                    edges.pb({nex, cur});
                    deg[nex] ^= 1;
                }
                else{
                    edges.pb({cur, nex});
                    deg[cur] ^= 1;
                }
            }
        }
    };
    bool works = true;
    rep(i, 0, n){
        if(!visited[i]) dfs(i, -1, dfs);
        if(deg[i]) works = false;
    }
    if(works){
        for(auto [a, b] : edges) cout << (a + 1) << " " << (b + 1) << nL;
    }
    else cout << "IMPOSSIBLE\n";
    // vector<
    
    return 0;
}
