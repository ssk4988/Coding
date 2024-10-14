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

inline int access(vi &v, int idx) {
    // if(idx < 0) return v.back();
    // if(idx >= sz(v)) return 0;
    // return v[sz(v) - 1 - idx];
    return idx < 0 || idx >= sz(v) ? 0 : v[sz(v) - 1 - idx];
}
inline int& accessref(vi &v, int idx) {
    return v[sz(v) - 1 - idx];
}
vvi dp, adj;
int n, d; 
void dfs(int u, int p, int depth) {
    int heavyc = -1;
    for(int v : adj[u]){
        if(v == p) continue;
        dfs(v, u, depth + 1);
        dp[v].push_back(0);
        if(heavyc == -1 || sz(dp[heavyc]) < sz(dp[v])) heavyc = v;
    }
    // cout << "got here " << u << endl;
    if (heavyc != -1) {
        swap(dp[heavyc], dp[u]);
        accessref(dp[u], 0) = max(access(dp[u], 1), 1 + access(dp[u], d));
    }
    else dp[u].push_back(1);
    // mx depth to update???
    int mx_d = 0;
    for(int v : adj[u]){
        if(v == p || v == heavyc) continue;
        rep(i, 1, sz(dp[v])) {
            accessref(dp[v], i) += access(dp[u], max(0, d - i));
        }
        rep(i, 1, sz(dp[v])) {
            int cur_d = min(i, max(0, d - i));
            accessref(dp[u], cur_d) = max(accessref(dp[u], cur_d), accessref(dp[v], i));
            mx_d = max(mx_d, cur_d);
        }
    }
    for(int d = mx_d; d >= 0; d--) accessref(dp[u], d) = max(accessref(dp[u], d), access(dp[u], d+1));
    return;
};
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> d;
    adj.resize(n);
    rep(i, 0, n-1){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dp.resize(n);
    dfs(0, -1, 0);
    int ans = access(dp[0], 0);
    cout << ans << "\n";
    
    return 0;
}
