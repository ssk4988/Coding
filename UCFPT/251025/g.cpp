#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct UF {
    vi e;
    UF(int n):e(n, -1) {

    }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int u, int v) {
        u = find(u), v = find(v);
        if(u==v) return false;
        if(e[u] > e[v]) swap(u, v);
        e[u] += e[v];
        e[v] = u;
        return true;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    UF uf(n);
    rep(i, 0, m) {
        int u, v; cin >> u >> v; u--, v--;
        uf.join(u, v);
    }
    vi ans(n), cnt(n);
    rep(i, 0, n) {
        int p = uf.find(i);
        if(-uf.e[p] < k) {
            cout << "impossible\n";
            return 0;
        }
        ans[i] = 1 + (cnt[p] % k);
        cnt[p]++;
    }
    rep(i, 0 ,n) cout << ans[i] << " ";
    cout << "\n";

    return 0;
}
