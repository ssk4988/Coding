#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<double>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

// probability of winning d for every number should be equal
// equations: sum of scenarios where choosing i wins = d
// ex: you choose 3, 2 people choose 1, 3 people choose 2, 1 person chooses 4 gives you p_1^2 * p_2^3 * p_4
// p1 + p2 + p3 + ... = 1
// m + 1 equations, m + 1 variables
// jacobian: you could calc it but code already does, just make list of powers of each thing
// time complexity: 100 * (J(m+1) + (m+1)^2 + f(m+1))
// J(m) = m * f(m)
// f(m) = m^m * m
// 100 * (m+1)^2 * (n-1)^(m+1) for m=8 = big???
vd operator*(vector<vd> A, vd b) {
    vd res(sz(A));
    rep(i, 0, sz(A)) {
        rep(j, 0, sz(A[i])) res[i] += A[i][j] * b[j];
    }
    return res;
}

vd operator-(vd a, vd b) {
    vd res(sz(a));
    rep(i, 0, sz(a)) res[i] = a[i] - b[i];
    return res;
}

const double eps = 1e-6;
template<class F, class T>
vector<vector<T>> makeJacobian(F &f, vector<T> &x) {
	int n = sz(x);
	vector<vector<T>> J(n, vector<T>(n));
	vector<T> fX0 = f(x);
	rep(i, 0, n) { 
		x[i] += eps;
		vector<T> fX1 = f(x);
		rep(j, 0, n){
			J[j][i] = (fX1[j] - fX0[j]) / eps;
		}
		x[i] -= eps;
	}
	return J;
}

int matInv(vector<vector<double>>& A) {
	int n = sz(A); vi col(n);
	vector<vector<double>> tmp(n, vector<double>(n));
	rep(i,0,n) tmp[i][i] = 1, col[i] = i;

	rep(i,0,n) {
		int r = i, c = i;
		rep(j,i,n) rep(k,i,n)
			if (fabs(A[j][k]) > fabs(A[r][c]))
				r = j, c = k;
		if (fabs(A[r][c]) < 1e-12) return i;
		A[i].swap(A[r]); tmp[i].swap(tmp[r]);
		rep(j,0,n)
			swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
		swap(col[i], col[c]);
		double v = A[i][i];
		rep(j,i+1,n) {
			double f = A[j][i] / v;
			A[j][i] = 0;
			rep(k,i+1,n) A[j][k] -= f*A[i][k];
			rep(k,0,n) tmp[j][k] -= f*tmp[i][k];
		}
		rep(j,i+1,n) A[i][j] /= v;
		rep(j,0,n) tmp[i][j] /= v;
		A[i][i] = 1;
	}

	/// forget A at this point, just eliminate tmp backward
	for (int i = n-1; i > 0; --i) rep(j,0,i) {
		double v = A[j][i];
		rep(k,0,n) tmp[j][k] -= v*tmp[i][k];
	}

	rep(i,0,n) rep(j,0,n) A[col[i]][col[j]] = tmp[i][j];
	return n;
}

template<class F, class T>
void solveNonlinear(F f, vector<T> &x){
	int n = sz(x);
	rep(iter, 0, 100) {
		vector<vector<T>> J = makeJacobian(f, x);
		matInv(J);
		vector<T> dx = J * f(x);
		x = x - dx;
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vvi> ways(m); // expressions for me = i
    vi fact = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

    auto dfs = [&](vi &f, int me, int start, int left, auto &&dfs) -> void {
        if(left == 0) {
            bool works = true;
            rep(i, 0, me) {
                if (f[i] == 1) works = false;
            }
            if(works){
                vi f1(f);
                int w = fact[n-1];
                rep(i, 0, sz(f)) w /= fact[f[i]];
                f1.pb(w);
                ways[me].pb(f1);
            }
            return;
        }
        rep(i, start, m) {
            if(i == me) continue;
            f[i]++;
            dfs(f, me, i, left-1, dfs);
            f[i]--;
        }
    };
    {
        vi f(m);
        rep(me, 0, m) {
            dfs(f, me, 0, n-1, dfs);
        }
    }
    auto f = [&](vd x) -> vd {
        vd res(sz(x));
        vector<vd> pws(sz(x), vd(10, 1));
        rep(i, 0, sz(pws)){
            rep(j, 1, sz(pws[i])) pws[i][j] = pws[i][j-1] * x[i];
        }
        rep(me, 0, m) {
            for(auto &v : ways[me]) {
                double y = 1;
                rep(i, 0, m) {
                    y *= pws[i][v[i]];
                }
                y *= v.back();
                res[me] += y;
            }
            res[me] -= x.back();
        }
        rep(i, 0, m){
            res.back() += x[i];
        }
        res.back() -= 1;
        return res;
    };
    vd x(m+1);
    solveNonlinear(f, x);
    rep(i, 0, m) {
        cout << fixed << setprecision(8) << x[i] << "\n";
    }

    
    return 0;
}
