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

typedef complex<double> C;
// typedef vector<double> vd;
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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, p; cin >> n >> p;
    string str; cin >> str;
    vi a(n);
    rep(i, 0, n){
        if(str[i] == 'B') a[i] = 1;
        if(str[i] == 'Y') a[i] = 2;
        if(str[i] == 'R') a[i] = 3;
    }
    vd a1(n), a2(2 * n);
    vi craziness(n, n);
    // IGNORE i = 0
    rep(t, 0, 3){
        rep(i, 0, n) a1[i] = (a[i] == t + 1);
        // rep(i, 0, n) a1[n + i] = a1[i];
        rep(i, 0, n){
            a2[i] = a1[n - 1 - i];
        }
        rep(i, n, 2 * n){
            a2[i] = a2[i - n];
        }
        vd res = conv(a1, a2);
        // rep(i, 0, sz(a)){
        //     cout << a1[i] << " ";
        // }
        // cout << nL;
        // rep(i, 0, sz(a2)) cout << a2[i] << " ";
        // cout << nL;
        // rep(i, 0, sz(res)){
        //     cout << int(res[i] + 0.1) << " " ;
        // }
        // cout << nL;
        rep(i, 1, n){
            craziness[i] -= int(res[2 * n - 1 - i] + 0.1);
        }
    }
    vector<vi> order(n + 1);
    rep(i, 1, n){
        order[craziness[i]].pb(i);
    }
    int idx = -1, cnt = 0;
    rep(i, 0, sz(order)){
        if(cnt + sz(order[i]) >= p){
            idx = i;
            break;
        }
        cnt += sz(order[i]);
        // cout << order[i].f << " " << order[i].s << nL;
    }
    cout << order[idx][0] << nL;

    
    return 0;
}
