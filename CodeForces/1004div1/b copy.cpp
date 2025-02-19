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

using S = int;
using F = int;
S op(S a, S b) { return max(a, b); }
S ego() { return 0; }
S mapping(F f, S s) {
    return s + f;
}
F composition(F a, F b) { return a + b; }
F id() { return 0; }
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
			l /= 2, r /= 2;
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
			l /= 2, r /= 2;
		}
		l = l2; r = r2;
		tip check(update);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        int lim = n+10;
        vi a(n);
        rep(i, 0, n) {
            cin >> a[i];
            a[i] = min(a[i], lim-5);
        }
        reverse(all(a));
        Tree tree(lim);
        rep(i, 0, n) {
            {
                int prv = tree.prod(a[i], a[i]+1);
                tree.set(a[i]+1, max(tree.prod(a[i]+1, a[i]+1+1), prv+1));
            }
            tree.apply(0, a[i], 1);
        }
        int ans = 0;
        rep(i, 0, lim) ans = max(ans, tree.prod(i, i+1));
        cout << ans << "\n";
    }
    
    return 0;
}
