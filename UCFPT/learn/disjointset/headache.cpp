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
    vector<array<int, 3>> edges(m);
    rep(i, 0, m) {
        int u, v, w; cin >> u >> v >> w; u--, v--;
        edges[i] = {w, u, v};
    }
    sort(all(edges));
    reverse(all(edges));
    int ans = 0;
    UF uf(2*n);
    for(auto [w, u, v] : edges) {
        uf.join(2*u, 2*v+1);
        uf.join(2*u+1, 2*v);
        if(uf.find(2*u) == uf.find(2*u+1)) {
            ans = w;
            break;
        }
    }
    cout << ans << "\n";
    return 0;
}
