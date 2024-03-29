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
        int n, s; cin >> n >> s;
        vi val(s);
        rep(i, 0, s){
            cin >> val[i];
        }
        vvi adj(s);
        rep(i, 0, n){
            int d; cin >> d; d--;
            int t; cin >> t;
            rep(j, 0, t){
                int x; cin >> x; x--;
                adj[x].pb(d);
            }
        }
        vi vis(s);
        auto dfs = [&](int u, auto &&dfs) -> void {
            if(vis[u]) return;
            vis[u] = true;
            for(int v : adj[u]){
                dfs(v, dfs);
            }
        };
        dfs(0, dfs);
        int ans = 0;
        rep(i, 0, s){
            if(vis[i]) ans = max(ans, val[i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
