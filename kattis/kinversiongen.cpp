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

using cd = complex<ld>;
const double PI = acos(-1);

typedef complex<double> C;
typedef vector<double> vd;
void fft1(vector<C>& a) {
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
	fft1(in);
	for (C& x : in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft1(out);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

vi kactlfft(string s1){
    int n = s1.length();
    vector<double> a(n), b(n);
    rep(i, 0, n){
        a[i] = s1[i] == 'B';
        b[i] = s1[i] == 'A';
    }
    reverse(all(b));
    vd ans = conv(a, b);
    reverse(ans.begin(), ans.begin() + n);
    vi ans1;
    rep(i, 1, n){
        ans1.pb(round(ans[i]));
    }
    return ans1;
}

vi solvefft(string s1){
    int n = s1.length();
    vi a(n), b(n);
    rep(i, 0, n){
        a[i] = s1[i] == 'B';
        b[i] = s1[i] == 'A';
    }
    reverse(all(b));
    int p2 = 1;
    while(p2 < n){
        p2 <<= 1;
    }
    p2 <<= 1;
    a.resize(p2);b.resize(p2);
    vector<cd> a1(all(a)), b1(all(b));
    fft(a1, false);
    fft(b1, false);
    rep(i, 0, p2){
        a1[i] *= b1[i];
    }
    fft(a1, true);
    reverse(a1.begin(), a1.begin() + n);
    vi ans;
    rep(i, 1, n){
        ans.pb(round(real(a1[i])));
    }
    return ans;
}

vi solve(string s1){
    int n = s1.length();
    vi ans(n - 1);
    rep(i, 0, n- 1){
        int i1 = i + 1;
        rep(j, 0, n - i1){
            if(s1[j] == 'B' && s1[j + i1] == 'A') ans[i]++;
        }
    }
    return ans;
}

int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int numtimes = 50;
    rep(i, 0, numtimes){
        string str;
        srand(NULL);
        if(i % (numtimes / 10) == 0) cout << i << nL;
        rep(j, 0, 10000){
            int k = rand() % 2;
            if(k){
                str.pb('A');
            }
            else{
                str.pb('B');
            }
        }   
        // cout << str << nL;
        vi fftans = kactlfft(str);
        vi ans = solve(str);
        bool works = true;
        rep(i, 0, str.length() - 1){
            if(fftans[i] != ans[i]){
                works = false;
            }
        }
        if(!works)cout << str << nL;
    }
    // string str; cin >> str;
    
    
    return 0;
}
