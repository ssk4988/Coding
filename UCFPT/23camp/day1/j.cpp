#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
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

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll) M);
}

ull modpow(ull b, ull e, ull mod){
    ull ans = 1;
    for(; e; b = modmul(b, b, mod), e /= 2){
        if(e & 1) ans = modmul(ans, b, mod);
    }
    return ans;
}

bool isPrime(ull n) {
    if(n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
        s = __builtin_ctzll(n - 1), d = n >> s;
    for(ull a : A) {
        ull p = modpow(a % n, d, n), i = s;
        while(p != 1 && p != n - 1 && a % n && i--){
            p = modmul(p, p, n);
        }
        if(p != n - 1 && i != s) return 0;
    }
    return 1;
}

ull pollard(ull n){
    auto f = [n](ull x) { return modmul(x, x, n) + 1; };
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while(t++ % 40 || __gcd(prd, n) == 1) {
        if(x==y) x = ++i, y = f(x);
        if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}
vector<ull> factor(ull n){
    if(n == 1) return {};
    if(isPrime(n)) return {n};
    ull x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}
vi curp, ps, es, factors;
void getFactors (int idx, int fa){
    // if(idx == sz(curp)) return;
    if(curp[idx] >= es[idx]){
        idx++;
    }
    factors.pb(fa);
    for(int j = idx; j < sz(curp); j++){
        curp[j]++;
        getFactors(j, fa * ps[j]);
        curp[j]--;
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, x, y; cin >> n >> x >> y;n++;
    int LIM = 2e5 + 10;
    vi freq(LIM);
    rep(i, 0, n){
        int v; cin >> v;
        freq[v]++;
    }
    vi freqrev(freq);
    reverse(all(freq));
    vd fr(all(freq)), frr(all(freqrev));
    vd res = conv(fr, frr);
    vi resr(sz(res));
    vi freqans(LIM);
    rep(i, 0, sz(res)){
        resr[i] = int(round(res[i]) + 0.1);
        if(resr[i] > 0){
            // cout << (LIM - 1 - i) << " " << resr[i] << nL;
            int i1 = LIM - 1 - i;
            if(i1 >= 0 && i1 < LIM) freqans[i1] = resr[i];
        }
    }
    
    
    int q; cin >> q;
    rep(i, 0, q){
        int v; cin >> v;
        vector<ull> fs = factor(v);
        unordered_map<int, int> ffreq;
        for(ull j : fs){
            ffreq[int(j)]++;
        }
        factors.clear();ps.clear();es.clear();
        int ans = -1;
        for(auto &p : ffreq){
            ps.pb(p.f);es.pb(p.s);
        }
        if(sz(ps) == 0){
            ps.pb(1);
            es.pb(0);
        }
        curp.clear();
        curp.resize(sz(es));
        getFactors(0, 1);
        sort(all(factors));
        for(int k : factors){
            if(k % 2 != 0) continue;
            int k1 = k / 2;
            k1 -= y;
            if(k1 > 0 && k1 < sz(freqans) && freqans[k1] > 0 && k > ans){
                ans = k;
            }
        }
        cout << ans << " ";
    }
    cout << nL;

    
    
    return 0;
}