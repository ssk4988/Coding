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

struct BitVector {
	vector<pair<ll, int>> b;
    BitVector() {}
	BitVector(vector<bool> a): b(sz(a) / 64 + 1) {
		rep(i, 0, sz(a))
			b[i >> 6].first |= ll(a[i]) << (i & 63);
		rep(i, 0, sz(b)-1)
			b[i + 1].second = __builtin_popcountll(b[i].first) 
				+ b[i].second;
	}
	int cnt1(int r) {
		auto [x, y] = b[r >> 6];
		return y 
			+ __builtin_popcountll(x & ((1ULL << (r & 63)) - 1));
	}
    int operator[](int r) { return cnt1(r); }
};

struct wt {
    ll lo, hi;
    wt *l, *r;
    // vi b;
    BitVector b;
    // values are in range [lo, hi]
    wt(vl a, ll lo, ll hi) : wt(all(a), lo, hi) {}
    wt(vl::iterator from, vl::iterator to, ll lo, ll hi) : lo(lo), hi(hi) {
        if(lo == hi || from == to) return;
        ll mid = (lo+hi)/2;
        auto f = [mid](ll x){ return x <= mid; };
        vector<bool> b2(to-from);
        transform(from, to, begin(b2), f);
        b = b2;
        // b.reserve(to-from+1); b.push_back(0);
        // for(auto it = from; it != to; it++)
        //     b.push_back(b.back() + f(*it));
        auto pivot = stable_partition(from, to, f);
        l = new wt(from, pivot, lo, mid);
        r = new wt(pivot, to, mid+1, hi);
    }

    // kth smallest element in [L, R)
    ll kth(int L, int R, int k){
        if(L >= R) return 0;
        if(lo == hi) return lo;
        int inLeft = b[R] - b[L];
        if(k <= inLeft) return l->kth(b[L], b[R], k);
        return r->kth(L-b[L], R-b[R], k-inLeft);
    }
 
    // count a[i] < k for i in [L, R)
    int rank(int L, int R, ll k) {
        if(L >= R || k <= lo) return 0;
        if(hi < k) return R - L;
        return l->rank(b[L], b[R], k) + r->rank(L-b[L], R-b[R], k);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    wt m(a, 0, 1000000000);
    rep(i, 0, q) {
        int l, r, k; cin >> l >> r >> k;
        cout << m.kth(l, r, k+1) << "\n";
    }
    
    return 0;
}
