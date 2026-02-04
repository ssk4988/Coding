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

const ll mod = 998244353;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<vl> dp(n, vl{1, 1});
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        vector<vl> terms;
        for(int v : adj[u]) if(v != p) {
            dfs(v, u, dfs);
            (dp[u][0] *= (dp[v][0] + dp[v][1])) %= mod;
            terms.push_back(dp[v]);
        }
        if(sz(terms) == 0) return;
        dp[u][1] = 0;
        vl pref(sz(terms));
        pref[0] = 1;
        vl suff(sz(terms));
        suff.back() = 1;
        rep(i, 1, sz(pref)) {
            pref[i] = pref[i-1] * (terms[i-1][0] + terms[i-1][1]) % mod;
        }
        for(int i = sz(suff) - 2; i >= 0; i--) {
            suff[i] = suff[i+1] * (terms[i+1][0] + terms[i+1][1]) % mod;
        }
        rep(i, 0, sz(terms)) {
            (dp[u][1] += pref[i] * terms[i][1] % mod * suff[i]) %= mod;
        }
    };
    dfs(0, -1, dfs);
    cout << dp[0][0] << "\n";
    
    return 0;
}
