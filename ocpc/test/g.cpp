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
const int B = 168;
using bs = bitset<B>;
const int N = 1e5+10;
bs basismax[B], basismin[B], in[N], usedmax[B], usedmin[B];
vi primes;

const ll mod = 998244353;

vi a;

void insert(vi &idx, bs *basis, bs *used, bs x, int index) {
    bs use;
    for(int j = B-1; j >= 0; j--) {
        if(x[j]) {
            if(idx[j] == -1) {
                basis[j] = x;
                idx[j] = index;
                use[j].flip();
                used[j] = use;
                return;
            }
            x ^= basis[j];
            use ^= used[j];
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;

    rep(i, 2, 1000) {
        bool prime = true;
        rep(p, 2, i) if(i % p == 0) prime = false;
        if(prime) primes.pb(i);
    }
    vi valmax(B, -1), valmin(B, -1), valp(B, -1), valn(B, -1); // -1 means empty
    a = vi(n);

    vii ord;
    rep(i, 0, n) {
        cin >> a[i];
        int v = abs(a[i]);
        rep(j, 0, B) {
            while(v % primes[j] == 0) {
                v /= primes[j];
                in[i][j].flip();
            }
        }
        ord.push_back({abs(a[i]), i});
    }
    sort(all(ord));
    for(auto [_, i] : ord) {
        insert(valmin, basismin, usedmin, in[i], i);
    }
    reverse(all(ord));
    for(auto [_, i] : ord) {
        insert(valmax, basismax, usedmax, in[i], i);
    }
        // add i to basismin
        
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
    // }
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
        rep(use, 0, n) {
            bool used = false;
            rep(j, 0, B) if(valmax[j] == use) used = true;
            if(used) continue;
            bs cur = in[use];
            if(cur.none()) continue;
            bs usedbits;
            for(int j = B-1; j >= 0; j--) {
                if(cur[j] && valmax[j] != -1) {
                    cur ^= basismax[j];
                    usedbits ^= usedmax[j];
                }
            }
            rep(j, 0, B) {
                if(usedbits[j] && (a[valmax[j]] > 0) != (a[use] > 0)) {
                    // cerr << "check " << use << " " << a[use] << " " << valmax[j] << " " << a[valmax[j]] << endl;
                    assert(abs(a[use]) <= abs(a[valmax[j]]));
                    if(best.f == -1 || ll(abs(a[best.f])) * abs(a[valmax[j]]) < ll(abs(a[use])) * abs(a[best.s])) {
                        best = pii{use, valmax[j]};
                    }
                }
            }
        }
        // cerr << best.f << " " << best.s << endl;
        // cerr << a[best.f] << " " << a[best.s] << endl;
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
                    } else
                    (ans *= a[valmax[j]]) %= mod;
                }
            }
            // cerr << "augmenting by replacing " << a[best.s] << " with " << a[best.f] << endl;
        }
    }
    (ans += mod) %= mod;
    cout << ans << "\n";
    // rep(i, 0, n) {
    //     cerr << "bits of " << i << " " << a[i] << ": ";
    //     rep(j, 0, B) if(in[i][j]) cerr << primes[j] << ",";
    //     cerr << endl;
    // }
    
    
    return 0;
}
