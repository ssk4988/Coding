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

const ll mod = 1e9+7;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    const int LIM = 1e6+10;
    vi prime(LIM, 1);
    prime[0] = prime[1] = 0;
    vl sump(LIM), cntp(LIM), p2(LIM);
    for(ll i = 2; i < LIM; i++) {
        sump[i] = sump[i-1];
        cntp[i] = cntp[i-1];
        p2[i] = p2[i-1];
        if(prime[i]) {
            (sump[i] += i) %= mod;
            (cntp[i] += 1) %= mod;
            (p2[i] += i*i) %= mod;
            for(ll j = i*i; j < LIM; j += i) prime[j] = 0;
        } else if(i == 4) {
            (sump[i] += 2) %= mod;
            (cntp[i] += 1) %= mod;
            (p2[i] += 2*2) %= mod;
        }
    }
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        ll ans = (n+2) * sump[n] % mod;
        (ans -= p2[n]) %= mod;
        // (ans += 2*sump[n])%= mod;
        (ans -= (n+1)*cntp[n])%=mod;
        (ans += mod) %= mod;
        cout << ans << "\n";
        ll sm = 0;
        rep(j, 1, n+1){
            // if(!prime[j]) continue;
            rep(i, j, n+1) {
                ll res = 1;
                for(int k = i; k > i-j; k--) res *= k;
                res /= j;
                res %= j;
                // cerr << i << " " << j << " " << res << endl;
                (sm += res) %= mod;
            }
        }
        cout << sm << endl;
    }

    
    return 0;
}
