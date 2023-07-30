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
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi ans(n + 1);
    rep(i, 0, n){
        vi ds;
        auto dfs = [&](int cur, int p, int d, auto &&dfs)->void{
            ds.pb(d);
            for(int i : adj[cur]){
                if(i == p) continue;
                dfs(i, cur, d + 1, dfs);
            }
        };
        dfs(i, -1, 0, dfs);
        sort(all(ds));
        int a = 0;
        rep(j, 0, sz(ds)){
            a += 2 * ds[j];
            ans[j + 1] = max(ans[j + 1], (n - 1) * (j + 1) - a);
        }
    }
    rep(i, 0, n + 1) cout << ans[i] << " ";
    cout << nL;
    
    return 0;
}
