#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr-tl);
    return min(tl+pw2, tr-pw2/2);
}

const ll inf = 1e18;
struct S{
    ll sum = 0, mx = -inf, mxfreq = 0, mn = inf, mnfreq = 0, mn2 = inf, mx2 = -inf;
};

struct F{ ll lzmin = 0, lzmax = 0, lzadd = 0; };

struct seg_tree {
    int n;
    vector<S> tree;
    vector<F> lazy;
    void pull(int ti) {
        tree[ti].sum = tree[2*ti].sum + tree[2*ti+1].sum;
        tree[ti].mx = max(tree[2*ti].mx, tree[2*ti+1].mx);
        tree[ti].mn = min(tree[2*ti].mn, tree[2*ti+1].mn);
        tree[ti].mnfreq = tree[ti].mxfreq = 0;
        for(auto p : {2*ti, 2*ti+1}){
            if(tree[p].mn == tree[ti].mn) tree[ti].mnfreq += tree[p].mnfreq;
            if(tree[p].mx == tree[ti].mx) tree[ti].mxfreq += tree[p].mxfreq;
        }
        tree[ti].mx2 = -inf, tree[ti].mn2 = inf;
        for(auto p : {2*ti, 2*ti+1}) {
            for(auto v : {tree[p].mn, tree[p].mx, tree[p].mn2, tree[p].mx2}) {
                if(abs(v)==inf) continue;
                if(v != tree[ti].mx) tree[ti].mx2 = max(tree[ti].mx2, v);
                if(v != tree[ti].mn) tree[ti].mn2 = min(tree[ti].mn2, v);
            }
        }
    }
    void push(int tl, int tm, int tr, int ti) {
        if(ti >= n) return;
        if (lazy[ti].lzadd) {
            apply(tl, tr, 2*ti, lazy[ti].lzadd, 0, 0);
            apply(tl, tr, 2*ti+1, lazy[ti].lzadd, 0, 0);
            lazy[ti].lzadd = 0;
        }
        if(lazy[ti].lzmin) {
            apply(tl, tr, 2*ti, 0, tree[ti].mn - lazy[ti].lzmin, lazy[ti].lzmin);
            apply(tl, tr, 2*ti+1, 0, tree[ti].mn - lazy[ti].lzmin, lazy[ti].lzmin);
            lazy[ti].lzmin = 0;
        }
        if(lazy[ti].lzmax) {
            apply(tl, tr, 2*ti, 0, tree[ti].mx - lazy[ti].lzmax, lazy[ti].lzmax);
            apply(tl, tr, 2*ti+1, 0, tree[ti].mx - lazy[ti].lzmax, lazy[ti].lzmax);
            lazy[ti].lzmax = 0;
        }
    }
    seg_tree(int n, vl &init) : n(n), tree(2*n), lazy(n) {
        int p2 = 1;
        while(p2 < n) p2 *= 2;
        rep(i, 0, n) {
            int idx = (p2 + i) % n + n;
            tree[idx] = S{init[i], init[i], 1, init[i], 1};
        }
        for(int i = n-1; i; i--) pull(i);
    }
    void apply(int tl, int tr, int ti, ll add, ll v, ll dv) {
        if(add) {
            tree[ti].sum += add * (tr - tl);
            tree[ti].mn += add;
            tree[ti].mx += add;
            if(tree[ti].mn2 != inf) tree[ti].mn2 += add;
            if(tree[ti].mx2 != -inf) tree[ti].mx2 += add;
            if(ti < n) lazy[ti].lzadd += add;
        }
        if(dv) {
            if(tree[ti].mn == v) {
                if(tree[ti].mn != tree[ti].mx) {
                    if(ti < n) lazy[ti].lzmin += dv;
                    tree[ti].sum += tree[ti].mnfreq * dv;
                }
                tree[ti].mn += dv;
            }
            if(tree[ti].mx == v) {
                if(ti < n) lazy[ti].lzmax += dv;
                tree[ti].sum += tree[ti].mxfreq * dv;
                tree[ti].mx += dv;
            }
            if(tree[ti].mn2 == v) tree[ti].mn2 += dv;
            if(tree[ti].mx2 == v) tree[ti].mx2 += dv;
        }
    }
    void add(int l, int r, ll x, int tl, int tr, int ti) {
        if(r <= tl || tr <= l) return;
        if(l <= tl && tr <= r) {
            return apply(tl, tr, ti, x, 0, 0);
        }
        int tm = split(tl, tr);
        push(tl, tm, tr, ti);
        add(l, r, x, tl, tm, 2*ti);
        add(l, r, x, tm, tr, 2*ti+1);
        pull(ti);
    }
    void chmin(int l, int r, ll x, int tl, int tr, int ti) {
        if(tr <= l || r <= tl || tree[ti].mx <= x) return;
        if(l <= tl && tr <= r && tree[ti].mx2 < x) {
            return apply(tl, tr, ti, 0, tree[ti].mx, x - tree[ti].mx);
        }
        if(ti >= n) return;
        int tm = split(tl, tr);
        push(tl, tm, tr, ti);
        chmin(l, r, x, tl, tm, 2*ti);
        chmin(l, r, x, tm, tr, 2*ti+1);
        pull(ti);
    }
    void chmax(int l, int r, ll x, int tl, int tr, int ti) {
        if(tr <= l || r <= tl || tree[ti].mn >= x) return;
        if(l <= tl && tr <= r && tree[ti].mn2 > x) {
            return apply(tl, tr, ti, 0, tree[ti].mn, x - tree[ti].mn);
        }
        if(ti >= n) return;
        int tm = split(tl, tr);
        push(tl, tm, tr, ti);
        chmax(l, r, x, tl, tm, 2*ti);
        chmax(l, r, x, tm, tr, 2*ti+1);
        pull(ti);
    }
    ll query(int l, int r, int tl, int tr, int ti) {
        if(tr <= l || r <= tl) return 0;
        if(l <= tl && tr <= r) return tree[ti].sum;
        int tm = split(tl, tr);
        push(tl, tm, tr, ti);
        return query(l, r, tl, tm, 2*ti) + query(l, r, tm, tr, 2*ti+1);
    }
};


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n, q; cin >> n >> q;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    seg_tree tree(n, a);
    rep(i, 0, q){
        // cerr << "dbg: " << tree.rangesum(0, n) << endl;
        int t, l, r; cin >> t >> l >> r;
        if(t == 3) {
            cout << tree.query(l, r, 0, n, 1) << "\n";
            continue;
        }
        ll b; cin >> b;
        if(t == 0) tree.chmin(l, r, b, 0, n, 1);
        else if(t == 1) tree.chmax(l, r, b, 0, n, 1);
        else tree.add(l, r, b, 0, n, 1);
    }
    return 0;
}
