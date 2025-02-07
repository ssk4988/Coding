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

vl differentiate(vl p) {
    if(sz(p) <= 1) return {0};
    vl res(sz(p)-1);
    rep(i, 1, sz(p)) res[i-1] = p[i] * i % mod;
    return res;
}

vl integrate(vl p) {
    vl res(sz(p)+1);
    rep(i, 0, sz(p)) {
        res[i+1] = p[i] * modpow(i+1, mod-2) % mod;
    }
    return res;
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
    assert(p[0] != 0);
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

vl ln(vl p, int lim) {
    vl diff = differentiate(p);
    diff = diff * reciprocal(p, lim);
    diff.resize(lim);
    return integrate(diff);
}

vl exp(vl p, int lim) {
    vl x{1};
    p[0]++;
    for(int len = 1; len < lim; len *= 2) {
        vl term = ln(x, len);
        rep(i, 0, len) term[i] = (mod - term[i]) % mod;
        rep(i, 0, min(sz(p), sz(term))) (term[i] += p[i]) %= mod;
        x = x * term;
        x.resize(len*2);
    }
    x.resize(lim);
    return x;
}

ll nc2(ll n) {
    return n * (n-1) / 2;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int m, k; cin >> m >> k;
    vl a(k+1);
    rep(i, 0, k+1) cin >> a[i];
    vl fact(m+1);
    vl ifact(m+1);
    fact[0] = ifact[0] = 1;
    rep(i, 1, m+1) {
        fact[i] = fact[i-1] * i % mod;
        ifact[i] = ifact[i-1] * modpow(i, mod-2) % mod;
    }

    vl ans(m+1);
    if(k == 0) {
        rep(i, 2, m+1) {
            (ans[i] += modpow(a[0], nc2(i))) %= mod;
            cout << ans[i] << " ";
        }
        cout << endl;
        return 0;
    }

    vl tree_contribution(m+1);
    tree_contribution[1] = 1;
    rep(i, 2, m+1) {
        ll base = a[1] * modpow(a[0], mod-2) % mod;
        tree_contribution[i] = modpow(base, nc2(i))
            * ifact[i] % mod * modpow(i, i-2) % mod;
    }
        // vl exp_tree = exp(tree_contribution, 2*m+1);
        // vl unexp_tree(exp_tree);
        // if(k == 1) {
        //     rep(i, 1, m+1) {
        //         (unexp_tree[i] *= fact[i]) %= mod;
        //         // cout << unexp_tree[i] << " ";
        //         (ans[i] += modpow(a[0], nc2(i)) * unexp_tree[i]) %= mod;
        //     }
        // }
        // cout << endl;
    // }
    // cerr << "before k=2: ";
    // rep(i, 2, m+1) cerr << ans[i] << " ";
    // cerr << endl;
    if(k >= 2) {
        // r[i] = number of rooted trees of i+1 nodes where root is 0
        vl rooted_1(m+1);
        rooted_1[0] = 1;
        rep(i, 1, m+1) {
            // rooted_1[i] = modpow(i+1, i-1) * ifact[i] % mod;
        }
        for(int i = m; i > 0; i--) {
            ll base = a[1] * modpow(a[2], mod-2) % mod; // rooted 1-components have 1 path, not 2
            rooted_1[i] = modpow(i, i-1) * ifact[i] % mod * modpow(base, nc2(i)) % mod;
        }
        rooted_1[0] = 0;
        vl unicycle(m+1);
        unicycle[0] = 1;
        rep(i, 1, m+1) {
            unicycle[i] = (unicycle[i] - rooted_1[i] + mod) % mod;
        }
        unicycle = ln(unicycle, 2 * m+1);
        vl rooted2 = rooted_1 * rooted_1;
        rep(i, 1, m+1){
            (unicycle[i] *= modpow(mod-2, mod-2)) %= mod;
            (unicycle[i] += mod - modpow(4, mod-2) * rooted2[i] % mod) %= mod;
            (unicycle[i] += mod - rooted_1[i] * modpow(2, mod-2) % mod);
        }
        // unicycle = unicycle - 
        // unicycle = unicycle - rooted_1 * rooted_1 * modpow(4, mod-2) - rooted_1 * modpow(2, mod-2);
        // rep(i, 0, 3) unicycle[i] = 0;
        // cerr << "unicycle plus:";

        vl uni_and_tree(m+1);
        rep(i, 2, m+1){
            ll base = a[2] * modpow(a[0], mod-2) % mod;
            (unicycle[i] *= modpow(base, nc2(i))) %= mod;
            (tree_contribution[i] += unicycle[i]) %= mod;
            // uni_and_tree[i] = (unicycle[i] + tree_contribution[i]) % mod;
        }

    }
    vl exp_2 = exp(tree_contribution, 2*m+1);
    vl unexp_2(exp_2);

    rep(i, 2, m+1) {
        (unexp_2[i] *= fact[i]) %= mod;
        // cerr << unexp_2[i] << " ";
        (ans[i] += modpow(a[0], nc2(i)) * unexp_2[i]) %= mod;
    }
    cerr << endl;

    rep(i, 2, m+1){
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
