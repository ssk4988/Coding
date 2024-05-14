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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vector<vll> adj(n);
        rep(i, 0, m){
            int u, v, w; cin >> u >> v >> w;
            adj[u].pb({v, w});
        }
        vl best(n, -1), worst(n, -1);
        best[n-1] = worst[n-1] = 0;
        auto go = [&](int u, auto &&go) -> void {
            if(best[u] != -1) return;
            best[u] = LLONG_MAX, worst[u] = LLONG_MIN;
            for(auto [v, w] : adj[u]){
                go(v, go);
                if(best[v] == LLONG_MAX) continue;
                best[u] = min(best[u], w + best[v]);
                worst[u] = max(worst[u], w + worst[v]);
            }
        };
        go(0, go);
        cout << best[0] << " " << worst[0] << "\n";
    }    
    
    return 0;
}
