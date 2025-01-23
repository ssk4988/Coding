#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

void solve() {
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    const int inf = 1e9;
    vi dist(n, inf);
    queue<pii> q;
    rep(i, 0, n){
        if(sz(adj[i]) == 1) q.push({0, i});
    }
    while(sz(q)){
        auto [d_u, u] = q.front(); q.pop();
        if(dist[u] != inf) continue;
        dist[u] = d_u;
        for(int v : adj[u]) {
            q.push({dist[u]+1, v});
        }
    }
    ll num2 = 0, num1 = 0, num0 = 0;
    rep(i, 0, n){
        if(dist[i] == 0) num0++;
        else if(dist[i] == 1) num1++;
        else num2++;
    } 
    ll ans = num0 * (num1 + num2);
    vi subsz2(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        subsz2[u] += dist[u] >= 2;
        for(int v : adj[u]) {
            if(v != p) {
                dfs(v, u, dfs);
                subsz2[u] += subsz2[v];
            }
        }
        for(int v : adj[u]) {
            if(v == p) continue;
            if(dist[u] != 0 && dist[v] == 1) {
                ans += subsz2[v];
            }
            if(dist[u] == 1 && dist[v] != 0) {
                ans += num2 - subsz2[v];
            }
        }
    };
    dfs(0, -1, dfs);
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc)
    solve();
    
    return 0;
}
