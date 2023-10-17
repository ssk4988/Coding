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

// typedef vector<double> vd;
const double eps = 1e-12;
const int mod = 37; // faster if const

int modpow(int b, int e) {
	int ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

int modinv(int k){
    return modpow(k, mod - 2);
}
int solveLinear(vector<vi>& A, vi& b, vi& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		int v, bv = 0;
		rep(r,i,n) rep(c,i,m)
			if ((v = abs(A[r][c])) > bv)
				br = r, bc = c, bv = v;
		if (bv <= 0) {
			rep(j,i,n) if (abs(b[j]) > 0) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = modinv(A[i][i]);
		rep(j,i+1,n) {
			int fac = (A[j][i] * bv) % mod;
			b[j] = ((b[j] - fac * b[i]) % mod + mod) % mod;
			rep(k,i+1,m) A[j][k] = ((A[j][k] - fac*A[i][k]) % mod + mod) % mod;
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] = (b[i] * modinv(A[i][i])) % mod;
		x[col[i]] = b[i];
		rep(j,0,i) b[j] = ((b[j] - A[j][i] * b[i]) % mod + mod) % mod;
	}
	return rank; // (multiple solutions if rank < m)
}

int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    auto cv = [](char c)->int{
        if(c == ' ') return 36;
        if(c >= 'A' && c <= 'Z') return c - 'A';
        return c - '0' + 26;
    };
    auto rv = [](int v)->char{
        if(v < 26) return 'A' + v;
        if(v < 36) return '0' - 26 + v;
        return ' ';
    };
    int n; cin >> n;
    string m1, m2;
    getline(cin, m1);
    getline(cin, m1);
    getline(cin, m2);
    while(sz(m1) % n) m1.pb(' ');
    while(sz(m2) % n) m2.pb(' ');
    vvi a;
    vi x(n * n), b;
    for(int i = 0; i < sz(m1); i += n){
        rep(j, 0, n){
            int k = i + j;
            b.pb(cv(m2[k]));
            a.pb(vi(n * n));
            rep(l, 0, n){
                // cout << j * n + l << " " << sz(a[k]) << " " << i + l << " " << sz(m1) << nL;
                a[k][j * n + l] = cv(m1[i + l]);
            }
        }
        // cout << i << nL;
    }
    // rep(i, 0, sz(a)){
    //     rep(j, 0, n * n){
    //         cout << a[i][j] << " ";
    //     }
    //     cout << nL;
    // }
    int res = solveLinear(a, b, x);
    if(res == -1){
        cout << "No solution" << nL;
    }
    else if(res < n * n){
        cout << "Too many solutions" << nL;
    }
    else{
        rep(i, 0, n){
            rep(j, 0, n){
                cout << x[i * n + j] << " ";
            }
            cout << nL;
        }
    }
    
    return 0;
}
