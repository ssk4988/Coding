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
        int n; ll w; cin >> n >> w;
        vvi child(n);
        vi par(n, -1);
        rep(i, 1, n){
            cin >> par[i]; par[i]--;
            child[par[i]].pb(i);
        }
        int prv = -1;
        vvi belong(n);
        vector<set<int>> path(n);
        auto dfs = [&](int u, auto &&dfs) -> void {
            if(prv != -1) {
                belong[u].pb(prv);
                path[prv].insert(u);
            }
            prv = u;
            for(int v : child[u]){
                dfs(v, dfs);
            }
            if(prv != -1 && u != 0) {
                belong[u].pb(prv);
                path[prv].insert(u);
            }
        };
        dfs(0, dfs);



        int unsatisfied = 0;
        rep(i, 0, n) unsatisfied += (sz(path[i]) > 0);
        ll ans = 0;
        rep(_, 0, n-1){
            int u; ll use; cin >> u >> use; u--;
            ans += use * sz(belong[u]);
            for(int b : belong[u]){
                path[b].erase(u);
                if(sz(path[b]) == 0) unsatisfied--;
            }
            w -= use;
            cout << (ans + (w * unsatisfied)) << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
