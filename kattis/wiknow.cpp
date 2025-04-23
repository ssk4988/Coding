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
const int inf = 1e9;
int split(int tl, int tr) {
    int pw2 = 1 <<__lg(tr-tl);
    return min(tl+pw2, tr-pw2/2);
}
using a2 = array<int, 2>;
a2 merge(a2 a, a2 b) {
    a2 res{inf, inf};
    for(int v : a) res[0] = min(res[0], v);
    for(int v : b) res[0] = min(res[0], v);
    for(int v : a) if(v != res[0]) res[1] = min(res[1], v);
    for(int v : b) if(v != res[0]) res[1] = min(res[1], v);
    return res;
}

vi merge(vi &l, vi &r) {
    vi res;
    int i=0, j=0;
    while(sz(res) < 2 && (i<sz(l) || j < sz(r))) {
        if(j == sz(r) || (i < sz(l) && l[i] < r[j])){
            if(sz(res) == 0 || res.back() != l[i]) res.pb(l[i]);
            i++;
        }else {
            if(sz(res) == 0 || res.back() != r[j]) res.pb(r[j]);
            j++;
        }
    }
    return res;
}
struct Tree {
    vector<a2> tree;
    Tree(int n) : tree(2*n, a2{inf, inf}) {}
    void mod(int tl, int tr, int ti, int idx, auto fun) {
        if(tr-tl == 1) {
            fun(tree[ti]);
            return;
        }
        int tm = split(tl, tr);
        if(tm <= idx) mod(tm, tr, 2*ti+1, idx, fun);
        else mod(tl, tm, 2*ti, idx, fun);
        a2 left = tree[2*ti], right = tree[2*ti+1];
        tree[ti] = merge(left, right);
    }
    a2 query(int tl, int tr, int ti, int l, int r) {
        if(tr <= l || r <= tl) return a2{inf, inf};
        if(l <= tl && tr <= r) return tree[ti];
        int tm = split(tl, tr);
        a2 left = query(tl, tm, 2*ti, l, r), right = query(tm, tr, 2*ti+1, l, r);
        return merge(left, right);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    vi prv(n, -1), nxt(n, -1);
    vi last(n, -1), first(n, -1);
    vvi occ(n);
    rep(i, 0, n) {
        cin >> a[i];
        a[i]--;
        occ[a[i]].pb(i);
        if(first[a[i]] == -1) {
            first[a[i]] = i;
        }
        prv[i] = last[a[i]];
        if(prv[i] != -1) nxt[prv[i]] = i;
        last[a[i]] = i;
    }
    Tree tree(n);
    pii ans{n, n};
    rep(i, 0, n) {
        if(first[a[i]] != i) {
            a2 res = tree.query(0, n, 1, first[a[i]]+1, i);
            for(int b : res) if(b != a[i] && b != inf) ans = min(ans, pii{a[i], b});
        }
        tree.mod(0, n, 1, i, [&](a2& v) -> void { v[0] = a[i]; });
        if(last[a[i]] == i) {
            for(int j : occ[a[i]]) {
                tree.mod(0, n, 1, j, [](a2 &v) -> void { v[0] = inf; });
            }
        }
    }
    if(ans.first == n) {
        cout << "-1\n";
    }
    else cout << ans.first+1 << " " << ans.second+1 << "\n";

    
    return 0;
}
