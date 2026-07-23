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

struct UF {
    vi e, valid;
    UF(int n) : e(n, -1), valid(n, 1) {}
    int find(int u) { return e[u] < 0 ? u : e[u] = find(e[u]); }
    bool join(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return false;
        if(e[u] > e[v]) swap(u, v);
        e[u] += e[v];
        e[v] = u;
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ll res = 0;
    UF uf(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> int {
        int mx = -1e9;
        vi mxs;
        for(int v : adj[u]) if(v != p) {
            int ret = dfs(v, u, dfs);
            if(a[ret] > mx) {
                mx = a[ret];
                mxs = vi{ret};
            } else if(a[ret] == mx) {
                uf.join(ret, mxs.back());
                mxs.push_back(ret);
            }
        }
        if(sz(mxs) == 0) {
            res += a[u];
            return u;
        }
        if(a[u] < mx) {
            res -= mx;
            res += a[u];
            if(uf.e[uf.find(mxs[0])] == -1) {
                uf.valid[uf.find(mxs[0])] = 0;
            }
        } else if(a[u] == mx) {
            // uf.join(u, mxs[0]);
        } else {
            uf.valid[u] = 0;
            return mxs[0];
        }
        return u;
    };
    dfs(0, -1, dfs);
    vi ans;
    rep(i, 0, n) {
        if(uf.valid[uf.find(i)]) ans.push_back(i);
    }
    cout << res << " " << sz(ans) << "\n";
    for(auto x : ans) cout << x+1 << " ";
    cout << "\n";
    
    return 0;
}
