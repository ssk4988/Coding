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
#define ssize(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"
 
 
template <class F> struct centroid {
    vector<vector<int>> adj;
    F f;
    vector<int> sub_sz;
    /**
     * @param a_adj unweighted undirected forest
     * @param a_f called on centroid of each decomposition
     * @time O(n log n)
     * @space `adj` and `sub_sz` arrays take O(n); recursion stack for `dfs` is
     * O(log n); recursion stack for `calc_sz` is O(n)
     */
    centroid(const vector<vector<int>>& a_adj, F a_f)
        : adj(a_adj), f(a_f), sub_sz(ssize(adj), -1) {
        for (int i = 0; i < ssize(adj); i++)
            if (sub_sz[i] == -1) dfs(i);
    }
    void calc_sz(int u, int p) {
        sub_sz[u] = 1;
        for (auto v : adj[u]) {
            if (v == p) continue;
            calc_sz(v, u);
            sub_sz[u] += sub_sz[v];
        }
    }
    void dfs(int u) {
        calc_sz(u, -1);
        for (int p = -1, sz_root = sub_sz[u];;) {
            auto big_ch = find_if(begin(adj[u]), end(adj[u]), [&](int v) -> bool {
                return v != p && 2 * sub_sz[v] > sz_root;
            });
            if (big_ch == end(adj[u])) break;
            p = u, u = *big_ch;
        }
        f(adj, u);
        for (auto v : adj[u]) {
            iter_swap(find(begin(adj[v]), end(adj[v]), u), rbegin(adj[v]));
            adj[v].pop_back();
            dfs(v);
        }
    }
};
 
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k1, k2; cin >> n >> k1 >> k2;
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    ll ans = 0;
    vl freq(n + 5), newfreq;
    centroid(adj, [&](const vvi &a, int root) -> void {
        int maxd = 0;
        auto dfs = [&](int cur, int par, int d, auto&&dfs) -> void {
            maxd = max(d, maxd);
            ans += freq[max(0, k1 - d)];
            ans -= freq[max(0, k2 - d + 1)];
            while(sz(newfreq) <= d) newfreq.pb(0);
            newfreq[d]++;
            for(int nex : a[cur]){
                if(nex == par) continue;
                dfs(nex, cur, d+1, dfs);
            }
        };
        freq[0]++;
        for(int nex : a[root]){
            dfs(nex, root, 1, dfs);
            ll acc = 0;
            for(int i = sz(newfreq) - 1; i >= 0; i--){
                acc += newfreq[i];
                freq[i] += acc;
            }
            newfreq.clear();
        }
        rep(i, 0, maxd + 1) freq[i] = 0;
    });
    cout << ans << "\n";
    
    return 0;
}
