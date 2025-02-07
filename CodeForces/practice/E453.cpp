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

const ll inf = 1e18;

int split(int tl, int tr) {
    int pw = 1 << __lg(tr - tl);
    return min(tl + pw, tr - pw/2);
}
struct S {
    int mxt=0, mnt=0;
    vector<array<ll, 3>> lines, slines;
};
struct seg_tree {
    int n;
    vector<S> tree;// time, slope, const
    vi lazy;
    seg_tree(int n, vector<array<ll, 3>> ponies) : n(n), tree(2*n), lazy(n, -1) {
        int p2 = 1;
        while(p2 < n) p2 *= 2;
        rep(i,0,n){
            int idx = (i + p2) % n + n;
            tree[idx].lines.pb({0, ponies[i][2], 0});
            if(ponies[i][2]) {
                int t = (ponies[i][1] + ponies[i][2]-1) / ponies[i][2];
                tree[idx].lines.pb({t, -ponies[i][2], ponies[i][1]});
            }
            tree[idx].slines.pb({0, ponies[i][2], ponies[i][0]});
            if(ponies[i][2]) {
                int t = (ponies[i][1] + ponies[i][2]-1 - ponies[i][0]) / ponies[i][2];
                tree[idx].slines.pb({t, -ponies[i][2], ponies[i][1] - ponies[i][0]});
            }
            sort(all(tree[idx].lines));
            sort(all(tree[idx].slines));
        }
        for(int i = n-1; i >= 1; i--) {
            merge(all(tree[i*2].lines), all(tree[i*2+1].lines), back_inserter(tree[i].lines));
            merge(all(tree[i*2].slines), all(tree[i*2+1].slines), back_inserter(tree[i].slines));
        }
        for(int i = sz(tree)-1; i >= 1; i--) {
            rep(j, 1, sz(tree[i].lines)) {
                tree[i].lines[j][1] += tree[i].lines[j-1][1];
                tree[i].lines[j][2] += tree[i].lines[j-1][2];
                tree[i].slines[j][1] += tree[i].slines[j-1][1];
                tree[i].slines[j][2] += tree[i].slines[j-1][2];
            }
        }
    }
    void apply(int t, int tl, int tr, int ti) {
        if(ti < n) lazy[ti] = t;
        tree[ti].mxt = tree[ti].mnt = t;
    }
    ll query(int l, int r, int cur_t, int tl, int tr, int ti) {
        if (r <= tl || tr <= l) return 0;
        if (l <= tl && tr <= r && tree[ti].mnt == tree[ti].mxt) {
            auto &li = tree[ti].mnt == 0 ? tree[ti].slines : tree[ti].lines;
            auto [t, slope, coef] = *prev(upper_bound(all(li), array<ll, 3>{cur_t - tree[ti].mnt, inf, inf}));
            ll res = (cur_t - tree[ti].mnt) * slope + coef;
            apply(cur_t, tl, tr, ti);
            return res;
        }
        int tm = split(tl, tr);
        push(tl, tm, tr, ti);
        ll res = query(l, r, cur_t, tl, tm, ti * 2) + query(l, r, cur_t, tm, tr, ti * 2 + 1);
        tree[ti].mnt = min(tree[ti*2].mnt, tree[ti*2+1].mnt);
        tree[ti].mxt = max(tree[ti*2].mxt, tree[ti*2+1].mxt);
        return res;
    }
    void push(int tl, int tm, int tr, int ti) {
        if(lazy[ti] == -1) return;
        apply(lazy[ti], tl, tm, 2*ti), apply(lazy[ti], tm, tr, 2*ti+1), lazy[ti]=-1;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<array<ll, 3>> ponies;
    rep(i, 0,n){
        int s, m, r; cin >> s >> m >> r;
        ponies.pb({s, m, r});
    }
    seg_tree tree(n, ponies);
    int m; cin >> m;
    rep(i, 0, m) {
        int t, l, r; cin >> t >> l >> r;
        l--;
        ll res = tree.query(l, r, t, 0, n, 1);
        cout << res << "\n";
    }
    return 0;
}
