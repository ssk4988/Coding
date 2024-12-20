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

const ll mod = 924844033;
// const ll mod = 998244353;

// 441 << 21 + 1

ll root = 62;
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


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // root = modpow()
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n-1){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vl freq(n+1);
    freq[n] = n;
    auto dfs = [&](int u, int p, auto &&dfs) -> int {
        int subsz = 1;
        for(int v : adj[u]) if(v != p) {
            int sub = dfs(v, u, dfs);
            freq[sub]--;
            subsz += sub;
        }
        freq[n - subsz]--;
        return subsz;
    };
    dfs(0, -1, dfs);
    vl fact(n+1);
    fact[0] = 1;
    rep(i, 1, sz(fact)){
        fact[i] = i * fact[i-1] % mod;
    }
    vl a(n+1);
    vl b(n+1);
    freq[0] = 0;
    rep(i, 0, sz(a)){
        a[i] = fact[i] * freq[i] % mod;
        b[n - i] = modpow(fact[i], mod-2);
    }
    vl c = conv(a, b);
    c.erase(begin(c), n + begin(c));
    rep(i, 1, n+1){
        (c[i] *= modpow(fact[i], mod-2)) %= mod;
        c[i] = (c[i] % mod + mod) % mod;
        cout << c[i] << "\n";
    }


    return 0;
}
