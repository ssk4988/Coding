#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;
template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2/2); 
}

struct SegTree {
    vector<Tree<pii>> st;
    SegTree(int n): st(2*n) {}
    void update(int tl, int tr, int ti, int idx, int val, int i) {
        // cout << "INSERTING" << ti << " " << tl << " " << tr << " " << idx << " " << val << endl;
        st[ti].insert(pii(val, i));
        if(tr - tl == 1) return;
        int tm = split(tl, tr);
        if(idx < tm) update(tl, tm, 2*ti, idx, val, i);
        else update(tm, tr, 2*ti+1, idx, val, i);
    }
    // return kth element less than or equal to y
    int query(int tl, int tr, int ti, int y, int k) {
        int cnt = st[ti].order_of_key(pii(y, 1e9));
        // Base Case
        if(tr - tl == 1) {
            // cout << "GOT TO LEAF REPRESENTING " << tl << ' ' << tr << endl;
            return cnt >= k ? tl : 1e9;
        }

        // Walk
        int tm = split(tl, tr);

        // kth smallest is in the left subtree
        int left_cnt = st[2*ti].order_of_key(pii(y, 1e9));
        // cout << tl << ' ' << tr << '\n';
        // cout << "TREE: \n";
        // for(auto [y, _]: st[2*ti]) cout << y << ' ' << _ << '\n';
        // cout << "END TREE\n";
        // if(y == 13) cout << "DEBUG: " << tm << ' ' << ti << ' ' << left_cnt << ' ' << k << '\n';
        if(left_cnt >= k) return query(tl, tm, 2*ti, y, k);
        
        // kth smallest is in the right subtree
        return query(tm, tr, 2*ti+1, y, k - left_cnt);
    }
};

using pt = pair<ll, ll>;
#define xx first
#define yy second

ll cross(pt p, pt q) {
    return p.xx * q.yy - p.yy * q.xx;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    if(cross(pt(x1, y1), pt(x2, y2)) == 0){
        ll mx = max(abs(x2), abs(y2));
        ll scale = (1000000000 + mx-1) / mx;
        x2 *= scale, y2 *= scale;
        bool fix = false;
        for(int dx : {-1, 0, 1}){
            for(int dy : {-1, 0, 1}) {
                if(!fix && cross(pt(x1, y1), pt(x2+dx, y2+dy)) != 0){
                    x2+=dx, y2+=dy;
                    fix = true;
                }
            }
        }
        assert(fix);
    }
    if(cross(pt(x1, y1), pt(x2, y2)) < 0) swap(x1, x2), swap(y1, y2);

    vector<pt> pts(n);
    rep(i, 0, n) {
        ll x0, y0; cin >> x0 >> y0;
        ll y = cross(pt(x0, y0), pt(x1, y1));
        ll x = cross(pt(x2, y2), pt(x0, y0));
        pts[i] = pt(-x, -y);
        // ll x = cross(pt(x0, y0), pt(x1, y1));
        // ll y = cross(pt(x0, y0), pt(x2, y2));
        // cout << -x << ' ' << -y << endl;

        // pts[i] = pt(y, -x);
    }

    vi k(n);
    rep(i, 0, n) cin >> k[i];

    vi ord(n); iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) -> bool {
        return pts[i] < pts[j];
    });

    SegTree st(n);
    vi res(n); iota(all(res), 0);

    for(int i: ord) {
        res[i] = min(res[i], st.query(0, n, 1, pts[i].yy, k[i]));
        // cout << "RES: " << i << ' ' << res[i] << ' ' << pts[i].yy << endl;
        st.update(0, n, 1, res[i], pts[i].yy, i);
    }

    rep(i, 0, n) cout << res[i] + 1 << ' ';
    cout << '\n';

    return 0;
}
