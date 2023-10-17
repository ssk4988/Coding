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
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi adj(n);
        vi subsz(n, 1);
        rep(i, 0, n - 1){
            int a, b; cin >> a >> b; a--, b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        ll edges = 0;
        auto dfs = [&](int cur, int par, auto &&dfs) -> void {
            // cout << "dfs on " << cur << nL;
            for(int nex : adj[cur]){
                if(nex == par) continue;
                dfs(nex, cur, dfs);
                subsz[cur] += subsz[nex];
                edges += ll(subsz[nex]) * (n - subsz[nex]);
            }
        };
        dfs(0, -1, dfs);
        cout << fixed << setprecision(8) << ld(edges) / n * 2 << nL;
    }
    
    return 0;
}