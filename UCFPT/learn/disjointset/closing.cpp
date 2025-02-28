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
    vi e;
    UF(int n) : e(n, -1) {}
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return false;
        if(e[u] > e[v]) swap(u, v);
        e[u] += e[v]; e[v] = u;
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi adj(n);
    vi on(n);
    rep(i, 0, m) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi p;
    rep(i, 0, n) {
        int u; cin >> u; u--;
        p.pb(u);
    }
    reverse(all(p));
    vi ans;
    int curon = 0;
    UF uf(n);
    for(int u : p) {
        on[u] = true;
        for(int v : adj[u]) if(on[v]) uf.join(u, v);
        curon++;
        ans.pb(-uf.e[uf.find(u)] == curon);
    }
    reverse(all(ans));
    rep(i, 0, sz(ans)) {
        cout << (ans[i] ? "YES" : "NO") << "\n";
    }
    return 0;
}
