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

using int128 = __int128_t;

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX-5;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};
using ull = unsigned long long;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ll m; cin >> n >> m;
    set<ll> crossover;
    vl a(n), da(n), b(n), db(n);
    rep(i, 0, n){
        cin >> a[i] >> da[i] >> b[i] >> db[i];
    }
    crossover.insert(0);
    crossover.insert(m + 1);
    rep(i, 0, n){
        if(da[i] != db[i]){
            ll inter = (a[i] - b[i]) / (db[i] - da[i]);
            if(inter >= 0 && inter <= m) crossover.insert(inter);
            if(inter + 1 >= 0 && inter + 1 <= m) crossover.insert(inter + 1);
            if(inter - 1 >= 0 && inter - 1 <= m) crossover.insert(inter - 1);
        }
        rep(j, i + 1, n){
            ll di = db[i] - da[i], dj = db[j] - da[j], vi = b[i] - a[i], vj = b[j] - a[j];
            if(di == dj) continue;
            ll inter = (vi - vj) / (dj - di);
            if(inter >= 0 && inter <= m) crossover.insert(inter);
            if(inter + 1 >= 0 && inter + 1 <= m) crossover.insert(inter + 1);
            if(inter - 1 >= 0 && inter - 1 <= m) crossover.insert(inter - 1);
        }
    }
    vl events;
    for(auto v : crossover) events.pb(v);
    ull ans = 0;
    rep(i, 0, sz(events) - 1){
        int128 t = events[i];
        cout << events[i] << " to " << events[i + 1] << nL;
        int128 dt = events[i + 1] - t;
        vi order;
        rep(j, 0, n) order.pb(j);
        sort(all(order), [&](int v1, int v2)-> bool {
            int s1 = ((db[v1] - da[v1]) * t - (b[v1] - a[v1])) < 0, s2 = ((db[v2] - da[v2]) * t - (b[v2] - a[v2])) < 0;
            if(s1 != s2) return s1 < s2;
            if(s1){
                return a[v1] + da[v1] * t < a[v2] + da[v2] * t;
            }
            else return b[v1] + db[v1] * t > b[v2] + db[v2] * t;
        });
        ll curv = 0, curd = 0;
        LineContainer lc;
        for(int j : order){
            curv -= a[j], curd -= da[j];
            lc.add(-curd, -curv);
            cout << "line: " << curd << " " << curv << nL;
            curv += b[j], curd += db[j];
        }
        lc.add(0, 0);
        ll prevt = t;
        for(Line l : lc){
            // cout << l.p << " ";
            ll nextt = max(prevt, min(events[i + 1], l.p + 1));
            cout << "T: " << prevt << " " << nextt << " " << l.p << nL;
            ull dift = nextt - prevt;
            ull v1 = ull(prevt) * ull(l.k) + ull(l.m);
            ull cont = v1 * dift;
            ull tri = (dift % 2 == 0 ? dift / 2 * (dift - 1) : ((dift - 1) / 2) * dift);
            cont = cont + tri * ull(l.k);
            // cont -= dift;
            cout << cont << nL;
            ans += cont;
            prevt = nextt;
        }
        cout << nL;
    }
    cout << ans << nL;
    return 0;
}
