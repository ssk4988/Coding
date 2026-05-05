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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vl a(n);
        vi p(n);
        rep(i, 0, n) {
            cin >> p[i]; p[i]--;
        }
        rep(i, 0, n) cin >> a[i];
        vvi adj(n);
        auto dfs = [&](int l, int r, auto &&dfs) -> int {
            if(l == r) return -1;
            if(l + 1 >= r) return l;
            int u = l;
            rep(i, l, r) if(p[i] < p[u]) u = i;
            int le = dfs(l, u, dfs);
            int ri = dfs(u+1, r, dfs);
            if(le != -1) adj[u].push_back(le);
            if(ri != -1) adj[u].push_back(ri);
            return u;
        };
        dfs(0, n, dfs);
        // rep(i, 0, n) {
        //     cerr << "adj " << i << ": ";
        //     for(int v : adj[i]) cerr << v << ",";
        //     cerr << "\n";
        // }
        int root = min_element(all(p)) - begin(p);
        vector<vl> dp(n);
        auto go = [&](int u, auto &&go) -> void {
            for(int v : adj[u]) go(v, go);
            if(sz(adj[u]) == 0){
                dp[u] = vl{0, a[u]};
            }
            if(sz(adj[u]) == 1) {
                int v = adj[u][0];
                dp[u] = vl(sz(dp[v])+1, 1e18);
                // dp[u][0] = 0;
                rep(i, 0, sz(dp[v])) {
                    dp[u][i] = min(dp[u][i], dp[v][i]);
                    dp[u][i+1] = min(dp[u][i+1], dp[v][i] + a[u]);
                }
            }
            if(sz(adj[u]) == 2) {
                int v = adj[u][0], w = adj[u][1];
                dp[u] = vl(sz(dp[v]) + sz(dp[w]) + 1, 1e18);
                dp[u][0] = 0;
                rep(i, 0, sz(dp[v])) {
                    rep(j, 0, sz(dp[w])) {
                        ll cost = dp[v][i] + dp[w][j];
                        int k = i+j;
                        if(i == 0 || j == 0) dp[u][k] = min(dp[u][k], cost);
                        k++;
                        cost += a[u];
                        dp[u][k] = min(dp[u][k], cost);

                    }
                }
            }
        };
        go(root, go);
        rep(i, 1, n+1) {
            cout << dp[root][i] << " ";
        }
        cout << "\n";
        // rep(i, 0, n) {
        //     cerr << i << ": ";
        //     rep(j, 0, sz(dp[i])) {
        //         cerr << dp[i][j] << " ";
        //     }
        //     cerr << "\n";
        // }
        // vvi mn(n, vi(n+1, n));
        // rep(i, 0, n) {
        //     mn[i][i+1] = i;
        //     rep(j, i+2, n+1) {
        //         mn[i][j] = p[j-1] < p[mn[i][j-1]] ? j-1 : mn[i][j-1];
        //     }
        // }
        // vl dp(n+1, 1e18);
        // dp[0] = 0;
        // rep(i, 0, n) {
        //     rep(j, i+1, n+1) {
        //         ll cost = a[j-1] + (mn[i][j] != j-1) * a[mn[i][j]];
        //         dp[j] = min(dp[j], dp[i] + cost);
        //     }
        // }
        // cout << dp[n] << "\n";
    }
    
    return 0;
}
