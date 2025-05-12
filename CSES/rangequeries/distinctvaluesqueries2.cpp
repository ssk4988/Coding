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
using S = pii;
// max left, min right
S ego() {
    return pii{-inf, inf};
}
S op(S a, S b) {
    return pii{max(a.f, b.f), min(a.s, b.s)};
}
using F = int;
S mapping(F f, S s) { return s; }
F id() { return -1; }
F composition(F newer, F older) { return newer; }

struct Tree {
	int n, size, log;
	vector<S> d;
	vector<F> lz;
	Tree(size_t m) {
		n = m; size = bit_ceil(m); log = __lg(size);
		d = vector(2*size, ego());
		lz = vector(size, id());
	}
	void update(int k) { d[k] = op(d[2*k], d[2*k + 1]); }
	void fid(int k, F f) {
		d[k] = mapping(f, d[k]);
		if (k < size) lz[k] = composition(f, lz[k]);
	}
	void push(int k) {
		fid(2 * k, lz[k]);
		fid(2 * k + 1, lz[k]);
		lz[k] = id();
	}
	#define tip for (int i = 1; i <= log; i++)
	#define dip for (int i = log; i >= 1; i--)
	#define check(p) { if (((1<<i)-1) & l) p(l >> i);\
	                   if (((1<<i)-1) & r) p((r-1) >> i); }
	void set(int p, S x) {
		p += size;
		dip push(p >> i);
		d[p] = x;
		tip update(p >> i);
	}
	S prod(int l, int r) {
		l += size; r += size;
		dip check(push);
		S sml = ego(); S smr = ego();
		while (l < r) {
			if (l & 1) sml = op(sml, d[l++]);
			if (r & 1) smr = op(d[--r], smr);
			l /= 2; r /= 2;
		}
		return op(sml, smr);
	}
	void apply(int l, int r, F f) {
		l += size; r += size;
		int l2 = l, r2 = r;
		dip check(push);
		while (l < r) {
			if (l & 1) fid(l++, f);
			if (r & 1) fid(--r, f);
			l /= 2; r /= 2;
		}
		l = l2; r = r2;
		tip check(update);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vi a(n);
    map<int, set<int>> loc;
    rep(i, 0, n) {
        cin >> a[i];
        loc[a[i]].insert(i);
    }
    Tree tree(n);
    auto upd = [&](int u) -> void {
        int left = -inf;
        auto it = loc[a[u]].lower_bound(u);
        if(it != begin(loc[a[u]])){
            left = *prev(it);
        }
        it = next(it);
        int right = inf;
        if(it != end(loc[a[u]])) {
            right = *it;
        }
        tree.set(u, S{left, right});
    };
    rep(i, 0, n) upd(i);
    rep(qid, 0, q) {
        int t; cin >> t;
        if(t == 1) {
            int i, v; cin >> i >> v; i--;
            vi upds;
            upds.pb(i);
            loc[a[i]].erase(i);
            auto it = loc[a[i]].lower_bound(i);
            if(it != end(loc[a[i]])) {
                upds.pb(*it);
            }
            if(it != begin(loc[a[i]])) {
                it--;
                upds.pb(*it);
            }
            a[i] = v;
            it = loc[a[i]].lower_bound(i);
            if(it != end(loc[a[i]])) {
                upds.pb(*it);
            }
            if(it != begin(loc[a[i]])) {
                it--;
                upds.pb(*it);
            }
            loc[a[i]].insert(i);
            for(int idx : upds) upd(idx);
        } else {
            int l, r; cin >> l >> r; l--;
            S res = tree.prod(l, r);
            if(res.f >= l || res.s < r) {
                cout << "NO\n";
            } else cout << "YES\n";
        }
    }
    
    return 0;
}
