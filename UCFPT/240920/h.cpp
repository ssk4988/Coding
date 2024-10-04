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
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

const int MOD = 998244353;
int lb;

vi conv(vi &a, vi &b) {
    vi res(min(lb * 2 + 1, sz(a) + sz(b) - 1));
    int side = sz(res)/2, as = sz(a)/2, bs = sz(b)/2;
    rep(i, 0, sz(a)){
        rep(j, 0, sz(b)){
            if(abs(i-as+j-bs) <= side){
                res[i-as+j-bs+side] += ll(a[i]) * b[j] % MOD;
                if(res[i-as+j-bs+side] >= MOD) res[i-as+j-bs+side] -= MOD;
            }
        }
    }
    return res;
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi c(n);
    rep(i, 0, n){
        cin >> c[i]; c[i]--;
    }
    vvi adj(n);
    rep(i, 0, n-1){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    ll ans = 0;
    vi dfsord;
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        auto it = find(all(adj[u]), p);
        if(it != adj[u].end()) adj[u].erase(it);
        for(int v : adj[u]){
            dfs(v, u, dfs);
        }
        dfsord.pb(u);
    };
    dfs(0, -1, dfs);
    rep(i, 0, n){
        lb = 0;
        rep(j, 0, n) if(c[j] == i) lb++;
        vector<vi> dp(n);
        for(int u : dfsord){
            auto &res = dp[u];
            if(c[u] == i) {
                // res.l = 1, res.r = 2, res.dp = {1};
                res = {0, 0, 1};
            } else res = {1, 0, 0}; // res.l = -1, res.r = 0, res.dp = {1};
            for(int v : adj[u]) {
                res = conv(res, dp[v]);
            }
            (res[sz(res)/2] += 1) %= MOD;
            ll cnt = 0;
            rep(j, sz(res)/2+1, sz(res)) {
                if(j > 0) cnt += res[j];
            }
            (ans += cnt) %= MOD;
            // cout << u << " col: " << i << " " << cnt << endl;
        }
        // cout << i << " " << ans << "\n";
        // cout << i << " " << ans << "\n";
    }
    cout << ans << "\n";
    
    return 0;
}
