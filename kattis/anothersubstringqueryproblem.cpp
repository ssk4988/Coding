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

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string s, int lim=256) { // or vector<int>
		s.push_back(0); int n = sz(s), k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

struct BitVector {
	vector<pair<ll, int>> b;
	BitVector(vector<bool> a): b(sz(a) / 64 + 1) {
		rep(i, 0, sz(a))
			b[i >> 6].first |= ll(a[i]) << (i & 63);
		rep(i, 0, sz(b)-1)
			b[i + 1].second = __builtin_popcountll(b[i].first) 
				+ b[i].second;
	}
	int cnt0(int r) {
		auto [x, y] = b[r >> 6];
		return r - y 
			- __builtin_popcountll(x & ((1ULL << (r & 63)) - 1));
	}
};

struct WaveletTree {
	int n; vector<BitVector> bv;
	WaveletTree(vl a, ll max_val):
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
    string s; cin >> s;
    int n = sz(s);
    SuffixArray sa(s);
    vl a;
    for(auto v : sa.sa) a.pb(v);
    WaveletTree wt(a, n);
    int q; cin >> q;
    rep(qid, 0, q) {
        string t; cin >> t;
        int l = -1;
        for(int dif = 1 << 20; dif; dif /= 2) {
            if(l+dif < sz(a) && s.substr(a[l+dif], sz(t)+1) < t) l += dif;
        }
        l++;
        int r = -1;
        for(int dif = 1 << 20; dif; dif /= 2) {
            if(r+dif < sz(a) && s.substr(a[r+dif], sz(t)) <= t) r += dif;
        }
        r++;
        int k; cin >> k;
        k--;
        int cnt = wt.count(l, r, n);
        if(k >= cnt) cout << -1 << "\n";
        else cout << wt.kth(l, r, k)+1 << "\n";
    }
    
    return 0;
}
