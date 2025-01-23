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

const ll mod = (119 << 23) + 1, root = 62; // = 998244353
ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<ll> vl;
void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, modpow(root, mod >> s)};
		rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? mod : 0);
			ai += (ai + z >= mod ? z - mod : z);
		}
}
vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s),
	    n = 1 << B;
	int inv = modpow(n, mod - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i,0,n)
		out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}

vl operator*(vl a, vl b){
    vl res = conv(a, b);
    return res;
}

vl reciprocal(vl p, int lim) {
    vl x(1);
    x[0] = modpow(p[0], mod-2);
    for(int len = 1; len < lim; len *= 2) {
        vl x2 = x * x * p;
        x2.resize(len * 2);
        x.resize(len * 2);
        rep(i, 0, sz(x)) {
            x[i] = 2 * x[i] - x2[i];
            x[i] = (x[i] % mod + mod) % mod;
        }
    }
    return x;
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vl p(n+1);
    vl q(n+1);
    vl fact(n+1, 1);
    rep(i, 1, n+1) fact[i] = fact[i-1] * i % mod;
    rep(i, 0, n+1){
        int v = k * i;
        if(v <= n) {
            q[v] = (i&1 ? -1 : 1) * modpow(fact[v], mod-2);
            (q[v] += mod) %= mod;
        }
        v = k * i + (n % k);
        if(v <= n) {
            p[v] = (i&1 ? -1 : 1) * modpow(fact[v], mod-2);
            (p[v] += mod) %= mod;
        }
    }
    // ll fact = 1;
    // rep(i, 0, n+1){
    //     if(i % k == n % k){
    //         p[i] = modpow(fact, mod-2) * ((i / k) & 1 ? -1 : 1);
    //         p[i] = (p[i] + mod) % mod;
    //     }
    //     if(i % k == 0) {
    //         q[i] = modpow(fact, mod-2) * ((i / k) & 1 ? -1 : 1);
    //         q[i] = (q[i] + mod) % mod;
    //     }
    //     (fact *= i+1) %= mod;
    // }
    vl res = p * reciprocal(q, 3*n+1);
    cout << (modpow(res[n], mod-2)+mod-1)%mod << "\n";
    // rep(i,0 , sz(res)) {
    //     cout << i << " " << res[i] << "\n";
    // }
    return 0;
}
