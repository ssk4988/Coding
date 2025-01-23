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

pii operator+(pii a, pii b) {
    return {a.f + b.f, a.s + b.s};
}
pii operator*(pii a, int b){
    return {a.f * b, a.s * b};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vvi adj(n);
        rep(i, 0 ,n-1) {
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vi res(n);
        auto dfs = [&](int u, int p, int t, auto &&dfs) -> void {
           
            for(int v : adj[u]) res[u] += (t ? 1 : -1);
            // assert(res[u] != 0);
            for(int v : adj[u]) if(v != p) {
                dfs(v, u, t^1, dfs);
            }
        };
        dfs(0, -1, 0, dfs);
        rep(i, 0, n) cout << res[i] << " ";
        cout << "\n";
    }
    
    return 0;
}
