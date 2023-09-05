#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using pi = pair<int, int>;
vi val, comp, z, cont;
int Time, ncomps;
vvi sccs;
void addscc(vi v){
    sccs.push_back({});
    for(int i : v) sccs.back().push_back(i);
}
vi dp;
vi belong;
template<class G, class F> int dfs(int j, G& g, F& f) {
    int low = val[j] = ++Time, x; z.push_back(j);
    for(auto e : g[j]) if(comp[e] < 0)
        low = min(low, val[e] ?: dfs(e, g, f));
    if (low == val[j]) {
        do{
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while(x != j);
        f(cont); cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
template<class G, class F> void scc(G& g, F f){
    int n = sz(g);
    val.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i, 0 ,n) if(comp[i] < 0) dfs(i, g, f);
}
void solve(int cur, vvi &g){
    if(dp[cur] != -1) return;
    dp[cur] = 0;
    for(int i : sccs[cur]){
        for(int j : g[i]){
            solve(belong[j], g);
            dp[cur] = max(dp[cur], dp[belong[j]]);
        }
    }
    dp[cur] += sz(sccs[cur]);
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi adj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        a--,b--;
        adj[a].push_back(b);
    }
    scc(adj, addscc);
    dp.assign(ncomps, -1);
    belong.resize(n);
    rep(j, 0, ncomps){
        for(int i : sccs[j]) belong[i] = j;
    }
    int ans = 0;
    rep(j, 0, ncomps){
        solve(j, adj);
        ans = max(ans, dp[j]);
    }
    cout << ans << "\n";
    
}
