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
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2 / 2);
}

pi op(pi a, pi b) {
    if(a.f < b.f) return a;
    return b;
}
const int inf = 1e9;
struct seg_tree {
    int n;
    vector<pi> tree;
    vi lazy;
    seg_tree(int n) : n(n), tree(2 * n), lazy(2 * n) {
        int pw2 = 1;
        while(pw2 < n) pw2 *= 2;
        rep(i, 0, n){
            tree[n + (i + pw2) % n] = {0, i};
        }
        for(int i = n-1; i >= 0; i--) pull(i);
    }
    void apply(int add, int u){
        tree[u].f += add;
        lazy[u] += add;
    }
    void push(int u) {
        if (lazy[u]) {
            apply(lazy[u], 2 * u), apply(lazy[u], 2 * u + 1);
            lazy[u] = 0;
        }
    }
    void pull(int u) { tree[u] = op(tree[2 * u], tree[2 * u + 1]); }
    void update(int l, int r, int add) {
        update(l, r, add, 0, n, 1);
    }
    void update(int l, int r, int add, int tl, int tr, int u) {
        if (r <= tl || tr <= l) return;
        if (l <= tl && tr <= r) {
            return apply(add, u);
        }
        push(u);
        int tm = split(tl, tr);
        update(l, r, add, tl, tm, 2 * u);
        update(l, r, add, tm, tr, 2 * u + 1);
        pull(u);
    }
    pi query(int l, int r) { return query(l, r, 0, n, 1); }
    pi query(int l, int r, int tl, int tr, int u) {
        if (r <= tl || tr <= l) return {inf, -1};
        if (l <= tl && tr <= r) return tree[u];
        push(u);
        int tm = split(tl, tr);
        return op(query(l, r, tl, tm, 2 * u), query(l, r, tm, tr, 2 * u + 1));
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n);
        vi last(n, -1);
        vi pre(n, -1), nex(n, n);
        rep(i, 0, n){
            cin >> a[i]; a[i]--;
            if(last[a[i]] != -1){
                pre[i] = last[a[i]];
                nex[last[a[i]]] = i;
            }
            last[a[i]] = i;
        }
        seg_tree tree(n);
        int ans = 0;
        int furthest = -1;
        rep(i, 0, n){
            tree.update(pre[i] + 1, i+1, 1);
            if(pre[i] != -1){
                tree.update(pre[pre[i]] + 1, pre[i] + 1, -1);
            }
            pi res = tree.query(0, i+1);
            if(res.f == 0){
                if(furthest < res.s) {
                    ans++;
                    furthest = i;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
