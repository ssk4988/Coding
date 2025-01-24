#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vvl = vector<vl>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

const ll mod = 1000000007;
ll det(vvl &a) {
    int n = sz(a); ll ans = 1;
    rep(i, 0, n) {
        rep(j, i+1, n) {
            while(a[j][i] != 0) {
                ll t = a[i][i] / a[j][i];
                if(t) rep(k, i, n)
                    a[i][k] = (a[i][k] - a[j][k] * t) % mod;
                swap(a[i], a[j]);
                ans *= -1;
            }
        }
        ans = ans * a[i][i] % mod;
        if(!ans) return 0;
    }
    return (ans + mod) % mod;
}

ll modpow(ll b, ll e) {
    ll res = 1;
    for(; e > 0; e >>= 1, b = b * b % mod)
        if(e & 1) res = res * b % mod;
    return res;
}

int matInv(vvl &A) {
    int n = sz(A); vi col(n);
    vvl tmp(n, vl(n));
    rep(i, 0, n) tmp[i][i] = 1, col[i] = i;

    rep(i, 0, n) {
        int r = i, c = i;
        rep(j, i, n) rep(k, i, n) if(A[j][k]) {
            r = j; c = k; goto found;
        }
        return i;
found:
        A[i].swap(A[r]); tmp[i].swap(tmp[r]);
        rep(j, 0, n) swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
        swap(col[i], col[c]);
        ll v = modpow(A[i][i], mod-2);
        rep(j, i+1, n) {
            ll f = A[j][i] * v % mod;
            A[j][i] = 0;
            rep(k, i+1, n) A[j][k] = (A[j][k] - f * A[i][k]) % mod;
            rep(k, 0, n) tmp[j][k] = (tmp[j][k] - f * tmp[i][k]) % mod;
        }
        rep(j, i+1, n) A[i][j] = A[i][j] * v % mod;
        rep(j, 0, n) tmp[i][j] = tmp[i][j] * v % mod;
        A[i][i] = 1;
    }

    for(int i = n-1; i > 0; --i) rep(j, 0, i) {
        ll v = A[j][i];
        rep(k, 0, n) tmp[j][k] = (tmp[j][k] - v * tmp[i][k]) % mod;
    }

    rep(i, 0, n) rep(j, 0, n)
        A[col[i]][col[j]] = tmp[i][j] % mod + (tmp[i][j] < 0 ? mod : 0);
    
    return n;
}

int solveLinear(vvl &A, vl &b, vector<optional<ll>> &x) {
    int n = sz(A), m = sz(x), rank = 0, br, bc;
    if(n) assert(sz(A[0]) == m);
    vi col(m); iota(all(col), 0);

    rep(i, 0, n) {
        ll v, bv = 0;
        rep(r, i, n) rep(c, i, m) 
            if((v = abs(A[r][c])) > bv)
                br = r, bc = c, bv = v;
        if(bv == 0) {
            rep(j, i, n) if (b[j] != 0) return -1;
            break;
        }
        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(col[i], col[bc]);
        rep(j, 0, n) swap(A[j][i], A[j][bc]);
        bv = modpow(A[i][i], mod-2);
        rep(j, 0, n) if(j != i) {
            ll fac = A[j][i] * bv % mod;
            (b[j] -= fac * b[i] % mod) %= mod;
            rep(k, i+1, m) (A[j][k] -= fac*A[i][k] % mod) %= mod;
        }
        rank++;
    }

    x.assign(m, nullopt);
    rep(i, 0, rank) {
        rep(j, rank, m) if(abs(A[i][j]) > 0) goto fail;
        x[col[i]] = b[i] * modpow(A[i][i], mod-2) % mod;
    fail:}

    return rank;
}

vl lincomb(vvl A) {
    int n = sz(A);
    auto tmp = A;
    vector<optional<ll>> xx(n);
    vl zero(n);
    solveLinear(tmp, zero, xx);
    // cout << "A: \n";
    // rep(i, 0, n){
    //     rep(j, 0, n) cout << A[i][j] << " ";
    //     cout << "\n";
    // }

    vl x(n);
    int fnd = -1;
    rep(i, 0, n) if(xx[i] == nullopt) {
        // cout << "AT: " << i << endl;
        fnd = i;
        break;
    }
    assert(fnd != -1);
    vvl coef(n, vl(n-1));
    vector<optional<ll>> x1(n-1);
    vl target(n);
    int seen = 0;
    rep(j, 0, n){
        if(j == fnd) {
            rep(i, 0, n) target[i] = A[i][j];
        } else {
            rep(i, 0, n){
                coef[i][seen] = A[i][j];
            }
            seen++;
        }
    }
    // cout << "target: \n";
    // rep(i, 0, n) cout << target[i] << "\n";
    // rep(i, 0, sz(coef)){
    //     rep(j, 0, sz(coef[i])) cout << coef[i][j] << " ";
    //     cout << "\n";
    // }
    solveLinear(coef, target, x1);
    vl res(n-1);
    rep(i, 0, n-1){
        res[i] = *x1[i];
    }
    res.insert(begin(res) + fnd, -1);
    // rep(i, 0, sz(res)){
    //     cout << res[i] << "\n";
    // }
    
    return res;
}

void solve() {
    int n; cin >> n;
    vector A(n, vl(n));
    rep(i, 0, n) rep(j, 0, n) cin >> A[i][j];

    auto inv = A;

    int rank = matInv(inv);
    if(rank <= n-2) {
        rep(i, 0, n) {
            rep(j, 0, n) cout << 0 << ' ';
            cout << '\n';
        }
        return;
    }

    if(rank == n-1) {
        vector<optional<ll>> xx(n);
        vl zero(n);
        auto tmp = A;
        solveLinear(tmp, zero, xx);
        vl collin = lincomb(A);
        vvl A2(A);
        rep(i, 0, n)
            rep(j, 0, n) A2[j][i] = A[i][j];
        vl rowlin = lincomb(A2);

        vector res(n, vl(n));
        rep(i, 0, n) rep(j, 0, n){
            int sgn = (i + j) % 2 ? -1 : 1;
            res[i][j] = rowlin[i] * collin[j] % mod;
            res[i][j] = (res[i][j] * sgn % mod + mod) % mod;
        }
        vvl mat(n-1, vl(n-1));
        int rem_r = -1, rem_c = -1;
        rep(i, 0, n) rep(j, 0, n)
            if(res[i][j] != 0) {
                rem_r = i, rem_c = j;
                break;
            }
        
        if(rem_r == -1)
            goto finished;
        rep(i, 0, n){
            rep(j,0,n){
                if(i == rem_r || j == rem_c) continue;
                mat[i - (i > rem_r)][j - (j > rem_c)] = A[i][j];
            }
        }

        // cout << "cof:\n";
        // rep(i, 0, n) {
        //     rep(j, 0, n) cout << res[i][j] << ' ';
        //     cout << '\n';
        // }

        // cout << "rem: " << rem_r << ' ' << rem_c << '\n';
        // rep(i, 0, n-1) {
        //     rep(j, 0, n-1) cout << mat[i][j] << ' ';
        //     cout << '\n';
        // }

        // cout << "RES: " << endl;
        // rep(i, 0, n) {
        //     rep(j, 0, n) cout << res[i][j] << ' ';
        //     cout << endl;
        // }

        if(rem_r != -1) {
            ll needed = det(mat);
            ll scale = needed * modpow(res[rem_r][rem_c], mod-2) % mod;
            // cout << "SCALE: " << scale << ' ' << modpow(res[rem_r][rem_c], mod-2) << '\n';
            rep(i, 0, n) rep(j, 0, n)
                res[i][j] = res[i][j] * scale % mod;
        }
        finished:
        rep(i, 0, n) {
            rep(j, 0, n) {
                int sgn = (i + j) % 2 ? -1 : 1;
                cout << res[i][j] << " ";
                // cout << (res[i][j] * sgn % mod + mod) % mod << ' ';
            }
            cout << '\n';
        }

        return;
    }

    int d = det(A);
    
    vector Id(n, vl(n));
    rep(i, 0, n) Id[i][i] = d;

    vector res(n, vl(n));
    rep(i, 0, n) rep(j, 0, n) rep(k, 0, n)
        res[i][j] = (res[i][j] + Id[i][k] * inv[k][j] % mod) % mod;

    rep(i, 0, n) {
        rep(j, 0, n) {
            int sgn = (i + j) % 2 ? -1 : 1;
            cout << (res[j][i] * sgn + mod) % mod << ' ';
        }
        cout << '\n';
    }  
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    // int t; cin >> t; while (t--)
    solve();

    return 0;
}