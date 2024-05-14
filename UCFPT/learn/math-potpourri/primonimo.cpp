#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)


ll modpow(ll b, ll e, ll mod) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

ll modinv(ll k, ll mod){
    return modpow(k, mod-2, mod);
}

int solveLinear(vector<vi>& A, vi& b, vi& x, int mod) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		int v, bv = 0;
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
		bv = modinv(A[i][i], mod);
		rep(j,i+1,n) {
			int fac = A[j][i] * bv;
			b[j] -= fac * b[i];
            b[j] = (b[j] % mod + mod) % mod;
			rep(k,i+1,m) {
                A[j][k] -= fac*A[i][k];
                A[j][k] = (A[j][k] % mod + mod) % mod;
            }
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
        b[i] = (b[i] * modinv(A[i][i], mod)) % mod;
		// b[i] /= A[i][i];
		x[col[i]] = b[i];
		rep(j,0,i) {
            b[j] -= A[j][i] * b[i];
            b[j] = (b[j] % mod + mod) % mod;
        }
	}
	return rank; // (multiple solutions if rank < m)
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, p; cin >> n >> m >> p;
    vvi a(n, vi(m));
    rep(i, 0, n){
        rep(j, 0,m){
            cin >> a[i][j];
        }
    }
    vi B(n * m);
    vi x(n * m);
    vvi A(n * m, vi(n * m));
    rep(i, 0, n){
        rep(j, 0, m){
            B[i * m + j] = (p - a[i][j]) % p;
            rep(i1, 0, n){
                rep(j1, 0, m){
                    if(i1 != i && j1 != j) continue;
                    A[i * m + j][i1 * m + j1] = 1;
                }
            }
        }
    }
    int rank = solveLinear(A, B, x, p);
    if(rank == -1){
        cout << -1 << "\n";
        return 0;
    }
    int k = 0;
    rep(i, 0, sz(x)){
        x[i] = (x[i] % p + p) % p;
        k += x[i];
    }
    cout << k << "\n";
    rep(i, 0, sz(x)){
        rep(j, 0, x[i]){
            cout << (i+1) << " ";
        }
    }
    cout << "\n";


    return 0;
}
