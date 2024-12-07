#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
// using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

typedef vector<double> vd;
const double eps = 1e-12;

bool solveLinear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		double v, bv = 0;
		rep(r,i,n) rep(c,i,m)
			if ((v = fabs(A[r][c])) > bv)
				br = r, bc = c, bv = v;
		if (bv <= eps) {
			rep(j,i,n) if (fabs(b[j]) > eps) assert(false);
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = 1/A[i][i];
		rep(j,0,n) if (j != i) {
			double fac = A[j][i] * bv;
			b[j] -= fac * b[i];
			rep(k,i+1,m) A[j][k] -= fac*A[i][k];
		}
		rank++;
	}

	// x.assign(m, 0);
	// for (int i = rank; i--;) {
	// 	b[i] /= A[i][i];
	// 	x[col[i]] = b[i];
	// 	rep(j,0,i) b[j] -= A[j][i] * b[i];
	// }
    x.assign(m, -1);
    rep(i,0,rank) {
        rep(j,rank,m) if (fabs(A[i][j]) > eps) goto fail;
        x[col[i]] = b[i] / A[i][i];
        return false;
    fail:; }
    return true;
	// return rank; // (multiple solutions if rank < m)
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n; cin >> n;
    string line;
    getline(cin, line);
    map<string, int> rl;
    vector<vd> A;
    rep(i, 0, n){
        getline(cin, line);
        istringstream is(line);
        string tok;
        int eq = false;
        A.pb(vd(sz(rl)));
        int mult = true;
        while(is >> tok) {
            if(tok == "*") {
                mult = true;
                continue;
            }
            if(tok == "/") {
                mult = false;
                continue;
            }
            if(tok == "="){
                eq = true;
                mult = true;
                continue;
            }
            if(tok == "1") continue;
            if(!rl.count(tok)){
                rl[tok] = sz(rl);
                rep(j, 0, sz(A)) A[j].resize(sz(rl));
            }
            // cout << tok << " " << rl[tok] << " " << sz(A) << " " << sz(A.back()) << endl;
            A.back()[rl[tok]] += (eq ^ mult) ? 1 : -1;
        }
    }
    int m = sz(A[0]);
    vd x(m);
    vd res(n);
    // int rank = solveLinear(A, res, x);
    bool valid = solveLinear(A, res, x);
    // rep(i, 0, m) if(x[i] != -1) valid = false;
    cout << (valid ? "valid" : "invalid") << "\n";

    return 0;
}
