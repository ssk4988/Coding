#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

const int mod = 10007, LIM = mod;
int *inv = new int[LIM] - 1;

int solveLinear(vector<vi>& A, vi & b, vi& x) {
    int n = sz(A), m = sz(x), rank = 0, br, bc;
    if(n) assert(sz(A[0]) == m);
    vi col(m); iota(all(col), 0);
    rep(i,0,n) {
        int v, bv = 0;
        rep(r, i, n) rep(c, i, m) 
            if((v = abs(A[r][c])) > bv)
                br = r, bc = c, bv = v;
        if(bv <= 0) {
            rep(j, i, n) if(abs(b[j]) > 0) return -1;
            break;
        }
        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(col[i], col[bc]);
        rep(j,0,n) swap(A[j][i], A[j][bc]);
        bv = inv[A[i][i]];
        rep(j,i+1,n) {
            int fac = A[j][i] * bv % mod;
            (b[j] += mod - fac * b[i] % mod) %= mod;
            rep(k,i+1,m) (A[j][k] += mod - fac * A[i][k] % mod) %= mod;
        }
        rank++;
    }
    x.assign(m, 0);
    for(int i = rank; i--; ) {
        (b[i] *= inv[A[i][i]]) %= mod;
        x[col[i]] = b[i];
        rep(j, 0, i) (b[j] += mod - A[j][i] * b[i] % mod) %= mod;
    }
    return rank;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    inv[1] = 1;
    rep(i,2,LIM) inv[i] = mod-(mod / i) * inv[mod % i] % mod;

    int n, d, w, l; cin >> n >> d >> w >> l;
    vi tp(n);
    rep(i, 0, w) {
        int v; cin >> v; v--;
        tp[v] = 1;
    }
    rep(i, 0, l) {
        int v; cin >> v; v--;
        tp[v] = -1;
    }
    if(w == 0){
        cout << 0 << "\n";
        return 0;
    }
    if(l == 0) {
        cout << 1 << "\n";
        return 0;
    }
    vvi A(n, vi(n));
    vi b(n);
    // cerr << inv[d] << endl;
    rep(i, 0, n) {
        A[i][i] = 1;
        if(tp[i] != 0) {
            b[i] = tp[i] == 1;
            continue;
        }
        rep(roll, 1, d+1) {
            int j = (i+roll) % n;
            A[i][j] = (A[i][j] - inv[d] + mod) % mod;
        }
    }
    // rep(i, 0, n) {
    //     rep(j, 0, n){
    //         cerr << A[i][j] << " ";
    //     }
    //     cerr << " = " << b[i] << endl;
    // }
    vi x(n);
    int rank = solveLinear(A, b, x);
    // cerr << rank << endl;
    assert(rank == n);
    cout << x[0] << "\n";

    return 0;
}