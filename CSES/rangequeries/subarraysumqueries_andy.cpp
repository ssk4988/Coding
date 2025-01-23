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

struct S {
    ll sum = 0, pref=0, suff=0, ans=0;
    S(ll v=0) {
        // v = max(v, 0LL);
        sum = pref = suff = ans = v;
    }
};

S e() {return S(); }

S op(S l, S r) {
    S res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max(max(l.ans, r.ans), l.suff + r.pref);
    return res;
}

using F = int;
S mapping(F lz, S v) {
	return v;
}
F composition(F a, F b) { return a; }
F id() {return 1; }

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
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    lazy_segtree tree(n);
    rep(i, 0, n) tree.set(i, S(a[i]));

    rep(i, 0, m){
        int k, x; cin >> k >> x; k--;
        tree.set(k, x);
        cout << max(0LL, tree.query(0, n).ans) << nL;
    }



    
    return 0;
}
