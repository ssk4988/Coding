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

const ll MOD = 998244353;

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % MOD, e /= 2)
		if (e & 1) ans = ans * b % MOD;
	return ans;
}

void FST(vl& a, bool inv) {
	for (int n = sz(a), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
			auto &u = a[j], &v = a[j + step]; tie(u, v) =
				inv ? pl(u - v, v) : pl(u + v, v); // AND
				// inv ? pl(v, u - v) : pl(u + v, u); // OR /// include-line
				// pl(v - u, v + u);                   // XOR /// include-line
            u %= MOD, v %= MOD;
		}
	}
	// if (inv) for (auto& x : a) x /= sz(a); // XOR only /// include-line
}
vl conv(vl a, vl b) {
	FST(a, 0); FST(b, 0);
	rep(i,0,sz(a)) a[i] *= b[i];
	FST(a, 1); 
    // ll invn = modpow(sz(a), MOD-2);
    // rep(i, 0, sz(a)) (a[i] *= invn) %= MOD;
    rep(i, 0, sz(a)) (a[i] += MOD) %= MOD;
    // reverse(all(a));
    return a;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl a(1 << n), b(1 << n);
    rep(i, 0, sz(a)) cin >> a[i];
    rep(i, 0, sz(b)) cin >> b[i];
    vl c = conv(a, b);
    rep(i, 0, sz(c)) cout << c[i] << " ";
    cout << "\n";
    return 0;
}
