#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr-tl);
    return min(tl+pw2, tr-pw2/2);
}
const int inf = 1e9;
struct Node {
    vi tree;
    Node(int n) : tree(2*n) {}
    void pull(int k) {
        tree[k] = min(tree[2*k], tree[2*k+1]);
    }
    int query(int tl, int tr, int ti, int l, int r) {
        if(tr <= l || r <= tl) return inf;
        if(l <= tl && tr <= r) return tree[ti];
        int tm = split(tl, tr);
        return min(query(tl, tm, 2*ti, l, r), query(tm, tr, 2*ti+1, l, r));
    }
    void update(int tl, int tr, int ti, int idx, int v) {
        if(tr-tl==1){
            tree[ti] = max(tree[ti], v);
            return;
        }
        int tm = split(tl, tr);
        if(tm <= idx) update(tm, tr, 2*ti+1, idx, v);
        else update(tl, tm, 2*ti, idx, v);
        pull(ti);
    }
};

int min_left(Node &tree, int r, auto g) {
    int val = inf;
    int ans = r;
    int n = sz(tree.tree)/2;
    auto dfs = [&](int tl, int tr, int ti, auto &&dfs) -> void {
        if(r <= tl) return;
        // cerr << "at " << tl << "," << tr << " ans=" << ans << " val=" << val << endl;
        if(tr <= r) {
            int val2 = min(val, tree.tree[ti]);
            if(g(val2)) {
                ans = tl;
                val = val2;
                return;
            }
        }
        if(ti >= n) return;
        int tm = split(tl, tr);
        dfs(tm, tr, 2*ti+1, dfs);
        if(ans <= tm){
            dfs(tl, tm, 2*ti, dfs);
        }
    };
    dfs(0, n, 1, dfs);
    return ans;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q; cin >> n >> q;
    Node tree(n);
    rep(i, 0, n) {
        tree.update(0, n, 1, i, i);
    }
    rep(qid, 0, q) {
        // cerr << "before next query tree is: ";
        // rep(i, 0, n) {
        //     int mn = tree.query(0, n, 1, i, i+1);
        //     cerr << mn << " ";
        // }
        // cerr << endl;
        int t; cin >> t;
        if(t == 1) {
            int l, r; cin >> l >> r; l--;
            tree.update(0, n, 1, l, r);
        } else {
            int i; cin >> i; i--;
            int l = min_left(tree, i+1, [&](int v) { return v != inf && v >= i+1; });
            // {
            //     int sub = 0;
            //     for(int dif = 1 << 20; dif; dif /= 2) {
            //         int l = i+1 - (sub + dif);
            //         if(l < 0) continue;
            //         int mn = tree.query(0, n, 1, l, i+1);
            //         if(mn != inf && mn >= i+1) sub += dif;
            //     }
            //     // cerr << "sub should be " << sub << endl;
            // }
            int sub = i+1-l;
            // cerr << "sub is " << sub << endl;
            cout << sub+1 << "\n";
        }
    }

    return 0;
}
