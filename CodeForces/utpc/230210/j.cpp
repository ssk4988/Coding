#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define pb push_back

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using pi = pair<int, int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi nex(n);
    vvi adj(n);
    rep(i, 0, n){
        cin >> nex[i];
        nex[i]--;
        adj[nex[i]].pb(i);
    }
    vi visited(n); // 0 not dfsd yet 1 in dfs currently, 2 out of dfs
    vi incycle(n);
    vvi cycles;
    vvi imposed(n);
    auto dfs = [&](int cur, auto &&dfs)->void{
        if(visited[cur] == 2) return;
        if(visited[cur] == 1){
            // have a cycle
            cycles.pb({});
            int c = cur;
            while(!incycle[c]){
                incycle[c] = true;
                cycles.back().pb(c);
                c = nex[c];
            }
            return;
        }
        if(visited[cur] == 0){
            visited[cur] = 1;
            dfs(nex[cur], dfs);
            visited[cur] = 2;
        }
    };
    rep(i, 0, n){
        if(visited[i] == 0){
            dfs(i, dfs);
        }
    }
    auto dfsrev = [&](vi &cycle, int d, int cur, int place, auto &&dfsrev)->void{
        imposed[cycle[((place - d) % sz(cycle) + sz(cycle)) % sz(cycle)]].pb(cur);
        for(int par : adj[cur]){
            if(incycle[par]) continue;
            dfsrev(cycle, d + 1, par, place, dfsrev);
        }
    };
    for(auto &v : cycles){
        // cout << "cycle: ";
        rep(i, 0, sz(v)){
            // cout << v[i] << " ";
            dfsrev(v, 0, v[i], i, dfsrev);
        }
        // cout << "\n";
    }
    ll ans = ll(n) * (n - 1) / 2;
    rep(i, 0, n){
        if(incycle[i]){
            ll v = sz(imposed[i]);
            // cout << "imposed on " << i << ": ";
            for(int j : imposed[i]){
                // cout << j << " ";
            }
            // cout << "\n";
            ans -= v * (v - 1) / 2;
        }
    }
    cout << ans % ll(1e9 + 7) << "\n";
    
}
