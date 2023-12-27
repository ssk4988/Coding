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
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vl subsz(n, 1);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        for (int v : adj[u]) {
            if(v == p) continue;
            dfs(v, u, dfs);
            subsz[u] += subsz[v];
        }
    };
    ll ans = 0;
    vector<vl> dp(n, vl(n, -1));
    auto calc = [&](int u, int v, int pu, int pv, auto &&calc) -> ll {
        if(dp[u][v] != -1) return dp[u][v];
        dp[u][v] = subsz[u] * subsz[v];
        ll best = 0;
        for(int u1 : adj[u]){
            if(u1 == pu) continue;
            best = max(best, calc(u1, v, u, pv, calc));
        }
        for(int v1 : adj[v]){
            if(v1 == pv) continue;
            best = max(best, calc(u, v1, pu, v, calc));
        }
        dp[u][v] += best;
        return dp[u][v];
    };
    auto solve = [&](int u, int p, auto &&solve) -> void {
        if (p != -1) {
            subsz = vl(n, 1);
            dfs(u, p, dfs);
            dfs(p, u, dfs);
            ans = max(ans, calc(u, p, p, u, calc));
            ans = max(ans, calc(p, u, u, p, calc));
        }
        for(int v : adj[u]){
            if(v == p) continue;
            solve(v, u, solve);
        }
    };
    solve(0, -1, solve);
    cout << ans << "\n";
    
    return 0;
}
