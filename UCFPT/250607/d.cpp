#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

#include <bits/extc++.h>
using namespace __gnu_pbds;
template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct UF {
    vi e;
    vector<Tree<pii>> t;
    UF(int n) : e(n, -1), t(n) {}
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        for(auto v : t[b]) {
            t[a].insert(v);
        }
        t[b] = Tree<pii>();
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, q; cin >> n >> m >> q;
    vi h(n);
    rep(i, 0, n) cin >> h[i];
    UF uf(n);
    rep(i, 0, n) uf.t[i].insert(pii{h[i], i});
    vi ans(q, -1);
    vector<array<int, 4>> events;
    rep(i, 0, m) {
        int u, v, c; cin >> u >> v >> c; u--, v--;
        events.push_back({c, -1, u, v});
    }
    rep(i, 0, q) {
        int v, x, k; cin >> v >> x >> k; v--;
        events.push_back({x, i, v, k});
    }
    sort(all(events));
    for(auto [_, t, a, b] : events) {
        if(t == -1) {
            uf.join(a, b);
            // cerr << "join " << a << " " << b << " weight " << _ << endl;
        } else {
            a = uf.find(a);
            if(sz(uf.t[a]) < b) continue;
            // cerr << "qid " << t << ": ";
            // for(auto [c, d] : uf.t[a]) cerr << c << "," << d << " ";
            // cerr << endl;
            ans[t] = (uf.t[a].find_by_order(sz(uf.t[a])-b))->first;
        }
    }
    rep(i, 0, q) {
        cout << ans[i] << "\n";
    }


    return 0;
}
