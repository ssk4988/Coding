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
const int N = 3e5+10;
int freq[N];
const int K = 5;
struct Freq {
    vi best;
    void add(int x) {
        freq[x]++;
        auto it = find(all(best), x);
        if(it == end(best)) {
            if(sz(best) < K) best.pb(x), it = prev(end(best));
            else return;
        }
        while(it != begin(best) && freq[*prev(it)] < freq[*it]) {
            iter_swap(it, prev(it));
            it--;
        }
    }
    void push_back(int x) {
        add(x);
    }
    void push_front(int x) {
        add(x);
    }
};
Freq id() { return Freq(); }
Freq merge(Freq &a, Freq &b) {
    Freq res;
    for(auto p : a.best) res.best.pb(p);
    for(auto p : b.best) res.best.pb(p);
    return res;
}
Freq push_back(Freq f, int x) { f.add(x); return f; }
Freq push_front(Freq f, int x) { f.add(x); return f; }

// template <typename T>
using T = int;
using R = Freq;
struct DisjointST {
    vi masks;
    vector<vector<R>> levels;
    DisjointST(const vector<T> &a){
        int n = sz(a);
        masks = vi(n);
        int b = bit_width(a.size());
        if(b > 1 && n * 2 == (1 << b)) b--;
        levels.assign(b, vector<R>(n, id()));
        auto build = [&](int l, int r, int mask, int lvl, auto &&build) {
            if(l+1 == r) {
                masks[l] = mask;
                push_back(levels[lvl][l], a[l]);
                return;
            }
            int m = (l+r)/2;
            R cur = id();
            rep(i, m, min(r, n)) {
                cur = push_back(cur, a[i]);
                levels[lvl][i] = cur;
            }
            cur = id();
            for(int i = min(m, n)-1; i >= l; i--) {
                cur = push_front(cur, a[i]);
                levels[lvl][i] = cur;
            }
            rep(i, l, min(n, r)) freq[a[i]] = 0;
            build(l, m, mask, lvl+1, build);
            build(m, r, mask ^ (1 << lvl), lvl+1, build);
        };
        build(0, 1 << b, 0, 0, build);
    }
    // [L, R)
    R query(int l, int r){
        if(l == r--) return id();
        if(l == r) return levels.back()[l];
        int h = __lg(l ^ r);
        return merge(levels[h][l], levels[h][r]);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vi a(n);
    vvi idxs(n);
    rep(i, 0, n) {
        cin >> a[i]; a[i]--;
        idxs[a[i]].pb(i);
    }
    auto cnt = [&](int x, int l, int r) {
        return lower_bound(all(idxs[x]), r) - lower_bound(all(idxs[x]), l);
    };
    DisjointST rmq(a);
    rep(qid, 0, q) {
        int l, r, k; cin >> l >> r >> k;
        l--;
        int ans = 1e9;
        auto rs = rmq.query(l, r);
        for(auto cand : rs.best) if(cnt(cand, l, r) > (r-l)/k && cand < ans) ans = cand;
        if(ans == 1e9) ans = -2;
        cout << ans+1 << "\n";
    }
    
    return 0;
}
