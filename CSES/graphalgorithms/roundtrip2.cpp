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
    vvi adj(n), radj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].pb(b);
        radj[b].pb(a);
    }
    vi path, visited(n), pd(n);
    bool undo = true;
    auto dfs = [&](int cur, auto &&dfs)->bool{
        path.pb(cur);
        if(visited[cur]){
            return true;
        }
        visited[cur] = true;
        for(int i : adj[cur]){
            if(!pd[i] && dfs(i, dfs)) return true;
        }

        if(undo) visited[cur] = false;
        if(!undo) pd[cur] = true;
        path.pop_back();
        return false;
    };
    bool found0 = false;
    rep(i, 0, n){
        if(sz(radj[i]) == 0){
            found0 = true;
            if(dfs(i, dfs)){
                break;
            }
        }
    }
    if(sz(path) == 0){
        // vvi adj2(adj);
        // rep(i, 0, n){
        //     adj[i].clear();
        // }
        // rep(i, 0, n){
        //     for(int j : adj2[i]){
        //         adj[j].pb(i);
        //     }
        // }
        undo = false;
        rep(i, 0, n){
            if(!pd[i]){
                if(dfs(i, dfs)){
                    break;
                }
            }
        }
    }
    if(sz(path) == 0){
        cout << "IMPOSSIBLE\n";
    }
    else{
        int start = 0;
        while(path[start] != path.back()){
            start++;
        }
        cout << (sz(path) - start) << nL;
        rep(i, start, sz(path)){
            cout << (1 + path[i]) << " " ;
        }
        cout << nL;
    }
    
    return 0;
}