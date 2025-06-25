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
    vi a(n);

    auto addunused = [&](int index, bs tmp) -> void {
        bool pos = a[index] > 0;
        bool placed = false;
        int best = -1;
        bs tmpcpy(tmp);
        for(int j = B-1; j >= 0; j--) {
            if(tmp[j]) {
                if(pos) {
                    if(valp[j] != -1) {
                        tmpcpy ^= unusedpos[j];
                        if(best == -1 || abs(a[valp[best]]) > abs(a[valp[j]])) best = j;
                    } else {
                        unusedpos[j] = tmpcpy;
                        valp[j] = index;
                        placed = true;
                        break;
                    }
                } else {
                    if(valn[j] != -1) {
                        tmpcpy ^= unusedneg[j];
                        if(best == -1 || abs(a[valn[best]]) > abs(a[valn[j]])) best = j;

                    } else {
                        unusedneg[j] = tmpcpy;
                        valn[j] = index;
                        placed = true;
                        break;
                    }
                }
            }
        }
        if(!placed && best != -1 && abs(a[index]) > abs(a[best])) {
            for(int j = B-1; j > best; j--) {
                if(tmp[j]) {
                    if(pos) {
                        if(valp[j] != -1) tmp ^= unusedpos[j];
                    }
                    else {
                        if(valn[j] != -1) tmp ^= unusedneg[j];
                    }
                }
            }
            if(pos) {
                valp[best] = index;
                unusedpos[best] = tmp;
            } else {
                valn[best] = index;
                unusedneg[best] = tmp;
            }
        }
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
        int best = -1; // best guy i can replace, want to replace smallest possible
        bs cur = in[i];
        for(int j = B-1; j >= 0; j--) {
            if(cur[j] && valmax[j] != -1) {
                cur ^= basismax[j];
                if(best == -1 || abs(a[valmax[best]]) > abs(a[valmax[j]])) best = j;
            }
        }
        // cerr << i << " best: " << best << endl;
        if(cur.any()) {
            for(int j = B-1; j >= 0; j--) {
                if(cur[j]) {
                    basismax[j] = cur;
                    valmax[j] = i;
                    break;
                }
            }
        } else if(best != -1) {
            if(abs(a[valmax[best]]) < abs(a[i])) {
                cur = in[i];
                for(int j = B-1; j > best; j--) {
                    if(cur[j] && valmax[j] != -1) {
                        cur ^= basismax[j];
                    }
                }
                int besti = valmax[best];
                bs tmp = in[valmax[best]];
                basismax[best] = cur;
                valmax[best] = i;
                addunused(besti, tmp);
            } else addunused(i, in[i]);
        }
        // add i to basismin
        best = -1; // best guy i can replace, find largest to replace
        cur = in[i];
        for(int j = B-1; j >= 0; j--) {
            if(cur[j] && valmin[j] != -1) {
                cur ^= basismin[j];
                if(best == -1 || abs(a[valmin[best]]) < abs(a[valmin[j]])) best = j;
            }
        }
        if(cur.any()) {
            for(int j = B-1; j >= 0; j--) {
                if(cur[j]) {
                    basismin[j] = cur;
                    valmin[j] = i;
                    break;
                }
            }
        } else if(best != -1 && abs(a[valmin[best]]) > abs(a[i])) {
            cur = in[i];
            for(int j = B-1; j > best; j--) {
                if(cur[j] && valmin[j] != -1) {
                    cur ^= basismin[j];
                }
            }
            valmin[best] = i;
            basismin[best] = cur;
        }
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
            pii augment{-1, -1};
            // replace pos in basismax with neg from unusedneg
            rep(use, 0, B) {
                if(valn[use] == -1) continue;
                cur = in[valn[use]];
                for(int j = B-1; j >= 0; j--) {
                    if(cur[j] && valmax[j] != -1) {
                        if(a[valmax[j]] > 0) {
                            cerr << "check " << valn[use] << " " << a[valn[use]] << " " << valmax[j] << " " << a[valmax[j]] << endl;
                            if(augment.f == -1 || ll(abs(a[augment.f])) * abs(a[valmax[j]]) < ll(abs(a[valn[use]])) * abs(a[augment.s])) {
                                augment = pii{valn[use], valmax[j]};
                            }
                        }
                        cur ^= basismax[j];
                    }
                }
            }
            // replace neg in basismax with pos from unusedpos
            rep(use, 0, B) {
                if(valp[use] == -1) continue;
                cur = in[valp[use]];
                for(int j = B-1; j >= 0; j--) {
                    if(cur[j] && valmax[j] != -1) {
                        if(a[valmax[j]] < 0) {
                            if(augment.f == -1 || ll(abs(a[augment.f])) * abs(a[valmax[j]]) < ll(abs(a[valp[use]])) * abs(a[augment.s])) {
                                augment = pii{valp[use], valmax[j]};
                            }
                        }
                        cur ^= basismax[j];
                    }
                }
            }
            if(augment.f == -1) {
                ans = 1;
                for(int j = B-1; j >= 0; j--) {
                    if(valmin[j] != -1) (ans *= a[valmin[j]]) %= mod;
                }
            } else {
                ans = 1;
                rep(j, 0, B) {
                    if(valmax[j] != -1) {
                        if(valmax[j] == augment.s) {
                            (ans *= a[augment.f]) %= mod;
                        } else (ans *= a[valmax[j]]) %= mod;
                    }
                }
                cerr << "augmenting by replacing " << a[augment.s] << " with " << a[augment.f] << endl;
            }
        }
        (ans += mod) %= mod;
        cout << ans << "\n";
        cerr << " i=" << i << " numneg:" << numneg << "\n";
        cerr << "basismax: ";
        for(int j = B-1; j >= 0; j--) {
            if(valmax[j] != -1) cerr << a[valmax[j]] << "," << primes[j] << " ";
        }
        cerr << endl;
        cerr << "basismin: ";
        for(int j = B-1; j >= 0; j--) {
            if(valmin[j] != -1) cerr << a[valmin[j]] << " ";
        }
        cerr << endl;
        cerr << "unusedpos: ";
        for(int j = B-1; j >= 0; j--) {
            if(valp[j] != -1) cerr << a[valp[j]] << " ";
        }
        cerr << endl;
        cerr << "unusedneg: ";
        for(int j = B-1; j >= 0; j--) {
            if(valn[j] != -1) cerr << a[valn[j]] << " ";
        }
        cerr << endl;
    }
    rep(i, 0, n) {
        cerr << "bits of " << i << " " << a[i] << ": ";
        rep(j, 0, B) if(in[i][j]) cerr << primes[j] << ",";
        cerr << endl;
    }
    
    
    return 0;
}
