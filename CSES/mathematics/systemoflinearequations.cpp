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

const ll mod = 1000000007; // faster if const

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

int solveLinear(vector<vl>& A, vl& b, vl& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		ll v, bv = 0;
		rep(r,i,n) rep(c,i,m)
			if ((v = abs(A[r][c])) > bv)
				br = r, bc = c, bv = v;
		if (bv == 0) {
			rep(j,i,n) if (abs(b[j]) > 0) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = modpow(A[i][i], mod-2);
		rep(j,i+1,n) {
			ll fac = A[j][i] * bv % mod;
			(b[j] -= fac * b[i]) %= mod;
            (b[j] += mod) %= mod;
			rep(k,i+1,m) {
                (A[j][k] -= fac*A[i][k]) %= mod;
                (A[j][k] += mod) %= mod;
            }
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
        (b[i] *= modpow(A[i][i], mod-2)) %= mod;
		x[col[i]] = b[i];
		rep(j,0,i) {
            (b[j] -= A[j][i] * b[i]) %= mod;
            (b[j] += mod) %= mod;
        }
	}
	return rank; // (multiple solutions if rank < m)
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vl> A(n, vl(m));
    vl b(n);
    rep(i, 0, n) {
        rep(j, 0, m) cin >> A[i][j];
        cin >> b[i];
    }
    vl x(m);
    int rank = solveLinear(A, b, x);
    if(rank == -1){
        cout << "-1\n";
    } else {
        rep(i, 0, m) cout << x[i] << " ";
        cout << "\n";
    }
    
    return 0;
}
