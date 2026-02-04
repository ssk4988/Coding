#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

typedef double T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8, inf = 1/.0;
#define MP make_pair
#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j

struct LPSolver {
	int m, n;
	vi N, B;
	vvd D;

	LPSolver(const vvd& A, const vd& b, const vd& c) :
		m(sz(b)), n(sz(c)), N(n+1), B(m), D(m+2, vd(n+2)) {
			rep(i,0,m) rep(j,0,n) D[i][j] = A[i][j];
			rep(i,0,m) { B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i];}
			rep(j,0,n) { N[j] = j; D[m][j] = -c[j]; }
			N[n] = -1; D[m+1][n] = 1;
		}

	void pivot(int r, int s) {
		T *a = D[r].data(), inv = 1 / a[s];
		rep(i,0,m+2) if (i != r && abs(D[i][s]) > eps) {
			T *b = D[i].data(), inv2 = b[s] * inv;
			rep(j,0,n+2) b[j] -= a[j] * inv2;
			b[s] = a[s] * inv2;
		}
		rep(j,0,n+2) if (j != s) D[r][j] *= inv;
		rep(i,0,m+2) if (i != r) D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool simplex(int phase) {
		int x = m + phase - 1;
		for (;;) {
			int s = -1;
			rep(j,0,n+1) if (N[j] != -phase) ltj(D[x]);
			if (D[x][s] >= -eps) return true;
			int r = -1;
			rep(i,0,m) {
				if (D[i][s] <= eps) continue;
				if (r == -1 || MP(D[i][n+1] / D[i][s], B[i])
				             < MP(D[r][n+1] / D[r][s], B[r])) r = i;
			}
			if (r == -1) return false;
			pivot(r, s);
		}
	}

	T solve(vd &x) {
		int r = 0;
		rep(i,1,m) if (D[i][n+1] < D[r][n+1]) r = i;
		if (D[r][n+1] < -eps) {
			pivot(r, n);
			if (!simplex(2) || D[m+1][n+1] < -eps) return -inf;
			rep(i,0,m) if (B[i] == -1) {
				int s = 0;
				rep(j,1,n+1) ltj(D[i]);
				pivot(i, s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		rep(i,0,m) if (B[i] < n) x[B[i]] = D[i][n+1];
		return ok ? D[m][n+1] : inf;
	}
};

double IP_EPS = 1e-6;

struct IPResult {
    bool feasible = false;
    double obj = -1e100;  // very low for maximization
    vd x;
};


void branchAndBound(const vvd &A, const vd &b, const vd &c, IPResult &best, int depth = 0) {
    // Solve LP relaxation
    LPSolver lp(A, b, c);
    vd x;
    double val = lp.solve(x);

    // Infeasible or unbounded
    if (val == inf || val == -inf) return;

    // Bound pruning: if we already have a better integer solution, skip
    if (best.feasible && val <= best.obj + 1e-9) return;

    // Find a fractional variable
    int frac_idx = -1;
    for (int i = 0; i < (int)x.size(); ++i) {
        double xi = x[i];
        double r = round(xi);
        if (fabs(xi - r) > IP_EPS) {
            frac_idx = i;
            break;
        }
    }

    // All variables integral → update best solution
    if (frac_idx == -1) {
        best.feasible = true;
        best.obj = val;
        best.x = x;
        return;
    }

    double xi = x[frac_idx];
    double fl = floor(xi);
    double ce = ceil(xi);

    // Safety: if fl == ce, it's basically integral, but our EPS missed it.
    if (fabs(xi - fl) < IP_EPS) fl = ce = fl;

    // --- Branch 1: x_k <= floor(x_k) ---
    {
        vvd A1 = A;
        vd b1 = b;

        vd newRow1(x.size(), 0.0);
        newRow1[frac_idx] = 1.0;  // x_k <= fl
        A1.push_back(newRow1);
        b1.push_back(fl);

        branchAndBound(A1, b1, c, best, depth + 1);
    }

    // --- Branch 2: x_k >= ceil(x_k) <=> -x_k <= -ceil(x_k) ---
    {
        vvd A2 = A;
        vd b2 = b;

        vd newRow2(x.size(), 0.0);
        newRow2[frac_idx] = -1.0; // -x_k <= -ce
        A2.push_back(newRow2);
        b2.push_back(-ce);

        branchAndBound(A2, b2, c, best, depth + 1);
    }
}


double solve() {
    vector<string> chunks;
    string line;
    getline(cin, line);
    // cout << ">" << line << "<line\n";
    stringstream ss(line);
    string token;
    while(getline(ss, token, ' ')) {
        chunks.push_back(token);
        // cout << ">" << token << "<\n";
    }
    int n = sz(chunks[0])-2;
    int m = sz(chunks)-2;
    auto splitcomma = [](string s) {
        vi res;
        stringstream ss(s);
        string token;
        while(getline(ss, token, ',')) {
            res.push_back(stoi(token));
        }
        return res;
    };
    vvd A(n, vd(m));
    vd b;
    vd c(m, -1);
    rep(i, 0, m) {
        vi but = splitcomma(chunks[i+1].substr(1, sz(chunks[i+1])-2));
        for(int j : but) A[j][i]++;
    }
    vi targ = splitcomma(chunks.back().substr(1, sz(chunks.back())));
    for(int x : targ) b.push_back(x);
    rep(i, 0, n) {
        A.push_back(A[i]);
        b.push_back(b[i]);
        b[n+i] *= -1;
        rep(j, 0, m) {
            A[n+i][j] *= -1;
        }
    }
    for(auto &v : A) {
        for(auto x : v) assert(x == -1 || x == 0 || x == 1);
    }
    for(auto x : b) assert((x-round(x)) <= 1e-8);
    assert(sz(A) == sz(b));
    assert(sz(A[0]) == sz(c));
    IPResult best;
    branchAndBound(A, b, c, best);
    // LPSolver lp(A, b, c);
    // vd x;
    // auto cost = lp.solve(x);
    assert(best.feasible);
    auto cost = best.obj;
    cout << cost << "\n";
    // for(auto y : x) cerr << y << ",";
    // cerr << endl;
    // cout << "done\n";
    return abs(cost);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    string t; getline(cin, t);
    double ans = 0;
    rep(cn, 0, nc) {
        ans += solve();
    }
    cout << ans << "\n";
    // solve();
    
    return 0;
}
