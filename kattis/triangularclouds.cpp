#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const ll mod = 1e9+9, base = 29;

ll modpow(ll b, ll e) {
	ll res = 1;
	b %= mod;
	for(; e; (b *= b) %= mod, e /= 2)
		if(e&1) (res *= b) %= mod;
	return res;
}

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
};

using P = Point<ll>;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	ll inv2 = modpow(2, mod-2), inv3 = modpow(3, mod-2), inv4 = modpow(4, mod-2);
	auto eval = [&](ll x, ll c, ll d) -> ll {
		ll c2x3 = modpow(c, 2) * modpow(x, 3) % mod * inv3 % mod;
		ll cdx2 = c * d % mod * modpow(x, 2) % mod;
		ll d2x = modpow(d, 2) * x % mod;
		ll interior = (c2x3+cdx2+d2x)%mod * inv2 % mod * base % mod;
		ll xy = (modpow(c, 2) * modpow(x, 4) % mod * inv4 % mod + 2 * c * d % mod * modpow(x, 3) % mod * inv3 % mod + modpow(d, 2) * modpow(x, 2) % mod * inv2 % mod) % mod * inv2 % mod;
		ll exterior2 = (c * modpow(x, 4) % mod * inv4 % mod + d * modpow(x, 3) % mod * inv3 % mod) % mod;
		return (interior + exterior2 + xy) % mod;
	};
	auto line = [&](ll a, ll b, ll c, ll d) -> ll {
		return (eval(b, c, d) - eval(a, c, d)) % mod;
	};
	ll res = 0;
	rep(t, 0, 2) {
		int n; cin >> n;
		ll ans = 0;
		rep(_, 0, n) {
			vector<P> tri(3);
			rep(j, 0, 3) cin >> tri[j].x >> tri[j].y;
			if(tri[0].cross(tri[1], tri[2]) < 0) swap(tri[1], tri[2]);
			assert(tri[0].cross(tri[1], tri[2]) >= 0);
			ll tans = 0;
			rep(i, 0, 3) {
				int j = (i+1)%3;
				if(tri[i].x == tri[j].x) continue;
				P dif = tri[j] - tri[i];
				ll slope = dif.y * modpow(dif.x, mod-2) % mod;
				ll intercept = (tri[i].y - slope * tri[i].x) % mod;
				(tans += line(tri[i].x, tri[j].x, slope, intercept)) %= mod;
			}
			// cerr << "tri: " << tans << endl;
			(ans += tans) %= mod;
		}
		(res += ans * (t == 0 ? 1 : -1)) %= mod;
		// cerr << ans << endl;
	}
	res = (res % mod + mod) % mod;
	// cerr << res << "\n";
	cout << (res == 0 ? "yes" : "no") << "\n";
	// cerr << (line(0, 1, 0, 3) + line(0, 1, 0, 2))%mod << " " << line(0, 1, 0, 5) << endl;
	return 0;
}
