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
    int comps;
    UF(int n) : e(n, -1), comps(n) {}
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return false;
        if(e[u] > e[v]) swap(u, v);
        e[u] += e[v]; e[v] = u; comps--;
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, q; cin >> m >> n >> q;
    vvi grid(n, vi(m, q));
    rep(qid, 0, q) {
        int r1, c1, r2, c2; cin >> c1 >> r1 >> c2 >> r2; c1--, r1--, c2--, r2--;
        if(r1 == r2) {
            rep(c, c1, c2+1) {
                if(grid[r1][c] == q) grid[r1][c] = qid;
            }
        } else rep(r, r1, r2+1) {
            if(grid[r][c1] == q) grid[r][c1] = qid;
        }
    }
    vector<vii> bucket(q+1);
    rep(i, 0, n) rep(j, 0, m) bucket[grid[i][j]].pb({i, j}); 
    vvi on(n, vi(m));
    int ison = 0;
    vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
    UF uf(n*m);
    vi ans;
    for(int t = q; t >= 0; t--) {
        for(auto [i, j] : bucket[t]) {
            ison++;
            on[i][j] = 1;
            rep(k, 0, 4) {
                int i1 = i + dr[k], j1 = j + dc[k];
                if(min(i1, j1) < 0 || i1 >= n || j1 >= m) continue;
                if(!on[i1][j1]) continue;
                uf.join(i*m+j, i1*m+j1);
            }
        }
        ans.pb(uf.comps - (n*m-ison));
    }
    reverse(all(ans));
    rep(i, 1, sz(ans)) {
        cout << ans[i] << "\n";
    }
    return 0;
}
