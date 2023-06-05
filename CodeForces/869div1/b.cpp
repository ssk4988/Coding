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
        vvi adj(n);
        rep(i, 0, m){
            int a, b; cin >> a >> b; a--,b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        bool works = false;
        rep(i, 0, n){
            if(works) break;
            if(sz(adj[i]) < 4)continue;
            for(int j : adj[i]){
                vi visited(n), par(n, -1);
                for(int j1 : adj[i]) par[j1] = i;
                auto dfs = [&](int cur, auto &&dfs)->bool{
                    visited[cur]= true;
                    if(cur == i){
                        return true;
                    }
                    for(int j : adj[cur]){
                        if(j == par[cur] || visited[j]) continue;
                        par[j] = cur;
                        if(dfs(j, dfs)) return true;
                    }
                    return false;
                };
                if(dfs(j, dfs)){
                    vpi edges;
                    edges.pb({i, j});
                    int cur = i;
                    vi incycle(n);
                    incycle[j] = incycle[i] = incycle[par[cur]] = true;
                    while(par[cur] != i){
                        incycle[par[cur]] = incycle[cur] = true;
                        edges.pb({par[cur], cur});
                        cur = par[cur];
                    }int cnt= 0;
                    for(int j1 : adj[i]){
                        if(incycle[j1]) continue;
                        edges.pb({j1, i});
                        cnt++;
                        if(cnt >= 2) break;
                    }
                    if(cnt == 2){
                        works = true;
                        cout << "YES\n";
                        cout << sz(edges) << nL;
                        for(auto &p : edges){
                            cout << (p.f + 1) << " " << (p.s + 1) << nL;
                        }
                        break;
                    }
                }
            }
            
        }
        if(!works){
            cout << "NO\n";
        }
    }
    
    return 0;
}
