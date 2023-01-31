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

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		k *= -1;
        m *= -1;
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
    int n, k; cin >> n >> k;
    vvi grid(n, vi(n));
    vector<vpl> val(k + 1);
    rep(i, 0, n){
        rep(j, 0, n){
            cin >> grid[i][j];
            val[grid[i][j]].pb({i, j});
        }
    }
    LineContainer r, c;
    r.add(0, 0);
    c.add(0, 0);
    ll minans = LLONG_MAX;
    // check k == 1
    rep(i, 1, k + 1){
        minans = LLONG_MAX;
        LineContainer newR, newC;
        if(val[i].size() <= 0 || (r.empty() || c.empty())){
            minans = -1;
            break;
        }
        for(auto &p : val[i]){
            ll dp = min((i > 1 ? p.f * p.f : 0) + r.query(p.f), (i > 1 ? p.s * p.s : 0) + c.query(p.s));
            minans = min(minans, dp);
            newR.add(-2 * p.f, p.f * p.f + dp);
            newC.add(-2 * p.s, p.s * p.s + dp);
        }
        r = newR, c = newC;
        // cout << i << " " << minans << nL;
    }
    cout << minans << nL;
    
    
    return 0;
}
