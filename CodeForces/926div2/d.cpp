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

const ll MOD = 998244353;
inline ll mod(ll k) {
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi adj(n);
        rep(i, 0, n-  1){
            int a, b; cin >> a >> b; a--, b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vector<vl> dp(n, vl(3));
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            vl prod(3, 1), sum(3, 0);
            ll prod01 = 1;
            int numc = 0;
            for(auto v : adj[u]){
                if(v == p) continue;
                dfs(v, u, dfs);
                rep(i, 0, 3){
                    prod[i] = mod(prod[i] * dp[v][i]);
                    sum[i] = mod(sum[i] + dp[v][i]);
                }
                prod01 = mod(prod01 * mod(dp[v][0] + dp[v][1]));
                numc++;
            }
            if(numc == 0) {
                dp[u] = {1, 1, 0};
                return;
            }

            dp[u][0] = 1;
            dp[u][1] = mod(1 + prod01 - 1);
            dp[u][2] = mod(sum[2] + sum[1]);
            // dp[u][1] = mod(prod[0] + prod[1]);
        };
        dfs(0, -1, dfs);
        cout << mod(dp[0][0] + dp[0][1] + dp[0][2]) << "\n";
    }
    
    return 0;
}