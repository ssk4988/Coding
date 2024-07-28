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
    return idx < 0 || idx >= sz(v) ? 0 : v[sz(v) - 1 - idx];
}
inline int& accessref(vi &v, int idx) {
    return v[sz(v) - 1 - idx];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, d; cin >> n >> d;
    vvi adj(n);
    rep(i, 0, n-1){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vvi dp(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        // cout << "dfs " << u << endl;
        vvi cs;
        cs.pb({1});
        for(int v : adj[u]){
            if(v == p) continue;
            dfs(v, u, dfs);
            cs.pb({});
            swap(cs.back(), dp[v]);
            cs.back().pb(0);
        }
        // cout << "got here " << u << endl;
        sort(all(cs), [&](vi &a, vi &b) -> bool { return sz(a) > sz(b); });
        int s2 = sz(cs) < 2 ? 0 : sz(cs[1]);
        vi sums(s2);
        rep(i, 0, sz(cs)){
            rep(j, 0, min(s2, sz(cs[i]))){
                sums[j] += accessref(cs[i], j);
            }
        }
        // cout << "calcd sums " << u << endl;
        for(int i = s2-1; i >= 0; i--){
            int best = 0;
            int other = max(i, d - i);
            int sm = other >= sz(sums) ? 0 : sums[other];
            rep(j, 0, sz(cs)) {
                if(i >= sz(cs[j])) break;
                best = max(best, sm + access(cs[j], i) - access(cs[j], other));
            }
            accessref(cs[0], i) = max({access(cs[0], i+1), accessref(cs[0], i), best, sums[i] - access(cs[0], i) + access(cs[0], other)});
        }
        swap(dp[u], cs[0]);
        // reverse(all(dp[u]));
        // cout << u << ": ";
        // for(int x : dp[u]) cout << x << " ";
        // cout << endl;
        // reverse(all(dp[u]));
    };
    dfs(0, -1, dfs);
    int ans = access(dp[0], 0);
    cout << ans << "\n";
    
    return 0;
}
