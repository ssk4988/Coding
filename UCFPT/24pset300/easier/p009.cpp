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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)


struct Line {
	mutable ld k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ld x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	ld inf = 1/.0L;
	ld div(ld a, ld b) { // floored division
        return a/b; }
		// return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ld k, ld m) {
        k *= -1; m *= -1;
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ld query(ld x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return -(l.k * x + l.m);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int sreg, treg, n; cin >> sreg >> treg >> n;
    ld start = log2l(sreg), target = log2l(treg);
    vii blades(n);
    rep(i, 0, n){
        int m, h; cin >> m >> h;
        blades[i].f = m;
        blades[i].s = h;
    }
    sort(all(blades));
    reverse(all(blades));
    if(blades[0].f < sreg){
        cout << -1 << "\n";
        return 0;
    }
    // if can get log of a with cost c, then blade with cost h will get you x with cost of c + (a-x) * h = -h * x + c + h * a
    LineContainer lc;
    for(auto [al, h] : blades){
        ld a = log2l(al);
        if(al >= sreg){
            lc.add(-h, h*start);
        } else if(sz(lc) && al >= treg) {
            ld c = lc.query(a);
            lc.add(-h, c + h * a);
        }
    }
    ld ans = lc.query(target);
    cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}
