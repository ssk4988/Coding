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

struct bit_vec {
  vector<pair<ll, int>> b;
  bit_vec(vector<bool> a): b(sz(a) / 64 + 1) {
    rep(i, 0, sz(a))
      b[i >> 6].first |= ll(a[i]) << (i & 63);
    rep(i, 0, sz(b)-1)
      b[i + 1].second = __builtin_popcountll(b[i].first) + b[i].second;
  }
  int cnt0(int r) {
    auto [x, y] = b[r >> 6];
    return r - y - __builtin_popcountll(x & ((1ULL << (r & 63)) - 1));
  }
};
struct wavelet_matrix {
  int n; vector<bit_vec> bv;
  wavelet_matrix(vl a, ll max_val):
    n(sz(a)), bv(1+__lg(max_val), {{}}) {
    vl nxt(n);
    for (int h = sz(bv); h--;) {
      vector<bool> b(n);
      rep(i, 0, n) b[i] = ((a[i] >> h) & 1);
      bv[h] = b;
      array it{begin(nxt), begin(nxt) + bv[h].cnt0(n)};
      rep(i, 0, n) *it[b[i]]++ = a[i];
      swap(a, nxt);
    }
  }
  ll kth(int l, int r, int k) {
    ll res = 0;
    for (int h = sz(bv); h--;) {
      int l0 = bv[h].cnt0(l), r0 = bv[h].cnt0(r);
      if (k < r0 - l0) l = l0, r = r0;
      else
        k -= r0 - l0, res |= 1ULL << h,
          l += bv[h].cnt0(n) - l0, r += bv[h].cnt0(n) - r0;
    }
    return res;
  }
  int count(int l, int r, ll ub) {
    int res = 0;
    for (int h = sz(bv); h--;) {
      int l0 = bv[h].cnt0(l), r0 = bv[h].cnt0(r);
      if ((~ub >> h) & 1) l = l0, r = r0;
      else
        res += r0 - l0, l += bv[h].cnt0(n) - l0,
          r += bv[h].cnt0(n) - r0;
    }
    return res;
  }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vector<ll> a(n);
    rep(i, 0, n) cin >> a[i];
    wavelet_matrix m(a, 1000000000);
    rep(i, 0, q) {
        int l, r, k; cin >> l >>r >> k;
        cout << m.kth(l, r, k) << "\n";
    }
    
    return 0;
}
