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
    vi e, w;
    UF(int n) : e(n, -1), w(n, 1e9+1) {}
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    bool join(int a, int b, int v) {
        a = find(a), b = find(b);
        if(a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        w[b] = v;
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<array<int, 4>> ed(m);
    rep(i, 0, m) {
        cin >> ed[i][1] >> ed[i][2] >> ed[i][0]; ed[i][1]--, ed[i][2]--;
        ed[i][3] = i;
    }    
    sort(all(ed));
    UF uf(n);
    vi ans(m);
    ll tot = 0;
    for(auto [w, u, v, i] : ed) {
        if(uf.join(u, v, w)) {
            tot += w;
        } else {
            while(u != v) {
                if(uf.w[u] > uf.w[v]) swap(u, v);
                ans[i] = max(ans[i], uf.w[u]);
                u = uf.e[u];
            }
            ans[i] = w - ans[i];
        }
    }
    rep(i, 0, m) {
        cout << ans[i] + tot << "\n";
    }
    
    return 0;
}
