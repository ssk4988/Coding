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

struct WaveletTree {
	int n; vvi bv; // vector<BitVector> bv;
	WaveletTree(vl a, ll max_val):
		n(sz(a)), bv(1+__lg(max_val), {{}}) {
		vl nxt(n);
		for (int h = sz(bv); h--;) {
			vector<bool> b(n);
			rep(i, 0, n) b[i] = ((a[i] >> h) & 1);
			bv[h] = vi(n+1); // bv[h] = b;
			rep(i, 0, n) bv[h][i+1] = bv[h][i] + !b[i]; // delete
			array it{begin(nxt), begin(nxt) + bv[h][n]};
			rep(i, 0, n) *it[b[i]]++ = a[i];
			swap(a, nxt);
		}
	}
	ll kth(int l, int r, int k) {
		ll res = 0;
		for (int h = sz(bv); h--;) {
			int l0 = bv[h][l], r0 = bv[h][r];
			if (k < r0 - l0) l = l0, r = r0;
			else
				k -= r0 - l0, res |= 1ULL << h,
					l += bv[h][n] - l0, r += bv[h][n] - r0;
		}
		return res;
	}
	int count(int l, int r, ll ub) {
		int res = 0;
		for (int h = sz(bv); h--;) {
			int l0 = bv[h][l], r0 = bv[h][r];
			if ((~ub >> h) & 1) l = l0, r = r0;
			else
				res += r0 - l0, l += bv[h][n] - l0,
					r += bv[h][n] - r0;
		}
		return res;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    WaveletTree wt(a, 1e9);
    rep(i, 0, q) {
        int l, r, lo, hi; cin >> l >> r >> lo >> hi; l--; hi++;
        cout << wt.count(l, r, hi)-wt.count(l, r, lo) << "\n";
    }
    
    return 0;
}
