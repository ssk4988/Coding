#include <bits/stdc++.h>
using namespace std;

#pragma GCC target("lzcnt,popcnt")

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
const int B = 95;
using bs = bitset<B>;
const int N = 1e5+10;
bs basismax[B], basismin[B], unusedpos[B], unusedneg[B], in[N];
vi primes;

const ll mod = 998244353;

vi a;

// returns what is leftover, -1 if none leftover
int insert(vi &idx, bs *basis, bs x, int index, bool maximize) {
    for(int j = B-1; j >= 0; j--) {
        if(x[j]) {
            if(idx[j] == -1) {
                basis[j] = x;
                idx[j] = index;
                return -1;
            }
            if((abs(a[idx[j]]) < abs(a[index])) == maximize) {
                swap(index, idx[j]);
                swap(x, basis[j]);
            }
            x ^= basis[j];
        }
    }
    return index;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;

    rep(i, 2, 500) {
        bool prime = true;
        rep(p, 2, i) if(i % p == 0) prime = false;
        if(prime) primes.pb(i);
    }
    // cerr << sz(primes) << "\n";
    vi valmax(B, -1), valmin(B, -1), valp(B, -1), valn(B, -1); // -1 means empty
    a = vi(n);

    auto addunused = [&](int index, bs tmp) -> void {
        bool pos = a[index] > 0;
        if(pos) insert(valp, unusedpos, tmp, index, true);
        else insert(valn, unusedneg, tmp, index, true);
    };
    rep(i, 0, n) {
        cin >> a[i];
        int v = abs(a[i]);
        rep(j, 0, B) {
            while(v % primes[j] == 0) {
                v /= primes[j];
                in[i][j].flip();
            }
        }
        int left = insert(valmax, basismax, in[i], i, true);
        if(left != -1) addunused(left, in[left]);
        // add i to basismin
        insert(valmin, basismin, in[i], i, false);
        int numneg = 0;
        ll ans = 1;
        rep(j, 0, B) {
            if(valmax[j] != -1) {
                if(a[valmax[j]] < 0) numneg++;
                (ans *= a[valmax[j]]) %= mod;
            }
        }
        if(numneg % 2 == 1) {
            // later add augmenting path with not used
            pii best{-1, -1};
            // replace pos in basismax with neg from unusedneg
            rep(use, 0, B) {
                if(valn[use] == -1) continue;
                bs cur = in[valn[use]];
                for(int j = B-1; j >= 0; j--) {
                    if(cur[j] && valmax[j] != -1) {
                        if(a[valmax[j]] > 0) {
                            // cerr << "check " << valn[use] << " " << a[valn[use]] << " " << valmax[j] << " " << a[valmax[j]] << endl;
                            if(best.f == -1 || ll(abs(a[best.f])) * abs(a[valmax[j]]) < ll(abs(a[valn[use]])) * abs(a[best.s])) {
                                best = pii{valn[use], valmax[j]};
                            }
                        }
                        cur ^= basismax[j];
                    }
                }
            }
            // replace neg in basismax with pos from unusedpos
            rep(use, 0, B) {
                if(valp[use] == -1) continue;
                bs cur = in[valp[use]];
                for(int j = B-1; j >= 0; j--) {
                    if(cur[j] && valmax[j] != -1) {
                        if(a[valmax[j]] < 0) {
                            if(best.f == -1 || ll(abs(a[best.f])) * abs(a[valmax[j]]) < ll(abs(a[valp[use]])) * abs(a[best.s])) {
                                best = pii{valp[use], valmax[j]};
                            }
                        }
                        cur ^= basismax[j];
                    }
                }
            }
            if(best.f == -1) {
                ans = 1;
                for(int j = B-1; j >= 0; j--) {
                    if(valmin[j] != -1) (ans *= a[valmin[j]]) %= mod;
                }
            } else {
                ans = 1;
                rep(j, 0, B) {
                    if(valmax[j] != -1) {
                        if(valmax[j] == best.s) {
                            (ans *= a[best.f]) %= mod;
                        } else (ans *= a[valmax[j]]) %= mod;
                    }
                }
                // cerr << "augmenting by replacing " << a[best.s] << " with " << a[best.f] << endl;
            }
        }
        (ans += mod) %= mod;
        cout << ans << "\n";
        // cerr << " i=" << i << " numneg:" << numneg << "\n";
        // cerr << "basismax: ";
        // for(int j = B-1; j >= 0; j--) {
        //     if(valmax[j] != -1) cerr << a[valmax[j]] << "," << primes[j] << " ";
        // }
        // cerr << endl;
        // cerr << "basismin: ";
        // for(int j = B-1; j >= 0; j--) {
        //     if(valmin[j] != -1) cerr << a[valmin[j]] << " ";
        // }
        // cerr << endl;
        // cerr << "unusedpos: ";
        // for(int j = B-1; j >= 0; j--) {
        //     if(valp[j] != -1) cerr << a[valp[j]] << " ";
        // }
        // cerr << endl;
        // cerr << "unusedneg: ";
        // for(int j = B-1; j >= 0; j--) {
        //     if(valn[j] != -1) cerr << a[valn[j]] << " ";
        // }
        // cerr << endl;
    }
    // rep(i, 0, n) {
    //     cerr << "bits of " << i << " " << a[i] << ": ";
    //     rep(j, 0, B) if(in[i][j]) cerr << primes[j] << ",";
    //     cerr << endl;
    // }
    
    
    return 0;
}
