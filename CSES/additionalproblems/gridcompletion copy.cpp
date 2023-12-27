#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
// using vd = vector<ld>;
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

typedef vector<double> vd;
const double eps = 1e-12;

int solveLinear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		double v, bv = 0;
		rep(r,i,n) rep(c,i,m)
			if ((v = fabs(A[r][c])) > bv)
				br = r, bc = c, bv = v;
		if (bv <= eps) {
			rep(j,i,n) if (fabs(b[j]) > eps) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = 1/A[i][i];
		rep(j,i+1,n) {
			double fac = A[j][i] * bv;
			b[j] -= fac * b[i];
			rep(k,i+1,m) A[j][k] -= fac*A[i][k];
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] /= A[i][i];
		x[col[i]] = b[i];
		rep(j,0,i) b[j] -= A[j][i] * b[i];
	}
	return rank; // (multiple solutions if rank < m)
}


int n;
int id(int r, int c, int t){
    return r * n * 3 + c * 3 + t;
    // 0 A 1 B 2 null

}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    vector<string> grid(n);
    const int vars = n * n * 3;
    vector<vd> A(0);
    vd x(vars), b(0);
    // exactly 1 for each cell
    rep(i, 0, n){
        rep(j, 0, n){
            A.push_back(vd(vars));
            b.push_back(1);
            rep(k, 0, 3)
                A.back()[id(i, j, k)] = 1;
        }
    }
    rep(i, 0, n){
        rep(k, 0, 2){
            // rows
            A.push_back(vd(vars));
            b.push_back(1);
            rep(j, 0, n){
                A.back()[id(i, j, k)] = 1;
            }
            // cols
            A.push_back(vd(vars));
            b.push_back(1);
            rep(j, 0, n){
                A.back()[id(j, i, k)] = 1;
            }
        }
    }

    rep(i, 0, n){
        cin >> grid[i];
        rep(j, 0, n){
            if(grid[i][j] == 'A'){
                A.push_back(vd(vars));
                A.back()[id(i, j, 0)] = 1;
                b.push_back(1);
            }
            else if(grid[i][j] == 'B'){
                A.push_back(vd(vars));
                A.back()[id(i, j, 1)] = 1;
                b.push_back(1);
            }
        }
    }
    int k = solveLinear(A, b, x);
    cout << vars << " " << k << " " << vars - k << "\n";
    
    return 0;
}
