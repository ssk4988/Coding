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
int mod = 997;
int maxval = 50001;
vl mult(vl &a, vl &b){
	vd a1(all(a)), b1(all(b));
	vd res = conv(a1, b1);
	res.resize(maxval);
	vl intres(sz(res));
	rep(i, 0, sz(res)){
		intres[i] = ll(round(res[i]) + 0.1);
		intres[i] %= 997;
	}
	return intres;
}

int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    int nc; cin >> nc;
	rep(cn, 0, nc){
		int n; cin >> n;
		vl freq(maxval);
		rep(i, 0, n){
			ld v; cin >> v;
			int v1 = int(round(v * 100) + 0.1);
			freq[v1]++;
		}
		// freq.assign(maxval, 996);
		// vi res = mult(freq, freq);
		// rep(i, 0, sz(res)){
		// 	if(res[i] > 0) cout << i << nL;
		// }
		auto solve = [&](int k, auto &&solve) -> vl{
			if(k == 1) return freq;
			vl res = solve(k / 2, solve);
			res = mult(res, res);
			if(k % 2 == 1){
				res = mult(res, freq);
			}
			return res;
		};
		int k, q; cin >> k >> q;
		vl kfreq = solve(k, solve);
		rep(i, 0, q){
			ld v; cin >> v;
			int v1 = int(round(v * 100) + 0.1);
			cout << kfreq[v1] << nL;
		}
		cout << nL;
	}

    return 0;
}
