#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
struct UF {
    vl e;
    ll s2 = 0, comps = 0;
    UF(int n) : e(n, -1), s2(n), comps(n) {}
    int find(int u) { return e[u] < 0 ? u : e[u] = find(e[u]); }
    bool join(int u, int v) {
        u = find(u), v = find(v);
        if(u ==v) return false;
        if(e[u] > e[v]) swap(u, v);
        comps--;
        s2 -= e[u] * e[u] + e[v] * e[v];
        e[u] += e[v];
        e[v] = u;
        s2 += e[u] * e[u];
        return true;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    UF uf(n);
    rep(i, 0, m) {
        int t; cin >> t;
        if(t == 2) {
            ll num = uf.s2, denom = uf.comps;
            ll g = gcd(num, denom);
            num /= g, denom /= g;
            cout << num << "/" << denom << "\n";
        } else 
        {
            int u, v; cin >> u >> v; u--, v--;
            uf.join(u, v);
        }
    }

    return 0;
}
