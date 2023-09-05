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
        int n; cin >> n;
        vector<vpi> adj(n);
        rep(i, 0, n- 1){
            int a, b; cin >> a >> b;
            a--, b--;
            adj[a].pb({b, i});
            adj[b].pb({a, i});
        }
        bool works = true;
        rep(i, 0, n){
            if(sz(adj[i]) > 2){
                works = false;
            }
        }
        if(!works){
            cout << "-1\n";
            continue;
        }
        vi ans(n - 1);
        auto dfs = [&](int cur, int par, int v, auto &&dfs)->void{
            for(auto [nex, id] : adj[cur]){
                if(nex == par) continue;
                int v1 = v == 2 ? 3 : 2;
                ans[id] = v1;
                dfs(nex, cur, v1, dfs);
                v = v1;
            }
        };
        rep(i, 0, n){
            if(sz(adj[i]) == 1){
                dfs(i, -1, -1, dfs);
                break;
            }
        }
        rep(i, 0, n - 1) cout << ans[i] << " ";
        cout << nL;
    }
    
    return 0;
}
