// it would be super funny if this works
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
        k *= -1, m *= -1;
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return -(l.k * x + l.m);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vi h(n);
    rep(i, 0, n) cin >> h[i];
    vi ord(n);
    iota(all(ord), 0);
    ranges::sort(ord, ranges::less{}, [&](int i) { return pii{h[i], i}; });
    LineContainer lc;
    // (nxt - (prv+1))^2 = nxt^2 - 2 * nxt * (prv+1) + (prv+1)^2
    lc.add(0, 0);
    for(ll i : ord) {
        ll val = lc.query(i) + i * i;
        lc.add(-2 * (i+1), (i+1)*(i+1) + val);
    }
    ll ans = lc.query(n) + ll(n)*n;
    cout << ans << "\n";

    
    
    return 0;
}
