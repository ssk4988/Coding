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

using S = ll;
const S inf = 1e18;
S e() { return inf; }
S op(S l, S r) { return min(l, r); }
using F = pll; // {add, set}
F id() { return {0, inf}; }
F composition(F g, F f) {
	if (g.second != inf) return g;
	if (g.first) {
		(f.second == inf ? f.first : f.second) += g.first;
	}
	return f;
}
S mapping(F lz, S v) {
	if (lz.second != inf) return lz.second;
	if (lz.first) v += lz.first;
	return v;
}


struct lazy_segtree {
  int n, size, log;
  vector<S> d;
  vector<F> lz;
  lazy_segtree(size_t nn): n(nn), size(bit_ceil(nn)),
    log(__lg(size)), d(2*size, e()), lz(size, id()) {}

  void pull(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
  void apply(int k, F f) {
    d[k] = mapping(f, d[k]);
    if (k < size) lz[k] = composition(f, lz[k]);
  }
  void push(int k) {
    apply(2 * k, lz[k]);
    apply(2 * k + 1, lz[k]);
    lz[k] = id();
  }
  void set(int p, S x) {
    p += size;
    for (int i = log; i >= 1; i--) push(p >> i);
    d[p] = x;
    rep(i, 1, log+1) pull(p >> i);
  }
  #define check(p) { if (((1<<i) - 1) & l) p(l >> i);\
              if (((1<<i) - 1) & r) p((r - 1) >> i); }
  S query(int l, int r) {
    l += size, r += size;
    for (int i = log; i >= 1; i--) check(push);
    S sml = e(), smr = e();
    while (l < r) {
      if (l & 1) sml = op(sml, d[l++]);
      if (r & 1) smr = op(d[--r], smr);
      l /= 2, r /= 2;
    }
    return op(sml, smr);
  }
  void update(int l, int r, F f) {
    l += size, r += size;
    for (int i = log; i >= 1; i--) check(push);
    int l2 = l, r2 = r;
    while (l < r) {
      if (l & 1) apply(l++, f);
      if (r & 1) apply(--r, f);
      l /= 2, r /= 2;
    }
    l = l2, r = r2;
    rep(i, 1, log+1) check(pull);
  }

  int max_right(int l, auto g) {
    l += size;
    for (int i = log; i >= 1; i--) push(l >> i);
    S sm = e();
    do {
      while (l % 2 == 0) l >>= 1;
      if (!g(op(sm, d[l]))) {
        while (l < size) {
          push(l);
          if (g(op(sm, d[l *= 2]))) sm = op(sm, d[l++]);
        }
        return l - size;
      }
      sm = op(sm, d[l++]);
    } while ((l & -l) != l);
    return n;
  }
  int min_left(int r, auto g) {
    r += size;
    for (int i = log; i >= 1; i--) push((r - 1) >> i);
    S sm = e();
    do {
      r--;
      while (r > 1 && (r % 2)) r /= 2;
      if (!g(op(d[r], sm))) {
        while (r < size) {
          push(r);
          if (g(op(d[r = 2*r+1], sm))) sm = op(d[r--], sm);
        }
        return r + 1 - size;
      }
      sm = op(d[r], sm);
    } while ((r & -r) != r);
    return 0;
  }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        vi a(n);
        rep(i, 0, n) {cin >> a[i]; a[i]--; }
        vl cold(k), hot(k);
        rep(i, 0, k) cin >> cold[i];
        rep(i, 0, k) cin >> hot[i];
		lazy_segtree tree(k+1);
		tree.set(k, 0);
        // Node tree(0, k+1);
        // tree.set(k, k+1, 0);
        rep(i, 0, n){
            ll mn = tree.query(0, k+1);
            ll mnsame = tree.query(a[i], a[i]+1);
            tree.update(0, k+1, pll{i == 0 || a[i] != a[i-1] ? cold[a[i]] : hot[a[i]], inf});
            int prv = i == 0 ? k : a[i-1];
            tree.set(prv, min({mn + cold[a[i]], mnsame + hot[a[i]], tree.query(prv, prv+1)}));
        }
        cout << tree.query(0, k+1) << "\n";
    }
    return 0;
}
