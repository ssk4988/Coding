#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("trapv")

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


vl operator-(vl a, vl b) {
    vl c(max(sz(a), sz(b)));
    rep(i, 0, sz(c)){
        if(i < sz(a)) c[i] = a[i];
        // if(i < sz(b)) (c[i] -= b[i]) %= mod;
        if(i < sz(b)) c[i] = ((c[i] - b[i]) % mod + mod) % mod;
    }
    return c;
}

vl operator+(vl a, vl b) {
    vl c(max(sz(a), sz(b)));
    rep(i, 0, sz(c)){
        if(i < sz(a)) c[i] = a[i];
        if(i < sz(b)) (c[i] += b[i]) %= mod;
    }
    return c;
}

vl operator*(vl a, ll c) {
    for(ll &v : a){
        (v *= c) %= mod;
    }
    return a;
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

vl psqrt(vl p, int lim) {
    vl x(1);
    assert(p[0] <= 1 && p[0] >= 0);
    x[0] = p[0];
    for(int len = 1; len < lim; len *= 2) {
        vl x2 = p * reciprocal(x, len);
        x.resize(len * 2);
        x2.resize(len * 2);
        rep(i, 0, sz(x)){
            (x[i] += x2[i]) %= mod;
            (x[i] *= 499122177) %= mod;
        }
    }
    return x;
}
const int W = 1e5 + 10;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vl c(W);
    rep(i, 0, n) {
        int v; cin >> v; c[v]++;
    }
    vl denom(sz(c));
    denom[0] = 1;
    rep(i, 0, sz(c)){
        denom[i] -= 4 * c[i];
        denom[i] = (denom[i] % mod + mod) % mod;
    }
    denom = psqrt(denom, 2 * m + 5);
    (denom[0] += 1) %= mod;
    vl res = reciprocal(denom, 2 * m + 5);
    for(ll &v : res){
        (v *= 2) %= mod;
    }
    rep(i, 1, m+1){
        cout << res[i] << "\n";
    }
    
    return 0;
}
